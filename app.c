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
            word_fput(target,mwa.word_arr[i]);
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
void show_choice(char** sa,char* choice,int len){
    printf("\n");
    for(int i=0;i<len;i++){
        printf("%c.%s\n",choice[i],sa[i]);
    }
}

//获取界面选择,获取choice里面的选择
char get_choice(char* choice,int len){
    printf("input your choice:");
    int t=1;
    do{
        char* s=mystr_read(stdin);
        fflush(stdin);
        int slen=mystrlen(s);
        char jud='y';//jud用来判断正确还是错误
        if(slen!=1){ 
            jud='n';
        }else{
            int i;
            for(i=0;i<len;i++){
                // printf("\n%c,%c",choice[i],s[0]);
                if(s[0]==choice[i]){
                    // printf("get%c",s[0]);
                    break;
                }
            }
            // printf("i:%d",i);
            if(i==len){
                jud='n';
            }
        }
        if(jud=='n'){ //如果输入不正确
            printf("Input Error!Please input again:");
        }else{  //如果输入正确
            char out=s[0];
            free(s);
            return out;
        }
        free(s);
    }while(1);
}

//控制控制台窗口大小,
void console_setsize(int height,int width){
    char s[100];
    sprintf(s,"mode con cols=%d lines=%d",height,width);
    system(s);
}




/*
具体功能实现
*/

//初始化应用信息,并初始化总记录数组
void app_init(void){
    
    //获取数据

    //获取总数据
    FILE* path=myfopen(MYENGLISH,"r");
    if(path==NULL){
        word_total=mwal_cre();
    }else{
        word_total=getdata(path);
        fclose(path);
    }

    //获取今日数据
    //获取今日日期
    char* time=get_time_str();
    //获取
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+6;
    char* today=(char*)malloc(sizeof(char)*len);
    sprintf(today,"%s\\%s.txt",MDAY_CLASSIFY,time);
    free(time);
    path=myfopen(today,"r");
    free(today);
    if(path==NULL){
        //如果今天的文件信息不存在
        word_today=mwal_cre();
    }else{
        //如果今天的文件信息存在
        word_today=getdata(path);
        fclose(path);
    }

    //获取应用信息
    path=myfopen(MAPP,"r");
    if(path==NULL){
        myapp.kind=NULL;
        myapp.kindSize=0;
    }else{
        int kindSize;
        int jud=fscanf(path,"%d",&kindSize);
        if(jud!=1||kindSize<=0){
            myapp.kind=NULL;
            myapp.kindSize=0;
        }else{
            myapp.kindSize=kindSize;
            myapp.kind=(char**)malloc(sizeof(char*)*kindSize);
            for(;kindSize>0;kindSize--){
                char* term=mystr_read(path);
                if(term==NULL){
                    break;
                }else{
                    myapp.kind[myapp.kindSize-kindSize]=term;
                }
            }
            if(kindSize!=0){    //如果读取到的信息有缺,则清空信息
                for(;kindSize<=myapp.kindSize;kindSize++){
                    free(myapp.kind[kindSize]);
                }
                free(myapp.kind);
                myapp.kindSize=0;
                myapp.kind=NULL;
            }
            fclose(path);
        }
    }
}

//应用进程结束后写入文件(并释放所有分配了的空间)
void app_end(void){
    //写文件

    //把app信息写入文件
    FILE* path=myfopen(MAPP,"w");
    if(myapp.kind==NULL){   //如果app信息为空
        fprintf(path,"%d\n",0);
    }else{  //如果app中记录有分类信息
        fprintf(path,"%d\n",myapp.kindSize);
        for(int i=0;i<myapp.kindSize;i++){
            fprintf(path,"%s\n",myapp.kind[i]);
        }
    }
    fclose(path);

    //把今天新录单词写入文件
    //获取今日日期
    char* time=get_time_str();
    //获取
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+2;
    char* today=(char*)malloc(sizeof(char)*len);
    sprintf(today,"%s\\%s.txt",MDAY_CLASSIFY,time);
    free(time);
    path=myfopen(today,"w");
    putdata(path,word_today);
    fclose(path);
    free(today);

    //把总单词信息写入文件
    path=myfopen(MYENGLISH,"w");
    putdata(path,word_total);
    fclose(path);

    //释放空间
    //释放今日数组
    mwal_delete(&word_today);

    //释放总单词数组
    mwal_delete(&word_total);

    //释放应用信息
    for(int i=0;i<myapp.kindSize;i++){
        free(myapp.kind[i]);
    }
    free(myapp.kind);

}

