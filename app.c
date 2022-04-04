#include "app.h"


//从文件中读取数据
Mwal getdata(FILE* path){
    //读取形式，直接读取。每两个单词之间距离为一个换行符
    Mwal out=mwal_cre();
    int cur;
    while(!feof(path)){//当文件没有读到尽头时
        fscanf(path,"%d.\n",&cur);
        Word term=word_read(path);
        if(word_isempty(term)){
            break;
        }
        mwal_add(&out,term);
        word_delete(term);
        fgetc(path);
    }
    return out;
}

//把单词数组链表（单词单元）中的数据存储到目标文件中
void putdata(FILE* target,Mwal mwal){
    //把文章写入目标文件
    Mwalp term=&mwal;
    int len=0;
    while(term!=NULL){
        Mwa mwa=term->mwa;
        for(int i=0;i<mwa.num;i++){
            fprintf(target,"%d.\n",len+1);
            len++;
            word_fput(target,mwa.word_arr[i]);
            fputs("\n\n",target);
        }
        term=term->next;
    }
}


/*
命令界面：
主界面：开始使用，帮助，设置
开始使用：添加单词,今日复习，阅览单词，导出为md文件，退出
帮助：显示如何使用
设置：设置快捷键，以及删除该程序
删除该程序：删除对应文件，或者保留对应单词文件但是保留exe
阅览单词：阅览分类单词，搜索单词，退出选项
阅览分类单词：按照类型分类，按照日期分类，退出选项
某分类阅览：逐单元阅读，能够实现翻页效果，一页出现5个，在下方显示页数然后可以选择翻到下一页或者退出或者上一页
*/

//实现界面
//界面显示,显示len条选项

void gotoxy(int x, int y)
{    
    COORD c;    
    c.X = x ;    
    c.Y = y ;    
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);    
}



void GetCurrentCursorPosition(int* x,int* y)
{
    // undefined
    HANDLE   hStdout;
    CONSOLE_SCREEN_BUFFER_INFO   pBuffer;
    hStdout   =   GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout,   &pBuffer);
    *x=pBuffer.dwCursorPosition.X;
    *y=pBuffer.dwCursorPosition.Y;
}







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
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+7;
    char today[len];
    sprintf(today,"%s\\%s.txt",MDAY_CLASSIFY,time);
    free(time);
    path=myfopen(today,"r");
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
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+6;
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
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+7;
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
    printf("自定义按键");
    printf("设置工作目录"); 
    system("pause");
}

//帮助界面
void help_choice(void){
    printf("\n根据提示输入命令使用功能");
    printf("\n更新的数据只有在程序使用退出方法退出后才会写入文件");
    printf("\n导出md文档默认导出到程序所在的目录\n");
    system("pause");
}

//开始使用界面
void start_choice(void){
    // 开始使用：添加单词,今日复习，阅览单词，退出
    //设计命令
    int len=5;
    char** order=(char **)malloc(sizeof(char*)*len);
    order[0]=mystrcpy("添加单词");
    order[1]=mystrcpy("今日复习");
    order[2]=mystrcpy("阅览单词");
    order[3]=mystrcpy("导出为md文档");
    order[4]=mystrcpy("退出");
    char choice[5]={'0','1','2','3','e'};
    char curchoice;
    do{
        system("cls");
        show_choice(order,choice,len);
        curchoice=get_choice(choice,len);
        switch(curchoice){
            case '0':
                system("cls");
                mywordadd();
            break;
            case '1':
                system("cls");
                myreview();
            break;
            case '2':
                system("cls");
                view_choice();
            break;
            case '3':
                system("cls");
                outputmd();
            break;
            default:
            break;
        }
    }while(curchoice!=choice[len-1]);
    //释放空间
    for(int i=0;i<len;i++){
        free(order[i]);
    }
    free(order);
}


