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
文件名称：stack.h
项目名称：DSExperiment1
创建者：黄永亮
创建时间：201.9.12
最后修改时间：2015.9.17
功能：堆栈的结构设计头文件
文件中的函数名称和简单功能描述：见下面
文件中定义的全局变量和简单功能描述：见下面
文件中用到的他处定义的全局变量及其出处：无
与其他文件的依赖关系：使用标准输入输出的库函数
//*/

#ifndef stack_h
#define stack_h
#include <stdio.h>
#include <stdlib.h>
typedef struct _stack {
	double* elements;
	int size;
	int top;
} Stack;

Stack*  createStack(int maxSize); //创建栈
int isFull(Stack* s); //判断堆栈S是否已满；
void push(Stack* s, double item); // 将元素item压入堆栈；
int isEmpty(Stack* s); // 判断堆栈S是否为空；
double seek(Stack* s);//查看当前栈顶
int pop(Stack* s, double* i); // 删除并返回栈顶元素,失败返回0,成功的话变量会被存到i；
//如果传NULL给i，那么就顶元素就不会被存到i
void printAll(Stack* s); //预览栈当前状态
int testStack();//测试函数
#endif