#include "mytime.h"


//��õ�������
void gettime(int* year,int* month,int* day){
    time_t timep;   //ʵ�������൱��һ��˫����ʵ��
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);
    *year=p->tm_year+1900;  //��Ϊ��ݴ�1900��ʼ��
    *month=p->tm_mon+1;   //��Ϊ�·��Ǵ�0-11
    *day=p->tm_mday;    
}

/*
��ñ�ʾ�������ڵ��ַ�������ʽΪ��20xx_(x)x_(x)x,
Ҳ������_��_�գ�*/
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









