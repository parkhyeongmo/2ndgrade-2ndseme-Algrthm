// 알고리즘및실습 Quiz01(ADT review) - 2번
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { // 트리의 노드로 사용할 구조체

	char id;
	struct node* left, * right;

}NODE;

typedef struct tnode { // 트리의 정보를 담을 연결리스트의 노드로 사용할 구조체

	char id, left, right;
	struct tnode* next;

}tNODE;

NODE* getnode() { // 새로운 노드(tree)를 만드는 함수

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE));
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;

}

tNODE* findRoot(tNODE* L) { // 입력받은 트리의 정보에서 Root 탐색 

	tNODE* t, * p;
	char id;

	for (t = L->next; t != NULL; t = t->next) {

		id = t->id;

		for (p = L->next; p != NULL; p = p->next) {
			if (id == p->left || id == p->right) {
				break;
			}
		}

		if (p == NULL) {
			break;
		}

	}

	return t;

}

tNODE* findNode(char id, tNODE* L){ // 트리를 제작할 때 특정 id를 가진 노드의 정보를 연결리스트에서 탐색

	tNODE* p;

	for (p = L; L != NULL; p = p->next) {

		if (p->id == id) break;

	}

	return p;

}

NODE* makeTree(tNODE* t, tNODE* L) { // 트리 제작 함수

	NODE* newnode;
	tNODE* tmp;

	newnode = getnode();
	newnode->id = t->id;

	if (t->left != '0') {

		tmp = findNode(t->left, L);
		newnode->left = makeTree(tmp, L);

	}

	if (t->right != '0') {

		tmp = findNode(t->right, L);
		newnode->right = makeTree(tmp, L);

	}

	return newnode;

}

void preOrder(NODE* t) { // 전위순회를 통해 트리를 탐색

	printf("%c", t->id);

	if (t->left != NULL) {
		preOrder(t->left);
	}

	if (t->right != NULL) {
		preOrder(t->right);
	}

}

void treeFree(NODE* t) { // 트리에 사용된 메모리 할당 해제

	if (t->left != NULL) {
		treeFree(t->left);
	}

	if (t->right != NULL) {
		treeFree(t->right);
	}

	free(t);

}

void main() {

	int i, n;
	NODE* R;
	tNODE* L = NULL, * tmp, * tmpp;
	char id, left, right;

	scanf("%d", &n); // 노드의 개수 입력
	getchar();

	for (i = 0; i < n; i++) { // 연결리스트에 입력받은 정보 저장

		scanf("%c %c %c", &id, &left, &right);
		getchar();

		tmp = (tNODE*)malloc(sizeof(tNODE));
		tmp->id = id;
		tmp->left = left;
		tmp->right = right;
		tmp->next = L;	

		L = tmp;

	}

	tmp = findRoot(L); // 루트를 찾아 트리 제작
	R = makeTree(tmp, L);

	preOrder(R); // 전위순회로 트리의 id 출력

	tmp = L;

	while (tmp != NULL) { // 연결리스트 메모리 할당 해제

		tmpp = tmp->next;
		free(tmp);
		tmp = tmpp;

	}

	treeFree(R); // 트리 메모리 할당 해제


}