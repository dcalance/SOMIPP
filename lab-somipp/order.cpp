#include "order.h"

using namespace std;

Order::Order(vector<Food> menu, vector<int> items, int priority)
{
	Order::priority = priority;
	Order::items = items;

	int max_wait = 0;
	for (vector<int>::iterator it = items.begin() ; it != items.end(); ++it)
	{
		if(menu[*it].preparation_time > max_wait)
		{
			max_wait = menu[*it].preparation_time;
		}
	}
	Order::max_wait = max_wait * 1.3;
}