#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

typedef struct Node {
	struct Node *left;
	struct Node *right;
	struct Node *data;
	struct node *p;
	int key;
}Node;

Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;

	return newNode;
}

int heap_size(int *arr);
Node* tree_insert(Node* node, Node* k);
void printNode(Node* node);
Node* tree_minimum(Node* node);
Node* tree_maximum(Node* node);
Node* tree_successor(Node *node);
Node* tree_predecessor(Node *node);

int main(void) {
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	Node *root = createNode(NULL);
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;
	Node *findNode;
	int input;

	f = fopen("data.txt", "r");

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	startTime = clock();

	for (int i = 0; i < heap_size(arr); i++) {
		tree_insert(root, createNode(arr[i]));
	}
	printNode(root);

	//while (1) {
	//	printf("ã�� ���� �Է����ּ���.");
	//	scanf("%d", &input);
	//	findNode = tree_search2(root, input);

	//	if (findNode != NULL) {
	//		printf("���� ã�ҽ��ϴ�.\n");
	//		printNode(root);
	//		printf("\n");
	//	}
	//	else {
	//		printf("���� ã�� �� �����ϴ�.\n");
	//	}
	//}

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("\n���� �ð� : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}

int heap_size(int *arr) { //arr�� ũ��
	return (_msize((void*)arr) / sizeof(int));
}

Node* tree_insert(Node* node, Node* k) {

	if (node == NULL) { //null�� ��� ���ο� ��� ����.
		return(createNode(k));
	}
	else { //null�� �ƴ� ���
		if (node->data < k->data) { //���� ������ node�� ũ�� �����ʿ� ����
			if (node->right == NULL)
				node->right = k;
			else {
				tree_insert(node->right, k);
			}
		}
		else if (node->data > k->data) { //������ ���ʿ� ����
			if (node->left == NULL)
				node->left = k;
			else {
				tree_insert(node->left, k);
			}
		}
		return node;
	}
}

void printNode(Node* node)
{
	if (node == NULL)
		return;
	printNode(node->left);
	printf("%d ", node->data);
	printNode(node->right);
}

/*�ּ� node*/
Node* tree_minimum(Node* node) {
	while (node->left = NULL)
		node = node->left;

	return node;
}

/*�ִ� node*/
Node* tree_maximum(Node* node) {
	while (node->right = NULL)
		node = node->right;

	return node;
}

Node* tree_successor(Node *node) {
	Node* newNode;

	if (node->right != NULL)
		return tree_minimum(node->right);
	newNode = node->p;

	while (newNode != NULL && node == newNode->right) {
		node = newNode;
		newNode = newNode->p;
	}

	return newNode;
		
}

Node* tree_predecessor(Node *node) {
	Node* newNode;

	if (node->left != NULL)
		return tree_maximum(node->left);
	newNode = node->p;

	while (newNode != NULL && node == newNode->left) {
		node = newNode;
		newNode = newNode->p;
	}

	return newNode;

}