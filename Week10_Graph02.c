#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex { // 정점(Vertex) 구조체

	int num;
	struct Vertex* next;

}V;

typedef struct Edge { // 간선(Edge) 구조체

	int o, d, weight;
	struct Edge* next;

}E;

typedef struct adj_matrix { // 인접행렬 구조체

	struct Edge* e;

}Adj;

V* getV();
E* getE();
void a();
void m();
E* areAdjacent();
void insertEdge();
void removeEdge();

void main() {

	V* G, * gtmp, * gttmp;
	E* E, * etmp, * ettmp;
	Adj A[6][6];
	int num1, num2, w;
	char cmd;

	G = getV(1); // 정점 리스트 초기화
	G->next = getV(2);
	gtmp = G->next;
	gtmp->next = getV(3);
	gtmp = gtmp->next;
	gtmp->next = getV(4);
	gtmp = gtmp->next;
	gtmp->next = getV(5);
	gtmp = gtmp->next;
	gtmp->next = getV(6);

	E = getE(1, 2, 1); // 간선 리스트 초기화
	E->next = getE(1, 3, 1);
	etmp = E->next;
	etmp->next = getE(1, 4, 1);
	etmp = etmp->next;
	etmp->next = getE(1, 6, 2);
	etmp = etmp->next;
	etmp->next = getE(2, 3, 1);
	etmp = etmp->next;
	etmp->next = getE(3, 5, 4);
	etmp = etmp->next;
	etmp->next = getE(5, 5, 4);
	etmp = etmp->next;
	etmp->next = getE(5, 6, 3);

	for (num1 = 0; num1 < 6; num1++) { // 인접행렬 원소 NULL로 초기화
		for (num2 = 0; num2 < 6; num2++) {
			A[num1][num2].e = NULL;
		}
	}

	etmp = E;

	while (etmp != NULL) { // 인접행렬에 간선 정보 입력

		A[etmp->o - 1][etmp->d - 1].e = etmp;
		A[etmp->d - 1][etmp->o - 1].e = etmp;

		etmp = etmp->next;

	}	

	while (1) {

		scanf("%c", &cmd); // 명령어 입력

		if (cmd == 'a') { // 'a' 입력 시 번호를 입력받아 해당 정점의 간선 정보 오름차순 출력

			scanf("%d", &num1);
			getchar();

			a(A, num1);

		}

		else if (cmd == 'm') { // 'm' 입력 시 두 개의 번호를 입력받아 해당 간선의 정보 수정

			scanf("%d%d%d", &num1, &num2, &w);
			getchar();

			m(A, &E, num1, num2, w);

		}

		else if (cmd == 'q') break; // 'q' 입력 시 프로그램 종료

	}

	gtmp = G;
	while (gtmp != NULL) { // 정점 리스트 메모리 할당 해제		

		gttmp = gtmp->next;
		free(gtmp);
		gtmp = gttmp;

	}

	etmp = E;
	while (etmp != NULL) { // 간선 리스트 메모리 할당 해제

		ettmp = etmp->next;
		free(etmp);
		etmp = ettmp;

	}

}

V* getV(int num) { // 새로운 정점 노드 할당 함수

	V* newnode;

	newnode = (V*)malloc(sizeof(V));

	newnode->num = num;
	newnode->next = NULL;

	return newnode;
}


E* getE(int origin, int dest, int weight) { // 새로운 간선 노드 할당 함수

	E* newnode;

	newnode = (E*)malloc(sizeof(E));

	newnode->o = origin;
	newnode->d = dest;
	newnode->weight = weight;
	newnode->next = NULL;

	return newnode;

}

void a(Adj* A, int num) { // 'a' 입력 시 해당 정점에 연결된 간선의 정보를 출력하는 함수

	int i;

	if (num <= 0 || num >= 7) { // 입력된 번호의 정점이 존재하지 않을 경우 예외처리
		printf("-1\n");
		return;
	}

	for (i = 0; i < 6; i++) { // 해당 num를 가진 정점의 간선 정보를 순차적으로 출력

		if ((A + (num - 1) * 6 + i)->e != NULL) { // 연결되지 않은 정점과의 자리는 NULL 포인터가 들어가 있으므로 수행하지 않음.

			if ((A + (num - 1) * 6 + i)->e->o == num) // 반대편 정점과 간선의 가중치 출력
				printf(" %d %d", (A + (num - 1) * 6 + i)->e->d, (A + (num - 1) * 6 + i)->e->weight);
			else
				printf(" %d %d", (A + (num - 1) * 6 + i)->e->o, (A + (num - 1) * 6 + i)->e->weight);

		}

	}

	printf("\n");

}



void m(Adj* A, E** E, int num1, int num2, int weight) { // 'm' 입력 시 간선의 정보를 수정하는 함수

	struct Edge* mod, * tmp;

	if (num1 <= 0 || num1 >= 7) { // 입력된 노드 번호 중 첫 번째가 존재하지 않을 경우 예외처리
		printf("-1\n");
		return;
	}

	else if (num2 <= 0 || num2 >= 7) { // 입력된 노드 번호 중 두 번째가 존재하지 않을 경우 예외처리
		printf("-1\n");
		return;
	}

	mod = areAdjacent(A, num1, num2); // 두 노드가 인접한지 검사, 인접하면 해당 간선의 주소를 반환 받고, 인접하지 않으면 NULL 반환

	if (mod == NULL && weight != 0) { // 새로운 간선 추가

		mod = getE(num1, num2, weight); // 새로운 간선 노드 할당

		mod->next = (*E)->next; // 간선리스트에 연결
		(*E)->next = mod;

		insertEdge(A, mod, num1, num2); // 양 끝 정점의 인접리스트에 저장
		
	}

	else if (mod != NULL && weight != 0) { // 기존 간선 가중치 변경

		mod->weight = weight;

	}

	else if (mod != NULL && weight == 0) { // 기존 간선 삭제

		removeEdge(A, num1, num2); // 양 끝 정점의 인접행렬에서 간선 삭제
	
		if (*E == mod) { // 해당 간선을 간선리스트에서도 삭제, 헤드노드 삭제할 경우를 위해 이중포인터로 간선리스트 전달받음.
			*E = mod->next;
			free(mod);

			return;
		}

		tmp = *E;

		while (tmp != NULL) {
			if (tmp->next == mod) break;
			tmp = tmp->next;
		}

		tmp->next = mod->next;
		free(mod);

	}

}


E* areAdjacent(Adj* A, int num1, int num2) { // 두 정점의 번호를 받고 인접하는지 판별하는 함수

	if ((A + (num1 - 1) * 6 + num2 - 1)->e != NULL) // 인접할 경우 해당 간선 노드 주소 반환, 인접하지 않을 경우 NULL 반환
		return (A + (num1 - 1) * 6 + num2 - 1)->e;
	else
		return NULL;

}

void insertEdge(Adj* A, E* mod, int num1, int num2) { // 정점의 인접행렬에 새로운 간선을 추가하는 함수
		
	(A + (num1 - 1) * 6 + num2 - 1)->e = mod;
	(A + (num2 - 1) * 6 + num1 - 1)->e = mod;	

}

void removeEdge(Adj* A, int num1, int num2) { // 정점의 인접행렬에서 간선을 삭제하는 함수

	(A + (num1 - 1) * 6 + num2 - 1)->e = NULL;
	(A + (num2 - 1) * 6 + num1 - 1)->e = NULL;

}