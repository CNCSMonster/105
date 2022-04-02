//word.h
#ifndef _WORD_H_ //���û������ͷ�ļ�word.h
    #define _WORD_H_ //�Ǿ�����ͷ�ļ�word.h

#include <stdio.h>
#include <string.h>

#include "mystring\\mystring.h"

//���ǵĵ���
typedef struct myword{
    int kind;   //������𣬿���û��
    char* word;
    char* meaning;
    char* sentence;  //��һ�����Ӻܳ�����������յ㣬���������ѡ������ֹ����
}Word,*Wordp;

//���嵥����������ֵ
#define WORD_ARR_MAX 100

#define WORD_DEFAULT_KIND 0


//��������
typedef struct mywordarr{
    Word word_arr[WORD_ARR_MAX];
    int num;    //���������е��ʵ���Ŀ
}Mwa,*Mwap;

//�������������
typedef struct mywordarrlist{
    Mwa mwa;
    struct mywordarrlist* next;
}Mwal,*Mwalp;

//****************���ʱ�����д����************************************

//�ӿ���̨�ж�ȡ��Ϣ��ȡ���ǵĵ���
Word word_get(void);

/*�ж�һ�����ʱ����Ƿ��ǺϷ��ģ���������ʾ��Ϣ,
�����������ǺϷ��ģ��򷵻ؿ�ָ��
*/
char* word_iflegal(Word word);

/*��ָ���ļ�����һ����ʽ��ȡ������Ϣ
�����ȡ���ɹ����򷵻صĽ��Ϊ�յĵ���
*/
Word word_read(FILE* path);

//�ѵ�����Ϣд��ָ���ļ���ǰ��û��\n
void word_fput(FILE* path,Word word);

//�жϵ��ʱ����Ƿ��ǿյģ�����ǿյķ���1�����򷵻�0
int word_isempty(Word word);

/*��һ���ַ���ת��Ϊ������Ϣ
����ַ������Ϸ����򷵻صĽ��Ϊ�յĵ�����Ϣ
������Ϣ���Է�Ϊ������ ���� ��˼ ���䣬�����Ϣʹ�û��з����
*/
Word str_to_word(char* s);


//����һ������
Word word_cpy(Word base);

//��ʾ������Ϣ
void word_show(Word word); 


//**********************���ʱ���������������ת���뵥�ʱ�����ɾ��**********


//�ѵ��ʱ���ת��Ϊһ���ַ���,ÿ����֮����\n����
char* word_tostr(Word word);

//ɾ�����ʱ���
void word_delete(Word word);


//********************������������Ĳ���****************************


//�����������������Ϊ���ʹ����һ��������λ

//����һ��������������
Mwal mwal_cre(void);


/*
��ѯ�������������е�һ������,ͨ��������������
�����������Ǵ��ڣ��򷵻�������ʵ�����(����ָ��)
���������ʲ����ڣ��򷵻ؿ�ָ��*/
Wordp mwal_find(Mwalp mwalh,char* word);

/*���������������м���һ������
�������ɹ��򷵻�1
��������Ѿ����ڣ��򷵻�0
*/
int mwal_add(Mwalp mwalh,Word word);

//�ӵ�������������ȡ��ָ�����͵ĵ��ʣ�������װ��һ����������������
Mwal mwal_get_kindpart(Mwalp mwalp,int kind);

//�ӵ������������л�����������еĵ��ʵĸ���
int mwal_getsize(Mwal mwal);

//���һ���������������ͷ��������пռ�
void mwal_delete(Mwalp mwalp);









#endif