#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;//Position表示指向一个结点
typedef struct TreeNode *SearchTree;//SearchTree代表指向一个二叉搜索树（默认指向根结点）
SearchTree MakeEmpty(SearchTree T);//构造一棵空树
Position Find(ElementType X,SearchTree T);//指数中寻找某一特定元素值所在的结点
Position FindMin(SearchTree T);//寻找树中最小元素的位置
Position FindMax(SearchTree T);//寻找树中最大元素所在的位置
SearchTree Insert(ElementType X,SearchTree T);//L
SearchTree DeleteRT(ElementType X,SearchTree T);//删除书中的某一个结点,以右子树的最小值代替
SearchTree DeleteLT(ElementType X,SearchTree T);//删除书中的某一个结点，以左子树的最大值代替
ElementType Retrieve(Position P);//寻找树中某一位置的特定元素值
void PrintTreeF(SearchTree T);//树的前序遍历
void PrintTreeM(SearchTree T);//树的中序遍历
void PrintTreeB(SearchTree T);//树的后序遍历
#endif // TREE_H_INCLUDED
