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
��ʼʹ�ã���ӵ���,���ո�ϰ���������ʣ�����Ϊmd�ļ����˳�
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
    int len=5;
    char** order=(char **)malloc(sizeof(char*)*len);
    order[0]=mystrcpy("��ӵ���");
    order[1]=mystrcpy("���ո�ϰ");
    order[2]=mystrcpy("��������");
    order[3]=mystrcpy("����Ϊmd�ĵ�");
    order[4]=mystrcpy("�˳�");
    char choice[5]={'0','1','2','3','e'};
    char curchoice;
    do{
        system("cls");
        show_choice(order,choice,len);
        curchoice=get_choice(choice,len);
        switch(curchoice){
            case '0':
                system("cls");
                mywordadd();
            break;
            case '1':
                system("cls");
                myreview();
            break;
            case '2':
                system("cls");
                view_choice();
            break;
            case '3':
                system("cls");
                outputmd();
            break;
            default:
            break;
        }
    }while(curchoice!=choice[len-1]);
    //�ͷſռ�
    for(int i=0;i<len;i++){
        free(order[i]);
    }
    free(order);
}


//��ӵ��ʽ��棬��ӵĵ���Ĭ��Ϊ������,������ѡ�����ͣ�����ֻ�Ӳ��ģ�
void mywordadd(void){
    //���ܽ���
    printf("����:c--����,s--����,e--�˳�,������ĸ--����:\n");
    //���ô��������øý�����.
    do{//����֮�����ѡ������Ҳ����ѡ��ˢ�½���
        //��ȥ���Ƿ������ˣ�ֻҪѡ��Ĳ���c/s/e�������
        printf("your choice:");
        char curord=getch();
        printf("\r");
        for(int i=0;i<30;i++){    //��յ�ǰ�У����ֽ�������
            printf(" ");
        }
        printf("\r");
        fflush(stdin);
        if(curord=='e'){
            break;
        }else if(curord=='c'){
            system("cls");
            printf("����:c--����,s--����,e--�˳�,������ĸ--����:\n");
        }else if(curord=='s'){
            printf("�ù�����δʵ��,�����������");
            getch();
            printf("\r");
            for(int i=0;i<40;i++){
                printf(" ");
            }
            printf("\r");
        }else{  //��������
            Word add=word_get();
            char* jud=word_iflegal(add);
            if(jud!=NULL){ //����������
                printf("�������%s",jud);
                free(jud);
                printf("\n************************************************\n");
            }else if(mwal_find(&word_total,add.word)!=NULL){  //�����������Ѿ��������
                printf("�õ����ѱ�����\n");
                printf("\n************************************************\n");
                word_delete(add);
            }else{  //������ӣ����
                printf("�����ɣ�\n");
                mwal_add(&word_total,add);
                mwal_add(&word_today,add);
                word_delete(add);
                printf("\n************************************************\n");
            }
            continue;
        }
    }while(1);

}

//���ո�ϰ����
void myreview(void){
    //���ܽ���
    //չʾ���յĵ���
    divide_show(word_today);
}

//�������ʽ���:���������ԶԴ˲�����������鿴���˳�
void view_choice(void){
    //ѡ�����
    //�������
    int len=3;
    char** order=(char **)malloc(sizeof(char*)*len);
    order[0]=mystrcpy("����");
    order[1]=mystrcpy("����鿴");
    order[2]=mystrcpy("�˳�");
    char choice[3]={'0','1','e'};
    char curchoice;
    do{
        show_choice(order,choice,len);
        curchoice=get_choice(choice,len);
        switch(curchoice){
            case '0':
                system("cls");
                view_find();
            break;
            case '1':
                system("cls");
                divide_choice();
            break;
            default:
            break;
        }
    }while(curchoice!=choice[2]);
    //�ͷſռ�
    for(int i=0;i<len;i++){
        free(order[i]);
    }
    free(order);
    
}

//�������ҵĵ��ʣ����ҿ��Զ��������ĵ��ʲ���
void view_find(void){
    //���ܽ���
    printf("��ʱû��ʵ��");
    system("pause");
}


