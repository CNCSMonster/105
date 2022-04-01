//app.h
#ifndef _APP_H_ //���û������ͷ�ļ�app.h
    #define _APP_H_ //�Ǿ�����ͷ�ļ�app.h

#include "word.h"
#include "mytime.h"
#include "mystring\\mystring.h"
#include "myrecord\\record.h"


//������ļ����潫��ʵ���������Ҫ����

typedef struct myappdata{
    char** kind;    //�������¼�Ѿ����ڵķ���
    int kindSize;   //�Ѿ����ڵķ������Ŀ
}App,*Appp;


App myapp;  //����ȫ�ֱ����洢������Ϣ

Mwal word_total=mwal_cre();    //����ȫ�ֵĴ洢��Ϣ�ĵ��ʴ洢��Ԫ

//����һ��ʼ�򿪵Ŀ���̨���ڴ�С
#define MAPP_HEIGHT 75
#define MAPP_WIDTH 100

//��Ҫ���������ļ�
#define MYENGLISH "E:\\Eglishword\\wordall.txt"

//Ӧ�������ļ�,�����¼�˵��ʷ�������Ϣ
#define MEAPP "E:\\Eglishword\\app.txt"

//�����ļ��У������¼�˽���һ����ļ���Ϣ����һ�����ݾ������ڡ�
#define MTODAY "E:\\Eglishword\\today.txt"

//���������ļ���·���������Ƿ�����ļ�����Ϣ����Ϣ��ʽ��Ϣ��������Ϣ����
#define DVFOLDER "E:\\Eglishword\\divide.txt"

//��ȡһ���ܵ��ļ�
//��Ϊ�Ǳ���������������ܵĴʻ���Ӧ�ôﵽ��10000����
//���Ժ���Ӧ��ʹ�����ݿ����������ݶ���Ĺ���



//���ļ��ж�ȡ����
Mwal getdata(FILE* path);

//�ѵ��������������ʵ�Ԫ���е����ݴ洢��Ŀ���ļ���
void putdata(FILE* target,Mwal mwal);


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









#endif