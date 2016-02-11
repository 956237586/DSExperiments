#ifndef LinearList_h
#define LinearList_h

typedef struct _listNode{
	int value;
	struct _listNode *next;
} ListNode;

typedef struct _list{
	ListNode *head;
	ListNode *last;
	int len;
} List;

List* createList();
ListNode* createNode(int number);
void listInit(List* pList);
void listAddNode(List* pList, int number);
ListNode* findNodeFrontOf(List* pList, ListNode* node);
ListNode* findNodeById(List* l, int index);
ListNode* findNodeByValue(List* pList, int value);
int getLength(List* pList);
//void printAll(List* pList);
int delNode(List* pList, ListNode* del);
int delNodeById(List* pList, int index);
int delNodeByValue(List* pList, int value);
int getNodeValueById(List* pList, int index);
void setNodeValueById(List* pList, int index, int value);
void insertInto(List* pList, int index, int x);
#endif