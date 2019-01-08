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


	while (1) {
		printf("삭제할 값을 입력해주세요.");
		scanf("%d", &input);
		tree_delete(root, input);
		printNode(root);
		printf("\n");

	}

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

void tree_insert(Node* node, Node* k) {

	if (node == NULL) { //null일 경우 새로운 노드 생성.
		node = createNode(k);
	}
	else { //null이 아닐 경우
		if (node->data < k->data) { //새로 삽입할 node가 크면 오른쪽에 삽입
			if (node->right == NULL)
				node->right = k;
			else
				tree_insert(node->right, k);
		}
		else if (node->data > k->data) { //작으면 왼쪽에 삽입
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
	Node *temp = node; //노드를 탐색하는 temp
	Node *parent = temp; //부모 노드
	Node *del; //temp트리 저장

	while ((temp != NULL) && (temp->key != key)) { // 삭제하려는 key값 찾기
		parent = temp;

		if (temp->key < key) //크면
			temp = temp->right; //오른쪽
		else //작으면
			temp = temp->left; //왼쪽
	}

	del = temp; //삭제할 키 값 위치 저장

	if (temp == NULL) {  //삭제할 노드가 없는 경우 
		printf("\n삭제 하려는 값이 없습니다.\n");
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
		if (temp->right != NULL) { //삭제 하려는 노드가 오른쪽자식 있을 때
			if (parent->left->key == key) {
				parent->left = temp->right;
			}
			else {
				parent->right = temp->right;
			}
		}
		if (temp->left != NULL) { //삭제 하려는 노드가 왼쪽자식 있을 때
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
		temp = temp->left; //삭제 하려는 노드의 왼쪽으로 
		if (temp->right == NULL) { //왼쪽자식에 오른쪽 자식 없을 경우
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
