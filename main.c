#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<conio.h>

/**********************��Ϊ�������ݹ���***********************/
struct books{
    char book_name[20];     //����
    char author_name[20];   //����
    char price[10];         //�۸�
    long long borrow;       //���������֤
    int id;                 //���ID
    struct books *next;
}*head_book=NULL;

struct members{
    char account[15];       //�˺�
    char password[15];      //����
    char name[15];          //����
    long long phone,id;     //�绰����+���֤��
    int sex;               //�Ա�
    int level;              //�û�����
    int cnt;                //����ͼ������
    int borrow[5];          //����ͼ��
    struct members *next;
}*head_member=NULL;

struct blacklist{
    long long id;
    struct blacklist *next;
}*head_black=NULL;

struct members *creat_members(struct members*,struct members);          //�û�������������
struct books *creat_books(struct books*,struct books);                  //ͼ��������������
struct blacklist *creat_blacklist(struct blacklist*,struct blacklist);  //������������������

/**********************��Ϊ��Ҫ����***************************/
void staff_list();                                                      //������Ա�嵥
void interface_login();                                                 //�������
void Manager_interface();                                               //�����߽���
void interface_rank0(struct members *);                                 //��ͨ�û�����
void interface_rank1(struct members *);                                 //��Ա�û�����

/**********************��Ϊ�û�����***************************/
void login();                                                           //�˺ŵ���
void regis();                                                           //�˺�ע��
void browse_members();                                                  //�����Ա��Ϣ������
void find_member();                                                     //���ҳ�Ա��Ϣ������
void modific_member();                                                  //����Ա�޸ĳ�Ա��Ϣ
void modific_mymessage(struct members *);                               //�û��޸��Լ���Ϣ
void find_mymessage(struct members *);                          //�û��鿴�Լ���Ϣ���޸�
void find_mybook(struct members *);                                     //��ѯ���˽����鼮
void del_member(long long);                                             //ɾ����Ա��Ϣ
void print_members();                                                   //�����Ա��Ϣ
void change_rank();                                                     //�û������޸�

/**********************��Ϊ����������*************************/
void add_blacklist();                                                   //���������
void browse_blacklist();                                                //���������
void del_blacklist();                                                   //����

/**********************��Ϊͼ�������***********************/
void browse_manage_books();                                             //���ͼ����Ϣ������
void find_manage_book();                                                //��ѯͼ����Ϣ������
void browse_books(struct members *);                                    //�û����ͼ����Ϣ
void find_book(struct members *);                                       //�û���ѯͼ����Ϣ
void print_books();                                                     //���ͼ����Ϣ
void add_book();                                                        //����Ա���ͼ����Ϣ
void del_book();                                                        //����Աɾ��ͼ����Ϣ
void modific_book();                                                    //����Ա�޸�ͼ����Ϣ
void borrow_book(struct members *);                                     //�û�����
void Back_book();                                                       //����Ա��������


/**********************��Ϊ������ʵ��*************************/


int main(){
    interface_login();
    return 0;
}

/**********************��Ϊ�������ݹ���***********************/

//�û�������������
struct members *creat_members(struct members *head,struct members data){
    struct members *p;
    p=(struct members*)malloc(sizeof(struct members));
    data.next=NULL;
    *p=data;
    if(head!=NULL)p->next=head;
    return p;
}

//ͼ��������������
struct books *creat_books(struct books *head,struct books data){
    struct books *p;
    p=(struct books*)malloc(sizeof(struct books));
    data.next=NULL;
    *p=data;
    if(head!=NULL)p->next=head;
    return p;
}

//������������������
struct blacklist *creat_blacklist(struct blacklist *head,struct blacklist data){
    struct blacklist *p;
    p=(struct blacklist*)malloc(sizeof(struct blacklist));
    data.next=NULL;
    *p=data;
    if(head!=NULL)p->next=head;
    return p;
}

/**********************��Ϊ�û�����***************************/

//�˻�ע��
void regis(){
    int n=1;
    struct members data,r_data,*q_member=NULL;
    while(n){
        int flag=0;
        system("cls");
        printf("�������˻�\n");
        scanf("%s",r_data.account);

        //�ж��˺��Ƿ�ע��
        q_member=head_member;
        if(q_member!=NULL){
            while(strcmp(q_member->account,r_data.account)&&q_member->next!=NULL)q_member=q_member->next;
            if(!strcmp(q_member->account,r_data.account))flag=1;
        }

        if(flag){
            system("cls");
            printf("���˺��ѱ�ע��\n����0 ������һ��\n��������ע��\n");
            scanf("%d",&n);
        }
        else{
            while(1){
                printf("���������룬����Ϊ6-14\n����0ȡ��ע��\n");
                scanf("%s",data.password);

                if(!strcmp(data.password,"0"))return;

                if(!(strlen(data.password)>5&&strlen(data.password)<15)){
                    memset(data.password,0,sizeof(data.password));
                    printf("������Ҫ��\n\n");
                }
                else{
                    system("cls");
                    printf("������������������֤\n");
                    scanf("%s",r_data.password);
                    if(strcmp(data.password,r_data.password)){
                        printf("2���������벻��ͬ\n��0������һ��\n��������ע��\n");
                        memset(data.password,0,sizeof(data.password));
                        memset(r_data.password,0,sizeof(r_data.password));
                        scanf("%d",&n);
                        break;
                    }
                    else{
                        printf("����������ͬ\n�밴����˳��������ϸ��Ϣ\n");
                        printf("����\t�绰����\t���֤����\t�Ա�Ů����0��������1��\n");
                        scanf("%s%lld%lld%d",r_data.name,&r_data.phone,&r_data.id,&r_data.sex);
                        r_data.level=0;
                        r_data.cnt=0;

                        //��֤�����Ϣ�Ƿ�����
                        struct blacklist *q_blacklist;
                        q_blacklist=head_black;
                        if(q_blacklist!=NULL){
                            while(q_blacklist->id!=r_data.id&&q_blacklist->next!=NULL)q_blacklist=q_blacklist->next;
                            if(q_blacklist->id==r_data.id)flag=1;
                        }

                        if(flag){
                            printf("���û�����ѱ���ֹע�ᣬ���ҹ���Ա����ע��\n");
                            printf("\n����������������˵���\n");
                            getch();
                            return;
                        }

                        //��֤���֤��绰�����Ƿ�ʹ��
                        q_member=head_member;
                        if(q_member!=NULL){
                            while(q_member->phone!=r_data.phone&&q_member->id!=r_data.id&&q_member->next!=NULL)q_member=q_member->next;
                            if(q_member->phone==r_data.phone)flag=1;
                            if(q_member->id==r_data.id)flag=2;
                        }
                        if(flag==1){
                            printf("�õ绰�ѱ�ʹ��\n");
                            printf("\n����������������˵���\n");
                            getch();
                            return;
                        }
                        if(flag==2){
                            printf("�����֤�ѱ�ʹ��\n");
                            printf("\n����������������˵���\n");
                            getch();
                            return;
                        }

                        //ע��ɹ�������Ϣ
                        FILE *fp1;
                        fp1=fopen("user.txt","a+");
                        fprintf(fp1,"%s %s %s %lld %lld %d %d %d\n",r_data.account,r_data.password,r_data.name,r_data.phone,r_data.id,r_data.sex,r_data.level,r_data.cnt);
                        head_member=creat_members(head_member,r_data);
                        printf("ע��ɹ�\n");
                        fclose(fp1);
                        printf("\n����������������˵���\n");
                        getch();
                        return;
                    }
                }
            }
        }
    }
}

