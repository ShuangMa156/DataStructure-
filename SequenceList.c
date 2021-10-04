/*
C语言中malloc是动态内存分配函数
函数原型：void *malloc(unsigned int num_bytes);
参数：num_bytes 是无符号整型，用于表示分配的字节数
返回值：如果分配成功则返回指向被分配内存的指针(此存储区中的初始值不确定)
否则返回空指针NULL。void* 表示未确定类型的指针，
void *可以指向任何类型的数据，更明确的说是指申请
内存空间时还不知道用户是用这段空间来存储什么类型的数据（比如是char还是int或者...）
功能：分配长度为num_bytes字节的内存块
注意：当内存不再使用时，应使用free()函数将内存块释放
函数返回的指针一定要适当对齐，使其可以用于任何数据对象
关于该函数的原型，在以前malloc返回的是char型指针，
新的ANSIC标准规定，该函数返回为void型指针，因此必要时要进行类型转换
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
typedef struct    //定义顺序表的存储结构
{
    int *elem;//动态分配空间的首地址
    int length;//表的当前长度
    int sizelist;//表的最大长度
}SqList;//定义一个顺序表结构体的全局变量
int InitList(SqList *L);//初始化表
int InitList(SqList *L)
{
    L->elem=(int*)malloc(MaxSize *sizeof(int));//动态分配内存
    if(!L->elem)//如果elem指向的内存空间不存在
    {
        printf("动态内存分配失败\n");//提示内存分配失败
        exit(0);
    }
    
    L->length=0;//初始化表长为0
    L->sizelist=MaxSize;//初始化表的大小为MaxSize
    return 0;
}
int DestoryList(SqList *L);//销毁表
int DestoryList(SqList *L)
{
    if(L->elem)
        free(L->elem);//如果表不为空，则释放存储空间
    L->elem=NULL;//将指向表头地址空间的指针置空
    return 0;
}
int Clear(SqList *L);//清空表
int Clear(SqList *L)
{
    L->length=0;//将表长置为0
    return 0;
}
int Empty(SqList *L);//判断表是否为空
int Empty(SqList *L)//通过函数返回值的比较可以判断出表是否为空
{
    if(L->length==0)
        return 1;
    else
        return 0;
}
int Length(SqList *L);
int Length(SqList *L)
{
    return L->length;//返回长度值
}
int InsertList(SqList *L,int data,int location);//向表中某个位置插入元素，并返回插入的数据
int InsertList(SqList *L,int data,int location)
{
    if(L->length==0 && location==1)
    {
        L->elem[0]=data;
        L->length++;
        printf("第一个元素插入成功\n");
    }
    else
    {
       if(location<1 || location>L->length)
       {
           printf("插入位置%d不合法\n",location);
           return 0;
       }
       if(L->length==L->sizelist)
       {
           printf("表已满，插入失败\n");
           return 0;
       }
       for(int i=L->length-1;i>location-1;i--)//将表中下标为location-1~L->length的元素全部后移
       {
           L->elem[i]=L->elem[i-1];
       }
       L->elem[location-1]=data;
       L->length=L->length+1;//表长加1
       printf("元素插入成功\n");
    }
    return data;//返回插入的数据
}
int DeleteList(SqList *L,int *data,int location);//删除表中某个位置上的元素，并返回删除的元素值
int DeleteList(SqList *L,int *data,int location)
{
    if(location<1 || location>L->length)
    {
        printf("删除%d位置不合法\n",location);
        return 0;
    }
    *data=L->elem[location-1];
    for(int i=location-1;i<L->length;i++)//将表中location位置之后的元素全部前移
    {
        L->elem[i]=L->elem[i+1];
    }
    L->length=L->length-1;//表长减1
    return *data;//返回删除的元素
}
int LocateList(SqList *L,int data);//按值查找，查找元素值为data的元素所在表中的位置
int LocateList(SqList *L,int data)
{
    int flag=1;//用于表示寻找结果的标志
    for(int i=0;i<L->length;i++)
    {
        if(L->elem[i]==data)
        {
            flag=0;//找到元素则将flag标志置为0
            printf("找到了，元素%d所在位置为%d\n",data,i+1);
            return i+1;//返回元素所在位置
        }
    }
    if(flag==1)
        printf("未找到%d元素",data);
    return 0;
}
int GetDataList(SqList *L,int location);//按位查找，查找表中位置为location的元素的值
int GetDataList(SqList *L,int location)
{
    if(location<1 || location>L->length)
    {
        printf("查找的位置%d不合法\n",location);
        return 0;
    }
    else
    {
        printf("表中第%d个元素值为%d\n",location,L->elem[location-1]);
        return L->elem[location-1];//返回第location个元素的值
    }
}
int PriorElem(SqList *L,int cur_elem,int *prior_elem);//求某个元素的前驱
int PriorElem(SqList *L,int cur_elem,int *prior_elem)
{
    int prior_location=0;//初始化前驱元素的位置
    for(int i=0;i<(L->length);i++)
    {
        if(L->elem[i]==cur_elem)
        {
            prior_location=i-1;
            break;
        }
    }
    if(prior_location>0)
    {
        *prior_elem=L->elem[prior_location];
        printf("%d元素的前驱元素为%d",cur_elem,*prior_elem);
        return *prior_elem;
    }
    else
    {
        printf("未找到元素%d",cur_elem);
        return 0;
    }
}
int NextElem(SqList *L,int cur_elem,int *next_elem);//寻找元素cur_elem的后继元素
int NextElem(SqList *L,int cur_elem,int *next_elem)
{
    int next_location=-1;
    for(int i=0;i<(L->length);i++)
    {
        if(L->elem[i]==cur_elem)
        {
            next_location=i+1;
            break;
        }
    }
    if(next_location>0 && next_location<(L->length))
    {
        *next_elem=L->elem[next_location];
        printf("元素%d的后继元素为%d",cur_elem,*next_elem);
        return *next_elem;
    }
    else
    {
        printf("未查询到元素%d",cur_elem);
        return 0;
    }
}
void PrintList(SqList *L);//打印输出整张表
void PrintList(SqList *L)
{
    if(L->length==0)
    {
        printf("顺序表为空\n");
    }
    for(int i=0;i<L->length;i++)
    {
        printf("第%d个元素：%d",i+1,L->elem[i]);
    }
}
int main()
{
    printf("\n\n\n***************************************菜单*****************************************\n");
    printf("******************************************************************************************\n");
    printf("**************1、初始化顺序表     2、判断表是否为空        3、清空表        4、销毁表     \n");
    printf("**************5、插入元素         6、删除元素              7、按值查找      8、按位查找   \n");
    printf("**************9、求前驱元素       10、求后继元素           11、打印表       12、求表长    \n");
    printf("**************13、退出程序\n");
    SqList list;//定义结构体变量list
    int d,l,pre_d,next_d;//定义变量：数据变量d、位置变量l、前驱位置变量pre_l,后继位置变量next_l
    int choice;//用于选择功能的变量choice
    do
    {
        printf("\n输入选项：\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1://初始化顺序表
            {
                InitList(&list);
                printf("初始化成功\n");
                break;
            }
        case 2:
            {
                if(Empty(&list))
                    printf("顺序表为空\n");
                else
                    printf("顺序表部位空\n");
                break;
            }
        case 3:
            {
                Clear(&list);
                printf("成功清空表\n");
                break;
            }
        case 4:
            {
                DestoryList(&list);
                printf("成功销毁表\n");
                break;
            }
        case 5:
            {
                printf("请输入插入元素的值:");
                scanf("%d",&d);
                printf("请输入插入元素的位置",location);
                scanf("%d",&l);
                InsertList(&list,d,l);
                break;
            }
        case 6:
            {
                printf("请输入要删除元素的位置：");
                scanf("%d",&l);
                printf("\n");
                DeleteList(&list,&d,l);
                break;
            }
        case 7:
            {
                printf("请输入要查找元素的值：");
                scanf("%d",&d);
                printf("\n");
                LocateList(&list,d);
                break;
            }
        case 8:
            {
                printf("请输入要查找元素的位置：");
                scanf("%d",&l);
                printf("\n");
                GetDataList(&list,l);
                break;
            }
        case 9://求前驱元素
            {
                printf("请输入要当前元素的值：");
                scanf("%d",&d);
                printf("\n");
                PriorElem(&list,d,&pre_d);
                break;
            }
        case 10://求后继元素
            {
                printf("请输入要当前元素的位置：");
                scanf("%d",&d);
                printf("\n");
                NextElem(&list,d,&next_d);
                break;
            }
        case 11:
            {
                printf("当前表中元素有：\n");
                PrintList(&list);
                break;
            }
        case 12:
            {
                printf("表的长度为：%d",Length(&list));
                break;
            }
        case 13:
            {
                break;
            }
        default:
            printf("输入选项不合法\n");
            break;
        }
    }while(choice!=13);

    return 0;
}
