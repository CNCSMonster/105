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










