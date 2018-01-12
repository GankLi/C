#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<conio.h>

/**********************下为基础数据管理***********************/
struct books{
    char book_name[20];     //书名
    char author_name[20];   //作者
    char price[10];         //价格
    long long borrow;       //借书者身份证
    int id;                 //书的ID
    struct books *next;
}*head_book=NULL;

struct members{
    char account[15];       //账号
    char password[15];      //密码
    char name[15];          //姓名
    long long phone,id;     //电话号码+身份证号
    int sex;               //性别
    int level;              //用户级别
    int cnt;                //所借图书数量
    int borrow[5];          //所借图书
    struct members *next;
}*head_member=NULL;

struct blacklist{
    long long id;
    struct blacklist *next;
}*head_black=NULL;

struct members *creat_members(struct members*,struct members);          //用户链表建立及增加
struct books *creat_books(struct books*,struct books);                  //图书链表建立及增加
struct blacklist *creat_blacklist(struct blacklist*,struct blacklist);  //黑名单链表建立及增加

/**********************下为主要界面***************************/
void staff_list();                                                      //制作人员清单
void interface_login();                                                 //登入界面
void Manager_interface();                                               //管理者界面
void interface_rank0(struct members *);                                 //普通用户界面
void interface_rank1(struct members *);                                 //会员用户界面

/**********************下为用户功能***************************/
void login();                                                           //账号登入
void regis();                                                           //账号注册
void browse_members();                                                  //浏览成员信息及管理
void find_member();                                                     //查找成员信息及管理
void modific_member();                                                  //管理员修改成员信息
void modific_mymessage(struct members *);                               //用户修改自己信息
void find_mymessage(struct members *);                          //用户查看自己信息及修改
void find_mybook(struct members *);                                     //查询本人借阅书籍
void del_member(long long);                                             //删除成员信息
void print_members();                                                   //输出成员信息
void change_rank();                                                     //用户级别修改

/**********************下为黑名单功能*************************/
void add_blacklist();                                                   //加入黑名单
void browse_blacklist();                                                //浏览黑名单
void del_blacklist();                                                   //拉白

/**********************下为图书管理功能***********************/
void browse_manage_books();                                             //浏览图书信息及管理
void find_manage_book();                                                //查询图书信息及管理
void browse_books(struct members *);                                    //用户浏览图书信息
void find_book(struct members *);                                       //用户查询图书信息
void print_books();                                                     //输出图书信息
void add_book();                                                        //管理员添加图书信息
void del_book();                                                        //管理员删除图书信息
void modific_book();                                                    //管理员修改图书信息
void borrow_book(struct members *);                                     //用户借书
void Back_book();                                                       //管理员操作还书


/**********************下为各函数实现*************************/


int main(){
    interface_login();
    return 0;
}

/**********************下为基础数据管理***********************/

//用户链表建立及增加
struct members *creat_members(struct members *head,struct members data){
    struct members *p;
    p=(struct members*)malloc(sizeof(struct members));
    data.next=NULL;
    *p=data;
    if(head!=NULL)p->next=head;
    return p;
}

//图书链表建立及增加
struct books *creat_books(struct books *head,struct books data){
    struct books *p;
    p=(struct books*)malloc(sizeof(struct books));
    data.next=NULL;
    *p=data;
    if(head!=NULL)p->next=head;
    return p;
}

//黑名单链表建立及增加
struct blacklist *creat_blacklist(struct blacklist *head,struct blacklist data){
    struct blacklist *p;
    p=(struct blacklist*)malloc(sizeof(struct blacklist));
    data.next=NULL;
    *p=data;
    if(head!=NULL)p->next=head;
    return p;
}

/**********************下为用户功能***************************/

