#include "all.h"

#define MYENGLISH "E:\\Eglishword\\wordall.txt"


int main(){
    //��ս�������ܵ��ö̵Ĵ���д��

    //���ʣ���ΪӢ�ġ����ġ�������
    /*
    word:water
    chinese:ˮ(/press 0 to back)
    sentence:Hunman need water.
    */
    //��������Ϊһ�������Ľ�������Ϊһ����
   
    
    // char* i=inttostr(-12345678);
    // printf("%s",i);
    // free(i);

    //�����ļ����ܺͽ⿪����
    FILE* path=myfopen("E:\\9999.txt","w");
    char* s=mystrcpy("Hello world!");
    int len=mystrlen(s);
    //���ü����ض�ֵȻ���ٰ�λȡ���ķ������ܡ�
    //���ܵ�ʱ��Ͳ�����ȡ��Ȼ���ȥ�ض�ֵ�ķ���
    int mycode=2;
    //����
    for(int i=0;i<len;i++){
        s[i]=s[i]+mycode;
        s[i]=~s[i];
    }
    fprintf(path,"%s",s);
    free(s);
    fclose(path);
    path=myfopen("E:\\9999.txt","r");
    s=mystr_read(path);
    printf("\n����ǰ:%s",s);
    len=mystrlen(s);
    for(int i=0;i<len;i++){
        s[i]=~s[i];
        s[i]-=mycode;
    }
    printf("\n�����:%s",s);
    free(s);
    fclose(path);
    return 0;

}