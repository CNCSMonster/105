#include "record.h"

/*我的打开文件，输入的是绝对路径的地址如果是文件本身路径不存在的话就会自动生成对应路径
如果输入正确并成功打开文件的话返回文件指针，打开失败返回NULl指针
*/
FILE* myfopen(char* filename,const char* mode){
    //此处默认路径中采用'\\'作为文件层次的分割
    char** fs;
    int num;
    FILE* out;
    fs=mystrdepart(filename,'\\',&num);
    if(num>2){  //如果该文件路径中有文件夹层次
        //则要判断对应的层级的文件夹层次是否存在
        char* foldername=mystr_add(fs[0],"\\");
        foldername=mystr_add(foldername,fs[1]);
        for(int i=0;i<num-2;i++){   //除了盘符和文件名，文件路径中总共要判断中间num-2个文件夹层次是否存在
            if(_access(foldername,F_OK)){  //如果对应文件层次不存在
                int jud=_mkdir(foldername);
                if(jud!=0){ //如果创建文件夹失败
                    //释放动态分配的空间后退出函数
                    for(int k=1;k<num;k++){ //0位不用删，之前删过了
                        free(fs[k]);
                    }
                    free(fs);
                    return NULL;
                }
            }
            //获得下一层
            foldername=mystr_add(foldername,"\\");
            foldername=mystr_add(foldername,fs[i+2]);
        }
        out=fopen(foldername,mode);
    }else{  //如果该文件直接在某个盘下
        out=fopen(filename,mode);
    }
    for (int k = 1; k < num; k++)
    { // 0位不用删，之前删过了
        free(fs[k]);
    }
    free(fs);

    return out;
}

//判断一个字符串是否是合法的文件路径
int ispath(char* s){
    //如何判断字符串是不是合法的字符串
    //假设只有C,D, E盘的情况
    //TODO

    return 0;
}






