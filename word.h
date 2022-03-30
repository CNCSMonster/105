//word.h
#ifndef _WORD_H_ //���û������ͷ�ļ�word.h
    #define _WORD_H_ //�Ǿ�����ͷ�ļ�word.h

#include <stdio.h>
#include <string.h>

#include "mystring\\mystring.h"

//���ǵĵ���
typedef struct myword{
    char* word;
    char* meaning;
    char* sentence;  //��һ�����Ӻܳ�����������յ㣬���������ѡ������ֹ����
}Word,*Wordp;

//�ӿ���̨�ж�ȡ��Ϣ��ȡ���ǵĵ���
Word getWord(void);

//����һ������
Word word_cpy(Word base);

//��ʾ������Ϣ
void word_show(Word word); 

//�ѵ��ʱ���ת��Ϊһ���ַ���
char* word_tostr(Word word);




#endif