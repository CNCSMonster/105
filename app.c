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
            word_fput(target,mwa.word_arr[i]);
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
void show_choice(char** sa,char* choice,int len){
    printf("\n");
    for(int i=0;i<len;i++){
        printf("%c.%s\n",choice[i],sa[i]);
    }
}

//��ȡ����ѡ��,��ȡchoice�����ѡ��
char get_choice(char* choice,int len){
    printf("input your choice:");
    int t=1;
    do{
        char* s=mystr_read(stdin);
        fflush(stdin);
        int slen=mystrlen(s);
        char jud='y';//jud�����ж���ȷ���Ǵ���
        if(slen!=1){ 
            jud='n';
        }else{
            int i;
            for(i=0;i<len;i++){
                // printf("\n%c,%c",choice[i],s[0]);
                if(s[0]==choice[i]){
                    // printf("get%c",s[0]);
                    break;
                }
            }
            // printf("i:%d",i);
            if(i==len){
                jud='n';
            }
        }
        if(jud=='n'){ //������벻��ȷ
            printf("Input Error!Please input again:");
        }else{  //���������ȷ
            char out=s[0];
            free(s);
            return out;
        }
        free(s);
    }while(1);
}

//���ƿ���̨���ڴ�С,
void console_setsize(int height,int width){
    char s[100];
    sprintf(s,"mode con cols=%d lines=%d",height,width);
    system(s);
}




/*
���幦��ʵ��
*/

//��ʼ��Ӧ����Ϣ,����ʼ���ܼ�¼����
void app_init(void){
    
    //��ȡ����

    //��ȡ������
    FILE* path=myfopen(MYENGLISH,"r");
    if(path==NULL){
        word_total=mwal_cre();
    }else{
        word_total=getdata(path);
        fclose(path);
    }

    //��ȡ��������
    //��ȡ��������
    char* time=get_time_str();
    //��ȡ
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+6;
    char* today=(char*)malloc(sizeof(char)*len);
    sprintf(today,"%s\\%s.txt",MDAY_CLASSIFY,time);
    free(time);
    path=myfopen(today,"r");
    free(today);
    if(path==NULL){
        //���������ļ���Ϣ������
        word_today=mwal_cre();
    }else{
        //���������ļ���Ϣ����
        word_today=getdata(path);
        fclose(path);
    }

    //��ȡӦ����Ϣ
    path=myfopen(MAPP,"r");
    if(path==NULL){
        myapp.kind=NULL;
        myapp.kindSize=0;
    }else{
        int kindSize;
        int jud=fscanf(path,"%d",&kindSize);
        if(jud!=1||kindSize<=0){
            myapp.kind=NULL;
            myapp.kindSize=0;
        }else{
            myapp.kindSize=kindSize;
            myapp.kind=(char**)malloc(sizeof(char*)*kindSize);
            for(;kindSize>0;kindSize--){
                char* term=mystr_read(path);
                if(term==NULL){
                    break;
                }else{
                    myapp.kind[myapp.kindSize-kindSize]=term;
                }
            }
            if(kindSize!=0){    //�����ȡ������Ϣ��ȱ,�������Ϣ
                for(;kindSize<=myapp.kindSize;kindSize++){
                    free(myapp.kind[kindSize]);
                }
                free(myapp.kind);
                myapp.kindSize=0;
                myapp.kind=NULL;
            }
            fclose(path);
        }
    }
}

//Ӧ�ý��̽�����д���ļ�(���ͷ����з����˵Ŀռ�)
void app_end(void){
    //д�ļ�

    //��app��Ϣд���ļ�
    FILE* path=myfopen(MAPP,"w");
    if(myapp.kind==NULL){   //���app��ϢΪ��
        fprintf(path,"%d\n",0);
    }else{  //���app�м�¼�з�����Ϣ
        fprintf(path,"%d\n",myapp.kindSize);
        for(int i=0;i<myapp.kindSize;i++){
            fprintf(path,"%s\n",myapp.kind[i]);
        }
    }
    fclose(path);

    //�ѽ�����¼����д���ļ�
    //��ȡ��������
    char* time=get_time_str();
    //��ȡ
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+2;
    char* today=(char*)malloc(sizeof(char)*len);
    sprintf(today,"%s\\%s.txt",MDAY_CLASSIFY,time);
    free(time);
    path=myfopen(today,"w");
    putdata(path,word_today);
    fclose(path);
    free(today);

    //���ܵ�����Ϣд���ļ�
    path=myfopen(MYENGLISH,"w");
    putdata(path,word_total);
    fclose(path);

    //�ͷſռ�
    //�ͷŽ�������
    mwal_delete(&word_today);

    //�ͷ��ܵ�������
    mwal_delete(&word_total);

    //�ͷ�Ӧ����Ϣ
    for(int i=0;i<myapp.kindSize;i++){
        free(myapp.kind[i]);
    }
    free(myapp.kind);

}

