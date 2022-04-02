//word.h
#ifndef _WORD_H_ //如果没有引入头文件word.h
    #define _WORD_H_ //那就引入头文件word.h

#include <stdio.h>
#include <string.h>

#include "mystring\\mystring.h"

//我们的单词
typedef struct myword{
    int kind;   //单词类别，可以没有
    char* word;
    char* meaning;
    char* sentence;  //这一条句子很长，如果读到终点，给出输入的选择还是终止输入
}Word,*Wordp;

//定义单词数组的最大值
#define WORD_ARR_MAX 100

#define WORD_DEFAULT_KIND 0


//单词数组
typedef struct mywordarr{
    Word word_arr[WORD_ARR_MAX];
    int num;    //单词数组中单词的数目
}Mwa,*Mwap;

//单词数组的链表
typedef struct mywordarrlist{
    Mwa mwa;
    struct mywordarrlist* next;
}Mwal,*Mwalp;

//****************单词变量读写复制************************************

//从控制台中读取信息获取我们的单词
Word word_get(void);

/*判断一个单词变量是否是合法的，并返回提示信息,
如果这个单词是合法的，则返回空指针
*/
char* word_iflegal(Word word);

/*从指定文件按照一定格式读取单词信息
如果读取不成功，则返回的结果为空的单词
*/
Word word_read(FILE* path);

//把单词信息写入指定文件，前后没有\n
void word_fput(FILE* path,Word word);

//判断单词变量是否是空的，如果是空的返回1，否则返回0
int word_isempty(Word word);

/*把一个字符串转化为单词信息
如果字符串不合法，则返回的结果为空的单词信息
单词信息可以分为：种类 单词 意思 例句，五点信息使用换行符间隔
*/
Word str_to_word(char* s);


//复制一个单词
Word word_cpy(Word base);

//显示单词信息
void word_show(Word word); 


//**********************单词变量与其他变量的转换与单词变量的删除**********


//把单词变量转化为一个字符串,每个量之间用\n隔开
char* word_tostr(Word word);

//删除单词变量
void word_delete(Word word);


//********************单词数组链表的操作****************************


//单词数组链表可以作为单词管理的一个基本单位

//创建一个单词数组链表
Mwal mwal_cre(void);


/*
查询单词数组链表中的一个单词,通过单词名来搜索
如果这个单词是存在，则返回这个单词的引用(单词指针)
如果这个单词不存在，则返回空指针*/
Wordp mwal_find(Mwalp mwalh,char* word);

/*往单词数组链表中加入一个单词
如果加入成功则返回1
如果单词已经存在，则返回0
*/
int mwal_add(Mwalp mwalh,Word word);

//从单词数组链表中取出指定类型的单词，把他们装入一个单词数组链表返回
Mwal mwal_get_kindpart(Mwalp mwalp,int kind);

//从单词数组链表中获得数组链表中的单词的个数
int mwal_getsize(Mwal mwal);

//清空一个单词数组链表，释放里面所有空间
void mwal_delete(Mwalp mwalp);









#endif