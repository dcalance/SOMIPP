#pragma once

struct timespec { long tv_sec; long tv_nsec; };   //header part
#define exp7           10000000i64     //1E+7     //C-file part
#define exp9         1000000000i64     //1E+9
#define w2ux 116444736000000000i64     //1.jan1601 to 1.jan1970

void unix_time(struct timespec *spec);
int clock_gettime(int, timespec *spec);