//�������,ѡ�������в鿴��ֻ������
void divide_choice(void){

    //�������
    if(myapp.kindSize==0){
        //������е��ʶ�û�з���Ļ���������Ĭ�Ϸ���
        printf("���е��ʾ�δ���࣬�ù����޷�ʹ�á�");
        fflush(stdin);
        printf("�밴���������");
        getch();
        return ;
    }
    int len=myapp.kindSize+1;
    char** order=(char**)malloc(sizeof(char*)*len); //������Ҫ�ͷſռ�
    char choice[len];
    for(int i=0;i<len-1;i++){
        order[i]=myapp.kind[i]; //��Ϊ����������ʾ����������ã���û���·���ռ䣬���Ժ����������ͷ�
        choice[i]=i+48;        //�����Ƿ��೬��10�������������ѷ���תΪ��Ӧ�ַ�
    }
    choice[len]='e';

    //�����ݴ�ĵ��ʻ����洢��Ԫ�����������ظ�����
    typedef struct curwordbase{
        Mwalp mwalp;
        int kind;
        struct curwordbase* next;
    }Cw,*Cwp;
    Cw cw_h;    //����ͷ��㣬�ýڵ��������������㣬���洢����
    cw_h.next=NULL; //��ʼʱ��Ԫ�ڵ�Ϊ0����ʾû�б����κη���ĵ�Ԫ����
    Cwp cw_t=&cw_h;
    char curchoice;
    do{
        show_choice(order,choice,len);
        printf("\n��������Ҫѡ��鿴�ķ�������˳�\n");
        curchoice=get_choice(choice,len);
        if(curchoice=='e'){
            break;
        }else{
            system("cls");
            //��ȡ�Լ���Ҫ�ķ��࣬���в鿴
            //���Ȼ�õķ��࣬��õ�ѡ��ת��Ϊ����
            int thischoice=curchoice-48;
            //�Ȳ����Ѿ������˵ķ����������Ƿ������ѡ���͵ķ���洢
            Mwalp cur_mwalp;    //��ǰ�ĵ�����������Ԫ
            cw_t=&cw_h;
            while(cw_t->next!=NULL){
                if(cw_t->next->kind==thischoice){
                    //����Լ�ѡ��ķ��������Ѿ�����
                    cur_mwalp=cw_t->next->mwalp;
                }
                cw_t=cw_t->next;
            }
            if(cw_t->next==NULL){
                //����Լ�ѡ��ķ�������δ����
                //�����Լ���Ҫ�ķ���
                cw_t->next=(Cwp)malloc(sizeof(Cw));
                cw_t=cw_t->next;
                cw_t->next=NULL;
                Mwal mwal_t=mwal_get_kindpart(&word_total,thischoice);
                cw_t->mwalp=&mwal_t;
                cw_t->kind=thischoice;
                cur_mwalp=cw_t->mwalp;
            }
            //Ȼ��չʾ��������
            system("cls");
            divide_show(*cur_mwalp);
        }
    }while(curchoice!=choice[len-1]);
    free(order);
    //�ͷ�ʹ�õĵ��ʴ洢��Ԫ����Ŀռ�
    while(cw_h.next!=NULL){
        cw_t=cw_h.next;
        cw_h.next=cw_h.next->next;
        mwal_delete(cw_t->mwalp);
        free(cw_t);
    }

}




