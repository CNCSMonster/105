//mytime.h
#ifndef _MYTIME_H_ //如果没有引入头文件mytime.h
    #define _MYTIME_H_ //那就引入头文件mytime.h

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//获得当天日期
void gettime(int* year,int* month,int* day);

/*
获得表示当天日期的字符串，格式为：20xx/(x)x/(x)x,
也就是年/月/日，*/
char* get_time_str(void);


#endif