#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char s[200]="i ma a tneduts";
    // printf("%s",s);
    int s_len=strlen(s);
    for(int i=0;i<s_len;i++){
        if(s[i]==' '){  //如果遇到空格跳过
            continue;
        }else{  //如果遇到单词开头
            int word_len=0; //用来记录单词长度
            for(int j=0;i+j<s_len;j++){
                if(s[i+j]!=' '){
                    word_len++;
                }else{
                    break;
                }
            }
            //经过上述代码后我们获得了首字母下标为i的单词的长度为word_len
            for(int j=0;j<word_len/2;j++){  //对该单词翻转,也就是交换单词前一半与后一半字母
                char term=s[j+i];  
                s[i+j]=s[i+word_len-1-j];
                s[i+word_len-1-j]=term;
            }
            i=i+word_len;   //让当前访问下标来到单词后面第一个字母处
        }
    }
    printf("%s",s);
    return 0;
}