#include "order_in_progress.h"

void Order_in_progress::add_item_done()
{
	Order_in_progress::items_done += 1;
	if (Order_in_progress::items_done == total_items)
	{
		Order_in_progress::is_done = true;
		milliseconds current_time_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		Order_in_progress::end_time = current_time_ms.count();
	}
}