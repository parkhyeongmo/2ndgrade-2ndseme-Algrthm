#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int findElement();

void main() {

	int* A, n, k, i;

	scanf("%d%d", &n, &k); // 원소의 개수와 키 값 입력

	A = (int*)malloc(sizeof(int) * n); // 배열 동적할당

	for (i = 0; i < n; i++) { // 배열 원소 입력
	
		scanf("%d", A + i);
	
	}

	printf(" %d", findElement(A, 0, n - 1, k)); // 이진탐색 함수 호출 및 출력

	free(A); // 메모리 할당 해제

}

int findElement(int* A, int l, int r, int k) { // 배열 내의 원소를 x라고 할 때 x >= k의 조건을 만족하는 원소 중 가장 작은 값을 반환하는 이진탐색 함수

	int mid;

	while (l <= r) { // 배열에서 더 이상 줄여나갈 구간이 없을 경우 종료

		mid = (l + r) / 2; // 현재 구간의 중간 값 위치 설정

		if (*(A + mid) == k) return mid; // 해당 회차의 중간 값이 k 값과 같을 경우 즉시 위치 반환		

		if (*(A + mid) < k) { // 해당 회차의 중간 값이 k 값보다 작을 경우 오른쪽 구간으로 위치 정보 변경

			l = mid + 1;

		}

		else if (*(A + mid) > k) { // 해당 회차의 중간 값이 k 값보다 클 경우 왼쪽 구간으로 위치 정보 변경

			r = mid - 1;

		}

	}

	return l; // 조건을 만족하는 원소 중 가장 작은 값 반환

}

/*int findElement(int* A, int l, int r, int k) { // 배열 내의 원소를 x라고 할 때 x >= k의 조건을 만족하는 원소 중 가장 작은 값을 반환하는 이진탐색 함수

	int mid = (l + r) / 2; // 초기 배열의 중간 값 위치 설정

	while (1) { // 탐색 종료시까지 반복

		if (*(A + mid) == k) return mid; // 해당 회차의 중간 값이 k 값과 같을 경우 위치 반환

		if (l + 1 == r || l == r) { // 더 이상 배열을 좁혀나갈 구간이 없을 경우 반환

			if (*(A + l) < k && *(A + r) >= k) return r; // r 위치의 값만 x >= k의 조건을 만족하는 경우 r 위치 반환
			if (*(A + l) < k && *(A + r) < k) return r + 1; // 배열 내의 모든 원소가 k 값보다 작을 경우 n 반환
			else return l; // 예외 처리 없이 x >= k 조건을 만족하는 경우의 가장 큰 원소 반환

		}

		if (*(A + mid) < k) { // 해당 회차의 중간 값이 k 값보다 작을 경우 오른쪽 구간으로 위치 정보 변경

			l = mid + 1;
			mid = (l + r) / 2;

		}

		else if (*(A + mid) > k) { // 해당 회차의 중간 값이 k 값보다 클 경우 왼쪽 구간으로 위치 정보 변경

			r = mid;
			mid = (l + r) / 2;

		}		

	}

}*/