//Ӧ�ù�����ˢ���ļ���Ϣ(�Ѹ��µ�����д���ļ�)�����ö��̵߳ķ���ʹ����
void app_flash(void){
    //д�ļ�
    //��app��Ϣд���ļ�
    FILE* path=myfopen(MAPP,"w");
    if(myapp.kind==NULL){   //���app��ϢΪ��
        fprintf(path,"%d\n",0);
    }else{  //���app�м�¼�з�����Ϣ
        fprintf(path,"%d\n",myapp.kindSize);
        for(int i=0;i<myapp.kindSize;i++){
            fprintf(path,"%s\n",myapp.kind[i]);
        }
    }
    fclose(path);
    //�ѽ�����¼����д���ļ�
    //��ȡ��������
    char* time=get_time_str();
    //��ȡ
    int len=mystrlen(time)+mystrlen(MDAY_CLASSIFY)+2;
    char* today=(char*)malloc(sizeof(char)*len);
    sprintf(today,"%s\\%s.txt",MDAY_CLASSIFY,time);
    free(time);
    path=myfopen(today,"w");
    putdata(path,word_today);
    fclose(path);
    free(today);
    //���ܵ�����Ϣд���ļ�
    path=myfopen(MYENGLISH,"w");
    putdata(path,word_total);
    fclose(path);
}



//������
void main_choice(void){
    // �����棺��ʼʹ�ã�����������,�Լ��˳�Ӧ��
    char curchoice;
    char* order[4]={
        mystrcpy("��ʼʹ��"),
        mystrcpy("����"),
        mystrcpy("����"),
        mystrcpy("�˳�����")
    };
    char choice[4]={'0','1','2','e'};
    app_init();
    do{
        system("cls");
        show_choice(order,choice,4);
        curchoice=get_choice(choice,4);
        switch(curchoice){
            case '0':
                system("cls");
                start_choice();
            break;
            case '1':
                system("cls");
                help_choice();
            break;
            case '2':
                system("cls");
                set_choice();
            break;
            default:
                app_end();
            break;
        }
    }while(curchoice!='e');
    //�ͷſռ�
    for(int i=0;i<4;i++){
        free(order[i]);
    }
}


//���ý���
void set_choice(void){
    printf("��δ���\n");
    system("pause");
}

//��������
void help_choice(void){
    printf("��δ���\n");
    system("pause");
}

//��ʼʹ�ý���
void start_choice(void){
    // ��ʼʹ�ã���ӵ���,���ո�ϰ���������ʣ��˳�
    //�������
    int len=4;
    char* order[len]={
        mystrcpy("��ӵ���"),
        mystrcpy("���ո�ϰ"),
        mystrcpy("��������"),
        mystrcpy("�˳�")
    };
    char choice[len]={
        '0','1','2','e'
    };
    char curchoice;
    do{
        show_choice(order,choice,len);
        curchoice=get_choice(choice,len);
    }while(curchoice!=choice[3]);
    //�ͷſռ�
    for(int i=0;i<len;i++){
        free(order[i]);
    }
}

//��ӵ��ʽ��棬��ӵĵ���Ĭ��Ϊ������,������ѡ�����ͣ�����ֻ�Ӳ��ģ�
void mywordadd(void){
    
}

//���ո�ϰ����
void myreview(void){

}

//�������ʽ���:���������ԶԴ˲�������������棬�˳�
void view_choice(void){

}

//�������,ѡ�������в鿴��ֻ������
void divide_choice(void){

}

//������ѡ��ķ���
void divide_show(Mwal show){

}

//����md�ĵ������Ի������룬���������Ӣ���ļ���������һ��md�ĵ�
void outputmd(void){

}   





