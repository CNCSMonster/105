#include "word.h"




/*从控制台中读取信息获取我们的单词
单词的类型不由我们指定，而是外界维护一个映射得到
所以并不是输入得到
*/
Word word_get(void){
    Word out;
    out.kind=0;
    printf("Word:\t");
    out.word=mystr_read(stdin);
    printf("meaning:\t");
    out.meaning=mystr_read(stdin);
    printf("sentence:\t");
    out.sentence=mystr_read(stdin);
    return out;
}

/*从指定文件按照一定格式读取单词信息
如果读取不成功，则返回的结果为空的单词
*/
Word word_read(FILE* path){
    Word out;
    out.meaning=NULL;
    out.word=NULL;
    out.sentence=NULL;
    out.kind=-1;    //-1表示默认的无分类信息
    int jud=fscanf(path,"%d\n",&(out.kind));
    if(jud!=1){
        return out;
    }
    out.word=mystr_read(path);
    if(out.word==NULL){
        return out;
    }
    out.meaning=mystr_read(path);
    if(out.meaning==NULL){
        free(out.word);
    }
    out.sentence=mystr_read(path);
    if(out.sentence==NULL){
        free(out.word);
        free(out.meaning);
        return out;
    }
    return out;
}

//把单词信息写入指定文件，前后没有\n
void word_fput(FILE* path,Word word){
    if(word_isempty(word)){
        return;
    }else{
        fprintf(path,"%d\n%s\n%s\n%s",word.kind,word.word,word.meaning,word.sentence);
    }
}

//判断单词变量是否是空的
int word_isempty(Word word){
    if(word.meaning==NULL){
        return 1;
    }else{
        return 0;
    }
}

/*把一个字符串转化为单词信息
如果字符串不合法，则返回的结果为空的单词信息
单词的各项信息之间用\n分割
结构如右：kind\nword\nmeaning\nsentence
类型\n单词本身\n单词意思\n单词例句
*/
Word str_to_word(char* s){
    Word out;
    if(s==NULL){
        out.meaning=NULL;
        out.sentence=NULL;
        out.word=NULL;
    }else{
        int num;
        char** sa=mystrdepart(s,'\\',&num);
        if(num!=4){
            for(int i=0;i<num;i++){
                free(sa[i]);
            }
            free(sa);
            out.meaning=NULL;
            out.sentence=NULL;
            out.word=NULL;
        }else{
            if(!str_ifint(sa[0])){
                for(int i=0;i<num;i++){
                    free(sa[i]);
                }
                free(sa);
                out.meaning=NULL;
                out.sentence=NULL;
                out.word=NULL;
            }else{
                out.kind=mystrtoint(sa[0]);
                out.word=sa[1];
                out.meaning=sa[2];
                out.sentence=sa[3];
                for(int i=0;i<num;i++){
                    free(sa[i]);
                }
                free(sa);
            }
        }
    }
    return out;
}

//复制一个单词
Word word_cpy(Word base){
    Word out;
    int len;
    out.kind=base.kind;
    len=strlen(base.word);
    out.word=(char *)malloc(sizeof(char)*(len+1));
    out.word[len]='\0';
    memcpy(out.word,base.word,sizeof(char)*len);

    len=strlen(base.meaning);
    out.meaning=(char *)malloc(sizeof(char)*(len+1));
    out.meaning[len]='\0';
    memcpy(out.meaning,base.meaning,sizeof(char)*len);

    len=strlen(base.sentence);
    out.word=(char *)malloc(sizeof(char)*(len+1));
    out.word[len]='\0';
    memcpy(out.word,base.word,sizeof(char)*len);
}

//控制台打印显示单词信息
void word_show(Word word){
    printf("word:\t%s\n",word.word);
    printf("meaning:\t%s\n",word.meaning);
    printf("sentence:\t%s",word.sentence);
}





//把单词变量转化为一个字符串,每个量之间用\n隔开
char* word_tostr(Word word){
    char* out;
    //可以使用itoa实现整数向字符串的转化，但是它是windows独有的，跨平台要用sprintf
    char* kind=inttostr(word.kind);
    int len=4+strlen(kind)+strlen(word.word)+strlen(word.meaning)+strlen(word.sentence);
    out=(char *)malloc(sizeof(char)*(len+1));
    sprintf(out,"%d\n%s\n%s\n%s\n",word.kind,word.word,word.meaning,word.sentence);
    free(kind);
    return out;
}

//删除单词变量
void word_delete(Word word){
    free(word.word);
    free(word.meaning);
    free(word.sentence);
}


//单词数组链表可以作为单词管理的一个基本单位

//创建一个单词数组链表
Mwal mwal_cre(void){
    Mwal out;   
    out.next=NULL;
    out.mwa.num=0;
    return out;
}


/*
查询单词数组链表中的一个单词,通过单词名来搜索
如果这个单词已经存在，则返回这个单词的引用(单词指针)
如果这个单词不存在，则返回空指针*/
Wordp mwal_find(Mwalp mwalh,char* word){
    if(mwalh==NULL){
        return NULL;
    }
    while(mwalh!=NULL){
        Mwap mwap=&(mwalh->mwa);
        for(int i=0;i<mwap->num;i++){
            if(mystreq(mwap->word_arr[i].word,word)){
                return &(mwap->word_arr[i]);
            }
        }
        mwalh=mwalh->next;
    }
    return NULL;
}

/*往单词数组链表中加入一个单词
如果加入成功则返回1
如果单词已经存在，则返回0
*/
int mwal_add(Mwalp mwalh,Word word){
    if(mwal_find(mwalh,word.word)!=NULL){
        return 0;
    }
    if(mwalh->mwa.num<WORD_ARR_MAX){    //如果数组链表的第一个数组没满
        Mwap term=&(mwalh->mwa);
        term->word_arr[term->num]=word_cpy(word);
        term->num++;
    }else{
        while(mwalh->next!=NULL){   //首先来到最后一个链表节点处
            mwalh=mwalh->next;
        }
        if(mwalh->mwa.num==WORD_ARR_MAX){
            //如果链表节点的数组满了，就创建一个新的链表节点，并把当前引用指向最后节点
            mwalh->next=(Mwalp)malloc(sizeof(Mwal));
            mwalh=mwalh->next;
            mwalh->next=NULL;
            mwalh->mwa.num=0;
        }
        Mwap term=&(mwalh->mwa);
        term->word_arr[term->num]=word_cpy(word);
        term->num++;
    }
    return 1;
}


//清空一个数组链表
void mwal_delete(Mwalp mwalp){
    if(mwalp==NULL){
        return ;
    }
    if(mwalp->next==NULL){
        Mwap term=&(mwalp->mwa);
        for(int i=0;i<term->num;i++){
            word_delete(term->word_arr[i]);
        }
        term->num=0;
    }else{
        Mwap term=&(mwalp->mwa);
        for(int i=0;i<term->num;i++){
            word_delete(term->word_arr[i]);
        }
        term->num=0;
        while(mwalp->next!=NULL){
            Mwalp tt=mwalp->next;
            mwalp->next=mwalp->next->next;
            term=&(tt->mwa);
            for(int i=0;i<term->num;i++){
                word_delete(term->word_arr[i]);
            }
            free(term);
        }
        mwalp->next=NULL;
    }
}











