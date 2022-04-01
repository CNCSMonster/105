//mystring.h
#ifndef _MYSTRING_H_ //如果没有引入头文件mystring.h
    #define _MYSTRING_H_ //那就引入头文件mystring.h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//定义用来加密的全局变量
#define MSTR_CODE 3



//获取字符串
//从控制台获得空白字符串
char* mystrcre(void); 

/*从文件动态读取一个字符串，遇到\n或者文件终止符停止
如果读取内容为空，返回NULL,否则返回字符串指针
*/
char* mystr_read(FILE* target); 


//字符串加密输入输出

//把字符串加密后输出到指定区域,safe_file_put
void mystr_sfput(FILE* target,char* s);

/*把加密的字符串从指定区域读取后解密
并返回解密后的字符串
*/
char* mystr_sget(FILE* target);



//其他数据类型转化为字符串
char *inttostr(int num);//把某个整数转化为字符串


//获取字符串信息
int mystrlen(char* s);//获取字符串长度
int mystreq(char* sa, char* sb);//比较两个字符串是否相同，相同返回1，否则返回0



//字符串操作
char* mystrcut(char*s ,int st,int end);//切割出指定的下标从st到end的字符串
char** mystrdepart(char*s,char t,int* returnNum);//以字符t为间隔把字符串隔开
char* mystradd(char* sa,char* sb);//把sb连接到sa后面形成新的字符串，并释放掉sa,本身的空间

char* mystrcpy(char* s);//复制字符串s，动态分配空间生成新的字符串返回

//把字符串转化为其他类型

/*判断一个字符串能否转化为整数
如果能，返回1，否则返回0
*/
int str_ifint(char* s);

int mystrtoint(char* s);//把字符串转化为整数

float mystrtofloat(char* s);//把字符串转化为小数

char mystrtoc(char* s);//把字符串转化为字符




//释放空间
void freeStrArr(char** s,int num);//释放字符串数组的空间




#endif