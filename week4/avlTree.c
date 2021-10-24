#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"
#define FatalError(Str) fprintf(stderr,"%s\n",Str),exit(1)
struct AVLNode
{
    ElementType Element;//节点的元素值
    AVLTree Left;//节点的左子树
    AVLTree Right;//节点的右子树
    int Height;//以该节点作为根节点的树的高度
};
AVLTree MakeEmpty(AVLTree T)//清空树
{
    if(T!=NULL)
    {
        MakeEmpty(T->Left);//递归的清空左子树
        MakeEmpty(T->Right);//递归的清空右子树
        free(T);//释放节点T所占用的存储空间
    }
    return NULL;//递归出口：树为空
}
Position Find(ElementType X,AVLTree T)
{
    if(T==NULL)
    {
        return NULL;//树为空时返回空
    }
    else
    {
        if(X<T->Element)
            return Find(X,T->Left);//如果要找的元素值大于当前AVL树根节点的元素值，则递归的查找其左子树
        if(X>T->Element)
            return Find(X,T->Right);//如果要查找的元素值小于当前AVL树根节点的元素值，则递归的查找其右子树
        else
            return T;//递归出口，如果要查找的元素值就是根节点的元素值，则返回根节点的位置
    }
}
Position FindMin(AVLTree T)
{
    if(T==NULL)
        return NULL;//树为空时返回空以示未找到
    else if(T->Left==NULL)//如果当前的AVL树没有左子树，则最小值即为根节点的元素值，最小值的位置为根节点所在的位置
        return T;//递归出口
    else
        return FindMin(T->Left);//如果当前的AVL树有左子树，则递归的在其左子树中寻找最小值所在的位置
}
Position FindMax(AVLTree T)
{
   /*if(T==NULL)
        return NULL;//树为空时返回空以示未找到
    else if(T->Right==NULL)//如果当前的AVL树没有右子树，则最大值即为根节点的元素值，最大值的位置为根节点所在的位置
        return T;//递归出口
    else
        return FindMin(T->Right);//如果当前的AVL树有右子树，则递归的在其右子树中寻找最大值所在的位置*/
    if(T!=NULL)//如果树不为空，则进入循环
    {
        while(T->Right!=NULL)//一次寻找右子树，直到找到深度最深的右子树（右子树为空的树）为止
        {
            T=T->Right;
        }
    }
    return T;//返回当前树的根节点，可能是整个AVL的根节点，也可能是右子树
}
int Height(Position P)
{
    if(P==NULL)
        return -1;//如果位置不存在，则返回-1
    else
        return P->Height;//返回位置P对应节点的高度值
}
int Max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}
static Position LeftSingleRotate(Position K2)//LL型（插入位置在根节点的左子树的左子树），K2表示要调整的树的根节点
{
    //调整方法：以当前不平衡树的左子树的根节点作为整个不平衡树的根节点，调整原根节点为新根节点的右子树
    Position K1;//临时节点为位置K1,用于存放旋转后的根节点
    K1=K2->Left;//让K1指向K2的左子树，则K1->Element < K2->Element
    K2->Left=K1->Right;//将K1的右子树作为K2的左子树,因为K1->Element < K1->Right->Element < K2->Element
    K1->Right=K2;//让K2成为K1的右子树，即让K1做当前树的根节点，则K1->Element < K2->Element
    K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;//调整后K2的高度发生变化，为左右子树中高度的最大值加1
    K1->Height=Max(Height(K1->Left),K2->Height)+1;//调整后K2的高度为左右子树中高度的最大值加1,此时的右子树为K2
    return K1;//返回调整后根节点的位置K1
}
static Position RightSingleRotate(Position K1)//RR型（插入位置在根节点的右子树的右子树），K2表示要调整的树的根节点
{
    //调整方法：以当前不平衡树的右子树的根节点作为整个不平衡树的根节点，调整原根节点为新根节点的左子树
    Position K2;//临时节点为位置K2,用于存放旋转后的根节点
    K2=K1->Right;//让K2指向K1的右子树，则K2->Element > K1->Element
    K1->Right=K2->Left;//将K2的左子树作为K1的右子树,因为K2->Element > K2->Left->Element > K1->Element
    K2->Left=K1;//让K1成为K2的左子树，即让K2做当前树的根节点，则K2->Element > K1->Element
    K1->Height=Max(Height(K1->Left),Height(K1->Right))+1;//调整后K1的高度发生变化，为左右子树中高度的最大值加1
    K2->Height=Max(K1->Height,Height(K2->Right))+1;//调整后K2的高度为左右子树中高度的最大值加1,此时的左子树为K1
    return K2;//返回调整后根节点的位置K1
}
static Position LeftDoubleRotate(Position K3)//LR型（插入位置在根节点的左子树的右子树），K3表示要调整的树的根节点
{
    K3->Left=RightSingleRotate(K3->Left);//先调整以K3为根节点的树的左子树，左子树的不平衡状态为RR型
    return LeftSingleRotate(K3);//再调整以K3为根节点的整棵树，此时整棵树的不平衡状态为LL型
}
static Position RightDoubleRotate(Position K1)//RL型（插入位置在根节点的的右子树的左子树）,K1表示要调整的根节点
{
    K1->Right=LeftSingleRotate(K1->Right);//先调整以K1为根节点的树的右子树，右子树的不平衡状态为LL型
    return RightSingleRotate(K1);//在调整以K1为根节点的整棵树，此时整棵树的不平衡状态为RR型
}
AVLTree Insert(ElementType X,AVLTree T)
{
    if(T==NULL)
    {
        T=malloc(sizeof(struct AVLNode));//申请一个节点大小的空间
        if(T==NULL)
            FatalError("Out of space");
        else
        {
            //初始化操作
            T->Element=X;
            T->Left=NULL;
            T->Right=NULL;
            T->Height=0;
        }
    }
    else if(X<T->Element)
    {
        T->Left=Insert(X,T->Left);//插入在左子树中
        if(Height(T->Left)-Height(T->Right)==2)//出现不平衡，需要调整
        {
            if(X<T->Left->Element)//出现在左子树的左子树
                T=LeftSingleRotate(T);//用LL型的方法调整
            else
                T=LeftDoubleRotate(T);//用LR型的方法调整
        }
    }
    else if(X>T->Element)
    {
        T->Right=Insert(X,T->Right);//插入在右子树中
        if(Height(T->Right)-Height(T->Left)==2)//出现不平衡，需要调整
        {
            if(X>T->Right->Element)//出现在右子树的右子树
                T=RightSingleRotate(T);//用RR型的方法调整
            else
                T=RightDoubleRotate(T);//用RL型的方法调整
        }
    }
    T->Height=Max(Height(T->Left),Height(T->Right))+1;//更新树的高度值
    return T;
}
ElementType Retrieve(Position P)
{
    return P->Element;
}
void PrintTree(AVLTree T)//树的前序遍历
{
    if(T!=NULL)
    {
        printf("%d\t",T->Element);
        PrintTree(T->Left);
        PrintTree(T->Right);
    }
}
int main()
{
    AVLTree T;
    Position P;
    int i,j=0;
    T=MakeEmpty(NULL);
    for(i=0;i<50;i++)
    {
        T=Insert(j,T);
        j=(j+7)%50;
    }
    for(i=0;i<50;i++)
    {
        if((P=Find(i,T))==NULL || Retrieve(P)!=i)
            printf("Error at %d\n",i);
    }
    printf("打印树：");
    PrintTree(T);
    printf("\n");
    printf("Min is %d,Max is %d\t",Retrieve(FindMin(T)),Retrieve(FindMax(T)));
    return 0;
}
