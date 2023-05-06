#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//���ڵ���ϵͳʱ�䣨�Դ�������
#include <conio.h>
#include <windows.h>
#include<mmsystem.h>//��������
#pragma comment(lib,"Winmm.lib")//��������

void getInput(struct VIP *vip);//¼���Ա��Ϣ
void addVIP(struct VIP **library);//�����µĻ�Ա��Ϣ
void printLibrary(struct VIP *library);//��ӡ��Ա��Ϣ��ȫ����
void printVIP(struct VIP *vip);//��ӡ��Ա��Ϣ��������
void deleteVIP(struct VIP **library,struct VIP *vip);//ɾ����Ա��Ϣ
void searchVIP(struct VIP **library,int a);//���һ�Ա��Ϣ
void saveVIP(struct VIP *library);//����VIP��Ϣ���ļ���ȫ����
void readVIP(struct VIP **library);//��ȡ�ļ��еĻ�Ա��Ϣ��ȫ����
void menuVIP(struct VIP *library,struct VIP *vip);
void menuWorkers(struct VIP **library);
void sortVIP(struct VIP *library);
void consumptionVIP(struct VIP *vip);//���Ѻ���
void savemoneyVIP(struct VIP *vip);
void find_expense_calendar(struct VIP *vip);//���Ѳ���

