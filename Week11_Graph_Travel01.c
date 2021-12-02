#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex { // 정점 구조체

	int name, label; // label : 0 (Fresh), 1 (Visited)
	struct incidenceList* L;

}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2;
	int label; // label : 0 (Fresh), 1 (Visited)

}E;

typedef struct incidenceList { // 인접리스트 노드 구조체

	struct edge* e;
	struct incidenceList* next;

}inList;

typedef struct graph { // 그래프 구조체
	
	struct vertex v[100];
	struct edge e[1000];

}G;

inList* getL();
void DFS();

void main() {

	G g;
	int i, n, m, s, v1, v2, tmp;
	inList* ltmp, * lttmp;

	scanf("%d%d%d", &n, &m, &s); // 정점, 간선의 개수와 순회 시작 정점 번호 입력

	for (i = 0; i < n; i++) { // 입력된 정점의 개수 n만큼 그래프에 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].label = 0; // 초기 방문 label을 Fresh로 초기화
		g.v[i].L = getL(); // 인접리스트 헤더노드

	}

	for (i = 0; i < m; i++) { // 입력된 간선의 개수 m만큼 그래프에 간선 정보 초기화

		scanf("%d%d", &v1, &v2);

		if (v1 > v2) { // 간선 정보 사용에 용이하기 위해 두 끝을 오름차순으로 정렬
			tmp = v1;
			v1 = v2;
			v2 = tmp;
		}

		g.e[i].v1 = g.v + v1 - 1;
		g.e[i].v2 = g.v + v2 - 1;
		g.e[i].label = 0;

	}

	for (i = 0; i < m; i++) { // 각 간선을 해당 정점의 인접리스트에 초기화

		v1 = g.e[i].v1->name;
		v2 = g.e[i].v2->name;

		ltmp = g.e[i].v1->L; // i번째 간선의 첫 번째 정점 인접리스트에 간선 정보 추가
		while (ltmp->next != NULL) {

			if (ltmp->next->e->v1->name == v1) {
				if (ltmp->next->e->v2->name > v2) {
					break;
				}
			}

			else {
				if (ltmp->next->e->v1->name > v2) {
					break;
				}
			}

			ltmp = ltmp->next;

		}

		lttmp = getL();
		lttmp->e = g.e + i;

		lttmp->next = ltmp->next;
		ltmp->next = lttmp;

		if (v1 != v2) { // loop가 아닐 경우 i번째 간선의 두 번째 정점 인접리스트에 간선 정보 추가
			ltmp = g.e[i].v2->L; 
			while (ltmp->next != NULL) {

				if (ltmp->next->e->v1->name == v2) {
					if (ltmp->next->e->v2->name > v1) {
						break;
					}
				}

				else {
					if (ltmp->next->e->v1->name > v1) {
						break;
					}
				}

				ltmp = ltmp->next;

			}

			lttmp = getL();
			lttmp->e = g.e + i;

			lttmp->next = ltmp->next;
			ltmp->next = lttmp;
		}

	}

	DFS(&g.v[s - 1]); // 깊이 우선 탐색 함수 호출
	
	for (i = 0; i < n; i++) { // 인접리스트 메모리 할당 해제

		ltmp = g.v[i].L;

		while (ltmp != NULL) {

			lttmp = ltmp->next;
			free(ltmp);
			ltmp = lttmp;

		}

	}

}

inList* getL() { // 인접리스트 노드를 할당하는 함수

	inList* newnode;

	newnode = (inList*)malloc(sizeof(inList)); // 새로운 노드를 동적할당하고 내부 값을 NULL로 선언
	newnode->e = NULL;
	newnode->next = NULL;

	return newnode; // 할당된 노드 주소 반환

}

void DFS(V* u) { // 깊이 우선 탐색 함수

	inList* tmp;

	u->label = 1; // 방문 label을 Visited로 표시
	printf("%d\n", u->name);

	tmp = u->L->next; 
	while (tmp != NULL) { // 해당 정점 인접리스트를 순회하며 작은 번호의 정점부터 탐색

		if (tmp->e->v1 == u) { // 해당 정점의 반대 정점
			if (tmp->e->v2->label == 0) { // 미방문 정점일 경우 방문
				DFS(tmp->e->v2);
			}
		}

		else { // 해당 정점의 반대 정점
			if (tmp->e->v1->label == 0) { // 미방문 정점일 경우 방문
				DFS(tmp->e->v1);
			}
		}

		tmp = tmp->next;

	}

}#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex { // 정점 구조체

	int name, label; // label : 0 (Fresh), 1 (Visited)
	struct incidenceList* L;

}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2;
	int label; // label : 0 (Fresh), 1 (Visited)

}E;

