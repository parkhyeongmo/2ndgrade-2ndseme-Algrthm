#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void SelectionSort();
void InsertionSort();
void Reverse_InsertionSort();

void main() {

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	int* Apq, * Bpq, n, i;

	scanf("%d", &n); // 배열의 크기 n 입력

	Apq = (int*)malloc(sizeof(int) * n); // 크기가 n인 배열 동적할당
	Bpq = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));

	for (i = 0; i < n; i++) { // n개의 난수를 두개의 배열에 입력

		*(Apq + i) = *(Bpq + i) = rand();

	}

	Reverse_InsertionSort(Apq, n); // C 방식의 측정을 위한 역정렬 함수 호출	
	Reverse_InsertionSort(Bpq, n);	

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start); // 시간 측정 시작
	SelectionSort(Apq, n); // 선택정렬 함수 호출
	QueryPerformanceCounter(&end); // 시간 측정 종료
	
	diff.QuadPart = end.QuadPart - start.QuadPart; // 측정값으로부터 실행시간 계산	
	printf("\n선택정렬 %.12f ms\n", (double)(diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start); // 시간 측정 시작
	InsertionSort(Bpq, n); // 삽입정렬 함수 호출
	QueryPerformanceCounter(&end); // 시간 측정 종료

	diff.QuadPart = end.QuadPart - start.QuadPart; // 측정값으로부터 실행시간 계산
	printf("삽입정렬 %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	free(Apq); // 배열에 사용된 메모리 할당 해제
	free(Bpq);

}

void SelectionSort(int* pq, int n) { // 배열과 배열의 크기를 인자로 하는 선택정렬 함수

	int i, j, tmp, tmp_max;
	
	tmp_max = 0; // 배열의 첫번째 인자를(index 0) 최대값으로 초기화 

	for (j = n - 1; j > 0; j--) { // 배열의 끝에서부터 최대값으로 채워나가기 위해 j를 배열의 마지막 인자 위치인 n - 1로 지정해 1씩 감소

		tmp_max = 0; // 매 시행마다 배열의 첫번째 인자를 최대값으로 초기화		

		for (i = 0; i <= j; i++) { // 첫번째 인자부터 해당 시행에서의 마지막까지 순회하며 최대값 탐색
			if (*(pq + tmp_max) < *(pq + i)) {				
				tmp_max = i;
			}
		}

		tmp = *(pq + tmp_max); // 해당 시행의 최대값을 마지막 인자와 교체
		*(pq + tmp_max) = *(pq + j); 
		*(pq + j) = tmp;

	}

}

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

void Reverse_InsertionSort(int* pq, int n) { // C 방식의 분석을 위해 배열을 역정렬 하는 함수

	int i, j, tmp;

	for (i = 1; i < n; i++) { // 배열의 맨 앞 두개 원소부터 정렬하도록 진행

		tmp = *(pq + i);
		j = i - 1;

		while (j >= 0 && *(pq + j) < tmp) { // 매 시행의 마지막 원소부터 첫번째 원소까지 크기를 비교하며 위치를 옮기고 다음 원소가 더 큰 경우 반복문 종료

			*(pq + j + 1) = *(pq + j);
			j--;

		}

		*(pq + j + 1) = tmp; // 해당 원소의 위치에 삽입

	}

}