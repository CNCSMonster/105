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
    
    // main_choice();

    //单元测试，divide_show 
    Mwal m=mwal_cre();
    Word w=word_get();
    mwal_add(&m,w);
    printf("显示分类");
    divide_show(m);
    getch();

    return 0;

}