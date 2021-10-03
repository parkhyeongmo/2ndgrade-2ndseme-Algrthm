#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct pivot { // 피벗 구간 정보를 전달하는데 사용하는 구조체 선언
	int a, b;
}Pivot;

int findPivot();
Pivot inPlacePartition();
void inPlaceQuickSort();

void main() {

	int* A, i, n;

	scanf("%d", &n); // 배열 크기 입력

	A = (int*)malloc(sizeof(int) * n); // 배열 동적 할당

	for (i = 0; i < n; i++) { // 배열 원소 입력
	
		scanf("%d", A + i);
	
	}
		
	inPlaceQuickSort(A, 0, n - 1); // 퀵정렬 함수 호출

	for (i = 0; i < n; i++) { // 정렬된 배열 출력

		printf(" %d", *(A + i));

	}

	free(A); // 메모리 할당 해제

}

int findPivot(int* A, int l, int r) { // 피벗을 선택하는 함수

	int a, b, c;

	a = *(A + l);
	b = *(A + r);
	c = *(A + ((r + l) / 2));

	if (a <= b && a <= c) { // 해당 구간의 배열 중 첫번째 인자, 가운데 인자, 마지막 인자 중 중간 값을 선택해 피벗으로 반환

		if (b <= c) return r;
		else return ((r + l) / 2);

	}

	else if (b <= a && b <= c) {

		if (a <= c) return l;
		else return ((r + l) / 2);

	}

	else {

		if (a <= b) return l;
		else return r;

	}

}

void inPlaceQuickSort(int* A, int l, int r) { // 퀵정렬 함수

	if (l >= r) return; // 더 이상 분할 할 구간이 없을 경우 반환

	int k;
	Pivot pivot;

	k = findPivot(A, l, r); // 피벗을 선택해 인덱스를 반환받아 저장

	pivot = inPlacePartition(A, l, r, k); // 분할 함수를 호출해 EQ 구간을 반환받아 저장

	inPlaceQuickSort(A, l, pivot.a - 1); // LT 구간 퀵정렬 재귀 호출
	inPlaceQuickSort(A, pivot.b + 1, r); // GT 구간 퀵정렬 재귀 호출

}

Pivot inPlacePartition(int* A, int l, int r, int k) { // 퀵정렬 도중 피벗을 기준으로 배열을 분할하는 함수

	int i, j, p, Pi, tmp, B;
	Pivot R;

	p = *(A + k); // 피벗 원소 저장
	
	*(A + k) = *(A + r); // 마지막 원소와 위치 교환
	*(A + r) = p;

	i = l;
	Pi = r - 1;

	while (i <= Pi) { // 전체 배열 중 피벗과 동일한 원소를 찾아 다른 원소들과 분리

		if (*(A + i) == p) {

			tmp = *(A + i);
			*(A + i) = *(A + Pi);
			*(A + Pi) = tmp;

			Pi--;

		}

		i++;

	}
	
	i = l;
	j = Pi;

	while (i <= j) { // 피벗과 같지 않은 원소들을 비교해가며 위치 교환

		while (i <= j && *(A + i) <= p) { // l 위치부터 전진하며 피벗보다 큰 원소 발견 시 정지

			i++;

		}

		while (i <= j && *(A + j) >= p) { // 피벗과 같지 않은 마지막 원소의 위치부터 감소하며 피벗보다 작은 원소 발견 시 정지

			j--;

		}

		if (i <= j) { // 위치가 맞지 않는 원소들끼리 교환하여 정렬

			tmp = *(A + i);
			*(A + i) = *(A + j);
			*(A + j) = tmp;

		}		

	}

	B = r;

	while (i <= Pi) { // GT 구간과 EQ 구간의 위치 교환

		tmp = *(A + B);
		*(A + B) = *(A + Pi);
		*(A + Pi) = tmp;

		Pi--;
		B--;

	}	

	R.a = i; // EQ 구간 인덱스 정보 저장
	R.b = B;

	return R; // EQ 구간 인덱스 정보 반환

}