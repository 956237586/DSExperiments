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
文件名称：calculator.h
项目名称：DSExperiment1
创建者：黄永亮
创建时间：201.9.12
最后修改时间：2015.9.17
功能：计算器程序设计头文件
文件中的函数名称和简单功能描述：见下面
文件中定义的全局变量和简单功能描述：见下面
文件中用到的他处定义的全局变量及其出处：无
与其他文件的依赖关系：stack.h
//*/

#ifndef __CALCU
#define __CALCU
#include "stack.h"
#define MAXSIZE 2000 //最大长度
int calculator(char * string);//入口函数，传入NULL手动输入
int calcu();//默认传给上个函数NULL参数，手动输入
char* preTreat(char** s);//过滤无效字符以及重复的小数点
int check(char* s);//输入合法性检查
void errorWarning(char* warning);//错误警告
int isOperator(char c);//操作符判断
int isNumber(char c);//数字判断
double encode(char c);//操作符编码
char decode(double d);//操作符解码
int priority(char c);//运算优先级
void merge(Stack* numbers, Stack* operators);//进行一次运算
double calculate(char operate, double num1, double num2);//实际运算					 
double parseNum(char** s);//解析一个数字
int canCalculate(char c, Stack* operators);//与当前栈顶元素比较优先级

#endif