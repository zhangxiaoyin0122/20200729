
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef char BTDataType;
typedef struct BinaryTreeNode {
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
	BTDataType _data;
}BTNode;

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树 
BTNode* BinaryTreeCreat(char* str, int* idx) {
	if (str[*idx] != '#') {
		BTNode* root = (BTNode*)malloc(sizeof(BTNode));
		root->_data = str[*idx];
		++(*idx);
		root->_left = creatTree(str, idx);
		++(*idx);
		root->_right = creatTree(str, idx);
	}
	else {
		return NULL;
	}
}

// 二叉树销毁 
void BinaryTreeDestory(BTNode** root) {
	BTNode* cur = *root;
	while (cur) {
		BinaryTreeDestory(&cur->_left);
		BinaryTreeDestory(&cur->_right);
		free(cur);
		*root = NULL;
	}
}

// 二叉树节点个数 
int BinaryTreeSize(BTNode* root) {
	//递归实现
	if (root == NULL)
		return 0;
	return BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}

//累加计数器
void BinaryTreeSize2(BTNode* root, int* count) {
	if (root) {
		(*count)++;
		BinaryTreeSize2(root->_left);
		BinaryTreeSize2(root->_right);
	}
}

// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root) {
	if (root == NULL)
		return 0;
	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);
}

// 二叉树第k层节点个数 
int BinaryTreeLevelKSize(BTNode* root, int k) {
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

// 二叉树查找值为x的节点 
BTNode* BinaryTreeFind(BTNode* root, BTDataType x) {
	BTNode* ret;
	if (root == NULL)
		return NULL;
	if (root->_data == x)
		return root;
	ret = BinaryTreeFind(root->_left, x);
	if (ret)
		return ret;
	return BinaryTreeFind(root->_right, x);
}

// 二叉树前序递归遍历 
void BinaryTreePrevOrder(BTNode* root) {
	if (root) {
		printf("%c ", root->_data);
		BinaryTreePrevOrder(root->_left);
		BinaryTreePrevOrder(root->_right);
	}
}
//二叉树非递归前序遍历
void BinaryTreePrevOrderNor(BTNode* root) {
	//借助栈完成非递归
	Stack sk;
	StackInit(&sk, 10);
	BTNode* cur = root;
	BTNode* top;
	while (cur || StackEmpty(&sk) != 1) {
		while (cur) {
			printf("%c ", cur->_data);
			StackPush(&sk, cur->_data);
			cur = cur->_left;
		}
		top = StackTop(&sk);
		StackPop(&sk);
		cur = top->_right;
	}
}

// 二叉树中序递归遍历 
void BinaryTreeInOrder(BTNode* root) {
	if (root) {
		BinaryTreeInOrder(root->_left);

		printf("%c ", root->_data);
		BinaryTreeInOrder(root->_right);
	}
}
//二叉树非递归中序遍历
void BinaryTreeInOrderNor(BTNode* root) {
	Stack sk;
	StackInit(&sk, 10);
	BTNode* cur = root;
	BTNode* top;
	while (cur || StackEmpty(&sk) != 1) {
		while (cur) {
			StackPush(&sk, cur->_data);
			cur = cur->_left;
		}
		top = StackTop(&sk);
		printf("%c ", top->_data);
		StackPop(&sk);
		cur = top->_right;
	}
}

// 二叉树后序递归遍历
void BinaryTreePostOrder(BTNode* root) {
	if (root) {
		BinaryTreePostOrder(root->_left);
		BinaryTreePostOrder(root->_right);

		printf("%c ", root->_data);
	}
}


//二叉树后序非递归遍历
void BinaryTreePostOrder(BTNode* root) {
	Stack sk;
	StackInit(&sk, 10);
	BTNode* cur = root;
	BTNode* top;
	BTNode* prev = NULL;
	while (cur || StackEmpty(&sk) != 1) {
		while (cur) {
			cur = cur->_left;
			StackPush(&sk, cur->_data);
		}
		top = StackTop(&sk);
		if (top->_right == NULL || top->_right == prev) {
			printf("%c ", top->_data);
			StackPop(&sk);
			prev = top;
		}
		else
			cur = top->_right;
	}
}


// //利用队列实现层序遍历
void BinaryTreeLevelOrder(BTNode* root) {
	Queue q;
	QueueInit(&q);
	BTNode* front;
	if (root)
		QueuePush(&q, root);
	//条件队列不为空
	while (QueueEmpty(&q) != 1) {
		front = QueueFront(&q);
		printf("%c ", front->_data);
		QueuePop(&q);
		if (front->_left) {
			QueuePush(&q, front->_left);
		}
		if (front->_right) {
			QueuePush(&q, front->_right);
		}
	}
}

// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root) {
	Queue q;
	QueueInit(&q);
	BTNode* front;
	if (root)
		QueuePush(&q, root);
	while (QueueEmpty(&q) != 1) {
		front = QueueFront(&q);
		QueuePop(&q);
		if (front) {
			QueuePush(&q, front->_left);
			QueuePush(&q, front->_right);
		}
		else
			break;
		while (QueueEmpty(&q) != 1) {
			front = QueueFront(&q);
			QueuePop(&q);
			if (front)
				return -1;
		}
	}
	return 1;
}