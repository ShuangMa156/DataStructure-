#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Cutoff (3)
#define LeftChild(i)(2*(i)+1)
void swap(int *a,int *b)//交换两个变量的值
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void SelectSort(int a[],int n)
{
    int i,j;
    int min;
    for(i=0;i<n-1;i++)
    {
        min=i;
        for(j=i+1;j<n;j++)
        {
            if(a[j]<a[min])
                min=j;
        }
        if(min!=i)
        {
            /*int tmp = a[min];
            a[min] = a[i];
            a[i] = tmp;*/
            swap(&a[min],&a[i]);
        }
    }

}
void BubbleSort(int a[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++)//外层循环，第几趟比较
    {
        for(j=0;j<n-i-1;j++)//内层循环，与剩下的元素比较，后面的i个元素已排好序
        {
            if(a[j]>a[j+1])
            {
                swap(&a[j],&a[j+1]);//将值较大的元素放到后面
            }
        }
    }
}
void InsertSort(int a[],int n)
{
    int i,j;
    int temp;
    for(i=1;i<n;i++)//遍历未排序中的每一个元素（待排序序列中第一个元素默认有序）
    {
        temp=a[i];
        for(j=i;j>0 && temp< a[j-1];j--)//依次将未排序序列a[1]~a[n]中的元素与已排序序列中的元素a[0]~a[i]进行比较，直到找到一个逆序数或者与有排序的全部元素比较完毕
        {
            a[j]=a[j-1];//交换
        }
        a[j]=temp;//此时的j为for循环结束后的j-1
    }
}
void ShellSort(int a[],int n)
{
    int i,j,increment;
    int temp;
    for(increment=n/2;increment>0;increment/=2)//设置增量序列的值
    {
        for(i=increment;i<n;i++)//找到每组的中间元素
        {
            temp=a[i];
            for(j=i;j>=increment;j-=increment)//比较同组元素，组内相邻元素的间隔为increment
            {
                if(temp<a[j-increment])//组内元素之间依次比较大小
                    a[j]=a[j-increment];
                else
                    break;
            }
            a[j]=temp;
        }
    }
}
void PercDown(int a[],int i,int n)//下滤
{
    int child;
    int temp;
    for(temp=a[i];LeftChild(i)<n;i=child)//依次找孩子，直到孩子为堆中的最后一个节点
    {
        child=LeftChild(i);//更新孩子节点的位置
        if(child!=n-1 && a[child+1]>a[child])//如果左孩子不是堆中最后的一个并且右孩子的值比左孩子的值大
            child=child+1;//更新孩子的位置为右孩子所在的位置，即寻找左右孩子中较小的那个
        if(temp<a[child])
            a[i]=a[child];//如果父节点的元素值小于子节点元素值，则更新父节点的值为子节点的值
        else
            break;
    }
    a[i]=temp;//更新位置i上的元素值
}
void HeapSort(int a[],int n)//堆排序
{
    int i;
    for(i=n/2;i>=0;i--)
        PercDown(a,i,n);//构建二叉堆
    for(i=n-1;i>0;i--)
    {
        swap(&a[0],&a[i]);//交换根节点和最后一个节点的值
        PercDown(a,0,i);//对根节点进行下滤操作
    }
}
void Merge(int a[],int temp[],int Lpos,int Rpos,int RightEnd)//归并两个有序序列
{
    int i,LeftEnd,NumElements,tempPos;
    LeftEnd=Rpos-1;//左子序列的结束位置
    tempPos=Lpos;//临时数组的开始位置
    NumElements=RightEnd-Lpos+1;//根据元素的起始和结束位置计算元素的个数
    while(Lpos<=LeftEnd && Rpos<=RightEnd)//当两个序列中元素的位置都未到达序列的结束位置
    {
        if(a[Lpos]<=a[Rpos])//当前要合并的两个子序列中元素位置未出现交叉，且左子序列的元素值小于右子序列的元素值
            temp[tempPos++]=a[Lpos++];//将左子序列中当前指示的元素放到临时数组中
        else
            temp[tempPos++]=a[Rpos++];//将右子序列中当前指示的元素放到临时数组中
    }
    while(Lpos<=LeftEnd)//当右子序列中所指示的元素位置到达右子序列的结尾时，将左子序列中剩下的元素按顺序拷贝到临时数组中
        temp[tempPos]=a[Lpos++];
    while(Rpos<=RightEnd)//当左子序列中所指示的元素位置到达左子序列的结尾时，将右子序列中剩下的元素按顺序拷贝到临时数组中
        temp[tempPos]=a[Rpos++];
    for(i=0;i<NumElements;i++,RightEnd--)
    {
        a[RightEnd]=temp[RightEnd];//将排序后的临时数组中的各个元素拷贝到原数组中
    }
}
void MSort(int a[],int temp[],int Left,int Right)//归并排序
{
    int center;
    if(Left < Right)
    {
        center=(Left+Right)/2;
        MSort(a,temp,Left,center);//递归的将原序列分割成两个子序列
        MSort(a,temp,center+1,Right);
        Merge(a,temp,Left,center+1,Right);//将分割的两个子序列归并
    }
}
void MergeSort(int a[],int n)
{
    int *temp;
    temp=malloc(n*sizeof(int));//申请临时存储空间
    if(temp!=NULL)
    {
        MSort(a,temp,0,n-1);//对维度为n的数组进行归并排序，左边从下标为0处开始，右边到下标n-1处结束
        free(temp);
    }
    else
        printf("No space for temp array!");
}
int Division(int a[],int Left,int Right)//三数中值分割寻找枢纽元
{
    int center=(Left+Right)/2;//找序列中心位置
    if(a[Left]>a[center])   //依次比较序列左端、中心位置、右端元素的大小，交换不符合从小到大排列的元素
        swap(&a[Left],&a[center]);
    if(a[Left]>a[Right])
        swap(&a[Left],&a[Right]);
    if(a[Right]< a[center])
        swap(&a[Right],&a[center]);

    swap(&a[center],&a[Right-1]);//选取中心位置处的元素作为枢纽元
    return a[Right-1];//返回枢纽元的大小
}
void QuickSort(int a[],int Left,int Right)//快速排序
{
    int i,j;
    int P;//标记枢纽元的大小
    if(Left+Cutoff <= Right)//判断数组中元素的个数是否符合快速排序的容量要求，当数组中元素个数小于3时，通过Division后就已经有序
    {
        P=Division(a,Left,Right);
        i=Left;
        j=Right-1;
        for( ; ; )
        {
            while(a[++i]<P) {}//左边标记元素的值小于枢纽元时，不做任何操作
            while(a[--j]>P) {}//右边标记元素的值大于枢纽元时，不做任何操作
            if(i<j)//当未出现交错时，且左边标记的元素值大于枢纽元且右边标记的元素值小于枢纽元时，交换两个元素的位置
                swap(&a[i],&a[j]);
            else
                break;//否则，跳出循环
        }
        swap(&a[i],&a[Right-1]);//将枢纽元的位置与左端标记停止的位置交换
        QuickSort(a,Left,i-1);//递归的对左边部分进行快速排序
        QuickSort(a,i+1,Right);//递归的对右边部分进行快速排序
    }
    else
        return;
}
int main()
{
    int num=17;
    int A[17] = {3,2,5,7,9,10,1,11,8,15,0,4,13,17,20,18,16};
    printf("原数组：");
    for(int i=0;i<num;i++)
    {
        printf("%d\t",A[i]);
    }
    printf("\n");
    printf("选择排序的结果：");
    SelectSort(A,num);
    for (int i = 0; i < num; i++)
        printf("%d\t", A[i]);
    printf("\n");
    printf("冒泡排序的结果：");
    BubbleSort(A,num);
    for (int i = 0; i < num; i++)
        printf("%d\t", A[i]);
    printf("\n");
    printf("插入排序的结果：");
    InsertSort(A,num);
    for (int i = 0; i < num; i++)
        printf("%d\t", A[i]);
    printf("\n");
    printf("希尔排序的结果：");
    ShellSort(A,num);
    for (int i = 0; i < num; i++)
        printf("%d\t", A[i]);
    printf("\n");
    printf(" 堆排序的结果：");
    HeapSort(A,num);
    for (int i = 0; i < num; i++)
        printf("%d\t", A[i]);
    printf("\n");
    printf("归并排序的结果：");
    HeapSort(A,num);
    for (int i = 0; i < num; i++)
        printf("%d\t", A[i]);
    printf("\n");
    printf("快速排序的结果：");
    QuickSort(A,0,num-1);
    for (int i = 0; i < num; i++)
        printf("%d\t", A[i]);
    return 0;
}
