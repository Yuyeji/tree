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
void tree_delete(Node* node, int key);
void deleteNode(Node *root, int key);
//Node* RemoveNode(Node* tree, int data);

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
		printf("������ ���� �Է����ּ���.");
		scanf("%d", &input);
		tree_delete(root, input);
		printNode(root);
		printf("\n");

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

void tree_delete(Node* node, int key) {
	Node *temp = node; //��带 Ž���ϴ� temp
	Node *parent = temp; //�θ� ���
	Node *del; //tempƮ�� ����

	while ((temp != NULL) && (temp->key != key)) { // �����Ϸ��� key�� ã��
		parent = temp;

		if (temp->key < key) //ũ��
			temp = temp->right; //������
		else //������
			temp = temp->left; //����
	}

	del = temp; //������ Ű �� ��ġ ����

	if (temp == NULL) {  //������ ��尡 ���� ��� 
		printf("\n���� �Ϸ��� ���� �����ϴ�.\n");
		return;
	}

	/*x has no children -> remove x*/
	if (temp->left == NULL && temp->right == NULL) {
		if (parent->left) {
			if (temp->key == parent->left->key) {
				parent->left = NULL;
			}
		}
		else {
			parent->right = NULL;
		}
			return 1;
	}
	/*x has one child -> splice out x*/
	else if ((temp->left == NULL) || (temp->right == NULL)) {
		if (temp->right != NULL) { //���� �Ϸ��� ��尡 �������ڽ� ���� ��
			if (parent->left->key == key) {
				parent->left = temp->right;
			}
			else {
				parent->right = temp->right;
			}
		}
		if (temp->left != NULL) { //���� �Ϸ��� ��尡 �����ڽ� ���� ��
			if (parent->left->key == key) {
				parent->left = temp->left;
			}
			else {
				parent->right = temp->left;
			}
		}
	}
	/*x has two child */
	else {
		temp = temp->left; //���� �Ϸ��� ����� �������� 
		if (temp->right == NULL) { //�����ڽĿ� ������ �ڽ� ���� ���
			del->key = temp->key;
			del->left = temp->left;
		}
		while (1) {
			if (temp->right == NULL) {
				del->key = temp->key;
				parent->right = temp->left;
			}
			else {
				parent = temp;
				temp = temp->right;
			}
		}
	}
}
