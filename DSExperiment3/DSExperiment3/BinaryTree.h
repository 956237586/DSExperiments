#ifndef _BINARY_TREE_
#define _BINARY_TREE_
typedef struct _tree_node {
	int element;
	struct _tree_node* leftChild;
	struct _tree_node* rightChild;
} TreeNode;

typedef TreeNode BinaryTree;

BinaryTree* createBinaryTree();//创建一个二叉树
TreeNode* createTreeNode();//创建一个二叉树节点
void initTreeNode(TreeNode* node);//初始化一个二叉树结点
void preOrderTravel(BinaryTree* tree);//前序遍历二叉树，递归
void preOrderTravelNonRecursive(BinaryTree* tree);//前序遍历二叉树，非递归
void swap(BinaryTree* tree);//交换所有节点的左右子树
void refresh(BinaryTree* node);//刷新显示
void printAll(BinaryTree* tree, int n);//打印整个树
#endif
