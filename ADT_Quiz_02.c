// 알고리즘및실습 Quiz01(ADT review) - 2번
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { // queue의 노드로 사용할 구조체

	char s[11];
	struct node* next;

}NODE;

NODE* getnode() { // 새로운 노드를 만드는 함수

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE));
	newnode->next = NULL;

	return newnode;

}

void reverse(char* str) { // 문자열을 반전시키는 함수
	char* p = str, * q = str + strlen(str) - 1;

	for (; p < q; p++, q--) {
		char tmp;
		tmp = *p;
		*p = *q;
		*q = tmp;
	}

}

void enqueue(NODE** r, char* sin) { // Queue enqueue

	NODE* newnode;

	newnode = getnode();	

	strcpy((*r)->s, sin);

	(*r)->next = newnode;

	*r = newnode;

}

char* dequeue(NODE** f) { // Queue dequeue, dequeue 된 노드의 문자열 반환

	NODE* tmp;
	char* st;
	st = (char*)malloc(sizeof(char) * 11);

	strcpy(st, (*f)->s);
	tmp = *f;

	*f = (*f)->next;

	free(tmp);

	return st;

}

void main() {

	NODE* f = NULL, * r = NULL, * tmp;
	char sin[11], * st;

	f = getnode(); // queue 헤더노드와 트레일러노드 생성후 연결
	r = getnode();

	f->next = r;


	while (1) { // 입력받은 문자열을 반전시켜 enqueue

		scanf("%s", sin);

		if (strcmp(sin, "*") == 0) break;

		reverse(sin);

		enqueue(&r, sin);

	}

	tmp = f; // 헤더노드를 지우고 첫번째 노드를 front로 설정후 헤더 메모리 할당 해제
	f = f->next;
	free(tmp);

	while (f != r) { // dequeue하며 출력

		st = dequeue(&f);

		printf("%s\n", st);

		free(st);

	}

	free(f); // 트레일러 노드 메모리 할당 해제

}