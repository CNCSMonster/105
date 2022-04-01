#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


int main(){
    // system("mode con cols=30 lines=20");
    int height=100;
    int width=200;
    char chCmd[32];
    sprintf(chCmd,"mode con cols=%d lines=%d",height,width);
    printf("nihao");
    getchar();
    return 0;
}