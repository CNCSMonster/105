#include "record.h"

/*�ҵĴ��ļ���������Ǿ���·���ĵ�ַ������ļ�����·�������ڵĻ��ͻ��Զ����ɶ�Ӧ·��
���������ȷ���ɹ����ļ��Ļ������ļ�ָ�룬��ʧ�ܷ���NULlָ��
*/
FILE* myfopen(char* filename,const char* mode){
    //�˴�Ĭ��·���в���'\\'��Ϊ�ļ���εķָ�
    char** fs;
    int num;
    FILE* out;
    fs=mystrdepart(filename,'\\',&num);
    if(num>2){  //������ļ�·�������ļ��в��
        //��Ҫ�ж϶�Ӧ�Ĳ㼶���ļ��в���Ƿ����
        char* foldername=mystradd(fs[0],"\\");
        foldername=mystradd(foldername,fs[1]);
        for(int i=0;i<num-2;i++){   //�����̷����ļ������ļ�·�����ܹ�Ҫ�ж��м�num-2���ļ��в���Ƿ����
            if(_access(foldername,F_OK)){  //�����Ӧ�ļ���β�����
                int jud=_mkdir(foldername);
                if(jud!=0){ //��������ļ���ʧ��
                    //�ͷŶ�̬����Ŀռ���˳�����
                    for(int k=1;k<num;k++){ //0λ����ɾ��֮ǰɾ����
                        free(fs[k]);
                    }
                    free(fs);
                    return NULL;
                }
            }
            //�����һ��
            foldername=mystradd(foldername,"\\");
            foldername=mystradd(foldername,fs[i+2]);
        }
        out=fopen(foldername,mode);
    }else{  //������ļ�ֱ����ĳ������
        out=fopen(filename,mode);
    }
    for (int k = 1; k < num; k++)
    { // 0λ����ɾ��֮ǰɾ����
        free(fs[k]);
    }
    free(fs);

    return out;
}