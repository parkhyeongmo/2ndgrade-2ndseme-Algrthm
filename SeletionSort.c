#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void SelectionSort();

void main() {

	int* pq, n, i;

	scanf("%d", &n); // 배열의 크기 n 입력

	pq = (int*)malloc(sizeof(int) * n); // 크기가 n인 배열 동적할당

	for (i = 0; i < n; i++) { // n개의 정수 입력

		scanf("%d", pq + i);

	}

	SelectionSort(pq, n); // 선택정렬 함수 호출

	for (i = 0; i < n; i++) { // 정렬 된 배열 출력

		printf(" %d", *(pq + i));

	}

	free(pq); // 배열에 사용된 메모리 할당 해제

}

void SelectionSort(int* pq, int n) { // 배열과 배열의 크기를 인자로 하는 선택정렬 함수

	int i, j, tmp, tmp_max;

	tmp = *pq; // 배열의 첫번째 인자를(index 0) 최대값으로 초기화 
	tmp_max = 0;

	for (j = n - 1; j > 0; j--) { // 배열의 끝에서부터 최대값으로 채워나가기 위해 j를 배열의 마지막 인자 위치인 n - 1로 지정해 1씩 감소

		tmp_max = 0; // 매 시행마다 배열의 첫번째 인자를 최대값으로 초기화
		tmp = *pq;

		for (i = 0; i <= j; i++) { // 첫번째 인자부터 해당 시행에서의 마지막까지 순회하며 최대값 탐색
			if (tmp < *(pq + i)) {
				tmp = *(pq + i);
				tmp_max = i;
			}
		}

		*(pq + tmp_max) = *(pq + j); // 해당 시행의 최대값을 마지막 인자와 교체
		*(pq + j) = tmp;

	}

}
