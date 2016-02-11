#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Linearlist.h"
#include "Stack.h"
#include "Queue.h"

//创建一个图
Graph* createGraph(char* path){
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if(graph) graph->path = path;
	return graph;
}

//从文件加载图信息，并创建图
Graph* loadFile(char* path) {
	Graph* graph = createGraph(path);
	FILE* in = initFile(path, "graph.txt", "r");
#ifdef _DEBUG_
	int i;
	ListNode* t;
#endif
	if(in) initGraph(graph, in);
	else return NULL;
#ifdef _DEBUG_
	for (i = 0; i < graph->countVertexes; i++) {
		printf("%d ", graph->adjacencyTable[i].value);
		t = graph->adjacencyTable[i].adj->head;
		while (t) {
			printf(" %d", t->value);
			t = t->next;
		}
		printf("\n");
	}
#endif
	fclose(in);
	return graph;
}

//指定模式初始化文件
FILE* initFile(char* path, char* fileName, char* mode) {
	FILE* file = NULL;
	char* filePath = (char*)malloc(strlen(path) * 2);
	if(filePath) strcpy(filePath, path);
	filePath = strcat(filePath, fileName);
	file = fopen(filePath, mode);
	return file;
}

//初始化图信息
void initGraph(Graph* graph, FILE* in) {
	fscanf(in, "%d %d", &graph->countVertexes, &graph->countEdges);
#ifdef _DEBUG_
	printf("%d %d", graph->countVertexes, graph->countEdges);
#endif
	initSearch(graph, in);
	initAdjacencyTable(graph, in);
}

//初始化搜索信息
void initSearch(Graph* graph, FILE* in) {
	if (graph) {
		graph->searchConfig = (SearchConfig*)malloc(sizeof(SearchConfig));
		fscanf(in, "%d %d %d", &graph->searchConfig->src, &graph->searchConfig->des, &graph->searchConfig->length);
#ifdef _DEBUG_
		printf("%d %d %d", graph->searchConfig->src, graph->searchConfig->des, graph->searchConfig->length);
#endif
	}
}

//初始化邻接表
void initAdjacencyTable(Graph* graph, FILE* in) {
	graph->adjacencyTable = (TableNode*)malloc(sizeof(TableNode)* graph->countVertexes);
	initVertexes(graph, in);
	initEdges(graph, in);
}

//初始化所有顶点
void initVertexes(Graph* graph, FILE* in) {
	int i;
	if (graph) {
		graph->vertexes = (Vertex**)malloc(sizeof(Vertex*) * graph->countVertexes);
		if (graph->vertexes) {
			for (i = 0; i < graph->countVertexes; i++) {
				fscanf(in, "%*d %*d %*d %*d");
#ifdef _DEBUG_
				printf("%d\n", i);
#endif
				graph->vertexes[i] = createVertex(i);
				graph->adjacencyTable[i].value = i;
				graph->adjacencyTable[i].adj = createList();
			}
		}
	}
}

//初始化所有边
void initEdges(Graph* graph, FILE* in) {
	int i;
	int vertex1;
	int vertex2;
	if (graph) {
		graph->edges = (Edge**)malloc(sizeof(Edge*) * graph->countEdges);
		if (graph->edges) {
			for (i = 0; i < graph->countEdges; i++) {
				fscanf(in, "%*d %d %d", &vertex1, &vertex2);
#ifdef _DEBUG_
				printf("%d %d %d\n", i, vertex1, vertex2);
#endif
				graph->edges[i] = createEdge(graph->vertexes[vertex1], graph->vertexes[vertex2]);
				listAddNode(graph->adjacencyTable[vertex1].adj, vertex2);
				listAddNode(graph->adjacencyTable[vertex2].adj, vertex1);
			}
		}
	}
}

//创建一个顶点
Vertex* createVertex(int id) {
	Vertex* ret;
	ret = (Vertex*)malloc(sizeof(Vertex));
	if(ret) ret->id = id;
	return ret;
}

//创建一条边
Edge* createEdge(Vertex* vertex1, Vertex* vertex2) {
	Edge* ret;
	ret = (Edge*)malloc(sizeof(Edge));
	if (ret) {
		ret->vertex1 = vertex1;
		ret->vertex2 = vertex2;
	}
	return ret;
}



void outputVertex(FILE* file, int vertex) {
	if(file) fprintf(file, "%d ", vertex);
#ifdef _DEBUG_
	printf("%d \n", vertex);
#endif
}

