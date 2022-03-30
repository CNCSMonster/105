#include "mystring.h"


char* mystrcre(void){ //获得空白字符串
    char* out=(char *)malloc(sizeof(char));
    out[0]='\0';
    return out;
}


char* mystr_read(FILE* target){//从文件动态读取一个字符串，遇到\n或者文件终止符停止
    char* out;
    struct mstr{    //定义字符链表暂存读取结果
        char c;
        struct mstr* next;
    }ms_h,*ms_t;
    ms_h.next=NULL;
    ms_t=&ms_h;
    int len=0;
    do{
        int cur=fgetc(target);
        if(cur=='\n'||cur==EOF){
            break;
        }else{
            ms_t->next=(struct mstr*)malloc(sizeof(struct mstr));
            ms_t=ms_t->next;
            ms_t->next=NULL;
            ms_t->c=(char)cur;
            len++;
        }
    }while(1);
    out=(char*)malloc(sizeof(char)*(len+1));
    out[len]='\0';
    ms_t=&ms_h;
    for(int i=0;i<len;i++){

    }
    return out;
}

//获取字符串信息
int mystrlen(char* s){//获取字符串长度
    if(s==NULL){    //如果输入的是空指针
        return -1;
    }
    int len=0;
    while(s[len]!='\0'){//没有读到结尾符号就继续读下去，直到读到结尾符号加一再退出
        len++;
    }
    return len; //返回字符串长度
}

int mystrcmp(char* sa, char* sb){//比较两个字符串是否相同，相同返回1，否则返回0
    int la=mystrlen(sa);
    int lb=mystrlen(sb);
    if(la!=lb){//字符串长度不同，则字符串肯定不同
        return 0;
    }else{
        for(int i=0;i<la;i++){
            if(sa[i]!=sb[i]){//循环比较每个对应位字母，若有一个字母不同则字符串不同
                return 0;
            }
        }
    }
    return 1;//经过上述程序还没有退出函数，说明两个字符串没有不同
}



//字符串操作
char* mystrcut(char*s ,int st,int end){//切割出指定的下标从st到end的字符串
    char* out;
    int L=mystrlen(s);
    //先进行输入合法性判断
    if(st>L-1){    //字符串长度为L,则下标最大为L-1
        //如果截取下标的开始都大于字符串的末尾下标
        return mystrcre();//则返回空串
    }else if(end>L-1){//截取的末尾下标超限，则截取超限之前的部分
        return mystrcut(s,st,L-1);
    }else{
        out=(char *)malloc(sizeof(char)*(end-st+2));//从st-end再加上结尾'\0'共需要字符串容量为end-st+2
        out[end-st+1]='\0';
        for(int i=st;i<=end;i++){
            out[i-st]=s[i];
        }
        return out;
    }
}

