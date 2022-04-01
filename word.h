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

//�ӿ���̨�ж�ȡ��Ϣ��ȡ���ǵĵ���
Word word_get(void);

/*��ָ���ļ�����һ����ʽ��ȡ������Ϣ
�����ȡ���ɹ����򷵻صĽ��Ϊ�յĵ���
*/
Word word_read(FILE* path);


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

//�ѵ��ʱ���ת��Ϊһ���ַ���,ÿ����֮����\n����
char* word_tostr(Word word);

//ɾ�����ʱ���
void word_delete(Word word);


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


//���һ���������������ͷ��������пռ�
void mwal_delete(Mwalp mwalp);









#endif