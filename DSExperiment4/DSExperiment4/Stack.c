/*栈的链表实现*/
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

//创建栈
Stack*  createStack(int maxSize) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack != NULL) {
		stack->top.element = maxSize;
		stack->top.next = NULL;
		stack->currentSize = 0;
	}
	return stack;
}
//判断堆栈S是否已满
int isFullStack(Stack* s) {
	return s->currentSize == s->top.element;
}

// 将元素item压入堆栈
void push(Stack* s, int item) {
	StackNode* newItem = NULL;
	//if (isFullStack(s) == 0) {
	if (!isFullStack(s)) {
		newItem = (StackNode*)malloc(sizeof(StackNode));
		newItem->element = item;
		newItem->next = s->top.next;
		s->top.next = newItem;
		s->currentSize++;
		//printf("push %d\n", item);
	} else {
		printf("Stack is already full!\n");
	}
}

// 判断堆栈S是否为空；
int isEmptyStack(Stack* s) {
	return s->currentSize == 0;
}

// 删除并返回栈顶元素,失败返回0,成功的话变量会被存到i；
int pop(Stack* s, int* i) {
	int ret;
	StackNode* t = s->top.next;
	//if (isEmptyStack(s) == 0) {
	if (!isEmptyStack(s)) {
		if (i != NULL) {
			*i = s->top.next->element;
		}
		//printf("pop %d\n", s->top.next->element);//为方便观察效果打印结果
		s->top.next = t->next;
		free(t);
		s->currentSize--;
		ret = 1;
	} else {
		printf("Stack is  already empty!\n");
		ret = 0;//特殊值，标志错误
	}
	return ret;
}

int top(Stack* s, int* i) {
	int ret = 0;
	if (!isEmptyStack(s)) {
		ret = 1;
		*i = s->top.next->element;
	}
	return ret;
}

//预览栈当前状态
/*/
void printAll(Stack* s) {
	StackNode* t = s->top.next;
	int i = s->currentSize - 1;
	
	if (t == NULL) {
		printf("Empty Stack\n");
	} else {
		while (t != NULL) {
			printf("elements[%d] = %d\n", i--, t->element);
			t = t->next;
		}
	}
	printf("\n");
}
//*/