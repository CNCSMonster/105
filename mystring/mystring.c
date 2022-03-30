#include "mystring.h"


char* mystrcre(void){ //��ÿհ��ַ���
    char* out=(char *)malloc(sizeof(char));
    out[0]='\0';
    return out;
}


char* mystr_read(FILE* target){//���ļ���̬��ȡһ���ַ���������\n�����ļ���ֹ��ֹͣ
    char* out;
    struct mstr{    //�����ַ������ݴ��ȡ���
        char c;
        struct mstr* next;
    }ms_h,*ms_t;
    ms_h.next=NULL;
    ms_t=&ms_h;
    int len=0;
    do{
        int cur=fgetc(target);
        if(cur=='\n'||cur==EOF){
            break;
        }else{
            ms_t->next=(struct mstr*)malloc(sizeof(struct mstr));
            ms_t=ms_t->next;
            ms_t->next=NULL;
            ms_t->c=(char)cur;
            len++;
        }
    }while(1);
    out=(char*)malloc(sizeof(char)*(len+1));
    out[len]='\0';
    ms_t=&ms_h;
    for(int i=0;i<len;i++){

    }
    return out;
}

//��ȡ�ַ�����Ϣ
int mystrlen(char* s){//��ȡ�ַ�������
    if(s==NULL){    //���������ǿ�ָ��
        return -1;
    }
    int len=0;
    while(s[len]!='\0'){//û�ж�����β���žͼ�������ȥ��ֱ��������β���ż�һ���˳�
        len++;
    }
    return len; //�����ַ�������
}

int mystrcmp(char* sa, char* sb){//�Ƚ������ַ����Ƿ���ͬ����ͬ����1�����򷵻�0
    int la=mystrlen(sa);
    int lb=mystrlen(sb);
    if(la!=lb){//�ַ������Ȳ�ͬ�����ַ����϶���ͬ
        return 0;
    }else{
        for(int i=0;i<la;i++){
            if(sa[i]!=sb[i]){//ѭ���Ƚ�ÿ����Ӧλ��ĸ������һ����ĸ��ͬ���ַ�����ͬ
                return 0;
            }
        }
    }
    return 1;//������������û���˳�������˵�������ַ���û�в�ͬ
}



//�ַ�������
char* mystrcut(char*s ,int st,int end){//�и��ָ�����±��st��end���ַ���
    char* out;
    int L=mystrlen(s);
    //�Ƚ�������Ϸ����ж�
    if(st>L-1){    //�ַ�������ΪL,���±����ΪL-1
        //�����ȡ�±�Ŀ�ʼ�������ַ�����ĩβ�±�
        return mystrcre();//�򷵻ؿմ�
    }else if(end>L-1){//��ȡ��ĩβ�±곬�ޣ����ȡ����֮ǰ�Ĳ���
        return mystrcut(s,st,L-1);
    }else{
        out=(char *)malloc(sizeof(char)*(end-st+2));//��st-end�ټ��Ͻ�β'\0'����Ҫ�ַ�������Ϊend-st+2
        out[end-st+1]='\0';
        for(int i=st;i<=end;i++){
            out[i-st]=s[i];
        }
        return out;
    }
}

