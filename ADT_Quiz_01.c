// 알고리즘및실습 Quiz01(ADT review) - 1번
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { // 스택의 노드로 사용할 구조체

	char s[11];
	struct node* next;

}NODE;

NODE* getnode() { // 새로운 노드를 만드는 함수

	NODE* newnode;

	newnode = (NODE*)malloc(sizeof(NODE));
	newnode->next = NULL;

	return newnode;

}

void push(NODE** t, char* s) { // stack push

	NODE* newnode;

	newnode = getnode();
	strcpy(newnode->s, s);

	newnode->next = *t;

	*t = newnode;

}

char* pop(NODE** t) { // stack pop, pop 된 노드의 문자열 반환

	NODE* tmp;
	char* st;

	st = (char*)malloc(sizeof(char) * 11);

	tmp = *t;
	strcpy(st, (*t)->s);

	*t = (*t)->next;

	free(tmp);

	return st;

}

void main() {

	NODE* S = NULL;
	char sin[11], * st;

	while (1) { // push

		scanf("%s", sin);

		if (strcmp(sin, "*") == 0) break;

		push(&S, sin);

	}

	while (S != NULL) { // pop하면서 출력

		st = pop(&S);

		printf("%s\n", st);

		free(st);

	}


}