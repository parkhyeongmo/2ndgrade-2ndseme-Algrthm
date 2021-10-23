#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { // 탐색트리의 노드로 사용할 구조체

	int key;
	struct node* parent, * l, * r;

}NODE;

NODE* getnode();
int findElement();
void insertItem();
NODE* treeSearch();
int removeElement();
int isExternal();
int isInternal();
NODE* inOrderSucc();
int isLeft();
int isRight();
void expendExternal();
void reduceExternal();
void preOrderTravel();
void treeFree();
NODE* sibling();


void main() {

	char cmd;
	int key, ret;
	NODE* T;

	T = getnode(); // 트리 초기화

	while (1) { // q가 입력될 때까지 반복

		scanf("%c", &cmd); // 명령어 입력

		if (cmd == 'i') { // i 입력 시, 키 값을 입력 받고 트리에 삽입
			
			scanf("%d", &key);
			getchar();

			insertItem(T, key);

		}

		else if (cmd == 'd') { // d 입력 시, 키 값을 입력 받고 해당 키 값을 가진 노드를 트리에서 삭제, 해당 키 값을 가진 노드가 없을 시 X 출력
		
			scanf("%d", &key);
			getchar();

			ret = removeElement(T, key);

			if (ret == -1) printf("X\n");
			else printf("%d\n", ret);

		}

		else if (cmd == 's') { // s 입력 시, 키 값을 입력 받고 해당 키 값을 가진 노드가 존재하면 해당 키 출력, 없을 시 X 출력
		
			scanf("%d", &key);
			getchar();

			ret = findElement(T, key);

			if (ret == -1) printf("X\n");
			else printf("%d\n", ret);
		
		}

		else if (cmd == 'p') { // p 입력 시, 트리 전위 순회로 출력

			getchar();
			
			preOrderTravel(T);

			printf("\n");
		
		}

		else if (cmd == 'q') break; // q 입력 시, 프로그램 종료

	}

	treeFree(T); // 트리 메모리 할당 해제

}

NODE* getnode() { // 새로운 노드를 할당하여 주소를 반환하는 함수

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE));

	newnode->parent = NULL; // 내부 포인터들은 모두 NULL로 초기화
	newnode->l = NULL;
	newnode->r = NULL;

	return newnode;

}

int findElement(NODE* T, int key) { // s 입력 시, 키 값을 찾아 반환하는 함수

	NODE* w;

	w = treeSearch(T, key); // 트리 내부를 순회하며 해당 키 값의 위치를 찾아 반환

	if (isInternal(w) == 1) { // 트리 내부에 키 값을 가진 노드가 존재하면 키 값 반환
		return w->key;
	}

	else return -1; // 트리 내부에 키 값을 가진 노드가 존재하지 않으면 -1 반환

}

void insertItem(NODE* T, int key) { // i 입력 시, 트리에 키 값을 삽입하는 함수

	NODE* w;

	w = treeSearch(T, key); // 해당 키 값의 자리를 찾아 반환

	expendExternal(w); // 중복 키 입력은 없으므로 내부노드로 확장하여 키 값 저장

	w->key = key;

}

NODE* treeSearch(NODE* w, int key) { // 키 값이 위치하는 주소 또는 위치해야하는 주소를 찾아 반환하는 함수

	if (w->key == key) return w; // 해당 키 값의 노드 발견 시 반환
	if (isExternal(w)) return w; // 해당 키 값의 자리가 외부노드일 경우 반환

	else if (w->key > key) { // 이진탐색을 통해 키 값이 현재 노드보다 작으면 왼쪽으로 이동하여 재귀 호출

		return treeSearch(w->l, key);

	}

	else { // 이진탐색을 통해 키 값이 현재 노드보다 크면 오른쪽으로 이동하여 재귀 호출

		return treeSearch(w->r, key);

	}

}

