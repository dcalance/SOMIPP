#include "order.h"

using namespace std;

Order::Order(vector<Food> menu, vector<int> items, int priorty)
{
	int max_wait = 0;
	for (vector<int>::iterator it = items.begin() ; it != items.end(); ++it)
	{
		if(menu[*it].preparation_time > max_wait)
		{
			max_wait = menu[*it].preparation_time;
		}
	}
	Order::priority = priority;
	Order::max_wait = max_wait * 1.3;
	Order::items = items;
}