//�˺ŵ���
void login(){
    system("cls");
    char l_account[15],l_password[15];
    struct members *q_member=NULL;
    int flag=1;

    printf("����������˺�\n");
    scanf("%s",l_account);

    //�����ߵ���
    if(strcmp(l_account,"bokuwasinnsekainokamitonaru")==0){
        Manager_interface();
        return;
    }
    q_member=head_member;
    if(q_member!=NULL){
        while(strcmp(q_member->account,l_account)&&q_member->next!=NULL)q_member=q_member->next;
        if(!strcmp(q_member->account,l_account))flag=0;
    }
    if(flag){
        printf("���˺Ų�����\n");
        printf("\n����������������˵���\n");
        getch();
        return;
    }
    printf("�������������\n");
    scanf("%s",l_password);
    if(strcmp(q_member->password,l_password)){
        printf("�������\n");
        printf("\n����������������˵���\n");
        getch();
        return;
    }
    if(q_member->level)interface_rank1(q_member);
    else interface_rank0(q_member);
}

//�����Ա��Ϣ
void print_members(){
    struct members *q_member=head_member;
    if(q_member==NULL){
        return;
    }
    printf("����           ���֤����          �˺�           ����           �绰����       �Ա� �ȼ� ����ͼ������\n");
    while(q_member!=NULL){
        printf("%-15s%-20lld%-15s%-15s%-15lld",q_member->name,q_member->id,q_member->account,q_member->password,q_member->phone);
        if(q_member->sex)printf("��   ");
        else printf("Ů   ");
        printf("%-5d%-5d\n",q_member->level,q_member->cnt);
        q_member=q_member->next;
    }
}

//����Ա�޸ĳ�Ա��Ϣ
void modific_member(){
    printf("������Ŀ�����֤\n");
    struct members a_member,*q_member=NULL;
    int flag=1;
    scanf("%lld",&a_member.id);

    q_member=head_member;
    if(q_member!=NULL){
        while(q_member->id!=a_member.id&&q_member->next!=NULL)q_member=q_member->next;
        if(q_member->id==a_member.id)flag=0;
    }
    if(flag){
        printf("���޴�����Ϣ\n");
        printf("\n���������������һ����\n");
        getch();
        return;
    }
    a_member=*q_member;
    printf("����\t����\t�绰����\t�Ա�Ů����0��������1��\n");
    scanf("%s%s%lld%d",a_member.password,a_member.name,&a_member.phone,&a_member.sex);
    if(!(strlen(a_member.password)>5&&strlen(a_member.password)<15)){
        printf("���벻����Ҫ��\n\n�������������\n");
        getch();
        return;
    }
    *q_member=a_member;
    if(q_member->phone!=a_member.phone){
        q_member=head_member;
        //��֤�ֻ��Ƿ�ע��
        if(q_member!=NULL){
            while(q_member->phone!=a_member.phone&&q_member->next!=NULL)q_member=q_member->next;
            if(q_member->phone==a_member.phone)flag=1;
        }
    }
    if(flag){
        printf("�õ绰�ѱ�ʹ��\n");
        printf("\n���������������һ����\n");
        getch();
        return;
    }

    FILE *fp1;
    fp1=fopen("user.txt","w");
    q_member=head_member;
    while(q_member!=NULL){
        int i;
        fprintf(fp1,"%s %s %s %lld %lld %d %d %d",q_member->account,q_member->password,q_member->name,q_member->phone,q_member->id,q_member->sex,q_member->level,q_member->cnt);
        for(i=0;i<q_member->cnt;i++)fprintf(fp1," %d",q_member->borrow[i]);
        fprintf(fp1,"\n");
        q_member=q_member->next;
    }
    fclose(fp1);
    printf("�޸ĳɹ�\n");
    printf("\n���������������һ����\n");
    getch();
}

