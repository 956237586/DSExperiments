// 我真诚地保证：

// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢 XXX, …, XXX对我的启发和帮助。下面的报告中，我还会具体地提到
// 他们在各个方法对我的帮助。

// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未没抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。

// 黄永亮

/*/
文件名称：stack.c
项目名称：DSExperiment1
创建者：黄永亮
创建时间：201.9.12
最后修改时间：2015.9.17
功能：栈的数组实现
文件中的函数名称和简单功能描述：见下面
文件中定义的全局变量和简单功能描述：见下面
文件中用到的他处定义的全局变量及其出处：无
与其他文件的依赖关系：stack.h
//*/

#include "stack.h"

/*/
函数名称：testStack
函数功能描述：对所有其他函数进行测试，如果无法返回1说明有错
函数调用之前的预备条件：其他函数正常
返回值（如果有的话）：1
函数的输入参数：无
//*/
int testStack() {
	Stack* stack = NULL;
	int i = 0, size = 10;

	printf("创建空栈：\n");
	stack = createStack(size);
	printAll(stack);

	printf("设置元素：\n");
	while (isFull(stack) == 0) {
		push(stack, i++);
		printAll(stack);
	}

	printf("边界测试，在满栈状态下继续push：\n");
	push(stack, 10);

	printf("pop * 5：\n");
	pop(stack, NULL);
	pop(stack, NULL); 
	pop(stack, NULL); 
	pop(stack, NULL); 
	pop(stack, NULL); 
	printAll(stack);

	printf("push * 2：\n");
	push(stack, 111);
	push(stack, 222);
	printAll(stack);

	printf("pop所有内容：\n");
	while (isEmpty(stack) == 0) {
		pop(stack, NULL);
		printAll(stack);
	}

	printf("边界测试，在空栈状态下继续pop：\n");
	pop(stack, NULL);//边界测试

	system("pause");
	return 0;
}

/*/
函数名称：createStack
函数功能描述：创建指定大小的栈
函数调用之前的预备条件：无
返回值（如果有的话）：创建成功的栈指针，失败返回NULL
函数的输入参数：栈的最大大小
//*/
Stack*  createStack(int maxSize) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if(stack != NULL){
		stack->size = maxSize;
		stack->top = -1;
		stack->elements = (double*)malloc(maxSize * sizeof(double));
	}
	return stack;
}

/*/
函数名称：isFull
函数功能描述：判断堆栈s是否已满
函数调用之前的预备条件：栈指针不是NULL
返回值（如果有的话）：满栈返回1，否则返回0
函数的输入参数：栈指针
//*/
int isFull(Stack* s) {
	return s->top == s->size - 1;
}

/*/
函数名称：push
函数功能描述：将元素item压入堆栈
函数调用之前的预备条件：栈指针不是NULL，且栈不满
返回值（如果有的话）：无
函数的输入参数：栈指针，要push的元素
//*/
void push(Stack* s, double item) {
	//if (isFull(s) == 0) {
	if (!isFull(s)) {
		s->top++;
		s->elements[s->top] = item;//注意这两句的顺序
		//printf("push %lf\n", item);
	} else {
		printf("Stack is already full!\n");
	}
}

/*/
函数名称：isEmpty
函数功能描述：判断堆栈s是否为空栈；
函数调用之前的预备条件：栈指针不是NULL
返回值（如果有的话）：空则返回1否则返回0
函数的输入参数：栈指针
//*/
int isEmpty(Stack* s) {
	return s->top == -1;
}

/*/
函数名称：pop
函数功能描述：删除并返回栈顶元素
函数调用之前的预备条件：栈不空
返回值（如果有的话）：失败返回0，成功返回1并且变量会被存到i
函数的输入参数：栈指针，要存储结果的变量地址（传入NULL不进行储存）
//*/
int pop(Stack* s, double* i) {
	int ret;
	//if (isEmpty(s) == 0) {
	if (!isEmpty(s)) {
		if (i != NULL) {
			*i = s->elements[s->top];
		}
		//printf("pop %lf\n", s->elements[s->top]);//为方便观察效果打印结果
		s->top--;//注意这两句的顺序
		ret = 1;
	} else {
		printf("Stack is  already empty!\n"); 
		ret = 0;//特殊值，标志错误
	}
	return ret;
}

/*/
函数名称：seek
函数功能描述：查看当前栈顶
函数调用之前的预备条件：栈不空
返回值（如果有的话）：栈顶元素
函数的输入参数：栈指针
//*/
double seek(Stack* s) {
	return s->elements[s->top];
}

/*/
函数名称：printAll
函数功能描述：预览栈当前状态
函数调用之前的预备条件：栈指针不为空
返回值（如果有的话）：无
函数的输入参数：栈指针
//*/
void printAll(Stack* s) {
	int i = 0;
	if (!isEmpty(s)) {
		for (i = s->top; i >= 0; i--) {
			printf("elements[%d] = %lf\n", i, s->elements[i]);
		}
	} else {
		printf("Empty Stack\n");
	}
	printf("\n");
}