//深度优先搜索
void DFS(Graph* graph) {
	TableNode* adjs = graph->adjacencyTable;
	SearchConfig* config = graph->searchConfig;
	FILE* out = initFile(graph->path, "DFS.txt", "w");
	Stack* stack = createStack(graph->countVertexes);
	int* visited = (int*)malloc(sizeof(int) * graph->countVertexes);
	int i = 0, flag = 0, vertex = config->src;
	ListNode* t = NULL;

	for (i = 0; i < graph->countVertexes; i++)visited[i] = 0;
	push(stack, vertex);
	visited[vertex] = 1;
	outputVertex(out, vertex);
	while (!isEmptyStack(stack)) {
		top(stack, &vertex);
		flag = 0;
		for (t = adjs[vertex].adj->head; t;t = t->next){
			if (!visited[t->value]) {
				push(stack, t->value);
				flag = visited[t->value] = 1;
				outputVertex(out, t->value);
				break;
			}
		}
		if (!flag) pop(stack, &vertex);
	}
	fclose(out);
}

//广度优先搜索
void BFS(Graph* graph) {
	TableNode* adjs = graph->adjacencyTable;
	SearchConfig* config = graph->searchConfig;
	FILE* out = initFile(graph->path, "BFS.txt", "w");
	Queue* queue = createQueue(graph->countVertexes);
	int* visited = (int*)malloc(sizeof(int) * graph->countVertexes);
	int i = 0, vertex = config->src;
	ListNode* t = NULL;
	
	for (i = 0; i < graph->countVertexes; i++) visited[i] = 0;
	append(queue, vertex);
	visited[vertex] = 1;
	while (!isEmptyQueue(queue)) {
		serve(queue, &vertex);
		outputVertex(out, vertex);
		for (t = adjs[vertex].adj->head; t; t = t->next){
			if (!visited[t->value]) {
				append(queue, adjs[t->value].value);
				visited[t->value] = 1;
			}
		}
	}
	fclose(out);
}

void printResult(Graph* graph, Stack* s, FILE* out) {
	StackNode* t = s->top.next;
	Stack* result = createStack(100);
	int i = 0;
	if (s->currentSize - 1 == graph->searchConfig->length) {
		for (i = 0; i < s->currentSize; i++) {
			push(result, t->element);
			t = t->next;
		}
		while (!isEmptyStack(result)) {
			pop(result, &i);
			fprintf(out, "%d ", i);
#ifdef _DEBUG_
			printf("%d ", t);
#endif
		}
		fprintf(out, "\n");
	}
}

//搜索指定长度的路径，顶点ID从src到des
void search(Graph* graph) {
	TableNode* adjs = graph->adjacencyTable;
	SearchConfig* config = graph->searchConfig;
	FILE* out = initFile(graph->path, "Search.txt", "w");
	Stack* stack = createStack(graph->countVertexes);
	int* visited = (int*)malloc(sizeof(int) * graph->countVertexes);
	int i = 0, j = 0, flag = 0, vertex = config->src;
	ListNode* t = NULL;
	int** vertexVisited = (int**)malloc(sizeof(int*) * graph->countVertexes);
	
	for (i = 0; i < graph->countVertexes; i++) {
		visited[i] = 0;
		vertexVisited[i] = (int*)malloc(sizeof(int) * graph->countVertexes);
		for (j = 0; j < graph->countVertexes; j++) {
			vertexVisited[i][j] = 0;
		}
	}
	push(stack, vertex);
	visited[vertex] = 1;
	while (!isEmptyStack(stack)) {
		top(stack, &vertex);
		if (vertex == config->des) {
			visited[vertex] = 0;
			printResult(graph, stack, out);
			pop(stack, NULL);
		} else {
			flag = 0;
			for (t = adjs[vertex].adj->head; t; t = t->next) {
				if (!visited[t->value] &&!vertexVisited[vertex][t->value]) {
					push(stack, t->value);
					vertexVisited[vertex][t->value] = 1;
					flag = visited[t->value] = 1;
					break;
				}
			}
			if (!flag) {
				for (t = adjs[vertex].adj->head; t; t = t->next) {
					visited[vertex] = 0;
					vertexVisited[vertex][t->value] = 0;
				}
				pop(stack, NULL);
			}
		}
	}
	fclose(out);
}