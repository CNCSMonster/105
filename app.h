//app.h
#ifndef _APP_H_ //如果没有引入头文件app.h
    #define _APP_H_ //那就引入头文件app.h

#include "word.h"
#include "mytime.h"
#include "mystring\\mystring.h"
#include "myrecord\\record.h"


//在这个文件里面将会实现软件的主要功能

typedef struct myappdata{
    char** kind;    //这里面记录已经存在的分类
    int kindSize;   //已经存在的分类的数目
}App,*Appp;


App myapp;  //定义全局变量存储内容信息

Mwal word_total;    //定义全局的存储信息的单词存储单元

Mwal word_today;

//设置一开始打开的控制台窗口大小
#define MAPP_HEIGHT 75
#define MAPP_WIDTH 100

//文件地址使用相对地址

//主要单词数据文件
#define MYENGLISH "Eglish_word\\wordall.txt"

//应用的数据文件,里面记录了单词分类表等设置信息
#define MAPP "Eglish_word\\settings.txt"

//按照日期分类的文件存储的文件夹
#define MDAY_CLASSIFY "Eglish_word\\day_classify"

//我的meaning_classify文件夹
#define MMN_CLASSIFY "Eglish_word\\meaning_classify"


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
阅览分类单词：按照类型分类，按照日期分类，退出选项
某分类阅览：逐单元阅读，能够实现翻页效果，一页出现5个，在下方显示页数然后可以选择翻到下一页或者退出或者上一页
*/

//实现界面

//获取输入光标位置，和移动输入光标到所需位置

//移动输入光标到指定位置
void gotoxy(int x, int y);

//获取输入光标当前的位置
void GetCurrentCursorPosition(int* x,int* y);



//界面显示,显示len条选项
void show_choice(char** sa,char* choice,int len);

//获取界面选择,获取choice里面的选择
char get_choice(char* choice,int len);

//控制控制台窗口大小,
void console_setsize(int height,int width);




/*
具体功能实现
*/

//初始化应用信息,并初始化总
void app_init(void);


//应用进程结束后写入文件
void app_end(void);

//应用过程中刷新文件信息(把更新的数据写入文件)，采用多线程的方法使用它
void app_flash(void);


//主界面
void main_choice(void);


//设置界面
void set_choice(void);

//帮助界面
void help_choice(void);

//开始使用界面
void start_choice(void);

//添加单词界面，添加的单词默认为无类型,但可以选择类型（但是只加不改）
void mywordadd(void);

//今日复习界面
void myreview(void);

//阅览单词界面:搜索（可以对此操作），分类界面，退出
void view_choice(void);

//搜索想找的单词，并且可以对搜索到的单词操作
void view_find(void);

//修改或者删除单词，提供对一个单词的修改,删除
void word_edit(Wordp wordp);


//分类界面,选择分类进行查看，只读不改
void divide_choice(void);

//阅览所选择的分类
void divide_show(Mwal show); 

//导出md文档，所以会检查输入，根据输入的英文文件名，导出一个md文档
void outputmd(void);    

//专门在导出md文档中使用的mdputdata
void md_putdata(FILE* target,Mwal mwal);







#endif