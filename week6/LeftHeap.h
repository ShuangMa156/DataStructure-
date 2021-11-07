#ifndef LEFT_HEAP_H_INCLUDED
#define LEFT_HEAP_H_INCLUDED
#define Insert(X,H) (H=Insert1((X),H))
#define DeleteMin(H)(H=DeleteMin1(H))
typedef int ElementType;//说明元素的数据类型为int
struct TreeNode;//定义节点对应的结构体
typedef struct TreeNode* PriorityQueue;//创建一个可以指向每个节点的对应指针作为一个优先队列
PriorityQueue Initialize(void);
int IsEmpty(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
PriorityQueue MergeHeap(PriorityQueue H1,PriorityQueue H2);
PriorityQueue Insert1(ElementType X,PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);
#endif // LEFT_HEAP_H_INCLUDED