typedef struct VIP//��Ա��Ϣ
{
    char Name[100];//����
    char PhoneNumber[100];//�绰����
    int ID;//ID
    int Year;//�쿨���ڣ��꣩
    int Month;//�쿨���ڣ��£�
    int Day;//�쿨���ڣ��գ�
    int Birth_Year;//���գ��꣩
    int Birth_Month;//���գ��£�
    int Birth_Day;//���գ��գ�
    int Level;//��Ա�ȼ�
    char Passwords[10];//����
    int Balance;//���
    int allin;//�ܴ���
    int allout;//��֧��
    int dealyear[100000];//�������
    int dealmonth[100000];//
    int dealday[100000];
    int dealhour[100000];
    int dealminute[100000];
    int dealsecond[100000];
    int dealmoney[100000];//���׽��
    int statement[10];//״̬����ʧ��
    int daddMoney;
    int u;
    struct VIP *next;//�������Ϊ����ָ����һ���ṹ��Ԫ�أ���ȽϾ����õ�
}VIP;

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
                                       *       ~~~~��������~~~~      *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       1.��Ϣ����            *\n\
                                       *       2.��ӡȫ����Ա��Ϣ    *\n\
                                       *       3.�˳�ϵͳ            *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
               \n\
                                       ��ѡ��");
        scanf("%d",&i);
        if(i==1)
        {
            system("cls");
            sortVIP(*library);
        }
        if(i==2)
        {
            system("cls");
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
    system("cls");
    while(1)
    {
        printf("\n\
               \n\
               \n\
               \n\
               \n\
                                                                      \n\
                                              ��ӭ������%s            \n\
                                                                      \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       1.��Ա��Ϣ��ѯ        *\n\
                                       *       2.��Ա����            *\n\
                                       *       3.��Ա����            *\n\
                                       *       4.���Ѳ�ѯ            *\n\
                                       *       5.��ʧ                *\n\
                                       *       6.�˿�                *\n\
                                       *       7.�˳�ϵͳ            *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
               \n\
                                       ��ѡ��",vip->Name);

        scanf("%d",&j);
        if(j==1)
        {
            system("cls");
            printVIP(vip);
            system("pause");
            system("cls");
        }
        if(j==2)
        {
            system("cls");
            savemoneyVIP(vip);
        }
        if(j==3)
        {
            system("cls");
            consumptionVIP(vip);
        }
        if(j==4)
        {
            system("cls");
            find_expense_calendar(vip);
        }
        if(j==6)
        {
            system("cls");
            printf("���Ҫ�뿪��:(\n����0ȷ������������˳���\n");
            ch=getch();
            if(ch=='0')
            {
                system("��������.exe");
                printf("\n���ټ��:(\n");
                deleteVIP(library,vip);
                system("pause");
                break;
            }
            else
            {
                system("cls");
                printf("���ǵ�ѡ��:)\n");
                system("pause");
                system("cls");
            }
        }
        if(j==7)
        {
            saveVIP(*library);
            break;
        }
    }
    system("cls");
}

void getInput(struct VIP *vip)//¼���Ա��Ϣ
{
    int i;
    char passwords1[100]={0},passwords2[100]={0};//��ͬ���õ�����
    time_t timep;//���ڵ���ϵͳʱ�䣨�Դ�������
    struct tm *p;//���ڵ���ϵͳʱ�䣨�Դ�������
    time(&timep);//���ڵ���ϵͳʱ�䣨�Դ�������
    p=gmtime(&timep);//���ڵ���ϵͳʱ�䣨�Դ�������
    vip->Level=0;

    for (i=0;i<25;i++)
    {
        printf("*");
    }
    printf("\n");
    printf("    ��ӭ������ͥ��    ");
    printf("\n");
    for (i=0;i<25;i++)
    {
        printf("*");
    }
    printf("\n");

    printf("������������");
    scanf("%s",vip->Name);//������
    printf("������绰���룺");
    scanf("%s",vip->PhoneNumber);//��绰
    printf("������������ڣ���-��-�գ���");
    while(1)
    {
        scanf("%d-%d-%d",&vip->Birth_Year,&vip->Birth_Month,&vip->Birth_Day);//��������Ϣ
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
        printf("�����д����������루��-��-�գ���");
    }
    printf("�����û�Ա�����룺");
    while(1)
    {
        memset(passwords1,0,sizeof passwords1);//��һ���������
        memset(passwords2,0,sizeof passwords2);//�ڶ����������
        for(i=0;i<100;i++)
        {
            passwords1[i]=getch();//¼���һ�����뵫����ʾ
            if(passwords1[i]!=8)//����������˸��
            {
                if(passwords1[i]=='\r')//����ǻس���
                {
                    break;
                }
                printf("*");//�����ַ����Ǻű�ʾ
            }
            else//����else���Ϊ�˸����
            {
                passwords1[i]='\0';
                passwords1[i-1]='\0';
                putchar('\b');
                putchar(' ');
                putchar('\b');
                i=i-2;
            }
        }
        printf("\n���ٴ�ȷ�ϻ�Ա�����룺");
        for(i=0;i<100;i++)//ԭ��ͬ��
        {
            passwords2[i]=getch();
            if(passwords2[i]!=8)
            {
                if(passwords2[i]=='\r')
                {
                    break;
                }
                printf("*");
            }
            if(passwords2[i]==8)
            {
                passwords2[i]='\0';
                passwords2[i-1]='\0';
                putchar('\b');
                putchar(' ');
                putchar('\b');
                i=i-2;
            }
        }
        if(!strcmp(passwords1,passwords2))//�Ա����������Ƿ���ͬ
        {
            printf("\n\n**********��ϲ���ɹ�ע���Ա��**********\n");
            strcpy(vip->Passwords, passwords2);//����������Ӧ�û��Ľṹ���С�
            break;
        }
        else
        {
            printf("\n�����д��������������룺");
        }
    }
    vip->ID=p->tm_mday*100000+p->tm_mon*10000+p->tm_year*1000+p->tm_sec*100+p->tm_min*10+p->tm_hour;//�����������ID�ŵ�һ��������Ͱ��������Ĺ�ʽ
    vip->Year=1900+p->tm_year;//��¼ϵͳ�겢��int�͵���ʽ��¼�ڽṹ��vip��Year��
    vip->Month=1+p->tm_mon;//��¼ϵͳ�²���int�͵���ʽ��¼�ڽṹ��vip��Month��
    vip->Day=p->tm_mday;//��¼ϵͳ�ղ���int�͵���ʽ��¼�ڽṹ��vip��Day��
    vip->Balance=0;
    printf("\n���Ļ�ԱID�ǣ�%d\n\n",vip->ID);//��ID
    vip->u=0;
    savemoneyVIP(vip);
}

void addVIP(struct VIP **library)//�����µĻ�Ա��Ϣ
{
    struct VIP *vip;//���ڽ����û�¼�������
    struct VIP *temp;//��ʱ�ṹ��
    char ch;//���ں����ж��Ƿ��������Ĵ�whileѭ��
    while(1)
    {
        vip=(struct VIP *)malloc(sizeof(struct VIP));//Ϊ�ṹ��vip�����ڴ�ռ�
        if(vip==NULL)
        {
            printf("�ڴ����ʧ���ˣ�\n");
            exit(1);
        }

        getInput(vip);//�����û�¼�������

        if(*library!=NULL)//����if-else����ʾ�����յ������ݴ���library������������
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
        printf("��0������\n\n��������������˵�\n");
        ch=getch();
        if(ch!='0')//�����û�����ȷ���Ƿ���Ҫ������whileѭ��
        {
            break;
        }
        else
        {
            system("cls");
        }
    }
}

void printLibrary(struct VIP *library)//��ӡ��Ա��Ϣ��ȫ����
{
    struct VIP *vip;
    vip=library;//���������Ϣ����vip��ָ������ĵ�һ��Ԫ��
    while(vip!=NULL)
    {
        printf("��Ա������%s\n",vip->Name);
        printf("��Ա�绰���룺%s\n",vip->PhoneNumber);
        printf("��Ա���գ�%d��%d��\n",vip->Birth_Month,vip->Birth_Day);
        printf("��Ա��ID��%d\n",vip->ID);
        printf("��Ա���쿨���ڣ�%d��%d��%d��\n",vip->Year,vip->Month,vip->Day);
        printf("��Ա���ȼ���%d\n",vip->Level);
        printf("��Ա����%d\n",vip->Balance);
        printf("��Ա�˺����룺%s\n",vip->Passwords);
        printf("\n");
        vip=vip->next;//ָ���������һ��Ԫ��
    }
    system("pause");//ϵͳ������������ͣ���ȴ��û�����������Լ��������ȥ����������Ϣ��һ��������
    system("cls");
}

void printVIP(struct VIP *vip)//��ӡ��Ա��Ϣ��������
{
    printf("��Ա������%s\n",vip->Name);
    printf("��Ա�绰���룺%s\n",vip->PhoneNumber);
    printf("��Ա��ID��%d\n",vip->ID);
    printf("��Ա���ȼ���%d\n",vip->Level);
    printf("��Ա����%d\n",vip->Balance);
    printf("\n");
}

void deleteVIP(struct VIP **library,struct VIP *vip)//ɾ����Ա��Ϣ
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
    printf("\n��Ա��Ϣ�ѳɹ�ɾ��\n\n");
    saveVIP(*library);
    free(current);
}

