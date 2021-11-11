#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex { // 정점(Vertex) 구조체

	int num;
	struct incidenceList* inList;
	struct Vertex* next;

}V;

typedef struct Edge { // 간선(Edge) 구조체

	int o, d, weight;
	struct Edge* next;

}E;

typedef struct incidenceList { // 인접리스트 구조체

	struct Edge* e;
	struct incidenceList* next;

}inList;

V* getV();
E* getE();
inList* getL();
void a();
void m();
E* areAdjacent();
void insertEdge();
void removeEdge();

void main() {

	V* G, * gtmp, * gttmp;
	E* E, * etmp, * ettmp;
	inList* tmp, * ttmp;
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

	gtmp = G;
	while (gtmp != NULL) { // 각 정점별 인접리스트 헤더노드 할당

		gtmp->inList = getL();
		gtmp = gtmp->next;

	}

	gtmp = G;
	while (gtmp != NULL) { // 각 정점별 인접리스트 초기화

		num1 = gtmp->num; // 해당 정점 번호 저장

		tmp = gtmp->inList; // 해당 정점 인접리스트 헤더노드 저장		

		etmp = E;
		while (etmp != NULL) { // 간선리스트를 순회하며 해당 정점이 포함된 간선 인접리스트에 저장

			if (etmp->o == num1) { // 해당 정점이 포함된 간선 발견 시 인접리스트에 다음 노드 할당 후 저장하고 포인터 이동		
				tmp->next = getL();
				tmp->next->e = etmp;
				tmp = tmp->next;
			}

			else if (etmp->d == num1) { // 해당 정점이 포함된 간선 발견 시 인접리스트에 다음 노드 할당 후 저장하고 포인터 이동	
				tmp->next = getL();
				tmp->next->e = etmp;
				tmp = tmp->next;
			}

			etmp = etmp->next; // 다음 간선으로 포인트 이동

		}

		gtmp = gtmp->next; // 다음 정점으로 포인터 이동
		
	}

	while (1) {

		scanf("%c", &cmd); // 명령어 입력

		if (cmd == 'a') { // 'a' 입력 시 번호를 입력받아 해당 정점의 간선 정보 오름차순 출력

			scanf("%d", &num1);
			getchar();

			a(G, num1);

		}

		else if (cmd == 'm') { // 'm' 입력 시 두 개의 번호를 입력받아 해당 간선의 정보 수정

			scanf("%d%d%d", &num1, &num2, &w);
			getchar();

			m(G, &E, num1, num2, w);

		}

		else if (cmd == 'q') break; // 'q' 입력 시 프로그램 종료

	}	

	gtmp = G;
	while (gtmp != NULL) { // 정점 리스트 메모리 할당 해제

		tmp = gtmp->inList;
		while (tmp != NULL) { // 각 정점별 인접리스트 메모리 할당 해제

			ttmp = tmp->next;
			free(tmp);
			tmp = ttmp;

		}

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
	newnode->inList = NULL;

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


inList* getL() { // 새로운 인접리스트 노드 할당 함수

	inList* node;

	node = (inList*)malloc(sizeof(inList));

	node->e = NULL;
	node->next = NULL;

	return node;

}

void a(V* G, int num) { // 'a' 입력 시 해당 정점에 연결된 간선의 정보를 출력하는 함수

	int i = 1;
	V* gtmp;
	inList* ltmp;

	if (num <= 0 || num >= 7) { // 존재하지 않는 노드 번호 입력 시 예외처리
		printf("-1\n");
		return;
	}

	gtmp = G;
	while (i != num) { // 해당 정점까지 정점리스트 순회
		gtmp = gtmp->next;
		i += 1;
	}

	ltmp = gtmp->inList->next;
	while (ltmp != NULL) { // 오름차순으로 정렬되어 있는 인접리스트 정보 순차적으로 출력

		if (ltmp->e->o == num) {
			printf(" %d %d", ltmp->e->d, ltmp->e->weight);
		}

		else {
			printf(" %d %d", ltmp->e->o, ltmp->e->weight);
		}

		ltmp = ltmp->next;

	}

	printf("\n");

}

void m(V* G, E** E, int num1, int num2, int weight) { // 'm' 입력 시 간선의 정보를 수정하는 함수

	struct Edge* mod, * tmp;

	if (num1 <= 0 || num1 >= 7) { // 입력된 노드 번호 중 첫 번째가 존재하지 않을 경우 예외처리
		printf("-1\n");
		return;
	}

	else if (num2 <= 0 || num2 >= 7) { // 입력된 노드 번호 중 두 번째가 존재하지 않을 경우 예외처리
		printf("-1\n");
		return;
	}

	mod = areAdjacent(*E, num1, num2); // 두 노드가 인접한지 검사, 인접하면 해당 간선의 주소를 반환 받고, 인접하지 않으면 NULL 반환

	if (mod == NULL && weight != 0) { // 새로운 간선 추가

		mod = getE(num1, num2, weight); // 새로운 간선 노드 할당

		mod->next = (*E)->next; // 간선리스트에 연결
		(*E)->next = mod;

		insertEdge(G, mod, num1, num2); // 양 끝 정점의 인접리스트에 저장
		if (num1 != num2) // Loop 간선의 경우 한 번만 저장
			insertEdge(G, mod, num2, num1);

	}

	else if (mod != NULL && weight != 0) { // 기존 간선 가중치 변경

		mod->weight = weight;

	}

	else if (mod != NULL && weight == 0) { // 기존 간선 삭제

		removeEdge(G, mod, num1); // 양 끝 정점의 인접리스트에서 삭제
		if (num1 != num2) // Loop 간선의 경우 한 번만 삭제
			removeEdge(G, mod, num2);
		
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


E* areAdjacent(E* E, int num1, int num2) { // 두 정점의 번호를 받고 인접하는지 판별하는 함수

	struct Edge* tmp;

	tmp = E;

	while (tmp != NULL) { // 간선리스트의 끝까지 순회하며 두 정점을 연결하는 간선 존재 검사

		if (tmp->o == num1 && tmp->d == num2) break;
		else if (tmp->d == num1 && tmp->o == num2) break;

		tmp = tmp->next;

	}

	return tmp; // 인접할 경우 해당 간선 노드 주소 반환, 인접하지 않을 경우 NULL 반환

}

void insertEdge(V* G, E* mod, int Vnum, int Enum) { // 정점의 인접리스트에 새로운 간선을 추가하는 함수

	V* gtmp;
	inList* tmp, * newnode;
	int i;

	gtmp = G; i = 1;
	while (i != Vnum) { // 정점리스트를 순회하며 해당 정점 위치 탐색
		gtmp = gtmp->next;
		i++;
	}

	tmp = gtmp->inList;
	while (tmp->next != NULL) { // 새로운 간선을 오름차순으로 입력하기 위해 적합한 위치 탐색

		if (tmp->next->e->o == Vnum) {
			if (tmp->next->e->d > Enum) {
				break;
			}
		}

		else {
			if (tmp->next->e->o > Enum) {
				break;
			}
		}

		tmp = tmp->next;

	}

	newnode = getL(); // 새로운 인접리스트 노드 할당
	newnode->e = mod;

	newnode->next = tmp->next; // 인접리스트에 저장
	tmp->next = newnode;

}

void removeEdge(V* G, E* mod, int Vnum) { // 정점의 인접리스트에서 간선을 삭제하는 함수

	V* gtmp;
	inList* tmp, *ttmp;
	int i;

	gtmp = G; i = 1;
	while (i != Vnum) { // 정점리스트를 순회하며 해당 정점 위치 탐색
		gtmp = gtmp->next;
		i++;
	}

	tmp = gtmp->inList;
	while (tmp != NULL) { // 인접리스트에서 삭제할 간선의 위치 탐색

		if (tmp->next->e == mod) break;
		tmp = tmp->next;

	}

	ttmp = tmp->next; // 해당 노드 제외하여 연결
	tmp->next = ttmp->next;

	free(ttmp); // 삭제된 인접리스트 노드 메모리 할당 해제

}