//应用过程中刷新文件信息(把更新的数据写入文件)，采用多线程的方法使用它
void app_flash(void){
    //写文件
    //把app信息写入文件
    FILE* path=myfopen(MAPP,"w");
    if(myapp.kind==NULL){   //如果app信息为空
        fprintf(path,"%d\n",0);
    }else{  //如果app中记录有分类信息
        fprintf(path,"%d\n",myapp.kindSize);
        for(int i=0;i<myapp.kindSize;i++){
            fprintf(path,"%s\n",myapp.kind[i]);
        }
    }
    fclose(path);
    //把今天新录单词写入文件
    //获取今日日期
    char* time=get_time_str();
    //获取
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+2;
    char* today=(char*)malloc(sizeof(char)*len);
    sprintf(today,"%s\\%s.txt",MDAY_CLASSIFY,time);
    free(time);
    path=myfopen(today,"w");
    putdata(path,word_today);
    fclose(path);
    free(today);
    //把总单词信息写入文件
    path=myfopen(MYENGLISH,"w");
    putdata(path,word_total);
    fclose(path);
}



//主界面
void main_choice(void){
    // 主界面：开始使用，帮助，设置,以及退出应用
    char curchoice;
    char* order[4]={
        mystrcpy("开始使用"),
        mystrcpy("帮助"),
        mystrcpy("设置"),
        mystrcpy("退出程序")
    };
    char choice[4]={'0','1','2','e'};
    app_init();
    do{
        system("cls");
        show_choice(order,choice,4);
        curchoice=get_choice(choice,4);
        switch(curchoice){
            case '0':
                system("cls");
                start_choice();
            break;
            case '1':
                system("cls");
                help_choice();
            break;
            case '2':
                system("cls");
                set_choice();
            break;
            default:
                app_end();
            break;
        }
    }while(curchoice!='e');
    //释放空间
    for(int i=0;i<4;i++){
        free(order[i]);
    }
}


//设置界面
void set_choice(void){
    printf("尚未完成\n");
    system("pause");
}

//帮助界面
void help_choice(void){
    printf("尚未完成\n");
    system("pause");
}

//开始使用界面
void start_choice(void){
    // 开始使用：添加单词,今日复习，阅览单词，退出
    //设计命令
    int len=4;
    char* order[len]={
        mystrcpy("添加单词"),
        mystrcpy("今日复习"),
        mystrcpy("阅览单词"),
        mystrcpy("退出")
    };
    char choice[len]={
        '0','1','2','e'
    };
    char curchoice;
    do{
        show_choice(order,choice,len);
        curchoice=get_choice(choice,len);
    }while(curchoice!=choice[3]);
    //释放空间
    for(int i=0;i<len;i++){
        free(order[i]);
    }
}

//添加单词界面，添加的单词默认为无类型,但可以选择类型（但是只加不改）
void mywordadd(void){
    
}

//今日复习界面
void myreview(void){

}

//阅览单词界面:搜索（可以对此操作），分类界面，退出
void view_choice(void){

}

//分类界面,选择分类进行查看，只读不改
void divide_choice(void){

}

//阅览所选择的分类
void divide_show(Mwal show){

}

//导出md文档，所以会检查输入，根据输入的英文文件名，导出一个md文档
void outputmd(void){

}   





