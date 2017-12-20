#include "main_includes.h"

vector<Food> menu;
vector<Cook> cooks;
vector<Order_in_progress> orders_in_progress;
vector<Item_cook> items_to_be_cooked;

auto cmp = [](Order left, Order right) { return left.priority < right.priority;};
priority_queue<Order, vector<Order>, decltype(cmp)> priority_orders(cmp);

int active_orders = 0;
int cond_signal = 0;

pthread_mutex_t order_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t process_order_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t items_to_be_cooked_lock = PTHREAD_MUTEX_INITIALIZER;
vector<pthread_cond_t> cooks_conditions;
vector<int> cooks_conditions_ints;
vector<pthread_mutex_t> cooks_locks;

void *generate_order(void *ptr)
{
	vector<int> orders_id;

	int number_of_items = generate_random(3);
	if (number_of_items == 0)
		number_of_items += 1;

	for (int i = 0; i < number_of_items; i++)
	{
		orders_id.push_back(generate_random(7));
	}
	Order order(menu, orders_id, generate_random(3));

	pthread_mutex_lock(&order_lock);
	priority_orders.push(order);
	pthread_mutex_unlock(&order_lock);

	return NULL;
}

void *process_orders(void *ptr)
{
	pthread_mutex_lock(&process_order_lock);
	Order_in_progress order;
	milliseconds current_time_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
	order.start_time = current_time_ms.count();
	order.total_items = priority_orders.top().items.size();
	order.is_done = false;
	order.max_time = priority_orders.top().max_wait;

	orders_in_progress.push_back(order);

	for (int i = 0; i < priority_orders.top().items.size(); i += 1)
	{
		Item_cook item;
		item.parent_order_id = orders_in_progress.size() - 1;
		item.item_id = priority_orders.top().items[i];
		
		items_to_be_cooked.push_back(item);
	}
	priority_orders.pop();
	pthread_mutex_unlock(&process_order_lock);
	return NULL;
}

void *cook_thread(void *ptr)
{
	Cook cook_specs = *(Cook*)ptr;
	int currently_cooking_items_nr = 0;

	Working_cook_info cook_info;
	cook_info.cook = cook_specs;
	cook_info.currently_cooking_items = &currently_cooking_items_nr;
	pthread_t thread;

	pthread_create(&thread, NULL, cook_item_finished, (void *)new Working_cook_info(cook_info));

	while (1)
	{
		if (items_to_be_cooked.size() == 0)
		{
			return NULL;
		}

		if (currently_cooking_items_nr < cook_specs.proficiency)
		{
			pthread_mutex_lock(&items_to_be_cooked_lock);
			for (std::vector<Item_cook>::iterator it = items_to_be_cooked.begin(); it != items_to_be_cooked.end(); ++it)
			{
				if (menu[it->item_id].complexity == cook_specs.rank || menu[it->item_id].complexity - 1 == cook_specs.rank)
				{
					
					pthread_t cook_thread;
					pthread_create(&cook_thread, NULL, item_is_cooking_thread, (void *)new Item_cook_info(cook_specs.id, it->item_id, it->parent_order_id));
					it = items_to_be_cooked.erase(it);
					pthread_mutex_lock(&cooks_locks[cook_specs.id]);
					currently_cooking_items_nr += 1;
					pthread_mutex_unlock(&cooks_locks[cook_specs.id]);
					break;
				}
			}
			pthread_mutex_unlock(&items_to_be_cooked_lock);
		}
	}
	return NULL;
}

void *cook_item_finished(void *ptr)
{
	Working_cook_info cook_info = *(Working_cook_info*)ptr;
	while (1)
	{
		pthread_mutex_lock(&cooks_locks[cook_info.cook.id]);
		while(cooks_conditions_ints[cook_info.cook.id] != 1) 
			pthread_cond_wait(&cooks_conditions[cook_info.cook.id], &cooks_locks[cook_info.cook.id]);
		*(cook_info.currently_cooking_items) -= 1;
		cooks_conditions_ints[cook_info.cook.id] = 0;
		pthread_mutex_unlock(&cooks_locks[cook_info.cook.id]);
	}
	return NULL;
}

void *item_is_cooking_thread(void *ptr)
{
	Item_cook_info info = *(Item_cook_info*)ptr;

	Sleep(menu[info.item_id].preparation_time * 100);
	pthread_mutex_lock(&process_order_lock);
	orders_in_progress[info.parent_id].add_item_done();
	pthread_mutex_unlock(&process_order_lock);
	cooks_conditions_ints[info.cook_id] = 1;
	pthread_cond_signal(&cooks_conditions[info.cook_id]);
	return NULL;
}

int main()
{
	init_menu(&menu);
	init_cooks(&cooks);
	init_cooks_conditions(&cooks_conditions, cooks.size());
	init_cooks_locks(&cooks_locks, cooks.size());
	inti_cooks_conditions_int(&cooks_conditions_ints, cooks.size());

	pthread_t generate_orders_threads[MAX_ORDERS];
	int counter = 0;

	while (active_orders < MAX_ORDERS)
	{
		pthread_create(&generate_orders_threads[active_orders], NULL, generate_order, NULL);
		active_orders += 1;
	}
	for (int i = 0; i < active_orders; i += 1)
	{
		pthread_join(generate_orders_threads[i], NULL);
	}

	pthread_t* process_orders_threads = new pthread_t[active_orders];
	while (active_orders > 0)
	{
		pthread_create(&process_orders_threads[counter], NULL, process_orders, NULL);
		active_orders -= 1;
		counter += 1;
	}

	for (int i = 0; i < counter; i += 1)
	{
		pthread_join(process_orders_threads[i], NULL);
	}

	pthread_t* cook_threads = new pthread_t[cooks.size()];
	for (int i = 0; i < cooks.size(); i += 1)
	{
		pthread_create(&cook_threads[i], NULL, cook_thread, new Cook(cooks[i]));
	}

	for (int i = 0; i < cooks.size(); i += 1)
	{
		pthread_join(cook_threads[i], NULL);
	}

	//Sleep(100 * RELATIVE_TIME);
	//for (int i = 0; i < cooks.size(); i += 1)
	//{
	//	pthread_cancel(cook_threads[i]);
	//}

	system("pause");
	return 0;

}