typedef struct incidenceList { // 인접리스트 노드 구조체

	struct edge* e;
	struct incidenceList* next;

}inList;

typedef struct graph { // 그래프 구조체
	
	struct vertex v[100];
	struct edge e[1000];

}G;

inList* getL();
void DFS();

void main() {

	G g;
	int i, n, m, s, v1, v2, tmp;
	inList* ltmp, * lttmp;

	scanf("%d%d%d", &n, &m, &s); // 정점, 간선의 개수와 순회 시작 정점 번호 입력

	for (i = 0; i < n; i++) { // 입력된 정점의 개수 n만큼 그래프에 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].label = 0; // 초기 방문 label을 Fresh로 초기화
		g.v[i].L = getL(); // 인접리스트 헤더노드

	}

	for (i = 0; i < m; i++) { // 입력된 간선의 개수 m만큼 그래프에 간선 정보 초기화

		scanf("%d%d", &v1, &v2);

		if (v1 > v2) { // 간선 정보 사용에 용이하기 위해 두 끝을 오름차순으로 정렬
			tmp = v1;
			v1 = v2;
			v2 = tmp;
		}

		g.e[i].v1 = g.v + v1 - 1;
		g.e[i].v2 = g.v + v2 - 1;
		g.e[i].label = 0;

	}

	for (i = 0; i < m; i++) { // 각 간선을 해당 정점의 인접리스트에 초기화

		v1 = g.e[i].v1->name;
		v2 = g.e[i].v2->name;

		ltmp = g.e[i].v1->L; // i번째 간선의 첫 번째 정점 인접리스트에 간선 정보 추가
		while (ltmp->next != NULL) {

			if (ltmp->next->e->v1->name == v1) {
				if (ltmp->next->e->v2->name > v2) {
					break;
				}
			}

			else {
				if (ltmp->next->e->v1->name > v2) {
					break;
				}
			}

			ltmp = ltmp->next;

		}

		lttmp = getL();
		lttmp->e = g.e + i;

		lttmp->next = ltmp->next;
		ltmp->next = lttmp;

		if (v1 != v2) { // loop가 아닐 경우 i번째 간선의 두 번째 정점 인접리스트에 간선 정보 추가
			ltmp = g.e[i].v2->L; 
			while (ltmp->next != NULL) {

				if (ltmp->next->e->v1->name == v2) {
					if (ltmp->next->e->v2->name > v1) {
						break;
					}
				}

				else {
					if (ltmp->next->e->v1->name > v1) {
						break;
					}
				}

				ltmp = ltmp->next;

			}

			lttmp = getL();
			lttmp->e = g.e + i;

			lttmp->next = ltmp->next;
			ltmp->next = lttmp;
		}

	}

	DFS(&g.v[s - 1]); // 깊이 우선 탐색 함수 호출
	
	for (i = 0; i < n; i++) { // 인접리스트 메모리 할당 해제

		ltmp = g.v[i].L;

		while (ltmp != NULL) {

			lttmp = ltmp->next;
			free(ltmp);
			ltmp = lttmp;

		}

	}

}

inList* getL() { // 인접리스트 노드를 할당하는 함수

	inList* newnode;

	newnode = (inList*)malloc(sizeof(inList)); // 새로운 노드를 동적할당하고 내부 값을 NULL로 선언
	newnode->e = NULL;
	newnode->next = NULL;

	return newnode; // 할당된 노드 주소 반환

}

void DFS(V* u) { // 깊이 우선 탐색 함수

	inList* tmp;

	u->label = 1; // 방문 label을 Visited로 표시
	printf("%d\n", u->name);

	tmp = u->L->next; 
	while (tmp != NULL) { // 해당 정점 인접리스트를 순회하며 작은 번호의 정점부터 탐색

		if (tmp->e->v1 == u) { // 해당 정점의 반대 정점
			if (tmp->e->v2->label == 0) { // 미방문 정점일 경우 방문
				DFS(tmp->e->v2);
			}
		}

		else { // 해당 정점의 반대 정점
			if (tmp->e->v1->label == 0) { // 미방문 정점일 경우 방문
				DFS(tmp->e->v1);
			}
		}

		tmp = tmp->next;

	}

}
