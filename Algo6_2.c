#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

typedef struct Node {
	struct Node *left;
	struct Node *right;
	struct Node *data;
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
void tree_insert(Node* node, Node* k);
void printNode(Node* node);
Node* tree_search(Node *node, int num);
Node* tree_search2(Node *node, int num);

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


	while (1) {
		printf("ã�� ���� �Է����ּ���.");
		scanf("%d", &input);
		findNode = tree_search2(root, input);

		if (findNode != NULL) {
			printf("���� ã�ҽ��ϴ�.\n");
			printNode(root);
			printf("\n");
		}
		else {
			printf("���� ã�� �� �����ϴ�.\n");
		}
	}

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

void tree_insert(Node* node, Node* k) {

	if (node == NULL) { //null�� ��� ���ο� ��� ����.
		node = createNode(k);
	}
	else { //null�� �ƴ� ���
		if (node->data < k->data) { //���� ������ node�� ũ�� �����ʿ� ����
			if (node->right == NULL)
				node->right = k;
			else
				tree_insert(node->right, k);
		}
		else if (node->data > k->data) { //������ ���ʿ� ����
			if (node->left == NULL)
				node->left = k;
			else
				tree_insert(node->left, k);
		}
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

/*tree_search using recursions*/
Node* tree_search(Node *node, int num) {
	//node�� NULL�϶�
	if (node == NULL)
		return NULL;

	if (node->data == num) //ã�� ���� ���� ��
		return node;
	else if (node->data > num) //ã�� ���� ���� �� ��������
		return tree_search(node->left, num);
	else  //ũ�ٸ� ����������
		return tree_search(node->right, num);
	
}

/*tree_search using iterative*/
Node* tree_search2(Node *node, int num) {
	while (node != NULL){
		if (node->data == num) //ã�� ���� ���� ��
			return node;
		else if (node->data > num) { //ã�� ���� ���� �� ��������
			node = node->left;
		}
		else {  //ũ�ٸ� ����������
			node = node->right;
		}
	}
	return NULL;
}
