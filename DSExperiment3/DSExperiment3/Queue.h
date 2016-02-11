#ifndef _QUEUE_
#define _QUEUE_
#include "BinaryTree.h"
typedef struct _queue_node {
	TreeNode* element;
	struct _queue_node* next;
} QueueNode;

typedef struct _queue {
	int currentSize;//当前元素个数
	int maxSize;
	QueueNode* first;//指向第一个节点的指针
	QueueNode* last;
} Queue;

Queue* creatQueue(int maxSize); //生成长度为MaxSize的空队列；
int isFullQueue(Queue* q); // 判断队列Q是否已满；
void append(Queue* q, TreeNode* item);// 将数据元素item插入队列Q中；
int isEmptyQueue(Queue* q);// 判断队列Q是否为空；
int serve(Queue* q, TreeNode** firstItem); // 将队头数据元素从队列中删除并返回。
//void printAll(Queue* q); //预览队列当前状态
#endif