#include "item_cook_info.h"

Item_cook_info::Item_cook_info(int input_cook_id, int input_item_id, int input_parent_id)
{
	Item_cook_info::cook_id = input_cook_id;
	Item_cook_info::item_id = input_item_id;
	Item_cook_info::parent_id = input_parent_id;
}