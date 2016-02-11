#ifndef _JOSEPH_RING_H_
#define _JOSEPH_RING_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int index;
	int value;
	struct _node *next;
} Node;

typedef struct _list{
	Node *head;
	//Node *last;
	int len;
} JosephRing;

JosephRing* createRing();
void init(JosephRing* pList);
Node* createNode(int number);
int getLength(JosephRing* pList);
void printAll(JosephRing* pList);
Node* delNode(JosephRing* pList, Node* del);
void insert(JosephRing* pList, int x);
int getNumber(JosephRing* pList, int k, int m);
int newGetNumber(JosephRing* pList, int k);
#endif