char** mystrdepart(char*s,char t,int* returnNum){//���ַ�tΪ������ַ�������,���صõ����ַ������飬��ͨ��ָ�봫�ε���ʽ�����ַ��������Ԫ������
    char **out;//��ǰ������Ҫ���ص���
    typedef struct strlist{ //����һ���ַ���������Ϊ��֪���ָ�������ַ��������������Բ������飬����ʹ�ÿ��Զ�̬�ӳ�������
        char* s;
        struct strlist* next;
    }Strlist,*Strlistp;
    Strlist stl_h;//���������洢�ָ�������ַ������ϸ��������ͷ���
    stl_h.next=NULL;//��ʼ����Ԫ���ΪNULL,��ʾû���ַ���������
    Strlistp stl_t=&stl_h;//�������������������������ָ��
    int num=0;//�洢�ָ���ַ�������
    int st=0;//�ָ�Ŀ�ʼ�±�
    int len=mystrlen(s);
    for(int i=0;i<len;i++){
        if(s[i]==t){//��������ضϷ��ţ����ж�֮ǰ��û�п��ԽضϵĲ��֣������ȡ
            if(st==i){  //˵�������ǽض��ַ�������û�п��Խضϵ�����
                st=i+1; //�������
                continue;
            }else{
                //���ǰ���п��Խ�ȡ��������ͨ��stl_tʹ��stl_h����ĩβ�����µĽڵ㣬�ڰ�stl_tָ���������ĩβ
                stl_t->next=(Strlistp)malloc(sizeof(Strlist));
                stl_t->next->s=mystrcut(s,st,i-1);
                stl_t->next->next=NULL;
                stl_t=stl_t->next;
                num++;  //ͬʱ��ȡ�����ַ���������1
                st=i+1;//ͬʱ��ȡ���ָ���µ�λ��
            }
        }
    }
    //��������ѭ�����ܻ���sĩβ�Ĳ���û�м�������
    if(st<len){ //���ѭ�����ȡ��㻹���ַ���s���±귶Χ�ڣ�˵�����ǿ���
        stl_t->next=(Strlistp)malloc(sizeof(Strlist));
        stl_t->next->s=mystrcut(s,st,len-1);
        stl_t->next->next=NULL;
        stl_t=stl_t->next;
        num++;  //ͬʱ��ȡ�����ַ���������1
    }
    *returnNum=num;//�ѵõ��Ľ�ȡ���ַ�������ͨ��ָ��������ݳ�ȥ��returnNumָ���int������
    out=(char **)malloc(sizeof(char *)*num);//ʵ�����ַ��������൱��һά�ַ�ָ������飬�ַ�������Ϊnum������Ҫ��out����num��char*�Ŀռ�
    //���ַ��������е��ַ��������ַ�������
    stl_t=&stl_h;
    for(int i=0;i<num;i++){
        out[i]=stl_t->next->s;  //�������иý���Ķ�Ӧ�ַ�ָ������ý����ַ������Ӧλ��
        Strlistp term=stl_t->next;//��term�ݴ�ò����õ�������ڵ�
        stl_t->next=stl_t->next->next;//�Ѹýڵ��������ȥ��
        free(term); //�ͷŸýڵ����Ŀռ�
    }
    return out;
}

char* mystradd(char* sa,char* sb){//��sb���ӵ�sa�����γ��µ��ַ��������ͷŵ�sa����Ŀռ�
    char *out;
    int la=mystrlen(sa);
    int lb=mystrlen(sb);
    out=(char *)malloc(sizeof(char)*(la+lb+1));
    out[la+lb]='\0';//��β�ȼ��ַ�����β��־��outΪһ���ַ�
    for(int i=0;i<la;i++){  //�Ȱ�a���ַ�����outǰ����
        out[i]=sa[i];
    }
    for(int i=la;i<la+lb;i++){  //�ٰ�b����Ч�ַ���ֵ��out�ĺ󲿷�
        out[i]=sb[i-la];
    }
    free(sa);
    // free(sb);    //����Ҳ���ͷ�sb�Ŀռ�ģ����ǻ����
    return out;
}

char* mystrcpy(char* s){//�����ַ���s����̬����ռ������µ��ַ�������
    char* out;
    int len=mystrlen(s);
    out=(char *)malloc(sizeof(char)*(len+1));
    out[len]='\0';
    for(int i=0;i<len;i++){
        out[i]=s[i];
    }
    return out;
}

//���ַ���ת��Ϊ��������
int mystrtoint(char* s){//���ַ���ת��Ϊ�����������Ǹ�����
    int out=0;
    int i=0;
    while(s[i]!='\0'){//������ÿһλ����
        out=out*10+(s[i]-48);
        i++;
    }
    return out;
}

float mystrtofloat(char* s){//���ַ���ת��ΪС��(�����Ǹ��������),��Ϊû���ر����Ȳ��ߣ����Ա���4λС��
    float out=0;
    int i=0;
    int z_w=0;//������¼�������������ֻ���β������
    while(s[i]!='\0'){
        if(s[i]=='.'){
            z_w=1;
        }else if(z_w==0){
            out=out*10+(s[i]-48);
        }else{
            float L=1;
            for(int k=0;k<z_w;k++){
                L/=10;
            }
            out+=((float)(s[i]-48))*L;
            z_w++;//����¼����β�����ֵ�ʱ��z_w������¼С������˵ڼ�λ
        }
        i++;
    }
    return ((float)((int)(out*1000)))/1000;     //���ر���3λС��(ֱ����ȥ���棬����������)�Ľ�� 
}


char mystrtoc(char* s){//���ַ���ת��Ϊ�ַ�
    return s[0];
}


//�ͷſռ�
void freeStrArr(char** s,int num){//�ͷ��ַ�������Ŀռ�
    for(int i=0;i<num;i++){
        free(s[i]);
    }
    free(s);

}