int removeElement(NODE* w, int key) { // d 입력 시, 해당 키 값을 가진 노드를 삭제하는 함수

	w = treeSearch(w, key); // 트리 내부를 순회하며 해당 키 값의 위치를 찾아 반환

	if (isExternal(w)) return -1; // 외부노드일 경우 존재하지 않는 키 값이므로 -1 반환

	int k = w->key; // 반환 할 키 값 저장

	if (isExternal(w->l)) { // 해당 노드의 왼쪽 노드가 외부노드일 경우 reduceExternal

		reduceExternal(w->l);

	}

	else if (isExternal(w->r)) { // 해당 노드의 오른쪽 노드가 외부노드일 경우 reduceExternal

		reduceExternal(w->r);

	}

	else { // 양 쪽 자식 노드가 모두 내부노드일 경우 중위순회 계승자를 찾아 키 값을 옮기고 reduceExternal

		NODE* y;

		y = inOrderSucc(w);

		w->key = y->key; // 중위순회 계승자의 키 값 복사

		if (isExternal(y->l)) reduceExternal(y->l);
		else reduceExternal(y->r);

	}

	return k;

}

int isExternal(NODE* w) { // 외부노드 여부 확인 함수, 외부노드면 1, 아니면 0을 반환

	if (w->l == NULL && w->r == NULL) return 1;
	else return 0;

}

int isInternal(NODE* w) { // 내부노드 여부 확인 함수, 내부노드면 1, 아니면 0을 반환

	if (w->l != NULL || w->r != NULL) return 1;
	else return 0;

}

NODE* inOrderSucc(NODE* w) { // 중위순회 계승자를 찾는 함수

	NODE* y;

	y = w->r; // y를 오른쪽 자식으로 초기화

	if (isExternal(y)) { // 오른쪽 자식이 외부노드일 경우 NULL 반환
		return NULL;
	}

	while (isInternal(y)) { // 외부노드가 나올 때까지 y의 왼쪽 자식으로 계속 내려가며 탐색 

		y = y->l;

	}

	return y->parent; // 외부노드가 나왔을 경우 그 부모인 중위순회 계승자 반환

}

void expendExternal(NODE* w) { // 외부노드를 내부노드로 확장하는 함수

	w->l = getnode(); // w 노드의 왼쪽, 오른쪽 자식을 외부노드로 할당
	w->r = getnode();

	w->l->parent = w; // 자식들의 parent를 w로 초기화
	w->r->parent = w;

}

void reduceExternal(NODE* z) { // z와 그 부모인 w를 트리에서 제거하는 함수

	NODE* w = z->parent, * zs;

	zs = sibling(z); // z의 형제를 zs에 반환

	if (w->parent == NULL) { // w가 루트노드일 경우 zs의 정보를 루트에 옮기고 zs의 자식들을 연결 

		NODE* tmp = zs;

		w->key = zs;
		w->l = zs->l;
		w->r = zs->r;

		free(zs); // zs와 z 메모리 할당 해제
		free(z);

		return;

	}

	else { // w가 루트노드가 아닌 일반적인 경우

		NODE* g = w->parent; // w의 부모
		zs->parent = g; // zs의 부모를 g로 저장

		if (w == g->l) g->l = zs; // w의 자리를 zs로 대체함.
		else g->r = zs;

	}

	free(w); // w와 z 메모리 할당 해제
	free(z);

}

void preOrderTravel(NODE* w) { // 선위순회로 트리 정보를 출력하는 함수

	printf(" %d", w->key);

	if (isInternal(w->l)) preOrderTravel(w->l);
	if (isInternal(w->r)) preOrderTravel(w->r);

}

void treeFree(NODE* T) { // 후위순회로 트리 메모리 할당 해제 함수

	if (T->l != NULL) treeFree(T->l);
	if (T->r != NULL) treeFree(T->r);

	free(T);

}

NODE* sibling(NODE* w) { // 노드의 형제를 찾는 함수

	if (w->parent == NULL) return NULL; // 루트노드일 경우 형제가 없으므로 NULL 반환

	if (w->parent->l == w) return w->parent->r; // 왼쪽 자식일 경우 오른쪽 자식 반환
	else return w->parent->l; // 오른쪽 자식일 경우 왼쪽 자식 반환

}