#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>//用于调出系统时间（自带函数）

typedef struct VIP//会员信息
{
    char Name[100];//姓名
    char PhoneNumber[100];//电话号码
    int ID;//ID
    int Year;//办卡日期（年）
    int Month;//办卡日期（月）
    int Day;//办卡日期（日）
    int Birth_Year;//生日（年）
    int Birth_Month;//生日（月）
    int Birth_Day;//生日（日）
    int Level;//会员等级
    char Passwords[10];//密码
    int Balance;//余额
    int allin;//总存入
    int allout;//总支出
    int dealyear[100000];//交易年份
    int dealmonth[100000];//
    int dealday[100000];
    int dealhour[100000];
    int dealminute[100000];
    int dealsecond[100000];
    int dealmoney[100000];//交易金额
    int statement[10];//状态（挂失）
    int daddMoney;
    int u;
    struct VIP *next;//可以理解为用来指向下一个结构体元素（会比较经常用到
}VIP;

void getInput(struct VIP *vip);//录入会员信息
void addVIP(struct VIP **library);//插入新的会员信息
void printLibrary(struct VIP *library);//打印会员信息（全部）
void printVIP(struct VIP *vip);//打印会员信息（单个）
void deleteVIP(struct VIP **library,struct VIP *vip);//删除会员信息
void searchVIP(struct VIP **library);//查找会员信息
void saveVIP(struct VIP *library);//保存VIP信息到文件（全部）
void readVIP(struct VIP **library);//读取文件中的会员信息（全部）
void menuVIP(struct VIP **library,struct VIP *vip);
void menuWorkers(struct VIP **library);
void sortVIP(struct VIP *library);
void consumptionVIP(struct VIP *vip);//消费函数
void savemoneyVIP(struct VIP *vip);
void find_expense_calendar(struct VIP *vip);//消费查找

void menuWorkers(struct VIP **library)
{
    int i;
    while(1)
    {
        printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       ~~~~神秘领域~~~~      *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       1.信息整理            *\n\
                                       *       2.打印全部会员信息    *\n\
                                       *       3.退出系统            *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
               \n\
                                       请选择：");
        scanf("%d",&i);
        if(i==1)
        {
            system("clear");
            sortVIP(*library);
        }
        if(i==2)
        {
            system("clear");
            printLibrary(*library);
        }
        if(i==3)
        {
            break;
        }
    }
}