//添加单词界面，添加的单词默认为无类型,但可以选择类型（但是只加不改）
void mywordadd(void){
    //功能界面
    printf("命令:c--清屏,s--设置,e--退出,其他字母--继续:\n");
    //设置处可以设置该界面风格.
    do{//输入之后可以选择下拉也可以选择刷新界面
        //不去检查非法输入了，只要选择的不是c/s/e就是添加
        printf("your choice:");
        char curord=getch();
        printf("\r");
        for(int i=0;i<30;i++){    //清空当前行，保持界面美观
            printf(" ");
        }
        printf("\r");
        fflush(stdin);
        if(curord=='e'){
            break;
        }else if(curord=='c'){
            system("cls");
            printf("命令:c--清屏,s--设置,e--退出,其他字母--继续:\n");
        }else if(curord=='s'){
            printf("该功能能未实现,按任意键继续");
            getch();
            printf("\r");
            for(int i=0;i<40;i++){
                printf(" ");
            }
            printf("\r");
        }else{  //进行任务
            Word add=word_get();
            char* jud=word_iflegal(add);
            if(jud!=NULL){ //如果输入错误
                printf("输入错误：%s",jud);
                free(jud);
                printf("\n************************************************\n");
            }else{
                int jud=mwal_add(&word_today,add);  //先试探着加入今日单词
                if(jud==0){
                    printf("该单词已被输入\n");
                    printf("\n************************************************\n");
                }else{  //如果该单词可以添加
                    mwal_add(&word_total,add);  //加入总单词
                    printf("添加完成！\n");
                    printf("\n************************************************\n");
                }
            }
            word_delete(add);
        }
    }while(1);

}

//今日复习界面
void myreview(void){
    //功能界面
    //展示今日的单词
    divide_show(word_today);
}

//阅览单词界面:搜索（可以对此操作），分类查看，退出
void view_choice(void){
    //选择界面
    //设计命令
    int len=3;
    char** order=(char **)malloc(sizeof(char*)*len);
    order[0]=mystrcpy("搜索");
    order[1]=mystrcpy("分类查看");
    order[2]=mystrcpy("退出");
    char choice[3]={'0','1','e'};
    char curchoice;
    do{
        show_choice(order,choice,len);
        curchoice=get_choice(choice,len);
        switch(curchoice){
            case '0':
                system("cls");
                view_find();
            break;
            case '1':
                system("cls");
                divide_choice();
            break;
            default:
            break;
        }
    }while(curchoice!=choice[2]);
    //释放空间
    for(int i=0;i<len;i++){
        free(order[i]);
    }
    free(order);
    
}

//搜索想找的单词，并且可以对搜索到的单词操作
void view_find(void){
    //功能界面
    printf("命令提示: e--退出,s--搜索,c--清屏,\n");
    char cur_choice;
    do{
        printf("you choose:");
        cur_choice=getch();
        fflush(stdin);
        printf("\r");
        printf("                   ");
        printf("\r");
        if(cur_choice=='s'){
            printf("输入你想要搜索的单词:");
            char* s=mystr_read(stdin);
            Wordp term=mwal_find(&word_total,s);
            if(term==NULL){ //如果该单词没有输入过
                printf("该单词未输入\n");
                printf("**********************\n");
            }else{      //如果该单词已经输入，进入修改
                word_edit(term);
                printf("**********************\n");
            }
        }else if(cur_choice=='c'){
            system("cls");
            printf("命令提示: e--退出,s--搜索,c--清屏,\n");
        }
    }while(cur_choice!='e');
}

//修改或者删除单词，提供对一个单词的修改,删除
void word_edit(Wordp wordp){
    //对单词的本身和意思和它的存在都可以进行修改
    //可以把它完全改成令一个单词
    Word cpy=word_cpy(*wordp);  //复制原单词
    char cur_choice;
    printf("按键命令:e--退出修改,d--删除这个单词，其他--继续修改\n");
    cur_choice==getch();
    if(cur_choice=='e'){
        word_delete(cpy);
        return;
    }else if(cur_choice=='d')
        word_delete(cpy);
        //从总单词库中和今日单词中都删除这个单词
        
    }
    do{
        system("cls");
        printf("当前该单词信息：\n");
        word_show(cpy);
        printf("更改为:");
        Word cc=word_read(stdin);
        if(mwal_find(&word_total,cc.word)==NULL||mystreq(cc.word,cpy.word)){
            //如果修改后不添加重复的单词信息。则修改可能合法
            word_delete(*wordp);
            *wordp=word_cpy(cc);
            Wordp tt=mwal_find(&word_today,cpy.word);
            if(tt!=NULL){   //如果今日数组里面也有这个单词，则这个单词也要修改
                word_delete(*tt);
                *tt=word_cpy(cc);
            }
            word_delete(cpy);
            cpy=word_cpy(cc);
            printf("修改成功!\n");
        }else{
            //修改不合法
            printf("修改后库中会有两个%s,修改无效！\n",cc.word);
            word_delete(cc);
        }
        printf("按键命令:e--退出修改,d--删除这个单词，其他--继续修改\n");
        cur_choice=getch();
        fflush(stdin);
        if(cur_choice=='e'){
            break;
        }
    }while(1);
    word_delete(cpy);
}

