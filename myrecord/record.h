//record.h
#ifndef _RECORD_H_ //���û������ͷ�ļ�record.h
    #define _RECORD_H_ //�Ǿ�����ͷ�ļ�record.h

#include <io.h> //�ж��ļ��Ƿ����
#include <direct.h>    //������ɾ�ļ���

#include "..\\mystring\\mystring.h"

//�ҵĴ��ļ���������ļ�����·�������ڵĻ��ͻ��Զ����ɶ�Ӧ·��
FILE* myfopen(char* filename,const char* mode);   

//�ж�һ���ַ����Ƿ��ǺϷ����ļ�·��(δʵ��)
int ispath(char* s);




#endif