void menuVIP(struct VIP **library,struct VIP *vip)
{
    int j;
    int ch;
    system("clear");
    while(1)
    {
        printf("\n\
               \n\
               \n\
               \n\
               \n\
                                                                      \n\
                                              欢迎回来，%s            \n\
                                                                      \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       1.会员信息查询        *\n\
                                       *       2.会员续费            *\n\
                                       *       3.会员消费            *\n\
                                       *       4.消费查询            *\n\
                                       *       5.挂失                *\n\
                                       *       6.退卡                *\n\
                                       *       7.退出系统            *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
               \n\
                                       请选择：",vip->Name);

        scanf("%d",&j);
        if(j==1)
        {
            system("clear");
            printVIP(vip);
            system("clear");
        }
        if(j==2)
        {
            system("clear");
            savemoneyVIP(vip);
        }
        if(j==3)
        {
            system("clear");
            consumptionVIP(vip);
        }
        if(j==4)
        {
            system("clear");
            find_expense_calendar(vip);
        }
        if(j==6)
        {
            system("clear");
            printf("真的要离开吗:(\n（按0确定，按任意键退出）\n");
            ch=getch();
            if(ch=='0')
            {
		char *c;
                c = getpass("\n那再见喽:(\n");
                deleteVIP(library,vip);
                break;
            }
            else
            {
                system("clear");
                printf("明智的选择:)\n");
                system("clear");
            }
        }
        if(j==7)
        {
            saveVIP(*library);
            break;
        }
    }
    system("clear");
}

void getInput(struct VIP *vip)//录入会员信息
{
    int i;
    char *passwords1,*passwords2;//不同功用的密码
    time_t timep;//用于调出系统时间（自带函数）
    struct tm *p;//用于调出系统时间（自带函数）
    time(&timep);//用于调出系统时间（自带函数）
    p=gmtime(&timep);//用于调出系统时间（自带函数）
    vip->Level=0;

    for (i=0;i<25;i++)
    {
        printf("*");
    }
    printf("\n");
    printf("    欢迎加入大家庭！    ");
    printf("\n");
    for (i=0;i<25;i++)
    {
        printf("*");
    }
    printf("\n");

    printf("请输入姓名：");
    scanf("%s",vip->Name);//存姓名
    printf("请输入电话号码：");
    scanf("%s",vip->PhoneNumber);//存电话
    printf("请输入出生日期（年-月-日）：");
    while(1)
    {
        scanf("%d-%d-%d",&vip->Birth_Year,&vip->Birth_Month,&vip->Birth_Day);//存生日信息
        if(vip->Birth_Month==1||vip->Birth_Month==3||vip->Birth_Month==5||vip->Birth_Month==7||vip->Birth_Month==8||vip->Birth_Month==10||vip->Birth_Month==12)
        {
            if(vip->Birth_Day>0&&vip->Birth_Day<32)
                break;
        }
        if(vip->Birth_Month==4||vip->Birth_Month==6||vip->Birth_Month==9||vip->Birth_Month==11)
        {
            if(vip->Birth_Day>0&&vip->Birth_Day<31)
                break;
        }
        if(vip->Birth_Month==2)
        {
            if(vip->Birth_Year%4==0)
            {
                if(vip->Birth_Day>0&&vip->Birth_Day<30)
                    break;
            }
            else
            {
                if(vip->Birth_Day>0&&vip->Birth_Day<29)
                    break;
            }
        }
        printf("数据有错，请重新输入（年-月-日）：");
    }
    //printf("请设置会员卡密码：");
    while(1)
    {
	    passwords1 = getpass("请设置密码：");
	    passwords2 = getpass("请确定密码：");
       // memset(passwords1,0,sizeof passwords1);//第一个密码归零
       // memset(passwords2,0,sizeof passwords2);//第二个密码归零
       // while(1)
       // {
       //     passwords1[i]=getchar();//录入第一个密码但不显示
       //     if(passwords1[i]!=8)//如果不是是退格键
       //     {
       //         if(passwords1[i]=='\r')//如果是回车键
       //         {
       //             break;
       //         }
       //         printf("*");//密码字符用星号表示
       //     }
       //     else//以下else语句为退格操作
       //     {
       //         passwords1[i]='\0';
       //         passwords1[i-1]='\0';
       //         putchar('\b');
       //         putchar(' ');
       //         putchar('\b');
       //         i=i-2;
       //     }
       // }
       // printf("\n请再次确认会员卡密码：");
       // while(1)//原理同上
       // {
        //    passwords2[i]=getchar();
        //    if(passwords2[i]!=8)
        //    {
        //        if(passwords2[i]=='\r')
        //        {
        //            break;
        //        }
        //        printf("*");
        //    }
        //    if(passwords2[i]==8)
        //    {
        //        passwords2[i]='\0';
        //        passwords2[i-1]='\0';
        //        putchar('\b');
        //        putchar(' ');
        //        putchar('\b');
        //        i=i-2;
        //    }
        //}
        if(!strcmp(passwords1,passwords2))//对比两个密码是否相同
        {
            printf("\n\n**********恭喜您成功注册会员！**********\n");
            strcpy(vip->Passwords, passwords2);//将密码存入对应用户的结构体中、
            break;
        }
        else
        {
            printf("\n密码有错，请重新设置\n");
        }
    }
    vip->ID=p->tm_mday*100000+p->tm_mon*10000+p->tm_year*1000+p->tm_sec*100+p->tm_min*10+p->tm_hour;//用于随机产生ID号的一个坐在马桶上想出来的公式
    vip->Year=1900+p->tm_year;//记录系统年并以int型的形式记录在结构体vip的Year中
    vip->Month=1+p->tm_mon;//记录系统月并以int型的形式记录在结构体vip的Month中
    vip->Day=p->tm_mday;//记录系统日并以int型的形式记录在结构体vip的Day中
    vip->Balance=0;
    printf("\n您的会员ID是：%d\n\n",vip->ID);//存ID
    vip->u=0;
    savemoneyVIP(vip);
}

void addVIP(struct VIP **library)//插入新的会员信息
{
    struct VIP *vip;//用于接收用户录入的数据
    struct VIP *temp;//临时结构体
    char *ch;//用于后面判断是否继续下面的大while循环
    while(1)
    {
        vip=(struct VIP *)malloc(sizeof(struct VIP));//为结构体vip申请内存空间
        if(vip==NULL)
        {
            printf("内存分配失败了！\n");
            exit(1);
        }

        getInput(vip);//接收用户录入的数据

        if(*library!=NULL)//以下if-else语句表示将接收到的数据存入library这个大的链表中
        {
            temp=*library;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=vip;
            vip->next=NULL;
        }
        else
        {
            *library=vip;
            vip->next=NULL;
        }
        ch=getpass("按0键继续\n\n按任意键返回主菜单\n");
        if(!strcmp(ch,"0"))//根据用户输入确定是否需要继续大while循环
        {
            system("clear");
        }
        else
        {
            break;
        }
    }
}

void printLibrary(struct VIP *library)//打印会员信息（全部）
{
    struct VIP *vip;
    vip=library;//将链表的信息导入vip并指向链表的第一个元素
    while(vip!=NULL)
    {
        printf("会员姓名：%s\n",vip->Name);
        printf("会员电话号码：%s\n",vip->PhoneNumber);
        printf("会员生日：%d月%d日\n",vip->Birth_Month,vip->Birth_Day);
        printf("会员卡ID：%d\n",vip->ID);
        printf("会员卡办卡日期：%d年%d月%d日\n",vip->Year,vip->Month,vip->Day);
        printf("会员卡等级：%d\n",vip->Level);
        printf("会员卡余额：%d\n",vip->Balance);
        printf("会员账号密码：%s\n",vip->Passwords);
        printf("\n");
        vip=vip->next;//指向链表的下一个元素
    }
    char *c;
    c = getpass("");//系统函数，用于暂停，等待用户输入任意键以继续（如果去掉则整个信息会一闪而过）
    system("clear");
}

void printVIP(struct VIP *vip)//打印会员信息（单个）
{
    printf("会员姓名：%s\n",vip->Name);
    printf("会员电话号码：%s\n",vip->PhoneNumber);
    printf("会员卡ID：%d\n",vip->ID);
    printf("会员卡等级：%d\n",vip->Level);
    printf("会员卡余额：%d\n",vip->Balance);
    printf("\n");
}

void deleteVIP(struct VIP **library,struct VIP *vip)//删除会员信息
{
    struct VIP *previous;
    struct VIP *current;

    current=*library;
    previous=NULL;

    while (current!=NULL&&current!=vip)
    {
        previous=current;
        current=current->next;
    }
    if (previous==NULL)
    {
        *library=current->next;
    }
    else
    {
        previous->next=current->next;
    }
    printf("\n会员信息已成功删除\n\n");
    saveVIP(*library);
    free(current);
}

void searchVIP(struct VIP **library)//查找会员信息
{
    struct VIP *vip;
    char *target1;//姓名
    char *target2;//输入的密码
    int target3;//ID号
    int i,j;
    char *k;

    vip=*library;//将链表的信息导入vip并指向链表的第一个元素

    printf("                                        1、姓名登录\n");
    printf("                                        2、ID登录\n");
    k=getpass("                                        请选择登录方式: ");
    system("clear");

    printf("%s",k);
    if(strcmp(k,"1"))//进行姓名查找
    {
        printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *        欢迎会员回家！       *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n");

        printf("                                        请输入会员姓名：");
        scanf("%s",target1);

        while (vip!=NULL)//如果还没到最后一个元素
        {
            j=1;
            if (!strcmp(vip->Name,target1))//比对查找会员信息
            {
                target2 = getpass("                                        请输入密码：");
		/*
                for(i=0;i<100;i++)//同上
                {
                    target2[i]=getch();
                    if(target2[i]!=8)
                    {
                        if(target2[i]=='\r')
                        {
                            break;
                        }
                        printf("*");
                    }
                    if(target2[i]==8)
                    {
                        target2[i]='\0';
                        target2[i-1]='\0';
                        putchar('\b');
                        putchar(' ');
                        putchar('\b');
                        i=i-2;
                    }
                }*/
                if (!strcmp(vip->Passwords,target2))//对比查找会员信息
                {
                    menuVIP(library,vip);
                    break;
                }
                else//防止有重名用户
                {
                    while(vip!=NULL)
                    {
                        if (!strcmp(vip->Name,target1))
                        {
                            if (!strcmp(vip->Passwords,target2))
                            {
                                menuVIP(library,vip);
                                k=0;
                                break;
                            }
                            else
                            {
                                vip=vip->next;
                            }
                        }
                        else
                        {
                            vip=vip->next;
                        }
                    }
                    if(vip==NULL)
                    {
                        printf("\n                                        密码错误，登录失败！\n");
                    }
                    if(k==0)
                    {
                        break;
                    }
                }
            }
            else
            {
                j=0;
                vip=vip->next;//若无法找到则指向下一个元素
            }
        }
        if(j==0)
        {
            printf("                                         很抱歉，未查找到此用户！\n");
        }
    }

    if(strcmp(k,"2"))//进行ID查找（原理同上）
    {
        printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *        欢迎会员回家！       *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n");


        printf("                                        请输入ID：");
        scanf("%d",&target3);

        while (vip!=NULL)
        {
            j=2;
            if (target3==vip->ID)
            {
                j=0;
                target2 = getpass("                                        请输入密码：");
               // for(i=0;i<100;i++)//同上
               // {
                //    target2[i]=getch();
                //    if(target2[i]!=8)
                //    {
                //        if(target2[i]=='\r')
                //        {
                //            break;
                //        }
                //        printf("*");
                //    }
                //    if(target2[i]==8)
                //    {
                //        target2[i]='\0';
                //        target2[i-1]='\0';
                //        putchar('\b');
                //        putchar(' ');
                //        putchar('\b');
                //        i=i-2;
                //    }
                //}
                if (!strcmp(vip->Passwords,target2))
                {
                    menuVIP(library,vip);
                    break;
                }
                else
                {
                    printf("\n                                        密码错误，登录失败！\n");
                    break;
                }
            }
            else
            {
                j=2;
                vip=vip->next;
            }
        }
        if(j==2)
            printf("                                         很抱歉，未找到用户！\n");
    }
}

void sortVIP(struct VIP *library)
{
    struct VIP *vip;
    int i,j,num=0,temp;
    int a[1000],b[1000];
    for(vip=library;vip!=NULL;vip=vip->next)
    {
        num++;
    }
    vip=library;
    for(i=0;i<num;i++)
    {
        a[i]=vip->Level;
        b[i]=vip->ID;
        vip=vip->next;
    }
    for(i=0;i<num;i++)
    {
        for(j=i+1;j<num;j++)
        {
            if(a[i]>a[j])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
                temp=b[i];
                b[i]=b[j];
                b[j]=temp;
            }
        }
    }
    for(i=0;i<num;i++)
    {
        for(vip=library;vip!=NULL;vip=vip->next)
        {
            if(a[i]==vip->Level&&b[i]==vip->ID)
            {
                printVIP(vip);
            }
        }
    }
    char *c;
    c = getpass("");
    system("clear");
}

