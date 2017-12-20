#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <stdio.h>
#include <vector>
#include "food.h"
#include "cook.h"
#include "order.h"
#include "init.h"
#include <iostream>
#include "time.h"
#include "stdlib.h"
#include <queue>
#include <windows.h>
#include <time.h>
#include "random.h"
#include <chrono>
#include "global_defines.h"
#include "order_in_progress.h"
#include "item_cook.h"
#include "working_cook_info.h"
#include "item_cook_info.h"
using namespace std;
using namespace std::chrono;

void *generate_order(void *ptr);
void *process_orders(void *ptr);
void *cook_thread(void *ptr);
void *cook_item_finished(void *ptr);
void *item_is_cooking_thread(void *ptr);
