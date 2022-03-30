#include "word.h"

//从控制台中读取信息获取我们的单词
Word getWord(void){
    Word out;
    printf("Word:\t");
    out.word=mystr_read(stdin);
    printf("meaning:\t");
    out.meaning=mystr_read(stdin);
    printf("sentence:\t");
    out.sentence=mystr_read(stdin);
    return out;
}

//复制一个单词
Word word_cpy(Word base){
    Word out;
    int len;
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

//显示单词信息
void word_show(Word word){
    printf("word:\t%s\n",word.word);
    printf("meaning:\t%s\n",word.meaning);
    printf("sentence:\t%s",word.sentence);
}

//把单词变量转化为一个字符串
char* word_tostr(Word word){

}
















