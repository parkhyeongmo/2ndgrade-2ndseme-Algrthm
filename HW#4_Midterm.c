/*
본 시험에서 문제 풀이에는 O(NlogN)의 속도를 보장하는 합병정렬을 사용하였다. 또한 공간 복잡도 O(N)을 유지하기 위해 제자리 합병정렬을 사용해야했고 이에 따라 연결리스트를 이용한 것이다.
정렬 시 같은 키 값을 가졌더라도 먼저 입력된 순서를 유지해 안정성을 가져가고자 했다. 때문에 역순으로 저장되는 연결리스트를 구현한 상황에서 순서상 뒤에 나온 같은 키 값을 먼저 저장하는 방식을 선택했다.
*/

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct subject { // 연결리스트에서 정보를 저장할 노드

	char subid[11]; // 학생ID, 과목 이름, 과목ID를 인자로 가진다.
	char subname[21];
	char stid[11];

	struct subject* next; // 리스트의 다음 노드 정보를 저장할 포인터

}SUB;

typedef struct part { // partition 함수에서 분할된 리스트 정보를 저장하고 반환하는데 사용될 구조체

	struct subject* L1, * L2;

}part;

SUB* getnode();
void mergeSort();
part partition();
SUB* merge();

void main() {

	int n, i;
	SUB* L = NULL, * tmp = NULL, * ttmp = NULL;
	char si[11], sn[21], sti[11];

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

		scanf("%s %s %s", si, sn, sti);

		strcpy(tmp->subid, si);
		strcpy(tmp->subname, sn);
		strcpy(tmp->stid, sti);

	}

	mergeSort(&L, n); // 합병정렬

	tmp = L;

	while (tmp != NULL) { // 정렬된 리스트 출력

		printf("%s %s %s\n", tmp->subid, tmp->subname, tmp->stid);
		tmp = tmp->next;

	}

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

void mergeSort(SUB** L, int n) { // 합병정렬 함수

	if (n <= 1) return; // 더 이상 분할할 수 없는 경우 반환

	int k;
	part p;
	SUB* L2;

	k = n / 2;

	p = partition(*L, k); // 인자로 받은 리스트를 절반으로 분할

	*L = p.L1;
	L2 = p.L2;

	mergeSort(L, k); // 분할된 리스트의 앞 부분 재귀호출
	mergeSort(&L2, n - k); // 분할된 리스트의 뒷 부분 재귀호출

	*L = merge(*L, L2); // 분할 후 정렬되어 올라온 부리스트들 합병

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

SUB* merge(SUB* L1, SUB* L2) { // 각각 정렬 된 두개의 연결리스트를 정렬하여 합병하는 함수

	SUB* L = NULL;

	if (L1 == NULL) return L2; // L1 리스트가 NULL이 되었을 경우 L2를 그대로 뒤에 붙일수 있도록 반환
	else if (L2 == NULL) return L1; // L2 리스트가 NULL이 되었을 경우 L1를 그대로 뒤에 붙일수 있도록 반환

	if (strcmp(L1->subid, L2->subid) <= 0) { // L1이 L2보다 작거나 같을 경우 리스트의 뒤에 해당 차례 L1의 최소 원소를 연결 후 L1을 한 칸 전진시켜 함수 다시 호출
		L = L1;
		L->next = merge(L1->next, L2);
	}

	else { // L2가 L1보다 작거나 같을 경우 리스트의 뒤에 해당 차례 L2의 최소 원소를 연결 후 L2를 한 칸 전진시켜 함수 다시 호출
		L = L2;
		L->next = merge(L1, L2->next);
	}

	return L; // 합병 정렬 된 리스트 반환

}