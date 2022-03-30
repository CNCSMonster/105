//word.h
#ifndef _WORD_H_ //如果没有引入头文件word.h
    #define _WORD_H_ //那就引入头文件word.h

#include <stdio.h>
#include <string.h>

#include "mystring\\mystring.h"

//我们的单词
typedef struct myword{
    char* word;
    char* meaning;
    char* sentence;  //这一条句子很长，如果读到终点，给出输入的选择还是终止输入
}Word,*Wordp;

//从控制台中读取信息获取我们的单词
Word getWord(void);

//复制一个单词
Word word_cpy(Word base);

//显示单词信息
void word_show(Word word); 

//把单词变量转化为一个字符串
char* word_tostr(Word word);




#endif