//账户注册
void regis(){
    int n=1;
    struct members data,r_data,*q_member=NULL;
    while(n){
        int flag=0;
        system("cls");
        printf("请输入账户\n");
        scanf("%s",r_data.account);

        //判断账号是否被注册
        q_member=head_member;
        if(q_member!=NULL){
            while(strcmp(q_member->account,r_data.account)&&q_member->next!=NULL)q_member=q_member->next;
            if(!strcmp(q_member->account,r_data.account))flag=1;
        }

        if(flag){
            system("cls");
            printf("此账号已被注册\n输入0 返回上一级\n否则重新注册\n");
            scanf("%d",&n);
        }
        else{
            while(1){
                printf("请输入密码，长度为6-14\n输入0取消注册\n");
                scanf("%s",data.password);

                if(!strcmp(data.password,"0"))return;

                if(!(strlen(data.password)>5&&strlen(data.password)<15)){
                    memset(data.password,0,sizeof(data.password));
                    printf("不符合要求\n\n");
                }
                else{
                    system("cls");
                    printf("请重新输入密码以验证\n");
                    scanf("%s",r_data.password);
                    if(strcmp(data.password,r_data.password)){
                        printf("2次输入密码不相同\n按0返回上一级\n否则重新注册\n");
                        memset(data.password,0,sizeof(data.password));
                        memset(r_data.password,0,sizeof(r_data.password));
                        scanf("%d",&n);
                        break;
                    }
                    else{
                        printf("两次密码相同\n请按以下顺序输入详细信息\n");
                        printf("姓名\t电话号码\t身份证号码\t性别（女输入0，男输入1）\n");
                        scanf("%s%lld%lld%d",r_data.name,&r_data.phone,&r_data.id,&r_data.sex);
                        r_data.level=0;
                        r_data.cnt=0;

                        //验证身份信息是否被拉黑
                        struct blacklist *q_blacklist;
                        q_blacklist=head_black;
                        if(q_blacklist!=NULL){
                            while(q_blacklist->id!=r_data.id&&q_blacklist->next!=NULL)q_blacklist=q_blacklist->next;
                            if(q_blacklist->id==r_data.id)flag=1;
                        }

                        if(flag){
                            printf("该用户身份已被禁止注册，可找管理员申请注册\n");
                            printf("\n输入任意键返回主菜单…\n");
                            getch();
                            return;
                        }

                        //验证身份证与电话号码是否被使用
                        q_member=head_member;
                        if(q_member!=NULL){
                            while(q_member->phone!=r_data.phone&&q_member->id!=r_data.id&&q_member->next!=NULL)q_member=q_member->next;
                            if(q_member->phone==r_data.phone)flag=1;
                            if(q_member->id==r_data.id)flag=2;
                        }
                        if(flag==1){
                            printf("该电话已被使用\n");
                            printf("\n输入任意键返回主菜单…\n");
                            getch();
                            return;
                        }
                        if(flag==2){
                            printf("该身份证已被使用\n");
                            printf("\n输入任意键返回主菜单…\n");
                            getch();
                            return;
                        }

                        //注册成功存入信息
                        FILE *fp1;
                        fp1=fopen("user.txt","a+");
                        fprintf(fp1,"%s %s %s %lld %lld %d %d %d\n",r_data.account,r_data.password,r_data.name,r_data.phone,r_data.id,r_data.sex,r_data.level,r_data.cnt);
                        head_member=creat_members(head_member,r_data);
                        printf("注册成功\n");
                        fclose(fp1);
                        printf("\n输入任意键返回主菜单…\n");
                        getch();
                        return;
                    }
                }
            }
        }
    }
}

//账号登入
void login(){
    system("cls");
    char l_account[15],l_password[15];
    struct members *q_member=NULL;
    int flag=1;

    printf("请输入你的账号\n");
    scanf("%s",l_account);

    //管理者登入
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
        printf("该账号不存在\n");
        printf("\n输入任意键返回主菜单…\n");
        getch();
        return;
    }
    printf("请输入你的密码\n");
    scanf("%s",l_password);
    if(strcmp(q_member->password,l_password)){
        printf("密码错误\n");
        printf("\n输入任意键返回主菜单…\n");
        getch();
        return;
    }
    if(q_member->level)interface_rank1(q_member);
    else interface_rank0(q_member);
}

//输出成员信息
void print_members(){
    struct members *q_member=head_member;
    if(q_member==NULL){
        return;
    }
    printf("姓名           身份证号码          账号           密码           电话号码       性别 等级 所借图书数量\n");
    while(q_member!=NULL){
        printf("%-15s%-20lld%-15s%-15s%-15lld",q_member->name,q_member->id,q_member->account,q_member->password,q_member->phone);
        if(q_member->sex)printf("男   ");
        else printf("女   ");
        printf("%-5d%-5d\n",q_member->level,q_member->cnt);
        q_member=q_member->next;
    }
}

