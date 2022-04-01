//record.h
#ifndef _RECORD_H_ //如果没有引入头文件record.h
    #define _RECORD_H_ //那就引入头文件record.h

#include <io.h> //判断文件是否存在
#include <direct.h>    //用来创删文件夹

#include "..\\mystring\\mystring.h"

//我的打开文件，如果是文件本身路径不存在的话就会自动生成对应路径
FILE* myfopen(char* filename,const char* mode);   

//判断一个字符串是否是合法的文件路径(未实现)
int ispath(char* s);




#endif