#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
typedef int ElementType;
struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
AVLTree MakeEmpty(AVLTree T);
Position Find(ElementType X,AVLTree T);
Position FindMin(AVLTree T);
Position FindMax(AVLTree T);
int Height(Position P);
int Max(int a,int b);
static Position LeftSingleRotate(Position K2);
static Position RightSingleRotate(Position K1);
static Position LeftDoubleRotate(Position K3);
static Position RightDoubleRotate(Position K1);
AVLTree Insert(ElementType X,AVLTree T);
ElementType Retrieve(Position P);
#endif // AVLTREE_H_INCLUDED