void savemoneyVIP(struct VIP *vip)//存钱函数
 {
    int n,s;
    time_t timep;
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);
    printf("请输入将存入金额：");
    scanf("%d",&n);
    s=(n+vip->allin)/10000-(vip->allin)/10000;
    vip->allin=vip->allin+n;    //总存入
    vip->Balance=vip->Balance+n;      //余额
    vip->dealmoney[vip->u]=n;
    vip->dealyear[vip->u]=1900+p->tm_year;
    vip->dealmonth[vip->u]=1+p->tm_mon;
    vip->dealday[vip->u]=p->tm_mday;
    vip->dealhour[vip->u]=8+p->tm_hour;
    vip->dealminute[vip->u]=p->tm_min;
    vip->dealsecond[vip->u]=p->tm_sec;
    (vip->u)++;
    if(s>=1)
    {
        vip->Level=vip->Level+s;
    }
    char *c;
    c = getpass("\n存款成功！！！\n\n");
    saveVIP(vip);
    system("clear");
 }

  void consumptionVIP(struct VIP *vip)//消费函数
 {
    int n;
    time_t timep;
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);
    printf("请输入已消费的金额：");
    scanf("%d",&n);
    if(vip->Balance<n)
    {
        printf("\n余额不足！！！\n");
    }
    else
    {
        vip->daddMoney=vip->daddMoney+n;   //总支出
        vip->Balance=vip->Balance-n;         //余额
        vip->dealmoney[vip->u]=-n;
        vip->dealyear[vip->u]=1900+p->tm_year;
        vip->dealmonth[vip->u]=1+p->tm_mon;
        vip->dealday[vip->u]=p->tm_mday;
        vip->dealhour[vip->u]=8+p->tm_hour;
        vip->dealminute[vip->u]=p->tm_min;
        vip->dealsecond[vip->u]=p->tm_sec;
        (vip->u)++;
        printf("\n消费成功！！！\n\n");
        saveVIP(vip);
    }
    system("clear");
 }

 void find_expense_calendar(struct VIP *vip)//消费查找
{
    int s,s1,s2,i;
    char *ch;
    int year,month,day;
    printf("0.查询近期十笔消费记录\n");
    printf("1.某日消费记录\n");
    printf("2.某月消费记录\n");
    scanf("%d",&s);
    system("clear");
    if(s==0)
    {
        do{
            s2=vip->u;
            for(s1=s2-1;(s2-s1<10)&&(s1>=0);s1--)
            printf("消费金额；%d\n消费时间；%d-%d-%d  %d:%d:%d\n",vip->dealmoney[s1],vip->dealyear[s1],vip->dealmonth[s1],vip->dealday[s1],vip->dealhour[s1],vip->dealminute[s1],vip->dealsecond[s1]);
            s2=s1;
            ch=getpass("查看下10笔记录请输入1\n");
            if(strcmp(ch,"1"))
                i=1;
            else
                i=0;
        }while(i==1);
    }
    if(s==1)
    {
        printf("请输入查询年月日（年-月-日）：");
        scanf("%d-%d-%d",&year,&month,&day);
        for(s1=vip->u;s1>=0;s1--)
        {
            if((year==vip->dealyear[s1])&&(month==vip->dealmonth[s1])&&(day==vip->dealday[s1]))
                printf("消费金额；%d\n消费时间；%d-%d-%d  %d:%d:%d\n",vip->dealmoney[s1],vip->dealyear[s1],vip->dealmonth[s1],vip->dealday[s1],vip->dealhour[s1],vip->dealminute[s1],vip->dealsecond[s1]);
        }
    }
    if(s==2)
    {
        printf("请输入查询年月日（年-月-日）：");
        scanf("%d-%d-%d",&year,&month,&day);
        for(s1=vip->u;s1>=0;s1--)
        {
            if((year==vip->dealyear[s1])&&(month==vip->dealmonth[s1]))
           printf("消费金额；%d\n消费时间；%d-%d-%d  %d:%d:%d\n",vip->dealmoney[s1],vip->dealyear[s1],vip->dealmonth[s1],vip->dealday[s1],vip->dealhour[s1],vip->dealminute[s1],vip->dealsecond[s1]);
        }
    }
    char *c;
    c = getpass("");
    system("clear");
}

