//mytime.h
#ifndef _MYTIME_H_ //���û������ͷ�ļ�mytime.h
    #define _MYTIME_H_ //�Ǿ�����ͷ�ļ�mytime.h

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//��õ�������
void gettime(int* year,int* month,int* day);

/*
��ñ�ʾ�������ڵ��ַ�������ʽΪ��20xx/(x)x/(x)x,
Ҳ������/��/�գ�*/
char* get_time_str(void);


#endif