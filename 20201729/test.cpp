
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef char BTDataType;
typedef struct BinaryTreeNode {
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
	BTDataType _data;
}BTNode;

// ͨ��ǰ�����������"ABD##E#H##CF##G##"���������� 
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

// ���������� 
void BinaryTreeDestory(BTNode** root) {
	BTNode* cur = *root;
	while (cur) {
		BinaryTreeDestory(&cur->_left);
		BinaryTreeDestory(&cur->_right);
		free(cur);
		*root = NULL;
	}
}

// �������ڵ���� 
int BinaryTreeSize(BTNode* root) {
	//�ݹ�ʵ��
	if (root == NULL)
		return 0;
	return BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}

//�ۼӼ�����
void BinaryTreeSize2(BTNode* root, int* count) {
	if (root) {
		(*count)++;
		BinaryTreeSize2(root->_left);
		BinaryTreeSize2(root->_right);
	}
}

// ������Ҷ�ӽڵ����
int BinaryTreeLeafSize(BTNode* root) {
	if (root == NULL)
		return 0;
	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);
}

// ��������k��ڵ���� 
int BinaryTreeLevelKSize(BTNode* root, int k) {
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

// ����������ֵΪx�Ľڵ� 
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

// ������ǰ��ݹ���� 
void BinaryTreePrevOrder(BTNode* root) {
	if (root) {
		printf("%c ", root->_data);
		BinaryTreePrevOrder(root->_left);
		BinaryTreePrevOrder(root->_right);
	}
}
//�������ǵݹ�ǰ�����
void BinaryTreePrevOrderNor(BTNode* root) {
	//����ջ��ɷǵݹ�
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

// ����������ݹ���� 
void BinaryTreeInOrder(BTNode* root) {
	if (root) {
		BinaryTreeInOrder(root->_left);

		printf("%c ", root->_data);
		BinaryTreeInOrder(root->_right);
	}
}
//�������ǵݹ��������
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

// ����������ݹ����
void BinaryTreePostOrder(BTNode* root) {
	if (root) {
		BinaryTreePostOrder(root->_left);
		BinaryTreePostOrder(root->_right);

		printf("%c ", root->_data);
	}
}


//����������ǵݹ����
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


// //���ö���ʵ�ֲ������
void BinaryTreeLevelOrder(BTNode* root) {
	Queue q;
	QueueInit(&q);
	BTNode* front;
	if (root)
		QueuePush(&q, root);
	//�������в�Ϊ��
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

// �ж϶������Ƿ�����ȫ������
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