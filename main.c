#include "all.h"

#define MYENGLISH "E:\\Eglishword\\wordall.txt"


int main(){
    //挑战，尽可能的用短的代码写完

    //单词，分为英文、中文、和例句
    /*
    word:water
    chinese:水(/press 0 to back)
    sentence:Hunman need water.
    */
    //单词限制为一个，中文解释限制为一个。
   
    
    // char* i=inttostr(-12345678);
    // printf("%s",i);
    // free(i);

    //尝试文件加密和解开密码
    FILE* path=myfopen("E:\\9999.txt","w");
    char* s=mystrcpy("Hello world!");
    int len=mystrlen(s);
    //采用加上特定值然后再按位取反的方法加密。
    //解密的时候就采用先取反然后减去特定值的方法
    int mycode=2;
    //加密
    for(int i=0;i<len;i++){
        s[i]=s[i]+mycode;
        s[i]=~s[i];
    }
    fprintf(path,"%s",s);
    free(s);
    fclose(path);
    path=myfopen("E:\\9999.txt","r");
    s=mystr_read(path);
    printf("\n解码前:%s",s);
    len=mystrlen(s);
    for(int i=0;i<len;i++){
        s[i]=~s[i];
        s[i]-=mycode;
    }
    printf("\n解码后:%s",s);
    free(s);
    fclose(path);
    return 0;

}