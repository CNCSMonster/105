#include "app.h"


//���ļ��ж�ȡ����
Mwal getdata(FILE* path){
    //��ȡ��ʽ��ֱ�Ӷ�ȡ��ÿ��������֮�����Ϊһ�����з�
    Mwal out=mwal_cre();
    while(!feof(path)){//���ļ�û�ж�����ͷʱ
        Word term=word_read(path);
        if(word_isempty(term)){
            break;
        }
        mwal_add(&out,term);
        word_delete(term);
    }
    return out;
}

//�ѵ��������������ʵ�Ԫ���е����ݴ洢��Ŀ���ļ���
void putdata(FILE* target,Mwal mwal){
    //������д��Ŀ���ļ�
    Mwalp term=&mwal;
    while(term!=NULL){
        Mwa mwa=term->mwa;
        for(int i=0;i<mwa.num;i++){
            word_fput(terget,mwa.word_arr[i]);
            fputc('\n',target);
        }
        term=term->next;
    }
}


/*
������棺
�����棺��ʼʹ�ã�����������
��ʼʹ�ã���ӵ���,���ո�ϰ���������ʣ��˳�
��������ʾ���ʹ��
���ã����ÿ�ݼ����Լ�ɾ���ó���
ɾ���ó���ɾ����Ӧ�ļ������߱�����Ӧ�����ļ����Ǳ���exe
�������ʣ��������൥�ʣ��������ʣ��˳�ѡ��
�������൥�ʣ��������ͷ��࣬�������ڷ��࣬�˳�ѡ��
ĳ������������Ԫ�Ķ����ܹ�ʵ�ַ�ҳЧ����һҳ����5�������·���ʾҳ��Ȼ�����ѡ�񷭵���һҳ�����˳�������һҳ
*/

//ʵ�ֽ���
//������ʾ,��ʾlen��ѡ��
void show_choice(char** sa,int len);

//��ȡ����ѡ��,��ȡchoice�����ѡ��
char get_choice(char* choice,int len);

//���ƿ���̨���ڴ�С,
void console_setsize(int height,int width);




/*
���幦��ʵ��
*/

//��ʼ��Ӧ����Ϣ,����ʼ����
void app_init(void);


//������
void main_choice(void);

//�˳�������,�˳��������ʱ��Ż��һ��д���ļ�֮��
void main_exit(void);

//���ý���
void set_choice(void);

//��������
void help_choice(void);

//��ʼʹ�ý���
void start_choice(void);

//��ӵ��ʽ��棬��ӵĵ���Ĭ��Ϊ������,������ѡ�����ͣ�����ֻ�Ӳ��ģ�
void mywordadd(void);

//���ո�ϰ����
void myreview(void);

//�������ʽ���:���������ԶԴ˲�������������棬�˳�
void view_choice(void);

//�������,ѡ�������в鿴��ֻ������
void divide_choice(void);

//������ѡ��ķ���
void divide_show(Mwal show); 

//����md�ĵ������Ի������룬���������Ӣ���ļ���������һ��md�ĵ�
void outputmd(void);    