#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"
#include "Queue.h"
#include "Stack.h"

/*
函数名称：createBinaryTree
函数功能描述：创建一个二叉树
返回值（如果有的话）：根节点指针
函数的输入参数(可选)：无
*/

BinaryTree* createBinaryTree() {
	BinaryTree* tree = createTreeNode();
	printf("Please input root node\n");
	initTreeNode(tree);
	return tree;
}

/*
函数名称：createTreeNode
函数功能描述：创建一个二叉树节点
返回值（如果有的话）：树节点指针
函数的输入参数(可选)：无
*/

TreeNode* createTreeNode() {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->element = -1;
	node->leftChild = node->rightChild = NULL;
	return node;
}


/*
函数名称：initTreeNode
函数功能描述：初始化一个二叉树结点,层序初始化
返回值（如果有的话）：无
函数的输入参数(可选)：树节点指针
*/

void initTreeNode(TreeNode* node) {
	int t;
	TreeNode* temp;
	Queue* queue = creatQueue(10000);
	append(queue, node);
	refresh(node);
	while (!isEmptyQueue(queue)) {
		serve(queue, &temp);
		printf("Please input value of first x:");
		scanf("%d", &temp->element);
		printf("This node has childs ?(1:yes, 0:no)\n", temp->element);
		printf("left child ?:");
		scanf("%d", &t);
		if (t) {
			temp->leftChild = createTreeNode();
			append(queue, temp->leftChild);
		}
		printf("right child ?:", temp->element);
		scanf("%d", &t);
		if (t) {
			temp->rightChild = createTreeNode();
			append(queue, temp->rightChild);
		}
		refresh(node);
	}
}

/*
函数名称：preOrderTravel
函数功能描述：前序遍历二叉树，递归
返回值（如果有的话）：无
函数的输入参数(可选)：树根指针
*/

void preOrderTravel(BinaryTree* tree) {
	if (tree) {
		printf("%d ", tree->element);
		preOrderTravel(tree->leftChild);
		preOrderTravel(tree->rightChild);
	}
}

/*
函数名称：preOrderTravel
函数功能描述：前序遍历二叉树，非递归
返回值（如果有的话）：无
函数的输入参数(可选)：树根指针
*/
void preOrderTravelNonRecursive(BinaryTree* tree) {
	Stack* stack = createStack(1000);
	TreeNode* temp = tree;
	while (temp || !isEmptyStack(stack)) {
		while (temp) {
			printf("%d ", temp->element);
			push(stack, temp);
			temp = temp->leftChild;
		}
		if (!isEmptyStack(stack)) {
			pop(stack, &temp);
			temp = temp->rightChild;
		}
	}
	printf("\n");
}


/*
函数名称：swap
函数功能描述：交换所有节点的左右子树
返回值（如果有的话）：无
函数的输入参数(可选)：树根指针
*/

void swap(BinaryTree* tree) {
	TreeNode* t;
	if (tree) {
		t = tree->leftChild;
		tree->leftChild = tree->rightChild;
		tree->rightChild = t;
		swap(tree->rightChild);
		swap(tree->leftChild);
	}
}

/*
函数名称：refresh
函数功能描述：刷新显示
返回值（如果有的话）：无
函数的输入参数(可选)：树根指针
*/

void refresh(BinaryTree* node) {
	system("cls");
	printf("Current Tree:\n\n");
	printAll(node, 0);
	printf("\n");
}


/*
函数名称：printAll
函数功能描述：打印整个树
返回值（如果有的话）：无
函数的输入参数(可选)：树根指针，层次n
*/
void printAll(BinaryTree* tree, int n) {
	int i = n;
	if (tree) {
		printAll(tree->leftChild, n + 1);
		while (i--)printf("\t");
		if (tree->element != -1)printf("%d", tree->element);
		else printf("x");
		printf("\n");
		printAll(tree->rightChild, n + 1);
	}
}