void searchVIP(struct VIP **library)//���һ�Ա��Ϣ
{
    struct VIP *vip;
    char target1[100]={0};//����
    char target2[100]={0};//���������
    int target3;//ID��
    int i,j;
    char k;

    vip=*library;//���������Ϣ����vip��ָ������ĵ�һ��Ԫ��

    printf("                                        1��������¼\n");
    printf("                                        2��ID��¼\n");
    printf("                                        ��ѡ���¼��ʽ��");
    k=getch();
    printf("%c",k);
    system("cls");

    if(k=='1')//������������
    {
        printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *        ��ӭ��Ա�ؼң�       *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n");

        printf("                                        �������Ա������");
        scanf("%s",target1);

        while (vip!=NULL)//�����û�����һ��Ԫ��
        {
            j=1;
            if (!strcmp(vip->Name,target1))//�ȶԲ��һ�Ա��Ϣ
            {
                printf("                                        ���������룺");
                for(i=0;i<100;i++)//ͬ��
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
                }
                if (!strcmp(vip->Passwords,target2))//�ԱȲ��һ�Ա��Ϣ
                {
                    menuVIP(library,vip);
                    break;
                }
                else//��ֹ�������û�
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
                        printf("\n                                        ������󣬵�¼ʧ�ܣ�\n");
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
                vip=vip->next;//���޷��ҵ���ָ����һ��Ԫ��
            }
        }
        if(j==0)
        {
            printf("                                         �ܱ�Ǹ��δ���ҵ����û���\n");
        }
    }

    if(k=='2')//����ID���ң�ԭ��ͬ�ϣ�
    {
        printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *        ��ӭ��Ա�ؼң�       *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n");


        printf("                                        ������ID��");
        scanf("%d",&target3);

        while (vip!=NULL)
        {
            j=2;
            if (target3==vip->ID)
            {
                j=0;
                printf("                                        ���������룺");
                for(i=0;i<100;i++)//ͬ��
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
                }
                if (!strcmp(vip->Passwords,target2))
                {
                    menuVIP(library,vip);
                    break;
                }
                else
                {
                    printf("\n                                        ������󣬵�¼ʧ�ܣ�\n");
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
            printf("                                         �ܱ�Ǹ��δ�ҵ��û���\n");
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
    system("pause");
    system("cls");
}

void savemoneyVIP(struct VIP *vip)//��Ǯ����
 {
    int n,s;
    time_t timep;
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);
    printf("�����뽫�����");
    scanf("%d",&n);
    s=(n+vip->allin)/10000-(vip->allin)/10000;
    vip->allin=vip->allin+n;    //�ܴ���
    vip->Balance=vip->Balance+n;      //���
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
    printf("\n���ɹ�������\n\n");
    saveVIP(vip);
    system("pause");
    system("cls");
 }

  void consumptionVIP(struct VIP *vip)//���Ѻ���
 {
    int n;
    time_t timep;
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);
    printf("�����������ѵĽ�");
    scanf("%d",&n);
    if(vip->Balance<n)
    {
        printf("\n���㣡����\n");
    }
    else
    {
        vip->daddMoney=vip->daddMoney+n;   //��֧��
        vip->Balance=vip->Balance-n;         //���
        vip->dealmoney[vip->u]=-n;
        vip->dealyear[vip->u]=1900+p->tm_year;
        vip->dealmonth[vip->u]=1+p->tm_mon;
        vip->dealday[vip->u]=p->tm_mday;
        vip->dealhour[vip->u]=8+p->tm_hour;
        vip->dealminute[vip->u]=p->tm_min;
        vip->dealsecond[vip->u]=p->tm_sec;
        (vip->u)++;
        printf("\n���ѳɹ�������\n\n");
        saveVIP(vip);
    }
    system("pause");
    system("cls");
 }

 void find_expense_calendar(struct VIP *vip)//���Ѳ���
{
    int s,s1,s2,i,ch;
    int year,month,day;
    printf("0.��ѯ����ʮ�����Ѽ�¼\n");
    printf("1.ĳ�����Ѽ�¼\n");
    printf("2.ĳ�����Ѽ�¼\n");
    scanf("%d",&s);
    system("cls");
    if(s==0)
    {
        do{
            s2=vip->u;
            for(s1=s2-1;(s2-s1<10)&&(s1>=0);s1--)
            printf("���ѽ�%d\n����ʱ�䣻%d-%d-%d  %d:%d:%d\n",vip->dealmoney[s1],vip->dealyear[s1],vip->dealmonth[s1],vip->dealday[s1],vip->dealhour[s1],vip->dealminute[s1],vip->dealsecond[s1]);
            s2=s1;
            printf("�鿴��10�ʼ�¼������1\n");
            ch=getch();
            if(ch=='1')
                i=1;
            else
                i=0;
        }while(i==1);
    }
    if(s==1)
    {
        printf("�������ѯ�����գ���-��-�գ���");
        scanf("%d-%d-%d",&year,&month,&day);
        for(s1=vip->u;s1>=0;s1--)
        {
            if((year==vip->dealyear[s1])&&(month==vip->dealmonth[s1])&&(day==vip->dealday[s1]))
                printf("���ѽ�%d\n����ʱ�䣻%d-%d-%d  %d:%d:%d\n",vip->dealmoney[s1],vip->dealyear[s1],vip->dealmonth[s1],vip->dealday[s1],vip->dealhour[s1],vip->dealminute[s1],vip->dealsecond[s1]);
        }
    }
    if(s==2)
    {
        printf("�������ѯ�����գ���-��-�գ���");
        scanf("%d-%d-%d",&year,&month,&day);
        for(s1=vip->u;s1>=0;s1--)
        {
            if((year==vip->dealyear[s1])&&(month==vip->dealmonth[s1]))
           printf("���ѽ�%d\n����ʱ�䣻%d-%d-%d  %d:%d:%d\n",vip->dealmoney[s1],vip->dealyear[s1],vip->dealmonth[s1],vip->dealday[s1],vip->dealhour[s1],vip->dealminute[s1],vip->dealsecond[s1]);
        }
    }
    system("pause");
    system("cls");
}

