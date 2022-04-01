#include "app.h"


//从文件中读取数据
Mwal getdata(FILE* path){
    //读取形式，直接读取。每两个单词之间距离为一个换行符
    Mwal out=mwal_cre();
    while(!feof(path)){//当文件没有读到尽头时
        Word term=word_read(path);
        if(word_isempty(term)){
            break;
        }
        mwal_add(&out,term);
        word_delete(term);
    }
    return out;
}

//把单词数组链表（单词单元）中的数据存储到目标文件中
void putdata(FILE* target,Mwal mwal){
    //把文章写入目标文件
    Mwalp term=&mwal;
    while(term!=NULL){
        Mwa mwa=term->mwa;
        for(int i=0;i<mwa.num;i++){
            word_fput(terget,mwa.word_arr[i]);
            fputc('\n',target);
        }
        term=term->next;
    }
}


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
//界面显示,显示len条选项
void show_choice(char** sa,int len);

//获取界面选择,获取choice里面的选择
char get_choice(char* choice,int len);

//控制控制台窗口大小,
void console_setsize(int height,int width);




/*
具体功能实现
*/

//初始化应用信息,并初始化总
void app_init(void);


//主界面
void main_choice(void);

//退出主界面,退出主界面的时候才会把一切写入文件之中
void main_exit(void);

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

//分类界面,选择分类进行查看，只读不改
void divide_choice(void);

//阅览所选择的分类
void divide_show(Mwal show); 

//导出md文档，所以会检查输入，根据输入的英文文件名，导出一个md文档
void outputmd(void);    