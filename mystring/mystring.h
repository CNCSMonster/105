//mystring.h
#ifndef _MYSTRING_H_ //���û������ͷ�ļ�mystring.h
    #define _MYSTRING_H_ //�Ǿ�����ͷ�ļ�mystring.h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//�����������ܵ�ȫ�ֱ���
#define MSTR_CODE 3



//��ȡ�ַ���
//�ӿ���̨��ÿհ��ַ���
char* mystrcre(void); 

/*���ļ���̬��ȡһ���ַ���������\n�����ļ���ֹ��ֹͣ
�����ȡ����Ϊ�գ�����NULL,���򷵻��ַ���ָ��
*/
char* mystr_read(FILE* target); 


//�ַ��������������

//���ַ������ܺ������ָ������,safe_file_put
void mystr_sfput(FILE* target,char* s);

/*�Ѽ��ܵ��ַ�����ָ�������ȡ�����
�����ؽ��ܺ���ַ���
*/
char* mystr_sget(FILE* target);



//������������ת��Ϊ�ַ���
char *inttostr(int num);//��ĳ������ת��Ϊ�ַ���


//��ȡ�ַ�����Ϣ
int mystrlen(char* s);//��ȡ�ַ�������
int mystreq(char* sa, char* sb);//�Ƚ������ַ����Ƿ���ͬ����ͬ����1�����򷵻�0



//�ַ�������
char* mystrcut(char*s ,int st,int end);//�и��ָ�����±��st��end���ַ���
char** mystrdepart(char*s,char t,int* returnNum);//���ַ�tΪ������ַ�������
char* mystradd(char* sa,char* sb);//��sb���ӵ�sa�����γ��µ��ַ��������ͷŵ�sa,����Ŀռ�

char* mystrcpy(char* s);//�����ַ���s����̬����ռ������µ��ַ�������

//���ַ���ת��Ϊ��������

/*�ж�һ���ַ����ܷ�ת��Ϊ����
����ܣ�����1�����򷵻�0
*/
int str_ifint(char* s);

int mystrtoint(char* s);//���ַ���ת��Ϊ����

float mystrtofloat(char* s);//���ַ���ת��ΪС��

char mystrtoc(char* s);//���ַ���ת��Ϊ�ַ�




//�ͷſռ�
void freeStrArr(char** s,int num);//�ͷ��ַ�������Ŀռ�




#endif