//分类界面,选择分类进行查看，只读不改
void divide_choice(void){

    //设计命令
    if(myapp.kindSize==0){
        //如果所有单词都没有分类的话，被归于默认分类
        printf("所有单词均未分类，该功能无法使用。");
        fflush(stdin);
        printf("请按任意键继续");
        getch();
        return ;
    }
    int len=myapp.kindSize+1;
    char** order=(char**)malloc(sizeof(char*)*len); //后面需要释放空间
    char choice[len];
    for(int i=0;i<len-1;i++){
        order[i]=myapp.kind[i]; //因为这里用来显示命令的是引用，而没有新分配空间，所以函数中无需释放
        choice[i]=i+48;        //不考虑分类超过10个的情况，这里把分类转为对应字符
    }
    choice[len]='e';

    //定义暂存的单词基本存储单元链表，避免多次重复加载
    typedef struct curwordbase{
        Mwalp mwalp;
        int kind;
        struct curwordbase* next;
    }Cw,*Cwp;
    Cw cw_h;    //定义头结点，该节点用来保存访问起点，不存储数据
    cw_h.next=NULL; //初始时首元节点为0，表示没有保存任何分类的单元链表
    Cwp cw_t=&cw_h;
    char curchoice;
    do{
        show_choice(order,choice,len);
        printf("\n请输入你要选择查看的分类或者退出\n");
        curchoice=get_choice(choice,len);
        if(curchoice=='e'){
            break;
        }else{
            system("cls");
            //获取自己需要的分类，进行查看
            //首先获得的分类，获得的选择转化为整数
            int thischoice=curchoice-48;
            //先查找已经加载了的分类数据中是否存在所选类型的分类存储
            Mwalp cur_mwalp;    //当前的单词数组链表单元
            cw_t=&cw_h;
            while(cw_t->next!=NULL){
                if(cw_t->next->kind==thischoice){
                    //如果自己选择的分类数据已经存在
                    cur_mwalp=cw_t->next->mwalp;
                }
                cw_t=cw_t->next;
            }
            if(cw_t->next==NULL){
                //如果自己选择的分类数据未加载
                //则获得自己想要的分类
                cw_t->next=(Cwp)malloc(sizeof(Cw));
                cw_t=cw_t->next;
                cw_t->next=NULL;
                Mwal mwal_t=mwal_get_kindpart(&word_total,thischoice);
                cw_t->mwalp=&mwal_t;
                cw_t->kind=thischoice;
                cur_mwalp=cw_t->mwalp;
            }
            //然后展示阅览界面
            system("cls");
            divide_show(*cur_mwalp);
        }
    }while(curchoice!=choice[len-1]);
    free(order);
    //释放使用的单词存储单元链表的空间
    while(cw_h.next!=NULL){
        cw_t=cw_h.next;
        cw_h.next=cw_h.next->next;
        mwal_delete(cw_t->mwalp);
        free(cw_t);
    }

}




