#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {

	int key;
	struct node* next;

}NODE;

NODE* getnode();
int h();
void insertItem();
int removeElement();
int findElement();
void printTable();

void main() {

	NODE* table, * tmp, *ttmp;
	int M, i, key;
	char cmd;
	
	scanf("%d", &M); // 해시테이블의 크기 M 입력

	table = (NODE*)malloc(sizeof(NODE) * M); // M 크기의 배열 동적할당

	for (i = 0; i < M; i++) { // 해시테이블 내부 초기화

		table[i].key = -1; // 최초로 할당된 배열의 노드 key는 비어있는지 비어있음을 구분하기 위해 -1로 초기화
		table[i].next = NULL;

	}

	while (1) {

		scanf("%c", &cmd); // 명령어 입력

		if (cmd == 'i') { // i 입력 시 키 값을 입력 받고 해시테이블에 추가

			scanf("%d", &key);
			getchar();

			i = h(key, M);
			insertItem(table + i, key);

		}

		else if (cmd == 'd') { // d 입력 시 키 값을 입력 받고 해시테이블에 있는 값일 경우 삭제 후 해당 index 출력, 없을 경우 0 출력

			scanf("%d", &key);
			getchar();

			i = h(key, M);
			printf("%d\n", removeElement(table + i, key));

		}

		else if (cmd == 's') { // s 입력 시 키 값을 입력 받고 해시테이블에 있는 값일 경우 해당 index 출력, 없을 경우 0 출력

			scanf("%d", &key);
			getchar();

			i = h(key, M);
			printf("%d\n", findElement(table + i, key));

		}

		else if (cmd == 'p') { // p 입력 시 해시테이블에 저장된 키들을 순서대로 출력

			printTable(table, M);

		}

		else if (cmd == 'e') { // e 입력 시 프로그램 종료

			break;

		}

	}


	for (i = 0; i < M; i++) { // 해시테이블 내부에 할당된 노드들 메모리 할당 해제

		tmp = (table + i)->next;

		for (; tmp != NULL;) {

			ttmp = tmp->next;
			free(tmp);
			tmp = ttmp;

		}

	}

	free(table); // 해시테이블 배열 메모리 할당 해제

}

NODE* getnode() { // 새로운 노드를 생성하는 함수

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE));
	newnode->next = NULL;

	return newnode; // 새로 생성된 노드의 주소 반환

}

int h(int key, int M) { // 해시 함수, 입력된 키 값을 해시하여 반환

	return (key % M);

}

void insertItem(NODE* table, int key) { // 새로운 키를 해시테이블에 삽입하는 함수

	NODE* newnode;

	newnode = getnode(); // 새로운 노드를 할당하여 키 값을 저장
	newnode->key = key;

	newnode->next = table->next; // 해당 버켓의 맨 앞에 삽입
	table->next = newnode;

	if (table->key == -1) table->key = 1; // 값이 처음 입력된 index일 경우 1로 표시

}

int removeElement(NODE* table, int key) { // 해시테이블의 키를 삭제하는 함수

	NODE* tmp, * ptmp;
	int i = 1;

	ptmp = table;
	tmp = table->next;

	while (tmp != NULL) { // 해당 키 값을 가진 원소가 존재하는지 탐색

		if (tmp->key == key) break;

		ptmp = tmp;
		tmp = tmp->next;
		i++;

	}

	if (tmp == NULL) return 0; // 없을 경우 0 반환

	ptmp->next = tmp->next; // 존재할 경우 해당 노드를 제외
	free(tmp); // 메모리 할당 해제

	if (table->next == NULL) table->key = 0; // 삭제된 후 해당 index가 비었을 경우 0으로 표시

	return i; // 삭제된 후 리스트에서의 순위 반환
	
}

int findElement(NODE* table, int key) { // 해시테이블의 키를 탐색하는 함수

	NODE* tmp;
	int i = 1;

	tmp = table->next;

	while (tmp != NULL) { // 해당 키 값을 가진 원소가 존재하는지 탐색

		if (tmp->key == key) break;

		tmp = tmp->next;
		i++;

	}

	if (tmp == NULL) return 0; // 없을 경우 0 반환

	return i; // 존재할 경우 리스트에서의 순위 반환

}

void printTable(NODE* table, int M) { // 해시테이블에 저장된 키들을 순서대로 출력하는 함수

	NODE* tmp;
	int i;

	for (i = 0; i < M; i++) { // 각 index 별로 반복하며 모든 키 값 출력

		tmp = (table + i)->next;

		while (tmp != NULL) {

			printf(" %d", tmp->key);
			tmp = tmp->next;

		}

	}

	printf("\n");

}