//�û��޸��Լ���Ϣ
void modific_mymessage(struct members *q_member){
    struct members a_member;
    int flag=0;
    a_member=*q_member;
    printf("����\t����\t�绰����\t�Ա�Ů����0��������1��\n");
    scanf("%s%s%lld%d",a_member.password,a_member.name,&a_member.phone,&a_member.sex);
    if(!(strlen(a_member.password)>5&&strlen(a_member.password)<15)){
        printf("���벻����Ҫ��\n\n�������������\n");
        getch();
        return;
    }
    *q_member=a_member;

    if(q_member->phone!=a_member.phone){
        q_member=head_member;
        //��֤�ֻ��Ƿ�ע��
        if(q_member!=NULL){
            while(q_member->phone!=a_member.phone&&q_member->next!=NULL)q_member=q_member->next;
            if(q_member->phone==a_member.phone)flag=1;
        }
    }
    if(flag){
        printf("�õ绰�ѱ�ʹ��\n");
        printf("\n���������������һ����\n");
        getch();
        return;
    }
    FILE *fp1;
    fp1=fopen("user.txt","w");
    q_member=head_member;
    while(q_member!=NULL){
        int i;
        fprintf(fp1,"%s %s %s %lld %lld %d %d %d",q_member->account,q_member->password,q_member->name,q_member->phone,q_member->id,q_member->sex,q_member->level,q_member->cnt);
        for(i=0;i<q_member->cnt;i++)fprintf(fp1," %d",q_member->borrow[i]);
        fprintf(fp1,"\n");
        q_member=q_member->next;
    }
    fclose(fp1);
    printf("�޸ĳɹ�\n");
    printf("\n���������������һ����\n");
    getch();
}

//�û��鿴�Լ���Ϣ���޸�
void find_mymessage(struct members *q_member){
    int n=1;
    while(n){
        system("cls");
        printf("����           %s\n",q_member->name);
        printf("���֤����     %lld******\n",q_member->id/1000000);
        printf("�˺�           %s\n",q_member->account);
        printf("����           %s\n",q_member->password);
        printf("�绰����       %lld\n",q_member->phone);
        if(q_member->sex)printf("�Ա�           ��\n");
        else printf("�Ա�           Ů\n");
        if(q_member->level)printf("��Ա�û�\n");
        else printf("��ͨ�û�\n");
        if(q_member->cnt)printf("����ͼ������\n");
        else printf("���޽���ͼ��\n");
        int i=0;
        for(i=0;i<q_member->cnt;i++){
            printf("����ͼ������\n");
            printf("�鼮���   ����                ����                �۸�\n");
            int i;
            for(i=0;i<q_member->cnt;i++){
                struct books *q_book=head_book;
                while(q_book->id!=q_member->borrow[i]&&q_book->next!=NULL)
                    q_book=q_book->next;
                printf("%-11d%-20s%-20s%-10s\n",q_book->id,q_book->book_name,q_book->author_name,q_book->price);
            }
        }
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     ����1 �޸��û���Ϣ          -------------\n");
        printf("-------------     ����0 ������һ��            -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:modific_mymessage(q_member);break;
        }
    }
}

//ɾ����Ա��Ϣ
void del_member(long long a_id){
    struct members *q_member=NULL,*p_member=head_member;
    while(p_member->next!=NULL&&a_id!=p_member->id){
        q_member=p_member;
        p_member=p_member->next;
    }
    //�ܵ���ıض�����
    if(q_member==NULL)head_member=p_member->next;
    else q_member->next=p_member->next;
    free(p_member);
    FILE *fp1;
    int i;
    fp1=fopen("user.txt","w");
    q_member=head_member;
    while(q_member!=NULL){
        fprintf(fp1,"%s %s %s %lld %lld %d %d %d",q_member->account,q_member->password,q_member->name,q_member->phone,q_member->id,q_member->sex,q_member->level,q_member->cnt);
        for(i=0;i<q_member->cnt;i++)fprintf(fp1," %d",q_member->borrow[i]);
        fprintf(fp1,"\n");
        q_member=q_member->next;
    }
    fclose(fp1);
}

//���ҳ�Ա��Ϣ������
void find_member(){
    struct members *q_member=head_member;
    long long f_id;
    printf("�������ѯĿ�����֤\n");
    scanf("%lld",&f_id);
    int flag=1;
    if(q_member==NULL){
        printf("���û�������\n�����������������\n");
        getch();
        return;
    }
    if(q_member!=NULL){
        while(q_member->id!=f_id&&q_member->next!=NULL)q_member=q_member->next;
        if(q_member->id==f_id)flag=0;
    }
    if(flag){
        printf("���û�������\n�����������������\n");
        getch();
        return;
    }

    int n=1;
    while(n){
        system("cls");
        printf("����           %s\n",q_member->name);
        printf("���֤����     %lld\n",q_member->id);
        printf("�˺�           %s\n",q_member->account);
        printf("����           %s\n",q_member->password);
        printf("�绰����       %lld\n",q_member->phone);
        if(q_member->sex)printf("�Ա�           ��\n");
        else printf("�Ա�           Ů\n");
        if(q_member->level)printf("��Ա�û�\n");
        else printf("��ͨ�û�\n");
        if(q_member->cnt){
            printf("����ͼ������\n");
            printf("�鼮���   ����                ����                �۸�\n");
            int i;
            for(i=0;i<q_member->cnt;i++){
                struct books *q_book=head_book;
                while(q_book->id!=q_member->borrow[i]&&q_book->next!=NULL)
                    q_book=q_book->next;
                printf("%-11d%-20s%-20s%-10s\n",q_book->id,q_book->book_name,q_book->author_name,q_book->price);
            }
        }
        else printf("���޽���ͼ��\n");
        int i=0;
        for(i=0;i<q_member->cnt;i++){

        }
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     ����1 �޸��û���Ϣ          -------------\n");
        printf("-------------     ����2 ע���û�              -------------\n");
        printf("-------------     ����3 �������֤            -------------\n");
        printf("-------------     ����4 �û������޸�          -------------\n");
        printf("-------------     ����5 ����                  -------------\n");
        printf("-------------     ����0 ������һ��            -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:modific_member();break;
            case 2:{
                long long c;
                printf("�������û����֤��ȷ��\n");
                scanf("%lld",&c);
                if(q_member->cnt){
                    printf("ͼ��δ��ȫ�飬�޷�ɾ��\n");
                    printf("\n������������ء�\n");
                    getch();
                    break;
                }
                if(c==q_member->id){
                    del_member(q_member->id);
                    printf("ɾ���ɹ�\n");
                    printf("\n���������������һ����\n");
                    getch();
                    return;
                }
                else{
                    printf("�������\n");
                    printf("\n������������ء�\n");
                    getch();
                }
                break;
            }
            case 3:add_blacklist();return;
            case 4:change_rank();break;
            case 5:Back_book();break;
        }
    }
}

