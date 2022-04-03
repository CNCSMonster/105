#include "word.h"




/*�ӿ���̨�ж�ȡ��Ϣ��ȡ���ǵĵ���
���ʵ����Ͳ�������ָ�����������ά��һ��ӳ��õ�
���Բ���������õ�
*/
Word word_get(void){
    Word out;
    out.kind=WORD_DEFAULT_KIND;     //��������ΪĬ������
    printf("Word:\t");
    out.word=mystr_read(stdin); //meaning��word����Ϊ��
    printf("meaning:\t");
    out.meaning=mystr_read(stdin);
    printf("sentence:\t");      //sentence����Ϊ��
    out.sentence=mystr_read(stdin);
    return out;
}

//�ж�һ�����ʱ����Ƿ��ǺϷ��ģ���������ʾ��Ϣ
char* word_iflegal(Word word){
    char* out=mystr_cre();
    if(mystreq(word.word,"")){
        out=mystr_add(out,"��������Ϊ��/");
    }else{
        if(!mystr_if_e(word.word)){
            out=mystr_add(out,"�������벻��Ӣ��/");
        }
    }
    if(mystreq(word.meaning,"")){
        out=mystr_add(out,"������������Ϊ��");
    }
    if(strlen(out)==0){
        free(out);
        return NULL;
    }
    return out;
}

/*��ָ���ļ�����һ����ʽ��ȡ������Ϣ
�����ȡ���ɹ����򷵻صĽ��Ϊ�յĵ���
*/
Word word_read(FILE* path){
    Word out;
    out.meaning=NULL;
    out.word=NULL;
    out.sentence=NULL;
    out.kind=WORD_DEFAULT_KIND;    //��������Ϊͷ�ļ������Ĭ������
    int jud=fscanf(path,"%d\n",&(out.kind));
    if(jud!=1){ //��ȡʧ��
        return out;
    }
    out.word=mystr_read(path);
    out.meaning=mystr_read(path);
    out.sentence=mystr_read(path);
    return out;
}

//�ѵ�����Ϣд��ָ���ļ���ǰ��û��\n
void word_fput(FILE* path,Word word){
    if(word_isempty(word)){
        return;
    }else{
        fprintf(path,"%d\n%s\n%s\n%s",word.kind,word.word,word.meaning,word.sentence);
    }
}

//�жϵ��ʱ����Ƿ��ǿյ�
int word_isempty(Word word){
    if(word.meaning==NULL){
        return 1;
    }else{
        return 0;
    }
}

/*��һ���ַ���ת��Ϊ������Ϣ
����ַ������Ϸ����򷵻صĽ��Ϊ�յĵ�����Ϣ
���ʵĸ�����Ϣ֮����\n�ָ�
�ṹ���ң�kind\nword\nmeaning\nsentence
����\n���ʱ���\n������˼\n��������
*/
Word str_to_word(char* s){
    Word out;
    if(s==NULL){
        out.meaning=NULL;
        out.sentence=NULL;
        out.word=NULL;
    }else{
        int num;
        char** sa=mystrdepart(s,'\\',&num);
        if(num!=4){
            for(int i=0;i<num;i++){
                free(sa[i]);
            }
            free(sa);
            out.meaning=NULL;
            out.sentence=NULL;
            out.word=NULL;
        }else{
            if(!mystr_if_i(sa[0])){
                for(int i=0;i<num;i++){
                    free(sa[i]);
                }
                free(sa);
                out.meaning=NULL;
                out.sentence=NULL;
                out.word=NULL;
            }else{
                out.kind=mystrtoint(sa[0]);
                out.word=sa[1];
                out.meaning=sa[2];
                out.sentence=sa[3];
                for(int i=0;i<num;i++){
                    free(sa[i]);
                }
                free(sa);
            }
        }
    }
    return out;
}

//����һ������
Word word_cpy(Word base){
    Word out;
    int len;
    out.kind=base.kind;
    len=strlen(base.word);
    if(out.word!=NULL){
        out.word=mystrcpy(base.word);
    }else{
        out.word=NULL;
    }
    if(out.meaning!=NULL){
        out.meaning=mystrcpy(base.meaning);
    }else{
        out.meaning=NULL;
    }
    if(out.sentence!=NULL){
        out.sentence=mystrcpy(base.sentence);
    }else{
        out.sentence=NULL;
    }
    // //�·���
    // out.word=(char *)malloc(sizeof(char)*(len+1));
    // out.word[len]='\0';
    // memcpy(out.word,base.word,sizeof(char)*len);

    // len=strlen(base.meaning);
    // out.meaning=(char *)malloc(sizeof(char)*(len+1));
    // out.meaning[len]='\0';
    // memcpy(out.meaning,base.meaning,sizeof(char)*len);

    // len=strlen(base.sentence);
    // out.sentence=(char *)malloc(sizeof(char)*(len+1));
    // out.sentence[len]='\0';
    // memcpy(out.sentence,base.sentence,sizeof(char)*len);
    return out;
}

