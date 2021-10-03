#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void InsertionSort();

void main() {

	int* pq, n, i;

	scanf("%d", &n); // 배열의 크기 n 입력

	pq = (int*)malloc(sizeof(int) * n); // 크기가 n인 배열 동적할당

	for (i = 0; i < n; i++) { // n개의 정수 입력

		scanf("%d", pq + i);

	}

	InsertionSort(pq, n); // 선택정렬 함수 호출

	for (i = 0; i < n; i++) { // 정렬 된 배열 출력

		printf(" %d", *(pq + i));

	}

	free(pq); // 배열에 사용된 메모리 할당 해제

}

//void InsertionSort(int* pq, int n) { // 배열과 배열의 크기를 인자로 하는 삽입정렬 함수
//
//	int i, j, tmp;
//
//	for (j = 1; j < n; j++) { // 배열의 맨 앞 두개 원소부터 정렬하도록 진행
//
//		for (i = j; i >= 0 || *(pq + i) > *(pq + i - 1); i--) { // 매 시행의 마지막 원소부터 첫번째 원소까지 크기를 비교하며 원소의 위치를 바꾸며 다음 인자가 더 작은 경우 반복문 종료
//
//			if (*(pq + i) < *(pq + i - 1)) { // 반복문의 조건에서 다음 인자보다 더 작은 경우 위치를 변경
//				tmp = *(pq + i);
//				*(pq + i) = *(pq + i - 1);
//				*(pq + i - 1) = tmp;
//			}
//
//		}
//
//	}
//
//}

void InsertionSort(int* pq, int n) { // 배열과 배열의 크기를 인자로 하는 삽입정렬 함수

	int i, j, tmp;

	for (i = 1; i < n; i++) { // 배열의 맨 앞 두개 원소부터 정렬하도록 진행

		tmp = *(pq + i);
		j = i - 1;

		while (j >= 0 && *(pq + j) > tmp) { // 매 시행의 마지막 원소부터 첫번째 원소까지 크기를 비교하며 위치를 옮기고 다음 원소가 더 작은 경우 반복문 종료

			*(pq + j + 1) = *(pq + j);
			j--;

		}

		*(pq + j + 1) = tmp; // 해당 원소의 위치에 삽입

	}

}