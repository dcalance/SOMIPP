#pragma once

class Item_cook_info
{
public:
	Item_cook_info(int input_cook_id, int input_item_id, int input_parent_id);
	int cook_id;
	int item_id;
	int parent_id;
};