//阅览所选择的分类
void divide_show(Mwal show){
    //功能界面
    //展示自己输入的单词
    int max=4;  //一页显示的单词的最大数量
    int total=mwal_getsize(show);  //用来记录总的单词数,则总的单词页数为
    if(total==0){
        printf("该列表为空。");
        printf("\n请按任意键继续");
        getch();
        return ;
    }
    int totalpage=total%max==0?(total/max):(total/max+1);
    /*
    则总页数为：total%max==0?total/max:total/max+1
    */
    int cur_page=0; //记录当前页数,下标从0-totalpage-1
    Mwalp cur_mwalp=&show;  //记录当前单词数组链表的当前显示结点
    int cur_index=0;    //记录当前单词数组链表的当前显示结点下标
    char cur_choice;  //记录当前获取的选项
    do{
        //展示当前页面的单词
        system("cls");
        Mwalp cur_show=cur_mwalp;
        int index_show=cur_index;
        for(int i=0;i<max;i++){
            printf("\n*********************************\n");
            word_show(cur_show->mwa.word_arr[index_show]);
            index_show++;
            if(index_show==WORD_ARR_MAX){   //如果当前的数组结点读取到头了
                if(cur_show->next!=NULL){    //如果下一级还有数组结点
                    cur_show=cur_show->next;
                    index_show=0;
                }else{  //否则结束循环
                    break;
                }
            }else if(index_show>=cur_show->mwa.num){
                break;
            }
        }
        printf("\n当前页数/总页数:%d/%d",cur_page+1,totalpage);
        printf("\n往前/往后翻页/退出查看:a/d/e");
        cur_choice=getch();
        if(cur_choice=='e'){
            break;
        }else{      //不达成循环效果，达到下(上)边界后就不能够减(增)
            switch(cur_choice){
                case 'a':   //往前翻页
                    if(cur_page>=0){
                        cur_page--;
                        cur_index-=max;
                        if(cur_index<0){
                            Mwalp ttt=&show;
                            while(ttt->next!=cur_mwalp){
                                ttt=ttt->next;
                            }
                            cur_mwalp=ttt;
                            cur_index=(cur_index+WORD_ARR_MAX)%WORD_ARR_MAX;
                        }
                    }
                break;
                case 'd':   //往后翻页
                    if(cur_page<totalpage-1){ //如果还能够往后翻页
                        cur_page++;
                        cur_index+=max;
                        if(cur_index>=WORD_ARR_MAX){
                            cur_index=cur_index%WORD_ARR_MAX;
                            cur_mwalp=cur_mwalp->next;
                        }
                    }
                break;
                default:
                break;
            }
        }
    }while(cur_choice!='e');
}

//导出md文档，所以会检查输入，根据输入的英文文件名，导出一个md文档
void outputmd(void){
    //加入开始使用之中
    //功能界面
    //选项：导出位置设置(默认为当前位置,也就是exe所在位置)，导出
    //导出会把自己记载的单词分类导出到各个位置，并且命名为自己命名的位置
    //输入文件名字(先实现这个功能)
    printf("\n请输入想要保存为的文件名字(纯粹英文):");
    char* name=mystr_read(stdin);
    while(!mystr_if_e(name)){
        free(name);
        printf("输入不符合规范，请重新输入：");
        name=mystr_read(stdin);
    }
    //首先打开对应的文件
    char path[strlen(name)+5];
    sprintf(path,"%s.md",name);
    free(name);
    FILE* mf=fopen(path,"w");   //使用相对路径
    fprintf(mf,"# My English Word Book\n\n");    //写入大标题
    fprintf(mf,"[TOC]\n\n");     //写入目录
    fprintf(mf,"## A. total words\n\n");    //写入次级标题
    md_putdata(mf,word_total);
    fprintf(mf,"\n\n## B. division");
    for(int i=0;i<myapp.kindSize;i++){  
        fprintf(mf,"\n\n### %d. %s",i+1,myapp.kind[i]);
        Mwal term=mwal_get_kindpart(&word_total,i);
        md_putdata(mf,term);
        mwal_delete(&term);
    }
    fclose(mf);
    printf("导出成功！");
    printf("请按任意键继续！");
    getch();
}   

//专门在导出md文档中使用的mdputdata
void md_putdata(FILE* target,Mwal mwal){
    Mwalp term=&mwal;
    int len=0;
    int len_total=mwal_getsize(mwal);   //计算mwal的单词数量
    //通过单词数量判断要几级标题，考虑到单词数量在10000左右，所以标题控制在2级(百，千)
    int level_num;  //小标题的级别数量
    //如果不超过2000个单词，采用1级标题，a,b,c,d
    //如果超过两千个单词，采用2级别，A每1000，a每100
    if(len_total<=10*WORD_ARR_MAX){
        level_num=1;
    }else{
        level_num=2;
    }
    int low=0;  //标记小标题
    int top=0;  //标记大标题
    //每一百个单词分一个部分
    while(term!=NULL){
        Mwa mwa=term->mwa;
        //先打标题
        if(level_num==1){   //如果只有一级
            fprintf(target,"### (%c)\n",low+97);
            low++;
        }else{  //如果有两级
            if(low%10==0){  //打印大标题
                fprintf(target,"### (%c)\n",top+65);
                top++;
            }
            fprintf(target,"#### (%c).\n",low%10+97);
        }
        for(int i=0;i<mwa.num;i++){
            fprintf(target,"%d.\n",len+1);
            len++;
            Word ttt=mwa.word_arr[i];
            fprintf(target,"%s\n%s\n%s\n",ttt.word,ttt.meaning,ttt.sentence);
            fputs("\n\n",target);
        }
        term=term->next;
    }
}



