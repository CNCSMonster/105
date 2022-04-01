#include "mystring.h"


char* mystrcre(void){ //��ÿհ��ַ���
    char* out=(char *)malloc(sizeof(char));
    out[0]='\0';
    return out;
}




/*���ļ���̬��ȡһ���ַ���������\n�����ļ���ֹ��ֹͣ
�����ȡ����Ϊ�գ�����NULL,���򷵻��ַ���ָ��
*/
char* mystr_read(FILE* target){
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
    if(len==0){
        ms_t=&ms_h;
        for(int i=0;i<len;i++){
            struct mstr* term=ms_t->next;
            ms_t->next=ms_t->next->next;
            free(term);
        }
        return NULL;
    }
    out=(char*)malloc(sizeof(char)*(len+1));
    out[len]='\0';
    ms_t=&ms_h;
    for(int i=0;i<len;i++){
        out[i]=ms_t->next->c;
        struct mstr* term=ms_t->next;
        ms_t->next=ms_t->next->next;
        free(term);
    }
    return out;
}


//�ַ��������������


//���ַ������ܺ������ָ������,safe_file_put
void mystr_sfput(FILE* target,char* s){
    //������Ҫ�õ��ļ�ȫ�ֶ���ļ��ܲ���
    s=mystrcpy(s);  //Ϊ�˷�ֹ��ԭ�ַ�������Ӱ�죬����
    int len=strlen(s);
    for(int i=0;i<len;i++){
        if(((int)s[i])%2==0){
            //��ĸ��Ӧascll����ż���������code
            s[i]=s[i]+MSTR_CODE;
            s[i]=~s[i];
        }else{
            //�������ascll�������������ȥcode
            s[i]=s[i]-MSTR_CODE;
            s[i]=~s[i];
        }
    }
    fprintf(target,"%s",s);
}

/*�Ѽ��ܵ��ַ�����ָ�������ȡ�����
�����ؽ��ܺ���ַ���
*/
char* mystr_sget(FILE* target){
    char* s=mystr_read(target);
    int len=strlen(s);
    for(int i=0;i<len;i++){
        if(((int)s[i])%2==0){
            //��ĸ��Ӧascll����ż���������code
            s[i]=~s[i];
            s[i]=s[i]-MSTR_CODE;
        }else{
            //�������ascll�������������ȥcode
            s[i]=~s[i];
            s[i]=s[i]+MSTR_CODE;
        }
    }
    return s;
}



//��һ��������ת��Ϊһ���ַ���
char *inttostr(int num){
    struct myints{
        char c;
        struct myints* next;
    }mh,*mt,*mhp;
    mh.next=NULL;
    mhp=NULL;
    int len;
    if(num<0){
        num=-num;
        mt->next=(struct myints*)malloc(sizeof(struct myints));
        mt=mt->next;
        mt->next=NULL;
        mt->c='-';
        mhp=mt;
        len++;
    }else if(num==0){
        return mystrcpy("0");
    }
    while(num!=0){
        int cur=num%10;
        num=(num-cur)/10;
        mt=(struct myints*)malloc(sizeof(struct myints));
        mt->next=mh.next;
        mt->c=cur+48;
        mh.next=mt;
        len++;
    }
    char* out=(char*)malloc(sizeof(char)*(len+1));
    out[len]='\0';
    if(mhp!=NULL&&mhp->c=='-'){
        out[0]='-';
        mt=&mh;
        free(mhp);
        for(int i=1;i<len;i++){
            out[i]=mt->next->c;
            mhp=mt->next;
            mt->next=mt->next->next;
            free(mhp);
        }
    }else{
        mt=&mh;
        for(int i=0;i<len;i++){
            out[i]=mt->next->c;
            mhp=mt->next;
            mt->next=mt->next->next;
            free(mhp);
        }
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

//�Ƚ������ַ����Ƿ���ͬ����ͬ����1�����򷵻�0
int mystreq(char* sa, char* sb){
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

//�ж�����ַ����ǲ���Ӣ���ַ���,����Ƿ���1�����򷵻�0
int mystr_if_e(char* s){
    int len=mystrlen(s);    //���������strlen����
    for(int i=0;i<len;i++){
        s[i]=s[i]<97?s[i]+32:s[i];
        if(s[i]<97||s[i]>122){
            return 0;
        }
    }
    return 1;
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

//��sb���ӵ�sa�����γ��µ��ַ��������ͷŵ�sa����Ŀռ�
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

/*�ж�һ���ַ����ܷ�ת��Ϊ����
����ܣ�����1�����򷵻�0
*/
int str_ifint(char* s){
    if(s==NULL){
        return 0;
    }
    int len=mystrlen(s);    //mystrlen������strlen����
    if(len==0){
        return 0;
    }else if(len==1&&(s[0]<48||s[0]>57)){
        return 0;
    }
    if(s[0]!='-'&&(s[0]<48||s[0]>57)){
        return 0;
    }
    for(int i=1;i<len;i++){
        if(s[i]<48||s[i]>57){
            return 0;
        }
    }
    return 1;
}


//���ַ���ת��Ϊ����,��������ַ������Ϸ����������0
int mystrtoint(char* s){
    //�滻������atoi
    if(!str_ifint(s)){
        return 0;
    }
    int out=0;
    if(s[0]=='-'){
        int i=1;
        while(s[i]!='\0'){//������ÿһλ����
            out=out*10+(s[i]-48);
            i++;
        }
        out=-out;
    }else{
        int i=0;
        while(s[i]!='\0'){//������ÿһλ����
            out=out*10+(s[i]-48);
            i++;
        }
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





