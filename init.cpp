#include "init.h"

void init_menu(vector<Food>* menu)
{
	Food item;
	item.name = "pizza"; item.preparation_time = 20; item.complexity = 2; item.cooking_apparatus = "oven";
	menu->push_back(item);
	item.name = "salad"; item.preparation_time = 10; item.complexity = 1; item.cooking_apparatus = "";
	menu->push_back(item);
	item.name = "zeama"; item.preparation_time = 7; item.complexity = 1; item.cooking_apparatus = "stove";
	menu->push_back(item);
	item.name = "Scallop Sashimi with Meyer Lemon Confit"; item.preparation_time = 32; item.complexity = 3; item.cooking_apparatus = "";
	menu->push_back(item);
	item.name = "Island Duck with Mulberry Mustard"; item.preparation_time = 35; item.complexity = 3; item.cooking_apparatus = "oven";
	menu->push_back(item);
	item.name = "Waffles"; item.preparation_time = 10; item.complexity = 1; item.cooking_apparatus = "stove";
	menu->push_back(item);
	item.name = "Aubergine"; item.preparation_time = 20; item.complexity = 2; item.cooking_apparatus = "";
	menu->push_back(item);
	item.name = "Lasagna"; item.preparation_time = 30; item.complexity = 2; item.cooking_apparatus = "oven";
	menu->push_back(item);
}

void init_cooks(vector<Cook>* cooks)
{
	Cook cook;
	cook.rank = 3; cook.proficiency = 3; cook.name = "Gordon Ramsay"; cook.catch_phrase = "Where is the lamb sauce";
	cooks->push_back(cook);
	cook.rank = 2; cook.proficiency = 3; cook.name = "Chef John"; cook.catch_phrase = "Cayenne";
	cooks->push_back(cook);
}