//�����Ա��Ϣ������
void browse_members(){
    int n=1;
    while(n){
        system("cls");
        print_members();
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    ����1 ��ѯ�û���Ϣ           -------------\n");
        printf("-------------    ����2 �޸��û���Ϣ           -------------\n");
        printf("-------------    ����3 ע���û�               -------------\n");
        printf("-------------    ����4 �������֤             -------------\n");
        printf("-------------    ����5 �û������޸�           -------------\n");
        printf("-------------    ����0 ������һ��             -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:find_member();break;
            case 2:modific_member();break;
            case 3:{
                struct members *q_member;
                long long c;
                int flag=0;
                printf("�������û����֤\n");
                scanf("%lld",&c);

                q_member=head_member;
                if(q_member!=NULL){
                    while(q_member->id!=c&&q_member->next!=NULL)q_member=q_member->next;
                    if(q_member->id==c)flag=1;
                }
                if(flag&&q_member->cnt){
                    printf("ͼ��δ��ȫ�飬�޷�ɾ��\n");
                    printf("\n������������ء�\n");
                    getch();
                    break;
                }
                if(flag){
                    del_member(q_member->id);
                    printf("ɾ���ɹ�\n");
                    printf("\n������������ء�\n");
                    getch();
                    break;
                }
                printf("���֤δ��ע��\n");
                printf("\n������������ء�\n");
                getch();
                break;
            }
            case 4:add_blacklist();break;
            case 5:change_rank();break;
        }
    }
}

//��ѯ���˽������
void find_mybook(struct members *user){
    if(user->cnt){
        printf("����ͼ������\n");
        printf("�鼮���   ����                ����                �۸�\n");
        int i;
        for(i=0;i<user->cnt;i++){
            struct books *q_book=head_book;
            while(q_book->id!=user->borrow[i]&&q_book->next!=NULL)
            q_book=q_book->next;
            printf("%-11d%-20s%-20s%-10s\n",q_book->id,q_book->book_name,q_book->author_name,q_book->price);
        }
    }
    else printf("���޽���ͼ��\n");
    printf("������������ء���\n");
    getch();
}

