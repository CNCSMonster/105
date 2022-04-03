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

/*
获得表示当天日期的字符串，格式为：20xx_(x)x_(x)x,
也就是年_月_日，*/
char* get_time_str(void){
    char* out;
    int year;
    int mon;
    int day;
    gettime(&year,&mon,&day);
    char* ys=inttostr(year);
    char* ms=inttostr(mon);
    char* ds=inttostr(day);
    int len=strlen(ys)+strlen(ms)+strlen(ds)+2;
    out=(char*)malloc(sizeof(char)*(len+1));
    sprintf(out,"%s_%s_%s",ys,ms,ds);
    free(ys);
    free(ms);
    free(ds);
    return out;
}









