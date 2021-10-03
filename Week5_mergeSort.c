#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node { // 연결리스트를 구성할 노드 구조체

	int e;
	struct node* next;

}NODE;

typedef struct list { // 합병정렬의 분할에 사용될 리스트 두개의 주소를 가지는 구조체

	NODE* L1;
	NODE* L2;

}LIST;

NODE* getnode();
void mergeSort();
NODE* merge();
LIST partition();

void main() {

	int t, n, i;
	NODE* L = NULL, *tmp, *ttmp;

	scanf("%d", &n); // 연결리스트의 크기 입력

	for (i = 0; i < n; i++) { // 원소 입력 및 연결리스트 만들기
		scanf("%d", &t);
		
		tmp = getnode(t);
		tmp->next = L;
		L = tmp;

	}

	mergeSort(&L, n); // 합병 정렬 함수 호출

	tmp = L;

	while (tmp != NULL) { // 정렬 된 연결리스트 출력

		printf(" %d", tmp->e);
		tmp = tmp->next;
	
	}

	tmp = L;

	while (tmp != NULL) { // 메모리 할당 해제

		ttmp = tmp->next;
		free(tmp);
		tmp = ttmp;

	}

}

NODE* getnode(int n) { // 새로운 노드를 생성하는 함수

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE)); // 새로운 노드를 동적할당 후 입력된 원소로 초기화 후 next를 NULL로 초기화
	newnode->e = n;
	newnode->next = NULL;

	return newnode;

}

void mergeSort(NODE** L, int n) { // 이중포인터 L과 리스트 원소 크기를 나타내는 n을 인자로 하는 합병정렬 함수
	
	LIST r;
	NODE* L2 = NULL;
	int k;

	if (n == 1) return; // 더 이상 분할 할 수 없을 경우 base case

	k = n / 2;

	r = partition(*L, k); // 분할 함수 호출, LIST 구조체에 분할된 리스트 정보 반환

	*L = r.L1; // 분할 된 리스트 초기화
	L2 = r.L2;

	mergeSort(L, k); // 재귀를 통해 base case까지 함수 호출
	mergeSort(&L2, n - k);

	*L = merge(*L, L2); // 분할 후 정렬되어 돌아온 연결리스트 합병

}

NODE* merge(NODE* L1, NODE* L2) { // 각각 정렬 된 두개의 연결리스트를 정렬하여 합병하는 함수

	NODE* L = NULL;

	if (L1 == NULL) return L2; // L1 리스트가 NULL이 되었을 경우 L2를 그대로 뒤에 붙일수 있도록 반환
	else if (L2 == NULL) return L1; // L2 리스트가 NULL이 되었을 경우 L1를 그대로 뒤에 붙일수 있도록 반환

	if (L1->e < L2->e) { // L1이 L2보다 작을 경우 리스트의 뒤에 해당 차례 L1의 최소 원소를 연결 후 L1을 한 칸 전진시켜 함수 다시 호출
		L = L1;
		L->next = merge(L1->next, L2);
	}

	else { // L2가 L1보다 작거나 같을 경우 리스트의 뒤에 해당 차례 L2의 최소 원소를 연결 후 L2를 한 칸 전진시켜 함수 다시 호출
		L = L2;
		L->next = merge(L1, L2->next);
	}

	return L; // 합병 정렬 된 리스트 반환

}

LIST partition(NODE* L1, int k) { // 하나의 리스트를 k개와 n - k개인 리스트로 분할하는 함수

	int i;
	LIST r;
	NODE* tmp = L1;

	for (i = 0; i < k - 1; i++) { // 0 ~ k - 1까지 진행하며 리스트 순회
		
		tmp = tmp->next;

	}

	r.L2 = tmp->next; // k + 1번째 원소부터는 L2로 연결
	
	tmp->next = NULL; // k번째 노드의 next를 NULL로 초기화해 두개의 리스트로 분리

	r.L1 = L1; // 1번째 노드부터 k번째 노드까지 L1에 연결

	return r; // 두 리스트의 정보를 가진 r 구조체 반환

}