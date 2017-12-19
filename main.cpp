#include "main_includes.h"

vector<Food> menu;
vector<Cook> cooks;
vector<Order> orders;
auto cmp = [](Order left, Order right) { return left.priority < right.priority;};
priority_queue<Order, vector<Order>, decltype(cmp)> priority_orders(cmp);

pthread_mutex_t order_lock = PTHREAD_MUTEX_INITIALIZER;

void *generate_order(void *ptr)
{
	vector<int> orders_id;
	int number_of_items = rand() % 3;
	if (number_of_items == 0)
		number_of_items += 1;

	for (int i = 0; i < number_of_items; i++)
	{
		orders_id.push_back(rand() % 7);
	}
	Order order(menu, orders_id, rand() % 3);

	pthread_mutex_lock(&order_lock);
	orders.push_back(order);
	pthread_mutex_unlock(&order_lock);
	return NULL;
}

int main()
{
	pthread_t threads[5];
	srand (time(NULL));

	init_menu(&menu);
	init_cooks(&cooks);

	cout << menu.size() << " " << cooks.size() << endl;

	for(int i = 0; i < 5; i += 1)
	{
		pthread_create( &threads[i], NULL, generate_order, NULL);
		pthread_join(threads[i], NULL);
	}

	for(int i = 0; i < 5; i += 1)
	{
		cout << orders[i].max_wait << "  " <<orders[i].items.size() << endl;
	}
	return 0;

}
