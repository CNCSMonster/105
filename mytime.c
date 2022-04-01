#include "mytime.h"


//获得当天日期
void gettime(int* year,int* month,int* day){
    time_t timep;   //实际上这相当于一个双精度实型
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);
    *year=p->tm_year+1900;  //因为年份从1900开始算
    *month=p->tm_mon+1;   //因为月份是从0-11
    *day=p->tm_mday;    
}










