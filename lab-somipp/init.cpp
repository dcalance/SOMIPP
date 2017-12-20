#include "init.h"
#include "global_defines.h"

void init_menu(vector<Food>* menu)
{
	Food item;
	item.name = "pizza"; item.preparation_time = 20 * RELATIVE_TIME; item.complexity = 2; item.cooking_apparatus = "oven";
	menu->push_back(item);
	item.name = "salad"; item.preparation_time = 10 * RELATIVE_TIME; item.complexity = 1; item.cooking_apparatus = "";
	menu->push_back(item);
	item.name = "zeama"; item.preparation_time = 7 * RELATIVE_TIME; item.complexity = 1; item.cooking_apparatus = "stove";
	menu->push_back(item);
	item.name = "Scallop Sashimi with Meyer Lemon Confit"; item.preparation_time = 32 * RELATIVE_TIME; item.complexity = 3; item.cooking_apparatus = "";
	menu->push_back(item);
	item.name = "Island Duck with Mulberry Mustard"; item.preparation_time = 35 * RELATIVE_TIME; item.complexity = 3; item.cooking_apparatus = "oven";
	menu->push_back(item);
	item.name = "Waffles"; item.preparation_time = 10 * RELATIVE_TIME; item.complexity = 1; item.cooking_apparatus = "stove";
	menu->push_back(item);
	item.name = "Aubergine"; item.preparation_time = 20 * RELATIVE_TIME; item.complexity = 2; item.cooking_apparatus = "";
	menu->push_back(item);
	item.name = "Lasagna"; item.preparation_time = 30 * RELATIVE_TIME; item.complexity = 2; item.cooking_apparatus = "oven";
	menu->push_back(item);
}

void init_cooks(vector<Cook>* cooks)
{
	Cook cook;
	cook.id = 0; cook.rank = 3; cook.proficiency = 3; cook.name = "Gordon Ramsay"; cook.catch_phrase = "Where is the lamb sauce";
	cooks->push_back(cook);
	cook.id = 1; cook.rank = 2; cook.proficiency = 3; cook.name = "Chef John"; cook.catch_phrase = "Cayenne";
	cooks->push_back(cook);
}

void init_cooks_conditions(vector<pthread_cond_t>* cook_conditions, int cooks_nr)
{
	for (int i = 0; i < cooks_nr; i += 1)
	{
		cook_conditions->push_back(PTHREAD_COND_INITIALIZER);
	}
}

void init_cooks_locks(vector<pthread_mutex_t>* cook_locks, int cooks_nr)
{
	for (int i = 0; i < cooks_nr; i += 1)
	{
		cook_locks->push_back(PTHREAD_MUTEX_INITIALIZER);
	}
}

void inti_cooks_conditions_int(vector<int>* cook_conditions_int, int cooks_nr)
{
	for (int i = 0; i < cooks_nr; i += 1)
	{
		cook_conditions_int->push_back(0);
	}
}