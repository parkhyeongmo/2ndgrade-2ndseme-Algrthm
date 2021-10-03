#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void rBuildHeap();
void buildHeap();
void downHeap();
void printArray();
int removeMax();
void inPlaceHeapSort();


void main() {

	int H[100], n = 0;
	int j;

	scanf("%d", &j); // 입력 받을 키의 개수 입력

	for (n = 1; n <= j; n++) { // 키를 입력 받는 순서대로 배열에 삽입

		scanf("%d", H + n);

	}

	n -= 1; // for문의 마지막에 n이 1만큼 더 늘어났으므로 감소시켜준다.

	buildHeap(H, n); // 힙 생성 함수를 호출해 배열 내부 정렬

	//rBuildHeap(H, 1, n);

	//inPlaceHeapSort(H, &n); // 제자리 힙 정렬 함수 호출

	printArray(H, n); // 정렬된 배열 출력

}


void rBuildHeap(int* H, int i, int n) { // 재귀적 방식으로 힙을 만드는 함수

	if (i > n) return; // 베이스케이스 더 이상 부트리가 없을 경우 종료

	rBuildHeap(H, 2 * i, n); // 해당 회차의 왼쪽 부트리 생성 호출
	rBuildHeap(H, 2 * i + 1, n); // 해당 회차의 오른쪽 부트리 생성 호출

	downHeap(H, i, n); // 해당 회차의 루트를 정렬해 왼쪽, 오른쪽 부트리를 하나의 힙으로 생성

}

void buildHeap(int* H, int n) { // 비재귀적 방식으로 힙을 만드는 함수

	int i;

	for (i = n / 2; i >= 1; i--) { // 마지막 내부노드부터 루트까지 downheap을 해가며 heap 정렬해준다.

		downHeap(H, i, n);

	}

}



void downHeap(int* H, int i, int n) { // i 위치에 있는 키의 위치를 찾아 내려 보내 주는 함수

	int bigger, tmp;

	if (i * 2 > n) return; // 자식 노드가 없으면 더 이상 내려갈 곳이 없으므로 정지

	bigger = i * 2; // 왼쪽 자식 노드를 일단 더 큰 값으로 초기화

	if (i * 2 + 1 <= n && *(H + (i * 2)) < *(H + (i * 2 + 1))) { // 오른쪽 자식 노드가 존재하고 왼쪽보다 클 경우 더 큰 값으로 초기화

		bigger = i * 2 + 1;

	}

	if (*(H + i) > *(H + bigger)) return; // 자식 노드 중 큰 값보다 자신이 더 크면 정지

	if (*(H + i) < *(H + bigger)) { // 자식 노드 중 큰 값이 자신의 키보다 크면 위치 변경

		tmp = *(H + bigger);
		*(H + bigger) = *(H + i);
		*(H + i) = tmp;

	}


	downHeap(H, bigger, n); // 바뀐 위치에서 다시 자식 노드와 비교를 위해 재귀 호출

}

void printArray(int* H, int n) { // 힙의 내용을 레벨순서로 인쇄하는 함수

	int i;

	for (i = 1; i <= n; i++) { // 1번부터 n번까지 순서대로 인쇄

		printf(" %d", *(H + i));

	}

}

int removeMax(int* H, int* n) { // 힙의 최대키를 삭제 후 반환하는 함수

	int key = *(H + 1); // 반환할 값을 위해 최대키를 임시로 저장

	*(H + 1) = *(H + *n); // 힙의 마지막인 n 위치의 키를 루트로 옮겨준다.
	(*n)--;

	downHeap(H, 1, *n); // 루트로 옮겨온 키의 순서를 찾아 정렬

	return key; // 삭제된 키 값 반환

}

void inPlaceHeapSort(int* H, int* n) { // 생성된 힙을 바탕으로 배열을 제자리 힙 정렬 해주는 함수

	while (*n >= 1) { // 루트를 제외한 힙의 원소들이 모두 제거될 때까지 반복

		*(H + *n + 1) = removeMax(H, n); // 해당 회차의 최대값을 반환받아 제자리에 삽입

	}

}

