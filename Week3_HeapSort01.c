#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int H[99], n = 0; // 전역변수로 크기 99의 int형 배열과 int형 변수 n 선언

void insertItem();
int removeMax();
void upHeap();
void downHeap();
void printHeap();


void main() {

	int key;
	char cmd;

	while (1) { // q가 입력 될 때까지 명령을 입력 받으며 작동

		scanf("%c", &cmd); // 해당 회차의 명령 입력

		if (cmd == 'i') { // i가 입력 될 경우 key를 입력 받아 힙에 삽입

			scanf("%d", &key);
			getchar();

			insertItem(key);

			printf("0\n");

		}

		else if (cmd == 'd') { // d가 입력 될 경우 힙의 최대키 삭제 후 출력

			getchar();

			printf("%d\n", removeMax());

		}

		else if (cmd == 'p') { // p가 입력 될 경우 힙의 내용들을 레벨 순서로 출력

			getchar();

			printHeap();

		}

		else if (cmd == 'q') // q가 입력 될 경우 프로그램 종료
			break;

	}

}

void insertItem(int key) { // 힙에 새로운 key를 삽입하는 함수

	n = n + 1; // n을 1개 올려 새로운 키를 추가
	H[n] = key;
	upHeap(n); // 새로 삽입된 키의 순서를 찾아 정렬

}


int removeMax() { // 힙의 최대키를 삭제 후 반환하는 함수

	int key = H[1]; // 반환할 값을 위해 최대키를 임시로 저장

	H[1] = H[n]; // 힙의 마지막인 n 위치의 키를 루트로 옮겨준다.
	H[n] = 0; // n 위치의 키를 0으로 변경 후 n을 1 줄여 최신화
	n = n - 1;

	downHeap(1); // 루트로 옮겨온 키의 순서를 찾아 정렬

	return key; // 삭제된 키 값 반환

}

void upHeap(int i) { // i 위치에 있는 키의 위치를 찾아 올려 보내 주는 함수

	int tmp;

	if (i == 1 || H[i / 2] > H[i]) return; // 루트거나 부모노드보다 키가 작으면 정지

	if (H[i / 2] < H[i]) { // 부모노드보다 i 노드의 키가 더 크면 위치 변경

		tmp = H[i / 2];
		H[i / 2] = H[i];
		H[i] = tmp;

	}

	upHeap(i / 2); // 다시 바뀐 위치의 부모노드와 비교를 위해 재귀 호출

}


void downHeap(int i) { // i 위치에 있는 키의 위치를 찾아 내려 보내 주는 함수

	int bigger, tmp;

	if (i * 2 > n) return; // 자식 노드가 없으면 더 이상 내려갈 곳이 없으므로 정지

	bigger = i * 2; // 왼쪽 자식 노드를 일단 더 큰 값으로 초기화

	if (H[i * 2 + 1] != 0 && H[i * 2] < H[i * 2 + 1]) { // 오른쪽 자식 노드가 존재하고 왼쪽보다 클 경우 더 큰 값으로 초기화

		bigger = i * 2 + 1;

	}

	if (H[i] > H[bigger]) return; // 자식 노드 중 큰 값보다 자신이 더 크면 정지

	if (H[i] < H[bigger]) { // 자식 노드 중 큰 값이 자신의 키보다 크면 위치 변경

		tmp = H[bigger];
		H[bigger] = H[i];
		H[i] = tmp;

	}


	downHeap(bigger); // 바뀐 위치에서 다시 자식 노드와 비교를 위해 재귀 호출

}

void printHeap() { // 힙의 내용을 레벨순서로 인쇄하는 함수

	int i;

	for (i = 1; i <= n; i++) { // 1번부터 n번까지 순서대로 인쇄

		printf(" %d", H[i]);

	}

	printf("\n");

}