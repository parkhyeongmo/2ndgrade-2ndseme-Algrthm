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

int findElement(int* A, int l, int r, int k) { // 배열 내의 원소를 x라고 할 때 x <= k의 조건을 만족하는 원소 중 가장 큰 값을 반환하는 이진탐색 함수

	if (l > r) return r; // 더 이상 분할할 구간이 없을 경우 조건에 맞는 원소 중 가장 큰 값의 위치 출력

	int mid = (l + r) / 2; // 해당 회차의 중간 값 위치 설정

	if (*(A + mid) == k) return mid; // 중간 값이 k와 같으면 위치 반환	

	else if (*(A + mid) < k) { // 중간 값이 k보다 작으면 중간 값 오른쪽 구간으로 재귀 호출

		return findElement(A, mid + 1, r, k);

	}

	else if (*(A + mid) > k) { // 중간 값이 k보다 크면 중간 값을 제외하고 왼쪽 구간으로 재귀 호출

		return findElement(A, l, mid - 1, k);

	}

}


/*int findElement(int* A, int l, int r, int k) { // 배열 내의 원소를 x라고 할 때 x <= k의 조건을 만족하는 원소 중 가장 큰 값을 반환하는 이진탐색 함수

	int mid = (l + r) / 2; // 해당 회차의 중간 값 위치 설정

	if (*(A + mid) == k) return mid; // 중간 값이 k와 같으면 위치 반환

	if (l + 1 == r || l == r){ // 더 이상 좁혀나갈 구간이 없을 경우 base case

		if (l == 0) { // 배열 내부의 모든 원소가 k보다 클 경우 조건에 맞는 원소가 없으므로 -1 반환
			if (*(A + l) > k) return -1;
		}
		else if (*(A + l) < k && *(A + r) < k) return r; // 최대한 좁혀진 배열 구간에서 두 원소 모두 x<=k의 조건을 만족한다면 더 큰 값의 위치 반환
		else if (*(A + l) < k && *(A + r) > k) return l; // 최대한 좁혀진 배열 구간에서 l은 조건을 만족하고 r은 조건을 만족하지 않는 경우 l 위치 반환
		else if (*(A + r) == k) return r; // l+1 == r의 상황에서 r 값이 k 값과 같다면 r 위치 반환
		else if(l == r) return l; // l과 r의 위치가 같을 경우 l 위치 반환

	}

	else if (*(A + mid) < k) { // 중간 값이 k보다 작으면 중간 값 오른쪽 구간으로 재귀 호출

	    return findElement(A, mid, r, k);

	}

	else if (*(A + mid) > k) { // 중간 값이 k보다 크면 중간 값을 제외하고 왼쪽 구간으로 재귀 호출

        return findElement(A, l, mid - 1, k);

	}

}*/