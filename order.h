#pragma once
#include <vector>
#include "food.h"

using namespace std;

class Order
{
public:
	Order(vector<Food> menu, vector<int> items, int priorty);
	vector<int> items;
	int priority;
	float max_wait;
};