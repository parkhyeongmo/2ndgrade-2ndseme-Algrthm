#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int h1();
int h2();
int insertItem();
int findElement();
void printTable();

void main() {

	int* table, M, n, q, i, key, cnt = 0;
	char cmd;

	scanf("%d%d%d", &M, &n, &q); // 해시테이블의 크기 M과 입력 데이터의 크기 n, h2에 사용될 q 입력
	getchar();

	table = (int*)malloc(sizeof(int) * M); // 크기 M인 배열 동적 할당

	for (i = 0; i < M; i++) { // 최초 할당된 해시테이블 내부 0으로 초기화
		table[i] = 0;
	}

	while (1) {

		scanf("%c", &cmd); // 명령어 입력

		if (cmd == 'i') { // i 입력 시 키 값을 입력 받고 해시테이블에 추가

			scanf("%d", &key); // 키 입력
			getchar();

			if (cnt > n) { // 최대 입력 크기 초과시 예외처리
				printf("full\n");
				continue;
			}

			printf("%d\n", insertItem(table, key, M, q)); // 해시테이블에 키 삽입 후 index 출력

			cnt++; // 입력된 키 개수 1개 추가

		}

		else if (cmd == 's') { // s 입력 시 키 값을 입력 받고 해시테이블에 있는 값일 경우 해당 index 출력, 없을 경우 0 출력

			scanf("%d", &key); // 키 입력
			getchar();

			i = findElement(table, key, M, q); // 해당 키가 위치한 주소 반환

			if (i == -1) { // 존재하지 않을 시 -1을 반환하므로 -1 출력 후 다음 시행

				printf("%d\n", i);
				continue;

			}

			printf("%d %d\n", i, *(table + i)); // 반환 받은 주소와 키 출력

		}

		else if (cmd == 'p') // p 입력 시 현재 해시테이블 출력
			printTable(table, M);

		else if (cmd == 'e') { // e 입력 시 해시테이블 출력 후 프로그램 종료

			printTable(table, M);
			break;

		}

	}
	
	free(table); // 해시테이블 배열 메모리 할당 해제

}

int h1(int key, int M) { // 해시 함수 h

	return key % M;

}

int h2(int key, int q) { // 해시 함수 h'

	return q - (key % q);

}

int insertItem(int* table, int key, int M, int q) { // 해시테이블에 키를 삽입하는 함수

	int i, j;

	i = h1(key, M);
	j = h2(key, q);

	if (*(table + i) == 0) { // 해당 키의 셀이 비어있을 경우 삽입 후 주소 반환

		*(table + i) = key;
		return i;

	}

	printf("C"); // 최초 삽입 실패시 충돌메세지 출력 
	i = h1(i + j, M); // 다음 셀로 이동

	while(1) {

		if (*(table + i) == 0) { // 해당 셀이 비었을 경우 삽입 후 반복문 종료
			*(table + i) = key;
			break;
		}

		printf("C"); // 충돌이 발생해 삽입이 발생했을 경우 충돌메세지 출력 후 다음 셀로 이동
		i = h1(i + j, M);
		
	}

	return i; // 삽입 된 주소 반환

}

int findElement(int* table, int key, int M, int q) { // 해시테이블에 키가 존재하는지 탐색하는 함수

	int i, j;

	i = h1(key, M);
	j = h2(key, q);

	while (1) {

		if (*(table + i) == key) { // 키 발견 시 종료
			break;
		}

		else if (*(table + i) == 0) { // 키 발견 이전에 비어있는 셀이 있을 경우 존재하지 않으므로 -1 반환
			return -1;
		}

		i = h1(i + j, M); // 다음 셀로 이동
				
	}

	return i; // 발견 된 주소 반환

}

void printTable(int* table, int M) { // 해시테이블 내부 출력 함수

	int i;

	for (i = 0; i < M; i++) { // 해시테이블로 사용중인 배열의 0부터 M-1까지 순서대로 출력

		printf(" %d", *(table + i));

	}

	printf("\n");

}