//����̨��ӡ��ʾ������Ϣ
void word_show(Word word){
    printf("word:\t%s\n",word.word);
    printf("meaning:\t%s\n",word.meaning);
    printf("sentence:\t%s",word.sentence);
}





//�ѵ��ʱ���ת��Ϊһ���ַ���,ÿ����֮����\n����
char* word_tostr(Word word){
    char* out;
    //����ʹ��itoaʵ���������ַ�����ת������������windows���еģ���ƽ̨Ҫ��sprintf
    char* kind=inttostr(word.kind);
    int len=4+strlen(kind)+strlen(word.word)+strlen(word.meaning)+strlen(word.sentence);
    out=(char *)malloc(sizeof(char)*(len+1));
    sprintf(out,"%d\n%s\n%s\n%s\n",word.kind,word.word,word.meaning,word.sentence);
    free(kind);
    return out;
}

//��ȫɾ�����ʱ����������û���ͷŵĿռ䣬�ͻ��ͷ�
void word_delete(Word word){
    if(word.word!=NULL){
        free(word.word);
    }
    if(word.meaning!=NULL){
        free(word.meaning);
    }
    if(word.sentence!=NULL){
        free(word.sentence);
    }
}


//�����������������Ϊ���ʹ����һ��������λ

//����һ��������������
Mwal mwal_cre(void){
    Mwal out;   
    out.next=NULL;
    out.mwa.num=0;
    return out;
}


/*
��ѯ�������������е�һ������,ͨ��������������
�����������Ѿ����ڣ��򷵻�������ʵ�����(����ָ��)
���������ʲ����ڣ��򷵻ؿ�ָ��*/
Wordp mwal_find(Mwalp mwalh,char* word){
    if(mwalh==NULL||word==NULL){
        return NULL;
    }
    while(mwalh!=NULL){
        Mwap mwap=&(mwalh->mwa);
        for(int i=0;i<mwap->num;i++){
            if(mystreq(mwap->word_arr[i].word,word)){
                return &(mwap->word_arr[i]);
            }
        }
        mwalh=mwalh->next;
    }
    return NULL;
}

/*���������������м���һ������
�������ɹ��򷵻�1
��������Ѿ����ڣ��򷵻�0
*/
int mwal_add(Mwalp mwalh,Word word){
    if(mwal_find(mwalh,word.word)!=NULL){
        return 0;
    }
    if(mwalh->mwa.num<WORD_ARR_MAX){    //�����������ĵ�һ������û��
        Mwap term=&(mwalh->mwa);
        term->word_arr[term->num]=word_cpy(word);
        term->num++;
    }else{
        while(mwalh->next!=NULL){   //�����������һ������ڵ㴦
            mwalh=mwalh->next;
        }
        if(mwalh->mwa.num==WORD_ARR_MAX){
            //�������ڵ���������ˣ��ʹ���һ���µ�����ڵ㣬���ѵ�ǰ����ָ�����ڵ�
            mwalh->next=(Mwalp)malloc(sizeof(Mwal));
            mwalh=mwalh->next;
            mwalh->next=NULL;
            mwalh->mwa.num=0;
        }
        Mwap term=&(mwalh->mwa);
        term->word_arr[term->num]=word_cpy(word);
        term->num++;
    }
    return 1;
}

//�ӵ�������������ȡ��ָ�����͵ĵ��ʣ�������װ��һ����������������
Mwal mwal_get_kindpart(Mwalp mwalp,int kind){
    Mwal out=mwal_cre();
    while(mwalp!=NULL){
        Mwa term=mwalp->mwa;
        for(int i=0;i<term.num;i++){
            if(term.word_arr[i].kind==kind){
                mwal_add(&out,term.word_arr[i]);
            }
        }
        mwalp=mwalp->next;
    }
    return out;
}

//�ӵ������������л�����������еĵ��ʵĸ���
int mwal_getsize(Mwal mwal){
    int out=0;
    Mwalp mwalp=&mwal;
    while(mwalp->next!=NULL){
        mwalp=mwalp->next;
        out+=WORD_ARR_MAX;  //����ǰ����һ����������
    }
    out+=mwalp->mwa.num;
    return out;
}

//���һ����������
void mwal_delete(Mwalp mwalp){
    if(mwalp==NULL){
        return ;
    }
    if(mwalp->next==NULL){
        Mwap term=&(mwalp->mwa);
        for(int i=0;i<term->num;i++){
            word_delete(term->word_arr[i]);
        }
        term->num=0;
    }else{
        Mwap term=&(mwalp->mwa);
        for(int i=0;i<term->num;i++){
            word_delete(term->word_arr[i]);
        }
        term->num=0;
        while(mwalp->next!=NULL){
            Mwalp tt=mwalp->next;
            mwalp->next=mwalp->next->next;
            term=&(tt->mwa);
            for(int i=0;i<term->num;i++){
                word_delete(term->word_arr[i]);
            }
            free(term);
        }
        mwalp->next=NULL;
    }
}











