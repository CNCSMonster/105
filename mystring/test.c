#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char s[200]="i ma a tneduts";
    // printf("%s",s);
    int s_len=strlen(s);
    for(int i=0;i<s_len;i++){
        if(s[i]==' '){  //��������ո�����
            continue;
        }else{  //����������ʿ�ͷ
            int word_len=0; //������¼���ʳ���
            for(int j=0;i+j<s_len;j++){
                if(s[i+j]!=' '){
                    word_len++;
                }else{
                    break;
                }
            }
            //����������������ǻ��������ĸ�±�Ϊi�ĵ��ʵĳ���Ϊword_len
            for(int j=0;j<word_len/2;j++){  //�Ըõ��ʷ�ת,Ҳ���ǽ�������ǰһ�����һ����ĸ
                char term=s[j+i];  
                s[i+j]=s[i+word_len-1-j];
                s[i+word_len-1-j]=term;
            }
            i=i+word_len;   //�õ�ǰ�����±��������ʺ����һ����ĸ��
        }
    }
    printf("%s",s);
    return 0;
}