void saveVIP(struct VIP *library)//����VIP��Ϣ���ļ���ȫ����
{
    struct VIP *vip;
    vip=library;
    FILE *fp=fopen("VIP","wb");

    while(vip!=NULL)
    {
        fwrite(vip,sizeof(struct VIP),1,fp);//��library�е���������д���ļ���
        vip=vip->next;
    }
    fclose(fp);
}

void readVIP(struct VIP **library)//��ȡ�ļ��еĻ�Ա��Ϣ��ȫ����
{
    struct VIP *vip;
    static struct VIP *tail;
    FILE *fp=fopen("VIP","rb");

    if(fp==NULL)
    {
        printf("���ļ�ʧ�ܣ�");
    }
    while(1)//�൱��addVIP����
    {
        vip=(struct VIP *)malloc(sizeof(struct VIP));
        if(vip==NULL)
        {
            printf("�ڴ����ʧ���ˣ�\n");
            break;
        }
        if(fread(vip,sizeof(struct VIP),1,fp))//�ж��Ƿ���������һ��Ԫ��
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
    struct VIP *library=NULL;//����һ��ר����������ȫ����Ա��Ϣ������
    FILE *fp=fopen("VIP","r");

    if(fp!=NULL)
    {
        readVIP(&library);
    }
    else
    {
        printf("�ļ�Ϊ��!\n\n");
    }

	printf("\n\n\n\n\n\n\n\n\n\n\n\n                                               ���ڿ���������������               \n\n\n\n\n\n\n\n\n\n\n");//�������֣���ɾ
    PlaySound(TEXT("Falcom Sound Team jdk - ���䤹��.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);//�������֣���ɾ
    Sleep(12000);//�������֣���ɾ
    PlaySound(NULL,NULL,SND_FILENAME);//�������֣���ɾ
    system("cls");//�������֣���ɾ

    while(1)//һ��ѭ������������ִ����֮���ܷ������˵�
    {
        printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       ��ӭʹ�û�Աϵͳ      *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *       0.ϵͳʹ��˵��        *\n\
                                       *       1.��Աע��            *\n\
                                       *       2.��Ա��½            *\n\
                                       *       3.����Ա����          *\n\
                                       *       4.�˳�ϵͳ            *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n\
               \n\
                                       ��ѡ��");

        scanf("%d",&j);
        system("cls");//����

        if(j==1)
        {
            addVIP(&library);
            saveVIP(library);
            system("cls");
        }
        if(j==2)
        {
            printf("\n\
               \n\
               \n\
               \n\
                                       * * * * * * * * * * * * * * * *\n\
                                       *                             *\n\
                                       *        ��ӭ��Ա�ؼң�       *\n\
                                       *                             *\n\
                                       * * * * * * * * * * * * * * * *\n");

            searchVIP(&library);
            system("cls");//����
        }
        if(j==3)
        {
            printf("�������������֣�");
            scanf("%d",&i);
            if(i==520)
            {
                system("cls");
                menuWorkers(&library);
            }
            else
            {
                system("cls");
                printf("���ǵ����ܲŲ���������أ�����\n\n");
                system("pause");
            }
            system("cls");//����
        }
        if(j==4)
        {
            break;
        }
    }
    return 0;
}
