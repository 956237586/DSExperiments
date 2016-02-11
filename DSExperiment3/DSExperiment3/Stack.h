#ifndef _STACK_
#define _STACK_
#include "BinaryTree.h"
typedef struct _stack_node {
	TreeNode* element;
	struct _stack_node* next;
} StackNode;

typedef struct _stack {
	int currentSize;//当前元素个数
	int size;
	StackNode* top;//头指针
} Stack;

Stack*  createStack(int maxSize); //创建栈
int isFullStack(Stack* s); //判断堆栈S是否已满；
void push(Stack* s, TreeNode* item); // 将元素item压入堆栈；
int isEmptyStack(Stack* s); // 判断堆栈S是否为空；
int pop(Stack* s, TreeNode** i); // 删除并返回栈顶元素,失败返回0,成功的话变量会被存到i；
						   //如果传NULL给i，那么就顶元素就不会被存到i
//void printAll(Stack* s); //预览栈当前状态
#endif