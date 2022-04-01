//app.h
#ifndef _APP_H_ //如果没有引入头文件app.h
    #define _APP_H_ //那就引入头文件app.h

#include "word.h"

//在这个文件里面将会实现软件的主要功能

//主要单词数据文件
#define MYENGLISH "E:\\Eglishword\\wordall.txt"

//应用数据文件,里面记录了单词分类表等信息
#define MEAPP "E:\\Eglishword\\app.txt"

//日期文件夹，里面记录了今天一天的文件信息，第一个内容就是日期。
#define MTODAY "E:\\Eglishword\\today.txt"

//分类数据文件夹路径，里面是分类的文件的信息
#define DVFOLDER "E:\\Eglishword\\divide.txt"

//获取一个总的文件
//因为是背单词软件，所以总的词汇量应该达到了10000量级
//所以后面应该使用数据库来进行数据读存的管理



//从文件中读取数据
Mwal getdata(FILE* path);

//把单词数组链表（单词单元）中的数据存储到目标文件中
void putdata(FILE* target,Mwal mwal);



/*
命令界面：
主界面：开始使用，帮助，设置
开始使用：添加单词,今日复习，阅览单词，退出
帮助：显示如何使用
设置：设置快捷键，以及删除该程序
删除该程序：删除对应文件，或者保留对应单词文件但是保留exe
阅览单词：阅览分类单词，搜索单词，退出选项
分类单词：按照类型分类，按照日期分类，退出选项
*/








#endif