char** mystrdepart(char*s,char t,int* returnNum){//以字符t为间隔把字符串隔开,返回得到的字符串数组，并通过指针传参的形式返回字符串数组的元素数量
    char **out;//在前面声明要返回的量
    typedef struct strlist{ //定义一个字符串链表，因为不知道分割出来的字符串的数量，所以不用数组，而是使用可以动态加长的链表
        char* s;
        struct strlist* next;
    }Strlist,*Strlistp;
    Strlist stl_h;//定义用来存储分割出来的字符串的紫福春链表的头结点
    stl_h.next=NULL;//初始化首元结点为NULL,表示没有字符串在里面
    Strlistp stl_t=&stl_h;//定义用来遍历链表的链表类型指针
    int num=0;//存储分割的字符串数量
    int st=0;//分割的开始下标
    int len=mystrlen(s);
    for(int i=0;i<len;i++){
        if(s[i]==t){//如果遇到截断符号，则判断之前有没有可以截断的部分，有则截取
            if(st==i){  //说明起点就是截断字符，所以没有可以截断的内容
                st=i+1; //更新起点
                continue;
            }else{
                //如果前面有可以截取的内容则通过stl_t使得stl_h链表末尾生成新的节点，在把stl_t指向链表的新末尾
                stl_t->next=(Strlistp)malloc(sizeof(Strlist));
                stl_t->next->s=mystrcut(s,st,i-1);
                stl_t->next->next=NULL;
                stl_t=stl_t->next;
                num++;  //同时截取到的字符串数量加1
                st=i+1;//同时截取起点指向新的位置
            }
        }
    }
    //经过上述循环可能还有s末尾的部分没有加入链表，
    if(st<len){ //如果循环后截取起点还在字符串s的下标范围内，说明还是可以
        stl_t->next=(Strlistp)malloc(sizeof(Strlist));
        stl_t->next->s=mystrcut(s,st,len-1);
        stl_t->next->next=NULL;
        stl_t=stl_t->next;
        num++;  //同时截取到的字符串数量加1
    }
    *returnNum=num;//把得到的截取的字符串数量通过指针参数传递出去到returnNum指向的int变量中
    out=(char **)malloc(sizeof(char *)*num);//实际上字符串数组相当于一维字符指针的数组，字符串数量为num，所以要给out分配num个char*的空间
    //把字符串链表中的字符串交给字符串数组
    stl_t=&stl_h;
    for(int i=0;i<num;i++){
        out[i]=stl_t->next->s;  //把链表中该结点存的对应字符指针的引用交给字符数组对应位置
        Strlistp term=stl_t->next;//用term暂存该不再用到的链表节点
        stl_t->next=stl_t->next->next;//把该节点从链表中去掉
        free(term); //释放该节点分配的空间
    }
    return out;
}

char* mystradd(char* sa,char* sb){//把sb连接到sa后面形成新的字符串，并释放掉sa本身的空间
    char *out;
    int la=mystrlen(sa);
    int lb=mystrlen(sb);
    out=(char *)malloc(sizeof(char)*(la+lb+1));
    out[la+lb]='\0';//结尾先加字符串结尾标志让out为一个字符
    for(int i=0;i<la;i++){  //先把a的字符赋给out前部分
        out[i]=sa[i];
    }
    for(int i=la;i<la+lb;i++){  //再把b的有效字符赋值给out的后部分
        out[i]=sb[i-la];
    }
    free(sa);
    // free(sb);    //本来也想释放sb的空间的，但是会出错
    return out;
}

char* mystrcpy(char* s){//复制字符串s，动态分配空间生成新的字符串返回
    char* out;
    int len=mystrlen(s);
    out=(char *)malloc(sizeof(char)*(len+1));
    out[len]='\0';
    for(int i=0;i<len;i++){
        out[i]=s[i];
    }
    return out;
}

//把字符串转化为其他类型
int mystrtoint(char* s){//把字符串转化为整数（不考虑负数）
    int out=0;
    int i=0;
    while(s[i]!='\0'){//遍历把每一位加上
        out=out*10+(s[i]-48);
        i++;
    }
    return out;
}

float mystrtofloat(char* s){//把字符串转化为小数(不考虑负数的情况),因为没有特别处理精度不高，所以保留4位小数
    float out=0;
    int i=0;
    int z_w=0;//用来纪录读到了整数部分还是尾数部分
    while(s[i]!='\0'){
        if(s[i]=='.'){
            z_w=1;
        }else if(z_w==0){
            out=out*10+(s[i]-48);
        }else{
            float L=1;
            for(int k=0;k<z_w;k++){
                L/=10;
            }
            out+=((float)(s[i]-48))*L;
            z_w++;//当纪录到了尾数部分的时候z_w用来记录小数点后到了第几位
        }
        i++;
    }
    return ((float)((int)(out*1000)))/1000;     //返回保留3位小数(直接舍去后面，非四舍五入)的结果 
}


char mystrtoc(char* s){//把字符串转化为字符
    return s[0];
}


//释放空间
void freeStrArr(char** s,int num){//释放字符串数组的空间
    for(int i=0;i<num;i++){
        free(s[i]);
    }
    free(s);

}





