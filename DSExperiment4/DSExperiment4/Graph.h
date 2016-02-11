#ifndef Graph_h
#define Graph_h
#include "Linearlist.h"
#include "Stack.h"
//#define _DEBUG_
typedef struct _tableNode {
	int value;
	List* adj;
} TableNode;

typedef struct _vertex {
	int id;
} Vertex;

typedef struct _edge {
	Vertex* vertex1;
	Vertex* vertex2;
} Edge;


typedef struct _searchConfig {
	int src;
	int des;
	int length;
} SearchConfig;

typedef struct _graph {
	int countVertexes;
	int countEdges;
	char* path;
	Vertex** vertexes;
	Edge** edges;
	TableNode* adjacencyTable;
	SearchConfig* searchConfig;
} Graph;


Graph* loadFile(char* path);//从文件加载图信息，并创建图
FILE* initFile(char* path, char* fileName, char* mode);//指定模式初始化文件
Graph* createGraph(char* path);//创建一个图
void initGraph(Graph* graph, FILE* in);//初始化图信息
void initSearch(Graph* graph, FILE* in);//初始化搜索信息
void initAdjacencyTable(Graph* graph, FILE* in);//初始化邻接表
void initVertexes(Graph* graph, FILE* in);//初始化所有顶点
void initEdges(Graph* graph, FILE* in);//初始化所有边
void outputVertex(FILE* file, int vertex);//输出顶点信息
Vertex* createVertex(int id);//创建一个顶点
Edge* createEdge(Vertex* vertex1, Vertex* vertex2);//创建一条边
void DFS(Graph* graph);//深度优先搜索
void BFS(Graph* graph);//广度优先搜索
void printResult(Graph* graph, Stack* s, FILE* out);//打印结果
void search(Graph* graph);//搜索指定长度的路径，顶点ID从src到des
#endif
