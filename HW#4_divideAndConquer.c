#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct subject { // 연결리스트에서 정보를 저장할 노드

	char name[21]; // 이름, 학번을 인자로 가진다.	
	int id;

	struct subject* next; // 리스트의 다음 노드 정보를 저장할 포인터

}SUB;

typedef struct part { // partition 함수에서 분할된 리스트 정보를 저장하고 반환하는데 사용될 구조체

	struct subject* L1, * L2;

}part;

SUB* getnode();
part partition();
SUB* divideAndConquer();

void main() {

	int id, n, i;
	SUB* L = NULL, * tmp = NULL, * ttmp = NULL;
	char name[21];

	scanf("%d", &n); // 원소의 개수 입력

	for (i = 0; i < n; i++) { // 연결리스트에 n개의 정보를 입력받아 저장

		if (i == 0) {
			L = getnode();
			tmp = L;
		}

		else {
			ttmp = getnode();
			tmp->next = ttmp;
			tmp = ttmp;
		}

		scanf("%d %s", &id, name);

		strcpy(tmp->name, name);
		tmp->id = id;

	}

	scanf("%d", &id); // 탐색할 ID 입력

	tmp = divideAndConquer(L, n, id); // 분할통치법으로 탐색

	if (tmp == NULL) // 일치하는 ID가 없을 경우 -1 출력
		printf("-1\n");

	else // 일치하는 ID를 찾았을 경우 발견한 정보 출력
		printf("%d %s\n", tmp->id, tmp->name);

	tmp = L;

	while (tmp != NULL) { // 메모리 할당 해제

		ttmp = tmp->next;
		free(tmp);
		tmp = ttmp;

	}

}


SUB* getnode() { // 새로운 노드를 할당받는 함수

	SUB* newnode;

	newnode = (SUB*)malloc(sizeof(SUB));

	newnode->next = NULL;

	return newnode; // 새로 할당된 노드의 주소 반환

}

part partition(SUB* L, int k) { // 리스트 L을 k개와 그 이외의 원소들로 분리해주는 함수

	int i = 0;
	SUB* tmp = NULL;
	part p;

	tmp = L;

	for (i = 1; i < k; i++) { // 리스트를 k개(n / 2)까지 구분

		tmp = tmp->next;

	}

	p.L2 = tmp->next; // 분할된 리스트의 뒷 부분 p 구조체의 L2에 저장

	tmp->next = NULL; // 분할된 리스트의 앞 부분의 끝을 NULL로 바꿔 분리 시킨 뒤 p 구조체의 L1에 저장
	p.L1 = L;

	return p; // 분할된 리스트 정보 반환

}

SUB* divideAndConquer(SUB* L, int n, int id) { // 분할통치법으로 특정 ID 탐색

	if (n == 1) { // 더 이상 분할할 구간이 없을 경우 해당 노드를 검사

		if (L->id == id) // 찾는 ID와 일치할 경우 해당 노드 주소 반환
			return L;

		else // 일치하지 않을 경우 NULL 반환
			return NULL;

	}

	int k;
	part p;
	SUB* tmp;

	k = n / 2;

	p = partition(L, k); // 전달받은 리스트를 절반으로 분할

	tmp = divideAndConquer(p.L1, k, id); // 분할한 리스트의 앞 부분을 재귀호출

	if (tmp != NULL) return tmp; // 앞 부분에서 일치하는 ID를 찾았을 경우 반환

	tmp = divideAndConquer(p.L2, n - k, id); // 분할한 리스트의 뒷 부분을 재귀호출

	return tmp; // 탐색 결과 반환

}