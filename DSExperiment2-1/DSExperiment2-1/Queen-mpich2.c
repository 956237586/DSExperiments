/*/
文件名称：Queen.c
项目名称：DSExperiment2
创建者：黄永亮
创建时间：2015.10.21
最后修改时间：2017.3.20
功能：八皇后程序主文件
文件中的函数名称和简单功能描述：见下面
文件中定义的全局变量和简单功能描述：见下面
文件中用到的他处定义的全局变量及其出处：无
//*/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
void search(CheesBoard chs, int start, int end);//开始搜索,闭区间
int beAttacked(Queens queens, int n);//第n个是否被攻击
int isSameColumn(Queens queens, int queen1, int queen2);//检测是否同列
int isSameMainDiagonal(Queens queens, int queen1, int queen2);//检测是否同主对角线
int isSameDiagonal(Queens queens, int queen1, int queen2);//检测是否同副对角线
void printResult(CheesBoard chs);//打印结果

/*
函数名称：main
函数功能描述：入口函数
*/
int main(int argc, char* argv[]) {
	int cheesBoardSize = 8;
	CheesBoard eightQueen = NULL;
	double startwtime = 0.0;
	double endwtime = 0.0;
	int myid;//进程ID
	int numprocs;//进程总数
	int namelen;//进程名称长度
	int result = 0;//总结果
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int base;//开始地址
	int split;//分片大小

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Get_processor_name(processor_name, &namelen);

	if (argc > 1) {
		sscanf(argv[1], "%d", &cheesBoardSize);//从命令行读入参数
	} else {
		if (myid == 0) {
			fprintf(stdout, "without input Board Size, use default value 8\n");
			fprintf(stdout, "usage: ./a.out cheesBoardSize\n");
			fflush(stdout);
		}
	}
	if (cheesBoardSize % numprocs != 0) {
		if (myid == 0) {
			fprintf(stdout, "you should ensure board size %% processes num == 0\ne.g.:mpiexec -n 4 ./a.out 8 ");
			fflush(stdout);
		}
		return 1;
	}
	eightQueen = createCheesBoard(cheesBoardSize);
	if (myid == 0) {
		startwtime = MPI_Wtime();
	}
	
	split = cheesBoardSize / numprocs;
	base = split * myid;
	fprintf(stdout, "Process %d of %d is on %s\n",
		myid, numprocs, processor_name);
	fflush(stdout);
	fprintf(stdout, "Process %d of %d base is searching in (%d - %d)\n",
		myid, numprocs, base, base + split - 1);
	fflush(stdout);

	search(eightQueen, base, base + split - 1);

	fprintf(stdout, "Process %d of %d (%d - %d) result = %d\n",
		myid, numprocs, base, base + split - 1, eightQueen->count);
	fflush(stdout);
	MPI_Reduce(&(eightQueen->count), &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myid == 0) {
		endwtime = MPI_Wtime();
		fprintf(stdout, "wall clock time = %f\n", endwtime - startwtime);
		fprintf(stdout, "sum of result is %d\n", result);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}

/*
函数名称：search
函数功能描述：开始搜索
返回值（如果有的话）：无
函数的输入参数(可选)：数量n
*/
void search(CheesBoard chs,int start ,int end) {
	Queens queens = chs->queens;
	int n = chs->size;
	int i = 0;
	chs->queens[0] = start;
	while (i < n) {
		if (!beAttacked(queens, i)) {		//如果没被攻击
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

			if (i != 0 || (i == 0 && queens[i] != end)) {//如果当前进程做完了自己的探索就结束
				queens[i]++;//当前行的位置向后移动一位
			} else if (i == 0 && queens[i] == end) {
				chs->end = 1;
			}
		}
		if (chs->end) break;
		if (i == n) {						//如果n行都搜索完毕
			(chs->count)++;					//结果变量加1
#ifdef _DEBUG_
			printResult(chs);				//打印当前结果
#endif			
			while (queens[i - 1] == n - 1){	//把最后一行再移动一次位置
				queens[--i] = 0;			//继续搜索下一个结果
			}
			if (i - 1 != 0 || (i - 1 == 0 && queens[0] != end)) {
				queens[--i]++; 
			}else if (i == 0 && queens[i] == end){
				chs->end = 1;
				break;
			}
		}
#ifdef _DEBUG_
		printResult(chs);
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
	system("clear");
	
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
}