//������ѡ��ķ���
void divide_show(Mwal show){
    //���ܽ���
    //չʾ�Լ�����ĵ���
    int max=4;  //һҳ��ʾ�ĵ��ʵ��������
    int total=mwal_getsize(show);  //������¼�ܵĵ�����,���ܵĵ���ҳ��Ϊ
    if(total==0){
        printf("���б�Ϊ�ա�");
        printf("\n�밴���������");
        getch();
        return ;
    }
    int totalpage=total%max==0?(total/max):(total/max+1);
    /*
    ����ҳ��Ϊ��total%max==0?total/max:total/max+1
    */
    int cur_page=0; //��¼��ǰҳ��,�±��0-totalpage-1
    Mwalp cur_mwalp=&show;  //��¼��ǰ������������ĵ�ǰ��ʾ���
    int cur_index=0;    //��¼��ǰ������������ĵ�ǰ��ʾ����±�
    char cur_choice;  //��¼��ǰ��ȡ��ѡ��
    do{
        //չʾ��ǰҳ��ĵ���
        system("cls");
        Mwalp cur_show=cur_mwalp;
        int index_show=cur_index;
        for(int i=0;i<max&&i<cur_show->mwa.num;i++){
            printf("\n");
            word_show(cur_show->mwa.word_arr[index_show]);
            index_show++;
            if(index_show==WORD_ARR_MAX){   //�����ǰ���������ȡ��ͷ��
                if(cur_show->next!=NULL){    //�����һ������������
                    cur_show=cur_show->next;
                    index_show=0;
                }else{  //�������ѭ��
                    break;
                }
            }
        }
        printf("\n��ǰҳ��/��ҳ��:%d/%d",cur_page+1,totalpage);
        printf("\n��ǰ/����ҳ/�˳��鿴:a/d/e");
        cur_choice=getch();
        while(cur_choice!='a'&&cur_choice!='d'&&cur_choice!='e'){
            cur_choice=getch();
        }
        if(cur_choice=='e'){
            break;
        }else{      //�����ѭ��Ч�����ﵽ��(��)�߽��Ͳ��ܹ���(��)
            switch(cur_choice){
                case 'a':   //��ǰ��ҳ
                    if(cur_page>=0){
                        cur_page--;
                        cur_index-=max;
                        if(cur_index<0){
                            Mwalp ttt=&show;
                            while(ttt->next!=cur_mwalp){
                                ttt=ttt->next;
                            }
                            cur_mwalp=ttt;
                            cur_index=(cur_index+WORD_ARR_MAX)%WORD_ARR_MAX;
                        }
                    }
                break;
                case 'd':   //����ҳ
                    if(cur_page<totalpage-1){ //������ܹ�����ҳ
                        cur_page++;
                        cur_index+=max;
                        if(cur_index>=WORD_ARR_MAX){
                            cur_index=cur_index%WORD_ARR_MAX;
                            cur_mwalp=cur_mwalp->next;
                        }
                    }
                break;
                default:
                break;
            }
        }
    }while(cur_choice!='e');
}

//����md�ĵ������Ի������룬���������Ӣ���ļ���������һ��md�ĵ�
void outputmd(void){
    //���뿪ʼʹ��֮��
    //���ܽ���
    //ѡ�����λ������(Ĭ��Ϊ��ǰλ��,Ҳ����exe����λ��)������
    //��������Լ����صĵ��ʷ��ർ��������λ�ã���������Ϊ�Լ�������λ��
    //�����ļ�����(��ʵ���������)
    printf("\n��������Ҫ����Ϊ���ļ�����(����Ӣ��):");
    char* name=mystr_read(stdin);
    while(!mystr_if_e(name)){
        free(name);
        printf("���벻���Ϲ淶�����������룺");
        name=mystr_read(stdin);
    }
    //���ȴ򿪶�Ӧ���ļ�
    char path[strlen(name)+5];
    sprintf(path,"%s.md",name);
    free(name);
    FILE* mf=fopen(path,"w");   //ʹ�����·��
    fprintf(mf,"# My English Word Book\n\n");    //д������
    fprintf(mf,"[TOC]\n\n");     //д��Ŀ¼
    fprintf(mf,"## A. total words\n\n");    //д��μ�����
    putdata(mf,word_total);
    fprintf(mf,"\n\n## B. division");
    for(int i=0;i<myapp.kindSize;i++){  
        fprintf(mf,"\n\n### %d. %s",i+1,myapp.kind[i]);
        Mwal term=mwal_get_kindpart(&word_total,i);
        putdata(mf,term);
        mwal_delete(&term);
    }
    fclose(mf);
    printf("�����ɹ���");
    printf("�밴�����������");
    getch();
}   





