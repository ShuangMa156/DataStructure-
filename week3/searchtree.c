#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tree.h"
#define FatalError(Str) fprintf(stderr,"%s\n",Str),exit(1)
#define Error(Str) fprintf(stderr,"%s\n",Str),exit(1)
struct TreeNode
{
    ElementType Element;//结点值
    SearchTree Left;//结点的左子树
    SearchTree Right;//结点的右子树
};
SearchTree MakeEmpty(SearchTree T)//构造一棵空树
{
    if(T!=NULL)//二叉搜索树T不为空
    {
        MakeEmpty(T->Left);//递归的将左子树置空
        MakeEmpty(T->Right);//递归的将右子树置空
        free(T);//释放根结点
    }
    return NULL;//二叉搜索树为空时则返回空------递归出口
}
Position Find(ElementType X,SearchTree T)//指数中寻找某一特定元素值所在的结点
{
    if(T==NULL)//二叉搜索树T为空
        return NULL;
    else if(X < T->Element)//要查找的元素值小于根节点的元素值，则递归查找左子树
        Find(X,T->Left);
    else if(X > T->Element)//要查找的元素值大于根节点的元素值，则递归查找右子树
        Find(X,T->Right);
    else
        return T;//要查找的元素值等于根节点的元素值，则返回根结点
}
Position FindMin(SearchTree T)//寻找树中最小元素的位置
{
    if(T==NULL)//二叉搜索树T为空，则返回空
        return NULL;
    else if(T->Left==NULL)//二叉搜索树根结点的左孩子为空，则返回根结点（因为二叉搜索树中左子树的所有结点的元素值小于根结点的元素值）
        return T;
    else
        return FindMin(T->Left);//如果二叉搜索树的根结点的左子树不为空，则递归的查找左子树
}
Position FindMax(SearchTree T)//寻找树中最大元素所在的位置
{
    if(T!=NULL)//当二叉搜索树不为空时，利用循环实现遍历二叉树的右子树，知道某一个结点没有右子树，则将该结点返回
    {
        while(T->Right!=NULL)
            T=T->Right;
    }
    return T;
}
SearchTree Insert(ElementType X,SearchTree T)//向树中插入一个结点
{
    if(T==NULL)//二叉搜索树为空，则插入的元素值作为新树的根结点的值
    {
        T=malloc(sizeof(struct TreeNode));//申请结点空间
        if(T==NULL)
            FatalError("Out of Space\n");//申请失败，抛出异常
        else
        {
            T->Element=X;//将元素值赋给根结点的元素值域
            T->Left=T->Right=NULL;//初始化左右子树为空
        }
    }
    else if(X<T->Element)//要插入的元素值小于根结点的元素值
        T->Left=Insert(X,T->Left);//将元素值插入到左子树中
    else if(X>T->Element)//要插入的元素值大于根结点的元素值
        T->Right=Insert(X,T->Right);//将该元素值插入到右子树中
    return T;//返回根结点
}
SearchTree DeleteRT(ElementType X,SearchTree T)//删除书中的某一个结点
{
    Position Temp;
    if(T==NULL)//二叉搜索树为空，则抛出错误提示
        Error("Element not find \n");
    else if(X<T->Element)//删除的元素值小于根结点的元素值，则递归的在左子树中删除
        T->Left=DeleteRT(X,T->Left);
    else if(X>T->Element)//删除的元素值大于根结点的元素值，则递归的在右子树中删除
        T->Right=DeleteRT(X,T->Right);
    else if(T->Left && T->Right)//如果根结点的左右子树均不为空，则在右子树中寻找元素值最小的结点
    {
        Temp=FindMin(T->Right);//将右子树中元素值最小的结点的赋值给临时变量Temp
        T->Element=Temp->Element;//保存找到的右子树中价值最小的结点的值
        T->Right=DeleteRT(T->Element,T->Right);//递归的删除右子树中中最小数据值结点
    }
    else//只有一个子节点的情况
    {
        Temp=T;
        if(T->Left==NULL)//左子树为空，则在右子树中寻找
            T=T->Right;
        else if(T->Right==NULL)//右子树为空，则在左子树中寻找
            T=T->Left;
        free(Temp);//释放临时节点变量
    }
    return T;//返回根结点
}
SearchTree DeleteLT(ElementType X,SearchTree T)//删除书中的某一个结点
{
    Position Temp;
    if(T==NULL)//二叉搜索树为空，则抛出错误提示
        Error("Element not find \n");
    else if(X<T->Element)//删除的元素值小于根结点的元素值，则递归的在左子树中删除
        T->Left=DeleteLT(X,T->Left);
    else if(X>T->Element)//删除的元素值大于根结点的元素值，则递归的在右子树中删除
        T->Right=DeleteLT(X,T->Right);
    else if(T->Left && T->Right)//如果根结点的左右子树均不为空，则在右子树中寻找元素值最小的结点
    {
        Temp=FindMax(T->Left);//将右子树中元素值最小的结点的赋值给临时变量Temp
        T->Element=Temp->Element;//保存找到的右子树中价值最小的结点的值
        T->Left=DeleteLT(T->Element,T->Left);//递归的删除右子树中中最小数据值结点
    }
    else//只有一个子节点的情况
    {
        Temp=T;
        if(T->Left==NULL)//左子树为空，则在右子树中寻找
            T=T->Right;
        else if(T->Right==NULL)//右子树为空，则在左子树中寻找
            T=T->Left;
        free(Temp);//释放临时节点变量
    }
    return T;//返回根结点
}
ElementType Retrieve(Position P)//寻找树中某一位置的特定元素值
{
    return P->Element;
}
void PrintTreeF(SearchTree T)//树的前序遍历
{
    if(T!=NULL)
    {
        printf("%d\t",T->Element);
        PrintTreeF(T->Left);
        PrintTreeF(T->Right);
    }
}
void PrintTreeM(SearchTree T)//树的中序遍历
{
    if(T!=NULL)
    {
        PrintTreeM(T->Left);
        printf("%d\t",T->Element);
        PrintTreeM(T->Right);
    }
}
void PrintTreeB(SearchTree T)//树的后序遍历
{
    if(T!=NULL)
    {
        PrintTreeB(T->Left);
        PrintTreeB(T->Right);
        printf("%d\t",T->Element);
    }
}
int TreeDepth(SearchTree T)
{
    if(T==NULL)
        return -1;
    else
    {
        int Ldepth=TreeDepth(T->Left);
        int Rdepth=TreeDepth(T->Right);
        if(Ldepth>Rdepth)
            return 1+Ldepth;
        else
            return 1+Rdepth;
    }
}
int main()
{
    SearchTree T;
    Position P;
    int i;
    srand((unsigned)time(NULL));
    int j=rand()%50;
    int depth;
    T=MakeEmpty(NULL);
    for(i=0;i<50;i++)//用顺序表的方式存储一棵树
     {
         T=Insert(j,T);
         j=(j+7)%50;
     }
    depth=TreeDepth(T);
    printf("树的深度：%d\n",depth);
    printf("前序遍历的结果：\n");
    PrintTreeF(T);
    printf("\n");
    printf("中序遍历的结果：\n");
    PrintTreeM(T);
    printf("\n");
    printf("后序遍历的结果：\n");
    PrintTreeB(T);
    printf("\n");
    for(i=0;i<50;i++)
    {
        if((P=Find(i,T))==NULL || Retrieve(P)!=i)
            printf("Error at %d/n",i);
    }
    for(i=1;i<50;i+=2)//删除奇数
    {
        T=DeleteRT(i,T);
    }
    //T=DeleteRT(i,T);
    depth=TreeDepth(T);
    printf("树的深度：%d\n",depth);
    printf("前序遍历的结果：\n");
    PrintTreeF(T);
    printf("\n");
    printf("中序遍历的结果：\n");
    PrintTreeM(T);
    printf("\n");
    printf("后序遍历的结果：\n");
    PrintTreeB(T);
    printf("\n");
    for(i=1;i<50;i+=2)
    {
        if((P=Find(i,T))==NULL || Retrieve(P)!=i)
            printf("Error at %d/n",i);
    }
    printf("Min is %d,Max is %d\t",Retrieve(FindMin(T)),Retrieve(FindMax(T)));
    return 0;
}
