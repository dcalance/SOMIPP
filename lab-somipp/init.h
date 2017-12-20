#pragma once
#include "food.h"
#include "cook.h"
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <vector>

using namespace std;

void init_menu(vector<Food>* menu);
void init_cooks(vector<Cook>* cooks);
void init_cooks_conditions(vector<pthread_cond_t>* cook_conditions, int cooks_nr);
void init_cooks_locks(vector<pthread_mutex_t>* cook_locks, int cooks_nr);
void inti_cooks_conditions_int(vector<int>* cook_conditions_int, int cooks_nr);