//�û���ѯͼ����Ϣ
void find_book(struct members *user){
    struct books *q_book=head_book;
    char a_book[20];
    printf("����������\n");
    scanf("%s",&a_book);
    int flag=1;
    if(q_book==NULL){
        printf("���鲻����\n�����������������\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(strcmp(q_book->book_name,a_book)&&q_book->next!=NULL)q_book=q_book->next;
        if(!strcmp(q_book->book_name,a_book))flag=0;
    }
    if(flag){
        printf("���鲻����\n�����������������\n");
        getch();
        return;
    }

    int n=1;
    while(n){
        system("cls");
        q_book=head_book;
        while(q_book!=NULL){
            if(!strcmp(q_book->book_name,a_book)){
                printf("�鼮���          %d\n",q_book->id);
                printf("����              %s\n",q_book->book_name);
                printf("����              %s\n",q_book->author_name);
                printf("�۸�              %s\n",q_book->price);
                printf("�鼮״̬          ");
                if(q_book->borrow)printf("���\n\n");
                else printf("�ڼ�\n\n");
            }
            q_book=q_book->next;
        }
        if(user->level==0){
            printf("������������ء���\n");
            getch();
            return;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("-------------     ����1 ����                   -------------\n");
        printf("-------------     ����0 ������һ��             -------------\n");
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:borrow_book(user);break;
        }
    }
}

//�û����ͼ����Ϣ
void browse_books(struct members *user){
    int n=1;
    while(n){
        system("cls");
        print_books();
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    ����1 ��ѯͼ����Ϣ           -------------\n");
        if(user->level)printf("-------------    ����2 ����                   -------------\n");
        printf("-------------    ����0 ������һ��             -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:find_book(user);break;
            case 2:{
                if(user->level)borrow_book(user);
                break;
            }
        }
    }
}

//�û������޸�
void change_rank(){
    printf("������Ŀ�����֤\n");
    struct members a_member,*q_member=NULL;
    int flag=1;
    scanf("%lld",&a_member.id);
    //�����û�
    q_member=head_member;
    if(q_member!=NULL){
        while(q_member->id!=a_member.id&&q_member->next!=NULL)q_member=q_member->next;
        if(q_member->id==a_member.id)flag=0;
    }
    if(flag){
        printf("���޴�����Ϣ\n");
        printf("\n���������������һ����\n");
        getch();
        return;
    }

    //�޸��û���Ϣ
    a_member=*q_member;
    printf("��ͨ�û�����0,��Ա�û�����1\n");
    scanf("%d",&a_member.level);
    if(a_member.level!=0)a_member.level=1;
    *q_member=a_member;

    //�����޸�
    FILE *fp1;
    fp1=fopen("user.txt","w");
    q_member=head_member;
    while(q_member!=NULL){
        int i;
        fprintf(fp1,"%s %s %s %lld %lld %d %d %d",q_member->account,q_member->password,q_member->name,q_member->phone,q_member->id,q_member->sex,q_member->level,q_member->cnt);
        for(i=0;i<q_member->cnt;i++)fprintf(fp1," %d",q_member->borrow[i]);
        fprintf(fp1,"\n");
        q_member=q_member->next;
    }
    fclose(fp1);
    printf("�޸ĳɹ�\n");
    printf("\n���������������һ����\n");
    getch();
}


/**********************��Ϊ����������*************************/

//���������
void add_blacklist(){
    printf("������Ŀ�����֤\n");
    struct blacklist a_id;
    int flag=0;
    scanf("%lld",&a_id.id);
    //��֤�����Ϣ�Ƿ�����
    struct blacklist *q_blacklist;
    q_blacklist=head_black;
    if(q_blacklist!=NULL){
    while(q_blacklist->id!=a_id.id&&q_blacklist->next!=NULL)q_blacklist=q_blacklist->next;
        if(q_blacklist->id==a_id.id)flag=1;
    }
    if(flag){
        printf("�����֤�ѱ�����\n");
        printf("\n���������������һ����\n");
        getch();
        return;
    }
    //��������֤��ע����ɾ��
    struct members *q_member=head_member;
    if(q_member!=NULL){
        if(q_member!=NULL){
            while(q_member->id!=a_id.id&&q_member->next!=NULL)q_member=q_member->next;
            if(q_member->id==a_id.id)flag=1;
        }
        if(flag){
            if(q_member->cnt){
                printf("Ŀ��ͼ��δ��ȫ�黹���޷�ִ��\n");
                printf("\n������������ء�\n");
                getch();
                return;
            }
            del_member(a_id.id);
        }
    }
    //������Ϣ
    FILE *fp1;
    fp1=fopen("blacklist.txt","a+");
    fprintf(fp1,"%lld\n",a_id.id);
    fclose(fp1);
    head_black=creat_blacklist(head_black,a_id);
    printf("���ڳɹ�\n");
    printf("\n������������ء�\n");
    getch();
}

//���������
void browse_blacklist(){
    int n=1;
    struct blacklist *q_blacklist=head_black;
    while(n){
        q_blacklist=head_black;
        system("cls");
        if(q_blacklist==NULL)printf("��������\n\n");
        else{
            printf("���֤�������£�\n");
            while(q_blacklist!=NULL){
                printf("%lld\n",q_blacklist->id);
                q_blacklist=q_blacklist->next;
            }
        }
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    ����1 ������֤             -------------\n");
        printf("-------------    ����2 ɾ�����֤             -------------\n");
        printf("-------------    ����0 ������һ��             -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:add_blacklist();break;
            case 2:del_blacklist();break;
        }
    }
}

//����
void del_blacklist(){
    long long a_id;
    struct blacklist *q_blacklist=NULL,*p_blacklist=head_black;
    printf("������Ŀ�����֤\n");
    scanf("%lld",&a_id);
    if(p_blacklist==NULL){
        printf("��������\n������������ء���\n");
        getch();
        return;
    }
    while(a_id!=p_blacklist->id&&p_blacklist->next!=NULL){
        q_blacklist=p_blacklist;
        p_blacklist=p_blacklist->next;
    }
    if(a_id!=p_blacklist->id){
        printf("���û�δ�����������\n������������ء���\n");
        getch();
        return;
    }
    if(q_blacklist==NULL)head_black=p_blacklist->next;
    else q_blacklist->next=p_blacklist->next;
    free(p_blacklist);

    FILE *fp1;
    fp1=fopen("blacklist.txt","w");
    q_blacklist=head_black;
    while(q_blacklist!=NULL){
        fprintf(fp1,"%lld\n",q_blacklist->id);
        q_blacklist=q_blacklist->next;
    }
    fclose(fp1);
    printf("ɾ���ɹ�\n������������ء���\n");
    getch();
}


/**********************��Ϊͼ�������***********************/

//����鼮
void add_book(){
    system("cls");
    struct books data,*q_book=head_book;
    int flag,n=1;
    while(n){
        flag=0;
        printf("������ͼ����,����0����\n");
        scanf("%d",&data.id);
        if(data.id==0)return;
        if(flag){
            printf("�ñ���ѱ�ʹ��\n����0���أ�������������\n");
            scanf("%d",&n);
            if(n==0)return;
        }
        else break;
    }
    printf("����������\n");
    scanf("%s",data.book_name);
    printf("��������������\n");
    scanf("%s",data.author_name);
    while(n){
        flag=0;
        printf("������۸�\n");
        scanf("%s",data.price);
        int len=strlen(data.price),i,cnt=0;
        if(data.price[0]=='.')flag=1;
        if(data.price[len-1]=='.')flag=1;
        for(i=0;i<len;i++){
            if(data.price[i]=='.')cnt++;
            if((data.price[i]<'0'||data.price[i]>'9')&&data.price[i]!='.')flag=1;
        }
        if(cnt>1)flag=1;
        if(flag){
            printf("������Ǽ۸�\n����0���ز˵�,������������\n");
            scanf("%d",&n);
            if(n==0)return;
        }
        else break;
    }
    data.borrow=0;
    head_book=creat_books(head_book,data);
    FILE *fp1;
    fp1=fopen("book.txt","a+");
    fprintf(fp1,"%s %s %s %lld %d\n",data.book_name,data.author_name,data.price,data.borrow,data.id);
    printf("ע��ɹ�\n");
    fclose(fp1);
    printf("\n������������ز˵���\n");
    getch();
    return;
}

//���ͼ����Ϣ
void print_books(){
    struct books *q_book=head_book;
    if(q_book==NULL){
        printf("����ͼ��\n\n");
        return;
    }
    printf("�鼮���   ����                ����                �۸�      �Ƿ��ڼ�\n");
    while(q_book!=NULL){
        printf("%-11d%-20s%-20s%-10s",q_book->id,q_book->book_name,q_book->author_name,q_book->price);
        if(q_book->borrow)printf("��\n");
        else printf("��\n");
        q_book=q_book->next;
    }
}

//����Ա�޸�ͼ����Ϣ
void modific_book(){
    struct books a_book,*q_book=head_book;
    int flag=1;
    printf("������Ŀ��ͼ����\n");
    scanf("%d",&a_book.id);
    if(q_book!=NULL){
        while(q_book->id!=a_book.id&&q_book->next!=NULL)q_book=q_book->next;
        if(q_book->id==a_book.id)flag=0;
    }
    if(flag){
        printf("���޸�ͼ����Ϣ\n");
        printf("\n������������ء�\n");
        getch();
        return;
    }
    a_book=*q_book;
    printf("�������޸���Ϣ\n����\t��������\t�۸�\n");
    int n=1;
    while(n){
        flag=0;
        scanf("%s %s %s",a_book.book_name,a_book.author_name,a_book.price);
        int len=strlen(a_book.price),i,cnt=0;
        if(a_book.price[0]=='.')flag=1;
        if(a_book.price[len-1]=='.')flag=1;
        for(i=0;i<len;i++){
            if(a_book.price[i]=='.')cnt++;
            if((a_book.price[i]<'0'||a_book.price[i]>'9')&&a_book.price[i]!='.')flag=1;
        }
        if(cnt>1)flag=1;
        if(flag){
            printf("������Ǽ۸�\n����0ȡ���޸�,������������\n");
            scanf("%d",&n);
            if(n==0)return;
        }
        else break;
    }
    *q_book=a_book;
    FILE *fp1;
    q_book=head_book;
    fp1=fopen("book.txt","w");
    while(q_book!=NULL){
        fprintf(fp1,"%s %s %s %lld %d\n",q_book->book_name,q_book->author_name,q_book->price,q_book->borrow,q_book->id);
        q_book=q_book->next;
    }
    fclose(fp1);
    printf("�޸ĳɹ�\n");
    printf("\n���������������һ����\n");
    getch();
}

//����Աɾ��ͼ����Ϣ
void del_book(){
    int a_id;
    printf("����Ŀ��ͼ����\n");
    scanf("%d",&a_id);
    struct books *q_book=NULL,*p_book=head_book;
    while(p_book->next!=NULL&&a_id!=p_book->id){
        q_book=p_book;
        p_book=p_book->next;
    }
    if(p_book->id!=a_id){
        printf("�鼮������\n�������������\n");
        getch();
        return;
    }
    if(p_book->borrow){
        printf("�鼮������޷�ɾ��\n�������������\n");
        getch();
        return;
    }
    if(q_book==NULL)head_book=p_book->next;
    else q_book->next=p_book->next;
    free(p_book);
    FILE *fp1;
    fp1=fopen("book.txt","w");
    q_book=head_book;
    while(q_book!=NULL){
        fprintf(fp1,"%s %s %s %lld %d\n",q_book->book_name,q_book->author_name,q_book->price,q_book->borrow,q_book->id);
        q_book=q_book->next;
    }
    fclose(fp1);
    printf("ɾ���ɹ�\n�������������\n");
    getch();
}

//���ͼ����Ϣ������
void browse_manage_books(){
    int n=1;
    while(n){
        system("cls");
        print_books();
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    ����1 ��ѯͼ����Ϣ           -------------\n");
        printf("-------------    ����2 �޸�ͼ����Ϣ           -------------\n");
        printf("-------------    ����3 ���ͼ��               -------------\n");
        printf("-------------    ����4 ɾ��ͼ��               -------------\n");
        printf("-------------    ����5 ����                   -------------\n");
        printf("-------------    ����0 ������һ��             -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:find_manage_book();break;
            case 2:modific_book();break;
            case 3:add_book();break;
            case 4:del_book();break;
            case 5:Back_book();break;
        }
    }
}

//��ѯͼ����Ϣ������
void find_manage_book(){
    struct books *q_book=head_book;
    char a_book[20];
    printf("����������\n");
    scanf("%s",&a_book);
    int flag=1;
    if(q_book==NULL){
        printf("���鲻����\n�����������������\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(strcmp(q_book->book_name,a_book)&&q_book->next!=NULL)q_book=q_book->next;
        if(!strcmp(q_book->book_name,a_book))flag=0;
    }
    if(flag){
        printf("���鲻����\n�����������������\n");
        getch();
        return;
    }

    int n=1;
    while(n){
        system("cls");
        q_book=head_book;
        while(q_book!=NULL){
            if(!strcmp(q_book->book_name,a_book)){
                printf("�鼮���          %d\n",q_book->id);
                printf("����              %s\n",q_book->book_name);
                printf("����              %s\n",q_book->author_name);
                printf("�۸�              %s\n",q_book->price);
                printf("�鼮״̬          ");
                if(q_book->borrow)printf("%lld\n\n",q_book->borrow);
                else printf("�ڼ�\n\n");
            }
            q_book=q_book->next;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("-------------     ����1 �鿴�û���Ϣ           -------------\n");
        printf("-------------     ����2 �޸�ͼ����Ϣ           -------------\n");
        printf("-------------     ����3 ���ͼ��               -------------\n");
        printf("-------------     ����4 ɾ��ͼ��               -------------\n");
        printf("-------------     ����5 ����                   -------------\n");
        printf("-------------     ����0 ������һ��             -------------\n");
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:find_member();break;
            case 2:modific_book();break;
            case 3:add_book();break;
            case 4:del_book();break;
            case 5:Back_book();break;
        }
    }
}

//�����鼮��Ż���
void Back_book(){
    int a_id;
    struct books *q_book=head_book;
    printf("������Ŀ��ͼ��ı��\n");
    scanf("%d",&a_id);
    int flag=1;
    if(q_book==NULL){
        printf("���鲻����\n������������ء���\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(q_book->id!=a_id&&q_book->next!=NULL)q_book=q_book->next;
        if(q_book->id==a_id)flag=0;
    }
    if(flag){
        printf("���鲻����\n������������ء���\n");
        getch();
        return;
    }
    if(q_book->borrow==0){
        printf("����δ�����\n������������ء���\n");
        getch();
        return;
    }
    struct members *q_member=head_member;
    //�ҵ������߲��޸�����
    while(q_member->next!=NULL){
        int i;
        for(i=0;i<q_member->cnt;i++){
            if(q_member->borrow[i]==q_book->id){
                q_member->borrow[i]=0;
                flag=1;
            }
        }
        if(flag)break;
        q_member=q_member->next;
    }
    q_member->cnt--;
    q_book->borrow=0;
    FILE *fp1=NULL;

    //�޸��û���Ϣ
    q_member=head_member;
    fp1=fopen("user.txt","w");
    while(q_member!=NULL){
        int i;
        fprintf(fp1,"%s %s %s %lld %lld %d %d %d",q_member->account,q_member->password,q_member->name,q_member->phone,q_member->id,q_member->sex,q_member->level,q_member->cnt);
        for(i=0;i<q_member->cnt+1;i++)
            if(q_member->borrow[i]!=0)fprintf(fp1," %d",q_member->borrow[i]);
        fprintf(fp1,"\n");
        q_member=q_member->next;
    }
    fclose(fp1);

    //�޸�ͼ����Ϣ
    q_book=head_book;
    fp1=fopen("book.txt","w");
    q_book=head_book;
    while(q_book!=NULL){
        fprintf(fp1,"%s %s %s %lld %d\n",q_book->book_name,q_book->author_name,q_book->price,q_book->borrow,q_book->id);
        q_book=q_book->next;
    }
    fclose(fp1);
    printf("����ɹ�\n������������ء���\n");
    getch();
}

//�û�����
void borrow_book(struct members *user){
    int a_id;
    struct books *q_book=head_book;
    if(user->cnt>4){
        printf("�û������������Ѵ�����\n������������ء���\n");
        getch();
        return;
    }
    printf("������Ŀ��ͼ��ı��\n");
    scanf("%d",&a_id);

    int flag=1;
    if(q_book==NULL){
        printf("���鲻����\n������������ء���\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(q_book->id!=a_id&&q_book->next!=NULL)q_book=q_book->next;
        if(q_book->id==a_id)flag=0;
    }
    if(flag){
        printf("���鲻����\n������������ء���\n");
        getch();
        return;
    }
    if(q_book->borrow){
        printf("�����ѱ����\n������������ء���\n");
        getch();
        return;
    }
    user->borrow[user->cnt]=q_book->id;
    user->cnt++;
    q_book->borrow=user->id;

    FILE *fp1=NULL;
    user=head_member;
    fp1=fopen("user.txt","w");
    while(user!=NULL){
        int i;
        fprintf(fp1,"%s %s %s %lld %lld %d %d %d",user->account,user->password,user->name,user->phone,user->id,user->sex,user->level,user->cnt);
        for(i=0;i<user->cnt;i++)fprintf(fp1," %d",user->borrow[i]);
        fprintf(fp1,"\n");
        user=user->next;
    }
    fclose(fp1);

    q_book=head_book;
    fp1=fopen("book.txt","w");
    q_book=head_book;
    while(q_book!=NULL){
        fprintf(fp1,"%s %s %s %lld %d\n",q_book->book_name,q_book->author_name,q_book->price,q_book->borrow,q_book->id);
        q_book=q_book->next;
    }
    fclose(fp1);
    printf("���ĳɹ�\n������������ء���\n");
    getch();
    return;
}


/**********************��Ϊ��Ҫ����***************************/

//������
void interface_login(){

    int n=1;

    //�����û�����
    struct members m_data;
    FILE *fp1;
    fp1=fopen("user.txt","a+");
    while(fscanf(fp1,"%s%s%s%lld%lld%d%d%d\n",m_data.account,m_data.password,m_data.name,&m_data.phone,&m_data.id,&m_data.sex,&m_data.level,&m_data.cnt)!=EOF){
        int i;
        for(i=0;i<5;i++)m_data.borrow[i]=0;
        for(i=0;i<m_data.cnt;i++)
            fscanf(fp1,"%d",&m_data.borrow[i]);
        head_member=creat_members(head_member,m_data);
    }
    fclose(fp1);

    //���������
    struct blacklist black_data;
    fp1=fopen("blacklist.txt","a+");
    while(fscanf(fp1,"%lld\n",&black_data.id)!=EOF){
        head_black=creat_blacklist(head_black,black_data);
    }
    fclose(fp1);

    //����ͼ������
    struct books b_data;
    fp1=fopen("book.txt","a+");
    while(fscanf(fp1,"%s%s%s%lld%d\n",b_data.book_name,b_data.author_name,b_data.price,&b_data.borrow,&b_data.id)!=EOF){
        head_book=creat_books(head_book,b_data);
    }
    fclose(fp1);


    while(n){
        system("cls");
        printf("-------------��ӭ����ͼ�����ϵͳ o(*�R���Q)��-------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     ����1 �˺ŵ���              -------------\n");
        printf("-------------     ����2 �˺�ע��              -------------\n");
        printf("-------------     ����3 �ۿ�������Ϣ          -------------\n");
        printf("-------------     ����0 �ر�ϵͳ              -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:login();break;
            case 2:regis();break;
            case 3:staff_list();break;
        }
    }
}

//�����߽���
void Manager_interface(){
    int n=1;
    while(n){
        system("cls");
        printf("-------------��ӭ��������߽���o(*�R���Q)��   -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    ����1 ���ͼ����Ϣ           -------------\n");
        printf("-------------    ����2 ��ѯͼ����Ϣ           -------------\n");
        printf("-------------    ����3 ���ͼ����Ϣ           -------------\n");
        printf("-------------    ����4 �޸�ͼ����Ϣ           -------------\n");
        printf("-------------    ����5 ɾ��ͼ����Ϣ           -------------\n");
        printf("-------------    ����6 ����                   -------------\n");
        printf("-------------    ����7 ����û���Ϣ           -------------\n");
        printf("-------------    ����8 ��ѯ�û���Ϣ           -------------\n");
        printf("-------------    ����9 �޸��û���Ϣ           -------------\n");
        printf("-------------    ����10ע���û���Ϣ           -------------\n");
        printf("-------------    ����11���������             -------------\n");
        printf("-------------    ����12�������֤             -------------\n");
        printf("-------------    ����13�������֤             -------------\n");
        printf("-------------    ����14�û������޸�           -------------\n");
        printf("-------------    ����0 ������һ��             -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:browse_manage_books();break;
            case 2:find_manage_book();break;
            case 3:add_book();break;
            case 4:modific_book();break;
            case 5:del_book();break;
            case 6:Back_book();break;
            case 7:browse_members();break;
            case 8:find_member();break;
            case 9:modific_member();break;
            case 10:{
                long long c;
                struct members *q_member=NULL;
                int flag=0;
                printf("�������û����֤\n");
                scanf("%lld",&c);
                q_member=head_member;
                if(q_member!=NULL){
                    while(q_member->id!=c&&q_member->next!=NULL)q_member=q_member->next;
                    if(q_member->id==c)flag=1;
                }
                if(flag&&q_member->cnt){
                    printf("ͼ��δ��ȫ�飬�޷�ɾ��\n");
                    printf("\n������������ء�\n");
                    getch();
                    break;
                }
                if(flag){
                    del_member(q_member->id);
                    printf("ɾ���ɹ�\n");
                    printf("\n������������ء�\n");
                    getch();
                    return;
                }
                else{
                    printf("���֤δ��ע��\n");
                    printf("\n������������ء�\n");
                    getch();
                }
                break;
            }
            case 11:browse_blacklist();break;
            case 12:add_blacklist();break;
            case 13:del_blacklist();break;
            case 14:change_rank();break;
        }
    }
}

//rank0����
void interface_rank0(struct members *user){
    int n=1;
    while(n){
        system("cls");
        printf("-------------     �ܸ���Ϊ�����o(*�R���Q)��  -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     ����1 ͼ����Ϣ���          -------------\n");
        printf("-------------     ����2 ͼ����Ϣ��ѯ          -------------\n");
        printf("-------------     ����3 ��ѯ������Ϣ          -------------\n");
        printf("-------------     ����4 �޸ı�����Ϣ          -------------\n");
        printf("-------------     ����5 ע���˻�              -------------\n");
        printf("-------------     ����0 ������һ��            -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:browse_books(user);break;
            case 2:find_book(user);break;
            case 3:find_mymessage(user);break;
            case 4:modific_mymessage(user);break;
            case 5:{
                long long c;
                printf("�������û����֤��ȷ��\n");
                if(user->cnt){
                    printf("ͼ��δ��ȫ�飬�޷�ɾ��\n");
                    printf("\n������������ء�\n");
                    getch();
                    break;
                }
                scanf("%lld",&c);
                if(c==user->id){
                    del_member(user->id);
                    printf("ɾ���ɹ�\n");
                    printf("\n���������������һ����\n");
                    getch();
                    return;
                }
                else{
                    printf("�������\n");
                    printf("\n������������ء�\n");
                    getch();
                }
                break;
            }
        }
    }
}

//rank1����
void interface_rank1(struct members *user){
    int n=1;
    while(n){
        system("cls");
        printf("-------------     �ܸ���Ϊ�����o(*�R���Q)��     ----------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     ����1 ͼ����Ϣ���          -------------\n");
        printf("-------------     ����2 ͼ����Ϣ��ѯ          -------------\n");
        printf("-------------     ����3 ����                  -------------\n");
        printf("-------------     ����4 ��ѯ���˽������      -------------\n");
        printf("-------------     ����5 ��ѯ������Ϣ          -------------\n");
        printf("-------------     ����6 �޸ĸ�����Ϣ          -------------\n");
        printf("-------------     ����7 ע���˻�              -------------\n");
        printf("-------------     ����0 ������һ��            -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:browse_books(user);break;
            case 2:find_book(user);break;
            case 3:borrow_book(user);break;
            case 4:find_mybook(user);break;
            case 5:find_mymessage(user);break;
            case 6:modific_mymessage(user);break;
            case 7:{
                long long c;
                printf("�������û����֤��ȷ��\n");
                scanf("%lld",&c);
                if(user->cnt){
                    printf("ͼ��δ��ȫ�飬�޷�ɾ��\n");
                    printf("\n������������ء�\n");
                    getch();
                    break;
                }
                if(c==user->id){
                    del_member(user->id);
                    printf("ɾ���ɹ�\n");
                    printf("\n���������������һ����\n");
                    getch();
                    return;
                }
                else{
                    printf("�������\n");
                    printf("\n������������ء�\n");
                    getch();
                }
                break;
            }
        }
    }
}

//�������嵥
void staff_list(){
    system("cls");
    printf("-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("--------------Include the following members----------------\n");
    printf("--------------           wzy               ----------------\n");
    printf("--------------           ToRe              ----------------\n");
    printf("-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------\n\n\n");
    printf("\n����������������˵���\n");
    getch();
}
