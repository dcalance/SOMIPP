#pragma once
#include <chrono>
using namespace std::chrono;

class Order_in_progress
{
	int items_done = 0;
public:
	int start_time = 0;
	int end_time = 0;
	int total_items = 0;
	int max_time = 0;
	bool is_done = false;
	void add_item_done();
};