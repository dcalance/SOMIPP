#include "random.h"

int generate_random(int range)
{
	unsigned int random = 0;
	int number = 0;
	int err = rand_s(&random);
	if (err != 0)
	{
		printf_s("The rand_s function failed!\n");
	}
	number = random % range;
	return number;
}
