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
	int *arr; // 파일의 데이터를 저장할 포인터 변수 선언.
	Node *root = createNode(NULL);
	int size = 1;
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;
	Node *findNode;
	int input;

	f = fopen("data.txt", "r");

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
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
	//	printf("찾을 값을 입력해주세요.");
	//	scanf("%d", &input);
	//	findNode = tree_search2(root, input);

	//	if (findNode != NULL) {
	//		printf("값을 찾았습니다.\n");
	//		printNode(root);
	//		printf("\n");
	//	}
	//	else {
	//		printf("값을 찾을 수 없습니다.\n");
	//	}
	//}

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("\n측정 시간 : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // 테스트 보기 위해.

}

int heap_size(int *arr) { //arr의 크기
	return (_msize((void*)arr) / sizeof(int));
}

Node* tree_insert(Node* node, Node* k) {

	if (node == NULL) { //null일 경우 새로운 노드 생성.
		return(createNode(k));
	}
	else { //null이 아닐 경우
		if (node->data < k->data) { //새로 삽입할 node가 크면 오른쪽에 삽입
			if (node->right == NULL)
				node->right = k;
			else {
				tree_insert(node->right, k);
			}
		}
		else if (node->data > k->data) { //작으면 왼쪽에 삽입
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

/*최소 node*/
Node* tree_minimum(Node* node) {
	while (node->left = NULL)
		node = node->left;

	return node;
}

/*최대 node*/
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