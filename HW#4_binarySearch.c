#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student { // 배열에서 정보를 저장할 노드

	char name[21]; // 이름, 학번을 인자로 가진다.	
	int id;

	struct subject* next; // 리스트의 다음 노드 정보를 저장할 포인터

}ST;

ST* binarySearch();

void main() {

	int id, n, i;
	ST A[100], * tmp;

	scanf("%d", &n); // 원소의 개수 입력	

	for (i = 0; i < n; i++) { // 구조체 배열에 n개의 정보를 입력받아 저장		

		scanf("%d %s", &A[i].id, &A[i].name);

	}

	scanf("%d", &id); // 탐색할 ID 입력

	tmp = binarySearch(A, 0, n - 1, id); // 이진탐색으로 ID 탐색

	if (tmp == NULL) // 반환받은 정보가 없을 경우 -1 출력 후 종료
		printf("-1\n");

	else // 일치하는 ID 정보를 찾았을 경우 출력 후 종료
		printf("%d %s\n", tmp->id, tmp->name);

}

ST* binarySearch(ST* A, int l, int r, int id) { // 이진탐색으로 특정 ID를 가진 학생을 찾는 함수

	if (l > r) return NULL; // 일치하는 ID 정보가 없을 경우 NULL 반환

	int mid = (l + r) / 2;
	ST* tmp;

	if (A[mid].id == id) // 일치하는 ID 정보를 찾았을 경우 반환
		return A + mid;

	if (A[mid].id > id) // 중간 값의 ID가 찾고자 하는 ID보다 클 경우 중간 값의 왼쪽 구간으로 재귀호출
		tmp = binarySearch(A, l, mid - 1, id);

	else // 중간 값의 ID가 찾고자 하는 ID보다 작을 경우 중간 값의 오른쪽 구간으로 재귀호출
		tmp = binarySearch(A, mid + 1, r, id);

	return tmp; // 탐색 결과 반환

}