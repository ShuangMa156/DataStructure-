#include <stdio.h>
#include <stdlib.h>
#include "left_heap.h"
struct TreeNode
{
    ElementType Element;//每个节点的元素值
    PriorityQueue Left;//指向以该结点为父节点的左孩子
    PriorityQueue Right;//指向以该结点为父节点的右孩子
    int Npl;//每个节点的零路径长
};
void FatalError(char *message) //错误提示
{
    printf("%s\n", message);
    exit(1);
}
PriorityQueue Initialize(void)//左氏堆的初始化
{
    PriorityQueue H=malloc(sizeof(struct TreeNode));//为创建的优先队列对象H申请内存空间，大小与优先队列中的节点大小相同
    if(H==NULL)
        FatalError("Out of space");
    H->Element=0;
    H->Left=NULL;
    H->Right=NULL;
    H->Npl=0;
    return H;
}
int IsEmpty(PriorityQueue H)//判空操作
{
    if((H->Left==NULL) && (H->Right==NULL))
        return 1;
    else
        return 0;
    //return H->Left=NULL && H->Right==NULL;//如果左右子树均为空，则该左氏堆为空
}
ElementType FindMin(PriorityQueue H)//找左氏堆中所有元素中的最小值
{
    if(H!=NULL)
        return H->Element;//根据左氏堆的结构特点，根节点的元素值最小
    return 0;
}
static void SwapChild(PriorityQueue H)
{
    PriorityQueue temp=malloc(sizeof(struct TreeNode));//创建临时节点变量
    temp=H->Left;//用临时节点暂存指向左氏堆左子树的指针
    H->Left=H->Right;//让二叉堆H的左子树的指针指向其右子树
    H->Right=temp;
    free(temp);
}
static PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2)
{
    if(H1->Left==NULL)//递归的出口
        H1->Left=H2;//如果左子树为空，则将另一个左氏堆作为左子树
    else
    {
        H1->Right=Merge(H1->Right,H2);//如果左子树不为空，则将H2与H1的右子树合并后作为H1的右子树
        if(H1->Left->Npl < H1->Right->Npl)//右子树的零路径长大于左子树
        {
            SwapChild(H1);//交换左氏堆H1的左右子树
            H1->Npl=H1->Right->Npl+1;//更新根节点的零路径长为其新的右子树的零路径长+1
        }
    }
    return H1;
}
PriorityQueue MergeHeap(PriorityQueue H1,PriorityQueue H2)
{
    if(H1==NULL)//左氏堆H1为空时，合并后的结果为H2
        return H2;
    if(H2==NULL)//左氏堆H2为空时，合并后的结果为H1
        return H1;
    if(H1->Element < H2->Element)//如果H1的元素值较小，则将H1的右子堆与H2合并
        return Merge(H1,H2);
    else
        return Merge(H2,H1);//如果H2的元素值较小或者两者相等，则将H2的右子堆与H1合并
}
PriorityQueue Insert1(ElementType X,PriorityQueue H)//将插入的节点与原二叉堆进行归并得到新的二叉堆
{
    PriorityQueue newNode;
    newNode=malloc(sizeof(struct TreeNode));//为新节点申请内存空间
    if(newNode==NULL)
        FatalError("Out of space");
    else
    {
        newNode->Element=X;//初始化新节点的元素值为插入的元素值
        newNode->Left=NULL;//初始化新节点的左子堆为空
        newNode->Right=NULL;//初始化新节点的右子堆为空
        newNode->Npl=0;//初始化新节点的零路径长为0
        H=MergeHeap(newNode,H);//将新节点与原二叉堆进行归并，得到插入一个元素后的新的二叉堆
    }
    return H;
}
PriorityQueue DeleteMin1(PriorityQueue H)//删除二叉堆的根节点后将左子堆与右子堆归并得到新的二叉堆
{
    PriorityQueue LeftHeap;
    PriorityQueue RightHeap;
    if(IsEmpty(H))
    {
        printf("Error\n");
        return H;
    }
    LeftHeap=H->Left;
    RightHeap=H->Right;
    free(H);
    return MergeHeap(LeftHeap,RightHeap);
}
void PrintTree(PriorityQueue H)//树的前序遍历
{
    if(H!=NULL)
    {
        printf("%d\t",H->Element);
        PrintTree(H->Left);
        PrintTree(H->Right);
    }
}
int main()
{
    PriorityQueue H;
    int num;
    int i;
    H=Initialize();
    printf("请输入要插入的节点的数量：");
    scanf("%d\n",&num);
    for(i=1;i<num+1;i++)
    {
        int k;
        printf("请输入插入的元素值:");
        scanf("%d\n",&k);
        H=Insert1(i,H);
    }
    printf("插入后的结果:");
    PrintTree(H);
    H=DeleteMin1(H);
    printf("删除最小元素后的结果:");
    PrintTree(H);
    return 0;
}

