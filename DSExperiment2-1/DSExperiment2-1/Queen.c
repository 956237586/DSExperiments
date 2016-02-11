// 我真诚地保证：

// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢 刘鸿喆学长对我的启发和帮助。下面的报告中，我还会具体地提到
// 他们在各个方法对我的帮助。

// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未没抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。

// 黄永亮

/*/
文件名称：Queen.c
项目名称：DSExperiment2
创建者：黄永亮
创建时间：2015.10.21
最后修改时间：2015.10.22
功能：八皇后程序主文件
文件中的函数名称和简单功能描述：见下面
文件中定义的全局变量和简单功能描述：见下面
文件中用到的他处定义的全局变量及其出处：无
//*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//#define _DEBUG_ //调试模式切换
typedef int* Queens;
struct _chessBoard {
	Queens queens;//皇后数组
	int size;//规模
	int end;//搜索结束标志
	int count;//结果计数器
};
typedef struct _chessBoard* CheesBoard;

CheesBoard createCheesBoard(int size);//初始化棋盘
Queens createQueens(int n);//初始化皇后棋盘
void search(CheesBoard chs);//开始搜索
int beAttacked(Queens queens, int n);//第n个是否被攻击
int isSameColumn(Queens queens, int queen1, int queen2);//检测是否同列
int isSameMainDiagonal(Queens queens, int queen1, int queen2);//检测是否同主对角线
int isSameDiagonal(Queens queens, int queen1, int queen2);//检测是否同副对角线
void printResult(CheesBoard chs);//打印结果

/*
函数名称：main
函数功能描述：入口函数
*/
int main() {
	CheesBoard eightQueen = createCheesBoard(11);
	search(eightQueen);
	system("pause");
	return 0;
}

/*
函数名称：search
函数功能描述：开始搜索
返回值（如果有的话）：无
函数的输入参数(可选)：数量n
*/
void search(CheesBoard chs) {
	Queens queens = chs->queens;
	int n = chs->size;
	int i = 0;

	while (i < n) {
		if (!beAttacked(queens, i)) {		//如果不被攻击
			i++;							//尝试下一行
		} else {
			while (queens[i] == n - 1) {	//如果已经尝试过当行所有位置
				if (i != 0) {				//如果不是第一行则归零
					queens[i--] = 0;		//并把i减1
				} else {					//否则结束搜索
					chs->end = 1; 
					break;
				}
			}
			queens[i]++;					//当前行的位置向后移动一位
		}
		if (chs->end) break;
		if (i == n) {						//如果n行都搜索完毕
			(chs->count)++;					//结果变量加1
			printResult(chs);				//打印当前结果
			while (queens[i - 1] == n - 1){	//把最后一行再移动一次位置
				queens[--i] = 0;			//继续搜索下一个结果
			}
			queens[--i]++;
		}
#ifdef _DEBUG_
		printResult(chs);
		system("pause");
#endif
	}
}

/*
函数名称：createChessBoard
函数功能描述：初始化棋盘
返回值（如果有的话）：初始化好的棋盘
函数的输入参数(可选)：规模size
*/

CheesBoard createCheesBoard(int size) {
	CheesBoard cheesBoard = (CheesBoard)malloc(sizeof(struct _chessBoard));
	cheesBoard->end = 0;
	cheesBoard->count = 0;
	cheesBoard->size = size;
	cheesBoard->queens = createQueens(size);
	return cheesBoard;
}

/*
函数名称：createQueens
函数功能描述：创建并初始化棋盘
返回值（如果有的话）：创建好的棋盘
函数的输入参数(可选)：皇后数量n
*/

Queens createQueens(int n) {
	int i;
	Queens queens = (Queens)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) queens[i] = 0;
	return queens;
}

/*
函数名称：beAttacked
函数功能描述：判断第n个是否被攻击
返回值（如果有的话）：如果被攻击返回1，反之返回0
函数的输入参数(可选)：棋盘变量以及要判断的皇后位置
*/

int beAttacked(Queens queens, int n) {
	int i = 0;
	int ret = 0;
	for (i = 0; i < n; i++) {
		if (isSameColumn(queens, i, n) || isSameMainDiagonal(queens, i, n)
			|| isSameDiagonal(queens, i, n)) {
			ret = 1;
			break;
		}
	}
	return ret;
}

/*
函数名称：isSameColumn
函数功能描述：检测是否同列
返回值（如果有的话）：同列返回1，否则返回0
函数的输入参数(可选)：皇后数组以及要判断的两个皇后
*/

int isSameColumn(Queens queens, int queen1, int queen2) {
	return queens[queen1] == queens[queen2];
}

/*
函数名称：isSameMainDiagonal
函数功能描述：检测是否同主对角线
返回值（如果有的话）：同主对角线返回1，否则返回0
函数的输入参数(可选)：皇后数组以及要判断的两个皇后
*/

int isSameMainDiagonal(Queens queens, int queen1, int queen2) {
	return queen2 - queen1 == queens[queen2] - queens[queen1];
}

/*
函数名称：isSameDiagonal
函数功能描述：检测是否同副对角线
返回值（如果有的话）：同副对角线返回1，否则返回0
函数的输入参数(可选)：皇后数组以及要判断的两个皇后
*/
int isSameDiagonal(Queens queens, int queen1, int queen2) {
	return queen1 + queens[queen1] == queen2 + queens[queen2];
}

//打印当前棋盘结果
void printResult(CheesBoard chs) {
	int i = 0;
	int j = 0;
	system("cls");
	printf("\n-----------------\n");
	for (i = 0; i < chs->size; i++) {
		for (j = 0; j < chs->size; j++) {
			if (chs->queens[i] == j)printf(" *");
			else printf(" -");
		}
		printf("\n");
	}
	printf("-----------------\n");
	printf(" count = %d\n", chs->count);
#ifdef _DEBUG_
	Sleep(30);
#else
	Sleep(100);
#endif
}
