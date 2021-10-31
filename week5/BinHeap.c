#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define MaxSize 20
#define MinPQSize 10
#define MinData -32767
#define FatalError(Str) fprintf(stderr,"%s\n",Str),exit(1)
#define Error(Str) fprintf(stderr,"%s\n",Str),exit(1)
struct HeapStruct
{
    int Capacity;//二叉堆的容量
    int Size;//二叉堆当前的大小
    ElementType *Elements;//用指针来指向二叉堆中的元素
};
PriorityQueue Initialize(int MaxElements)//参数为要初始化的二叉堆的大小
{
    if(MaxElements<MinPQSize)//如果初始化的二叉堆大小小于对二叉堆最小容量的限制，则抛出异常
        Error("Priority queue size is too small");
    PriorityQueue H=malloc(sizeof(struct HeapStruct));//申请大小与二叉堆结构体相等的空间
    if(H==NULL)
        FatalError("Out of Space");//申请失败时抛出异常
    H->Elements=malloc((MaxElements+1)*sizeof(ElementType));//为整个二叉堆的元素申请空间，多申请一个元素的位置作为哨兵
    if(H->Elements==NULL)
        FatalError("Out of Space");//申请失败时抛出异常
    H->Elements[0]=MinData;//初始化堆中0号位置作为哨兵（一个较小值，能够满足小于堆中所有的元素值）
    H->Capacity=MaxElements;//初始化堆的容量为设定的堆的大小
    H->Size=0;//初始化当前堆的大小
    return H;
}
void Destory(PriorityQueue H)
{
    free(H->Elements);//先释放堆中元素所占的存储空间
    free(H);//再释放堆所占的存储空间
}
void MakeEmpty(PriorityQueue H)
{
    H->Size=0;
}
void Insert(ElementType X,PriorityQueue H)
{
    int i;
    if(IsFull(H))
    {
        Error("Priority Queue is full");
        return;
    }
    for(i=H->Size+1;H->Elements[i/2]>X;i/=2)//上滤，先将插入的元素位置初始化为二叉堆的最后，然后通过堆序性调整插入元素的位置
    {
        H->Elements[i]=H->Elements[i/2];//每次将位置i上的元素（即新插入的元素）与其父节点的值进行比较，如果小于父节点的值则交换其余父节点的位置，直到它的值大于其所在住的父节点的值
    }
    H->Elements[i]=X;//找到合适的位置i，并将插入的元素X放在该位置上
}
ElementType DeleteMin(PriorityQueue H)
{
    int i,child;
    ElementType MinElement,LastElement;
    if(IsEmpty(H))
    {
        Error("Priority Queue is Empty");
        return H->Elements[0];
    }
    MinElement=H->Elements[1];//初始化当前二叉堆中的最小元素为根节点的元素值
    LastElement=H->Elements[H->Size];//初始化当前二叉堆中的最后一个元素为二叉堆中最后一个元素的元素值
    H->Size=H->Size-1;
    for(i=1;i*2<=H->Size;i=child)//从堆中第一个元素开始，依次比较当前节点与其子节点的值，找到值最小的子节点
    {
        child=i*2;//寻找位置为i的节点的左孩子所在的位置
        if(child!=H->Size && (H->Elements[child+1])<(H->Elements[child]))//如果做孩子的位置不是堆中最后一个元素所在的位置，并且左孩子的值大于右孩子，则更新child为右孩子的位置
            child++;
    if(LastElement> (H->Elements[child]))//比较根节点与最小子节点的值，如果最小子节点的值更小，则用最小子节点的元素值代替根节点的元素值
        H->Elements[i]=H->Elements[child];//根节点的值被删除
    else
        break;
    }
    H->Elements[i]=LastElement;//将原来堆中最后一个元素的值放到找到的最小子节点的位置处
    return MinElement;
}
ElementType FindMin(PriorityQueue H)
{
    if(!IsEmpty(H))
        return H->Elements[1];//如果二叉堆不为空，根据堆序性，堆中第一个元素即为堆中元素最小值
    Error("Priority Queue is Empty");
    return H->Elements[0];
}
int IsEmpty(PriorityQueue H)
{
    return H->Size=0;
}
int IsFull(PriorityQueue H)
{
    return H->Size==H->Capacity;
}
int main()
{
    PriorityQueue H;
    int i;
    int j=0;
    H=Initialize(MaxSize);
    for(i=0,j=MaxSize/2;i<MaxSize;i++,j=(j+71)%MaxSize)
    {
        Insert(j,H);
    }
    printf("插入值后的堆：");
    for(i=0;i<H->Size;i++)
    {
        printf("%d\t",H->Elements[i]);
    }
    j=0;
    while(!IsEmpty(H))
    {
        if(DeleteMin(H)!=j++)
            printf("Error in DeleteMin,%d\n",j);
    }
    printf("删除最小元素后的堆：");
    for(i=0;i<H->Size;i++)
    {
        printf("%d\t",H->Elements[i]);
    }
    return 0;
}