void saveVIP(struct VIP *library)//保存VIP信息到文件（全部）
{
    struct VIP *vip;
    vip=library;
    FILE *fp=fopen("VIP","wb");

    while(vip!=NULL)
    {
        fwrite(vip,sizeof(struct VIP),1,fp);//将library中的数据逐组写入文件中
        vip=vip->next;
    }
    fclose(fp);
}

void readVIP(struct VIP **library)//读取文件中的会员信息（全部）
{
    struct VIP *vip;
    static struct VIP *tail;
    FILE *fp=fopen("VIP","rb");

    if(fp==NULL)
    {
        printf("打开文件失败！");
    }
    while(1)//相当于addVIP函数
    {
        vip=(struct VIP *)malloc(sizeof(struct VIP));
        if(vip==NULL)
        {
            printf("内存分配失败了！\n");
            break;
        }
        if(fread(vip,sizeof(struct VIP),1,fp))//判断是否读到了最后一个元素
        {
            if (*library!=NULL)
            {
                tail->next=vip;
                vip->next=NULL;
            }
            else
            {
                *library=vip;
                vip->next=NULL;
            }
            tail=vip;
        }
        else
            break;
    }
    fclose(fp);
}

int main()
{
    int i,j;
    struct VIP *library=NULL;//建立一个专门用来储存全部会员信息的链表
    FILE *fp=fopen("VIP","r");
    system("clear");
    while(1)//一个循环，各个函数执行完之后能返回主菜单
    {
        printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       欢迎使用会员系统      *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       0.系统使用说明        *\n\
                                       *       1.会员注册            *\n\
                                       *       2.会员登陆            *\n\
                                       *       3.管理员界面          *\n\
                                       *       4.退出系统            *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
               \n\
                                       请选择：");

        scanf("%d",&j);
        system("clear");//清屏

        if(j==1)
        {
            addVIP(&library);
            saveVIP(library);
            system("clear");
        }
        if(j==2)
        {
            printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *        欢迎会员回家！       *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n");

            searchVIP(&library);
            system("clear");//清屏
        }
        if(j==3)
        {
            printf("请输入神秘数字：");
            scanf("%d",&i);
            if(i==520)
            {
                system("clear");
                menuWorkers(&library);
            }
            else
            {
                system("clear");
                printf("我们的秘密才不和你分享呢！！！\n\n");
            }
            system("clear");//清屏
        }
        if(j==4)
        {
            break;
        }
    }
    return 0;
}

