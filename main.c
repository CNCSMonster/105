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
   
    char* time=get_time_str();
    printf("%s",time);
    free(time);

    return 0;

}