//管理员修改成员信息
void modific_member(){
    printf("请输入目标身份证\n");
    struct members a_member,*q_member=NULL;
    int flag=1;
    scanf("%lld",&a_member.id);

    q_member=head_member;
    if(q_member!=NULL){
        while(q_member->id!=a_member.id&&q_member->next!=NULL)q_member=q_member->next;
        if(q_member->id==a_member.id)flag=0;
    }
    if(flag){
        printf("暂无此人信息\n");
        printf("\n输入任意键返回上一级…\n");
        getch();
        return;
    }
    a_member=*q_member;
    printf("密码\t姓名\t电话号码\t性别（女输入0，男输入1）\n");
    scanf("%s%s%lld%d",a_member.password,a_member.name,&a_member.phone,&a_member.sex);
    if(!(strlen(a_member.password)>5&&strlen(a_member.password)<15)){
        printf("密码不符合要求\n\n输入任意键返回\n");
        getch();
        return;
    }
    *q_member=a_member;
    if(q_member->phone!=a_member.phone){
        q_member=head_member;
        //验证手机是否被注册
        if(q_member!=NULL){
            while(q_member->phone!=a_member.phone&&q_member->next!=NULL)q_member=q_member->next;
            if(q_member->phone==a_member.phone)flag=1;
        }
    }
    if(flag){
        printf("该电话已被使用\n");
        printf("\n输入任意键返回上一级…\n");
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
    printf("修改成功\n");
    printf("\n输入任意键返回上一级…\n");
    getch();
}

//用户修改自己信息
void modific_mymessage(struct members *q_member){
    struct members a_member;
    int flag=0;
    a_member=*q_member;
    printf("密码\t姓名\t电话号码\t性别（女输入0，男输入1）\n");
    scanf("%s%s%lld%d",a_member.password,a_member.name,&a_member.phone,&a_member.sex);
    if(!(strlen(a_member.password)>5&&strlen(a_member.password)<15)){
        printf("密码不符合要求\n\n输入任意键返回\n");
        getch();
        return;
    }
    *q_member=a_member;

    if(q_member->phone!=a_member.phone){
        q_member=head_member;
        //验证手机是否被注册
        if(q_member!=NULL){
            while(q_member->phone!=a_member.phone&&q_member->next!=NULL)q_member=q_member->next;
            if(q_member->phone==a_member.phone)flag=1;
        }
    }
    if(flag){
        printf("该电话已被使用\n");
        printf("\n输入任意键返回上一级…\n");
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
    printf("修改成功\n");
    printf("\n输入任意键返回上一级…\n");
    getch();
}

//用户查看自己信息及修改
void find_mymessage(struct members *q_member){
    int n=1;
    while(n){
        system("cls");
        printf("姓名           %s\n",q_member->name);
        printf("身份证号码     %lld******\n",q_member->id/1000000);
        printf("账号           %s\n",q_member->account);
        printf("密码           %s\n",q_member->password);
        printf("电话号码       %lld\n",q_member->phone);
        if(q_member->sex)printf("性别           男\n");
        else printf("性别           女\n");
        if(q_member->level)printf("会员用户\n");
        else printf("普通用户\n");
        if(q_member->cnt)printf("所借图书如下\n");
        else printf("暂无借阅图书\n");
        int i=0;
        for(i=0;i<q_member->cnt;i++){
            printf("所借图书如下\n");
            printf("书籍编号   书名                作者                价格\n");
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
        printf("-------------     输入1 修改用户信息          -------------\n");
        printf("-------------     输入0 返回上一级            -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:modific_mymessage(q_member);break;
        }
    }
}

//删除成员信息
void del_member(long long a_id){
    struct members *q_member=NULL,*p_member=head_member;
    while(p_member->next!=NULL&&a_id!=p_member->id){
        q_member=p_member;
        p_member=p_member->next;
    }
    //能到这的必定存在
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

//查找成员信息及管理
void find_member(){
    struct members *q_member=head_member;
    long long f_id;
    printf("请输入查询目标身份证\n");
    scanf("%lld",&f_id);
    int flag=1;
    if(q_member==NULL){
        printf("该用户不存在\n输入任意键继续……\n");
        getch();
        return;
    }
    if(q_member!=NULL){
        while(q_member->id!=f_id&&q_member->next!=NULL)q_member=q_member->next;
        if(q_member->id==f_id)flag=0;
    }
    if(flag){
        printf("该用户不存在\n输入任意键继续……\n");
        getch();
        return;
    }

    int n=1;
    while(n){
        system("cls");
        printf("姓名           %s\n",q_member->name);
        printf("身份证号码     %lld\n",q_member->id);
        printf("账号           %s\n",q_member->account);
        printf("密码           %s\n",q_member->password);
        printf("电话号码       %lld\n",q_member->phone);
        if(q_member->sex)printf("性别           男\n");
        else printf("性别           女\n");
        if(q_member->level)printf("会员用户\n");
        else printf("普通用户\n");
        if(q_member->cnt){
            printf("所借图书如下\n");
            printf("书籍编号   书名                作者                价格\n");
            int i;
            for(i=0;i<q_member->cnt;i++){
                struct books *q_book=head_book;
                while(q_book->id!=q_member->borrow[i]&&q_book->next!=NULL)
                    q_book=q_book->next;
                printf("%-11d%-20s%-20s%-10s\n",q_book->id,q_book->book_name,q_book->author_name,q_book->price);
            }
        }
        else printf("暂无借阅图书\n");
        int i=0;
        for(i=0;i<q_member->cnt;i++){

        }
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     输入1 修改用户信息          -------------\n");
        printf("-------------     输入2 注销用户              -------------\n");
        printf("-------------     输入3 拉黑身份证            -------------\n");
        printf("-------------     输入4 用户级别修改          -------------\n");
        printf("-------------     输入5 还书                  -------------\n");
        printf("-------------     输入0 返回上一级            -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:modific_member();break;
            case 2:{
                long long c;
                printf("请输入用户身份证以确认\n");
                scanf("%lld",&c);
                if(q_member->cnt){
                    printf("图书未完全归，无法删除\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                    break;
                }
                if(c==q_member->id){
                    del_member(q_member->id);
                    printf("删除成功\n");
                    printf("\n输入任意键返回上一级…\n");
                    getch();
                    return;
                }
                else{
                    printf("输入错误\n");
                    printf("\n输入任意键返回…\n");
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

//浏览成员信息及管理
void browse_members(){
    int n=1;
    while(n){
        system("cls");
        print_members();
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    输入1 查询用户信息           -------------\n");
        printf("-------------    输入2 修改用户信息           -------------\n");
        printf("-------------    输入3 注销用户               -------------\n");
        printf("-------------    输入4 拉黑身份证             -------------\n");
        printf("-------------    输入5 用户级别修改           -------------\n");
        printf("-------------    输入0 返回上一级             -------------\n");
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
                printf("请输入用户身份证\n");
                scanf("%lld",&c);

                q_member=head_member;
                if(q_member!=NULL){
                    while(q_member->id!=c&&q_member->next!=NULL)q_member=q_member->next;
                    if(q_member->id==c)flag=1;
                }
                if(flag&&q_member->cnt){
                    printf("图书未完全归，无法删除\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                    break;
                }
                if(flag){
                    del_member(q_member->id);
                    printf("删除成功\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                    break;
                }
                printf("身份证未被注册\n");
                printf("\n输入任意键返回…\n");
                getch();
                break;
            }
            case 4:add_blacklist();break;
            case 5:change_rank();break;
        }
    }
}

//查询本人借阅情况
void find_mybook(struct members *user){
    if(user->cnt){
        printf("所借图书如下\n");
        printf("书籍编号   书名                作者                价格\n");
        int i;
        for(i=0;i<user->cnt;i++){
            struct books *q_book=head_book;
            while(q_book->id!=user->borrow[i]&&q_book->next!=NULL)
            q_book=q_book->next;
            printf("%-11d%-20s%-20s%-10s\n",q_book->id,q_book->book_name,q_book->author_name,q_book->price);
        }
    }
    else printf("暂无借阅图书\n");
    printf("输入任意键返回……\n");
    getch();
}

//用户查询图书信息
void find_book(struct members *user){
    struct books *q_book=head_book;
    char a_book[20];
    printf("请输入书名\n");
    scanf("%s",&a_book);
    int flag=1;
    if(q_book==NULL){
        printf("该书不存在\n输入任意键继续……\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(strcmp(q_book->book_name,a_book)&&q_book->next!=NULL)q_book=q_book->next;
        if(!strcmp(q_book->book_name,a_book))flag=0;
    }
    if(flag){
        printf("该书不存在\n输入任意键继续……\n");
        getch();
        return;
    }

    int n=1;
    while(n){
        system("cls");
        q_book=head_book;
        while(q_book!=NULL){
            if(!strcmp(q_book->book_name,a_book)){
                printf("书籍编号          %d\n",q_book->id);
                printf("书名              %s\n",q_book->book_name);
                printf("作者              %s\n",q_book->author_name);
                printf("价格              %s\n",q_book->price);
                printf("书籍状态          ");
                if(q_book->borrow)printf("借出\n\n");
                else printf("在架\n\n");
            }
            q_book=q_book->next;
        }
        if(user->level==0){
            printf("输入任意键返回……\n");
            getch();
            return;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("-------------     输入1 借书                   -------------\n");
        printf("-------------     输入0 返回上一级             -------------\n");
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:borrow_book(user);break;
        }
    }
}

//用户浏览图书信息
void browse_books(struct members *user){
    int n=1;
    while(n){
        system("cls");
        print_books();
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    输入1 查询图书信息           -------------\n");
        if(user->level)printf("-------------    输入2 借书                   -------------\n");
        printf("-------------    输入0 返回上一级             -------------\n");
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

//用户级别修改
void change_rank(){
    printf("请输入目标身份证\n");
    struct members a_member,*q_member=NULL;
    int flag=1;
    scanf("%lld",&a_member.id);
    //查找用户
    q_member=head_member;
    if(q_member!=NULL){
        while(q_member->id!=a_member.id&&q_member->next!=NULL)q_member=q_member->next;
        if(q_member->id==a_member.id)flag=0;
    }
    if(flag){
        printf("暂无此人信息\n");
        printf("\n输入任意键返回上一级…\n");
        getch();
        return;
    }

    //修改用户信息
    a_member=*q_member;
    printf("普通用户输入0,会员用户输入1\n");
    scanf("%d",&a_member.level);
    if(a_member.level!=0)a_member.level=1;
    *q_member=a_member;

    //数据修改
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
    printf("修改成功\n");
    printf("\n输入任意键返回上一级…\n");
    getch();
}


/**********************下为黑名单功能*************************/

//加入黑名单
void add_blacklist(){
    printf("请输入目标身份证\n");
    struct blacklist a_id;
    int flag=0;
    scanf("%lld",&a_id.id);
    //验证身份信息是否被拉黑
    struct blacklist *q_blacklist;
    q_blacklist=head_black;
    if(q_blacklist!=NULL){
    while(q_blacklist->id!=a_id.id&&q_blacklist->next!=NULL)q_blacklist=q_blacklist->next;
        if(q_blacklist->id==a_id.id)flag=1;
    }
    if(flag){
        printf("该身份证已被拉黑\n");
        printf("\n输入任意键返回上一级…\n");
        getch();
        return;
    }
    //如果该身份证被注册则删除
    struct members *q_member=head_member;
    if(q_member!=NULL){
        if(q_member!=NULL){
            while(q_member->id!=a_id.id&&q_member->next!=NULL)q_member=q_member->next;
            if(q_member->id==a_id.id)flag=1;
        }
        if(flag){
            if(q_member->cnt){
                printf("目标图书未完全归还，无法执行\n");
                printf("\n输入任意键返回…\n");
                getch();
                return;
            }
            del_member(a_id.id);
        }
    }
    //存入信息
    FILE *fp1;
    fp1=fopen("blacklist.txt","a+");
    fprintf(fp1,"%lld\n",a_id.id);
    fclose(fp1);
    head_black=creat_blacklist(head_black,a_id);
    printf("拉黑成功\n");
    printf("\n输入任意键返回…\n");
    getch();
}

//浏览黑名单
void browse_blacklist(){
    int n=1;
    struct blacklist *q_blacklist=head_black;
    while(n){
        q_blacklist=head_black;
        system("cls");
        if(q_blacklist==NULL)printf("暂无数据\n\n");
        else{
            printf("身份证号码如下：\n");
            while(q_blacklist!=NULL){
                printf("%lld\n",q_blacklist->id);
                q_blacklist=q_blacklist->next;
            }
        }
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    输入1 添加身份证             -------------\n");
        printf("-------------    输入2 删除身份证             -------------\n");
        printf("-------------    输入0 返回上一级             -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        scanf("%d",&n);
        switch(n){
            case 1:add_blacklist();break;
            case 2:del_blacklist();break;
        }
    }
}

//拉白
void del_blacklist(){
    long long a_id;
    struct blacklist *q_blacklist=NULL,*p_blacklist=head_black;
    printf("请输入目标身份证\n");
    scanf("%lld",&a_id);
    if(p_blacklist==NULL){
        printf("暂无数据\n输入任意键返回……\n");
        getch();
        return;
    }
    while(a_id!=p_blacklist->id&&p_blacklist->next!=NULL){
        q_blacklist=p_blacklist;
        p_blacklist=p_blacklist->next;
    }
    if(a_id!=p_blacklist->id){
        printf("该用户未被进入黑名单\n输入任意键返回……\n");
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
    printf("删除成功\n输入任意键返回……\n");
    getch();
}


/**********************下为图书管理功能***********************/

//添加书籍
void add_book(){
    system("cls");
    struct books data,*q_book=head_book;
    int flag,n=1;
    while(n){
        flag=0;
        printf("请输入图书编号,输入0返回\n");
        scanf("%d",&data.id);
        if(data.id==0)return;
        if(flag){
            printf("该编号已被使用\n输入0返回，否则重新输入\n");
            scanf("%d",&n);
            if(n==0)return;
        }
        else break;
    }
    printf("请输入书名\n");
    scanf("%s",data.book_name);
    printf("请输入作者姓名\n");
    scanf("%s",data.author_name);
    while(n){
        flag=0;
        printf("请输入价格\n");
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
            printf("这真的是价格？\n输入0返回菜单,否则重新输入\n");
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
    printf("注册成功\n");
    fclose(fp1);
    printf("\n输入任意键返回菜单…\n");
    getch();
    return;
}

//输出图书信息
void print_books(){
    struct books *q_book=head_book;
    if(q_book==NULL){
        printf("暂无图书\n\n");
        return;
    }
    printf("书籍编号   书名                作者                价格      是否在架\n");
    while(q_book!=NULL){
        printf("%-11d%-20s%-20s%-10s",q_book->id,q_book->book_name,q_book->author_name,q_book->price);
        if(q_book->borrow)printf("否\n");
        else printf("是\n");
        q_book=q_book->next;
    }
}

//管理员修改图书信息
void modific_book(){
    struct books a_book,*q_book=head_book;
    int flag=1;
    printf("请输入目标图书编号\n");
    scanf("%d",&a_book.id);
    if(q_book!=NULL){
        while(q_book->id!=a_book.id&&q_book->next!=NULL)q_book=q_book->next;
        if(q_book->id==a_book.id)flag=0;
    }
    if(flag){
        printf("暂无该图书信息\n");
        printf("\n输入任意键返回…\n");
        getch();
        return;
    }
    a_book=*q_book;
    printf("请输入修改信息\n书名\t作者姓名\t价格\n");
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
            printf("这真的是价格？\n输入0取消修改,否则重新输入\n");
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
    printf("修改成功\n");
    printf("\n输入任意键返回上一级…\n");
    getch();
}

//管理员删除图书信息
void del_book(){
    int a_id;
    printf("输入目标图书编号\n");
    scanf("%d",&a_id);
    struct books *q_book=NULL,*p_book=head_book;
    while(p_book->next!=NULL&&a_id!=p_book->id){
        q_book=p_book;
        p_book=p_book->next;
    }
    if(p_book->id!=a_id){
        printf("书籍不存在\n输入任意键返回\n");
        getch();
        return;
    }
    if(p_book->borrow){
        printf("书籍被借出无法删除\n输入任意键返回\n");
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
    printf("删除成功\n输入任意键返回\n");
    getch();
}

//浏览图书信息及管理
void browse_manage_books(){
    int n=1;
    while(n){
        system("cls");
        print_books();
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    输入1 查询图书信息           -------------\n");
        printf("-------------    输入2 修改图书信息           -------------\n");
        printf("-------------    输入3 添加图书               -------------\n");
        printf("-------------    输入4 删除图书               -------------\n");
        printf("-------------    输入5 还书                   -------------\n");
        printf("-------------    输入0 返回上一级             -------------\n");
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

//查询图书信息及管理
void find_manage_book(){
    struct books *q_book=head_book;
    char a_book[20];
    printf("请输入书名\n");
    scanf("%s",&a_book);
    int flag=1;
    if(q_book==NULL){
        printf("该书不存在\n输入任意键继续……\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(strcmp(q_book->book_name,a_book)&&q_book->next!=NULL)q_book=q_book->next;
        if(!strcmp(q_book->book_name,a_book))flag=0;
    }
    if(flag){
        printf("该书不存在\n输入任意键继续……\n");
        getch();
        return;
    }

    int n=1;
    while(n){
        system("cls");
        q_book=head_book;
        while(q_book!=NULL){
            if(!strcmp(q_book->book_name,a_book)){
                printf("书籍编号          %d\n",q_book->id);
                printf("书名              %s\n",q_book->book_name);
                printf("作者              %s\n",q_book->author_name);
                printf("价格              %s\n",q_book->price);
                printf("书籍状态          ");
                if(q_book->borrow)printf("%lld\n\n",q_book->borrow);
                else printf("在架\n\n");
            }
            q_book=q_book->next;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("-------------     输入1 查看用户信息           -------------\n");
        printf("-------------     输入2 修改图书信息           -------------\n");
        printf("-------------     输入3 添加图书               -------------\n");
        printf("-------------     输入4 删除图书               -------------\n");
        printf("-------------     输入5 还书                   -------------\n");
        printf("-------------     输入0 返回上一级             -------------\n");
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

//根据书籍编号还书
void Back_book(){
    int a_id;
    struct books *q_book=head_book;
    printf("请输入目标图书的编号\n");
    scanf("%d",&a_id);
    int flag=1;
    if(q_book==NULL){
        printf("该书不存在\n输入任意键返回……\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(q_book->id!=a_id&&q_book->next!=NULL)q_book=q_book->next;
        if(q_book->id==a_id)flag=0;
    }
    if(flag){
        printf("该书不存在\n输入任意键返回……\n");
        getch();
        return;
    }
    if(q_book->borrow==0){
        printf("该书未被借出\n输入任意键返回……\n");
        getch();
        return;
    }
    struct members *q_member=head_member;
    //找到借书者并修改数据
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

    //修改用户信息
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

    //修改图书信息
    q_book=head_book;
    fp1=fopen("book.txt","w");
    q_book=head_book;
    while(q_book!=NULL){
        fprintf(fp1,"%s %s %s %lld %d\n",q_book->book_name,q_book->author_name,q_book->price,q_book->borrow,q_book->id);
        q_book=q_book->next;
    }
    fclose(fp1);
    printf("还书成功\n输入任意键返回……\n");
    getch();
}

//用户借书
void borrow_book(struct members *user){
    int a_id;
    struct books *q_book=head_book;
    if(user->cnt>4){
        printf("用户所借书数量已达上限\n输入任意键返回……\n");
        getch();
        return;
    }
    printf("请输入目标图书的编号\n");
    scanf("%d",&a_id);

    int flag=1;
    if(q_book==NULL){
        printf("该书不存在\n输入任意键返回……\n");
        getch();
        return;
    }
    if(q_book!=NULL){
        while(q_book->id!=a_id&&q_book->next!=NULL)q_book=q_book->next;
        if(q_book->id==a_id)flag=0;
    }
    if(flag){
        printf("该书不存在\n输入任意键返回……\n");
        getch();
        return;
    }
    if(q_book->borrow){
        printf("该书已被借出\n输入任意键返回……\n");
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
    printf("借阅成功\n输入任意键返回……\n");
    getch();
    return;
}


/**********************下为主要界面***************************/

//主界面
void interface_login(){

    int n=1;

    //读入用户数据
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

    //读入黑名单
    struct blacklist black_data;
    fp1=fopen("blacklist.txt","a+");
    while(fscanf(fp1,"%lld\n",&black_data.id)!=EOF){
        head_black=creat_blacklist(head_black,black_data);
    }
    fclose(fp1);

    //读入图书数据
    struct books b_data;
    fp1=fopen("book.txt","a+");
    while(fscanf(fp1,"%s%s%s%lld%d\n",b_data.book_name,b_data.author_name,b_data.price,&b_data.borrow,&b_data.id)!=EOF){
        head_book=creat_books(head_book,b_data);
    }
    fclose(fp1);


    while(n){
        system("cls");
        printf("-------------欢迎进入图书管理系统 o(*≧▽≦)ツ-------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     输入1 账号登入              -------------\n");
        printf("-------------     输入2 账号注册              -------------\n");
        printf("-------------     输入3 观看制作信息          -------------\n");
        printf("-------------     输入0 关闭系统              -------------\n");
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

//管理者界面
void Manager_interface(){
    int n=1;
    while(n){
        system("cls");
        printf("-------------欢迎进入管理者界面o(*≧▽≦)ツ   -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------    输入1 浏览图书信息           -------------\n");
        printf("-------------    输入2 查询图书信息           -------------\n");
        printf("-------------    输入3 添加图书信息           -------------\n");
        printf("-------------    输入4 修改图书信息           -------------\n");
        printf("-------------    输入5 删除图书信息           -------------\n");
        printf("-------------    输入6 还书                   -------------\n");
        printf("-------------    输入7 浏览用户信息           -------------\n");
        printf("-------------    输入8 查询用户信息           -------------\n");
        printf("-------------    输入9 修改用户信息           -------------\n");
        printf("-------------    输入10注销用户信息           -------------\n");
        printf("-------------    输入11浏览黑名单             -------------\n");
        printf("-------------    输入12拉黑身份证             -------------\n");
        printf("-------------    输入13拉白身份证             -------------\n");
        printf("-------------    输入14用户级别修改           -------------\n");
        printf("-------------    输入0 返回上一级             -------------\n");
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
                printf("请输入用户身份证\n");
                scanf("%lld",&c);
                q_member=head_member;
                if(q_member!=NULL){
                    while(q_member->id!=c&&q_member->next!=NULL)q_member=q_member->next;
                    if(q_member->id==c)flag=1;
                }
                if(flag&&q_member->cnt){
                    printf("图书未完全归，无法删除\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                    break;
                }
                if(flag){
                    del_member(q_member->id);
                    printf("删除成功\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                    return;
                }
                else{
                    printf("身份证未被注册\n");
                    printf("\n输入任意键返回…\n");
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

//rank0界面
void interface_rank0(struct members *user){
    int n=1;
    while(n){
        system("cls");
        printf("-------------     很高兴为你服务o(*≧▽≦)ツ  -------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     输入1 图书信息浏览          -------------\n");
        printf("-------------     输入2 图书信息查询          -------------\n");
        printf("-------------     输入3 查询本人信息          -------------\n");
        printf("-------------     输入4 修改本人信息          -------------\n");
        printf("-------------     输入5 注销账户              -------------\n");
        printf("-------------     输入0 返回上一级            -------------\n");
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
                printf("请输入用户身份证以确认\n");
                if(user->cnt){
                    printf("图书未完全归，无法删除\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                    break;
                }
                scanf("%lld",&c);
                if(c==user->id){
                    del_member(user->id);
                    printf("删除成功\n");
                    printf("\n输入任意键返回上一级…\n");
                    getch();
                    return;
                }
                else{
                    printf("输入错误\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                }
                break;
            }
        }
    }
}

//rank1界面
void interface_rank1(struct members *user){
    int n=1;
    while(n){
        system("cls");
        printf("-------------     很高兴为你服务o(*≧▽≦)ツ     ----------\n");
        printf("-----------------------------------------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("-------------     输入1 图书信息浏览          -------------\n");
        printf("-------------     输入2 图书信息查询          -------------\n");
        printf("-------------     输入3 借书                  -------------\n");
        printf("-------------     输入4 查询本人借阅情况      -------------\n");
        printf("-------------     输入5 查询本人信息          -------------\n");
        printf("-------------     输入6 修改个人信息          -------------\n");
        printf("-------------     输入7 注销账户              -------------\n");
        printf("-------------     输入0 返回上一级            -------------\n");
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
                printf("请输入用户身份证以确认\n");
                scanf("%lld",&c);
                if(user->cnt){
                    printf("图书未完全归，无法删除\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                    break;
                }
                if(c==user->id){
                    del_member(user->id);
                    printf("删除成功\n");
                    printf("\n输入任意键返回上一级…\n");
                    getch();
                    return;
                }
                else{
                    printf("输入错误\n");
                    printf("\n输入任意键返回…\n");
                    getch();
                }
                break;
            }
        }
    }
}

//制作者清单
void staff_list(){
    system("cls");
    printf("-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("--------------Include the following members----------------\n");
    printf("--------------           wzy               ----------------\n");
    printf("--------------           ToRe              ----------------\n");
    printf("-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------\n\n\n");
    printf("\n输入任意键返回主菜单…\n");
    getch();
}
