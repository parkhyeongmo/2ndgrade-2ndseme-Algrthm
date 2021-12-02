#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct vertex { // 정점 구조체

	char name; // 정점의 이름	
	struct incidenceList* L; // 인접리스트
	int d, loc; // 최단거리를 나타내는 d와 우선순위 큐(힙)에서의 위치를 나타내는 loc
	
}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2; // 양 끝 정점의 주소 저장
	int weight; // 간선 가중치

}E;

typedef struct incidenceList { // 인접리스트에 사용되는 노드

	struct edge* e; // 간선 주소 저장
	struct incidenceList* next; // 다음 노드를 가리키는 포인터

}inList;

typedef struct graph { // 그래프 구조체

	struct vertex v[100]; // 정점 100개를 저장할 수 있는 정점 배열
	struct edge e[1000]; // 간선 1000개를 저장할 수 있는 간선 배열		

}G;

inList* getL();
void Dijkstra();
void downHeap();
void upHeap();
V* removeMin();
void replaceKey();

void main() {

	G g;
	int i, tmp, n, m, s, v1, v2, weight;
	inList* ltmp, * lttmp;

	scanf("%d %d %d", &n, &m, &s); // 정점과 간선의 개수 입력
	
	for (i = 0; i < n; i++) { // 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].d = INT_MAX;
		g.v[i].L = getL();

		if (g.v[i].name == s) g.v[i].d = 0; // 출발 정점의 거리를 0으로 초기화

	}

	for (i = 0; i < m; i++) { // 간선 정보 입력

		scanf("%d%d%d", &v1, &v2, &weight);

		if (v1 > v2) {
			tmp = v1;
			v1 = v2;
			v2 = tmp;
		}

		g.e[i].v1 = g.v + v1 - 1;
		g.e[i].v2 = g.v + v2 - 1;
		g.e[i].weight = weight;

	}

	for (i = 0; i < m; i++) { // 간선 정보를 정점의 인접리스트에 오름차순으로 입력

		v1 = g.e[i].v1->name;
		v2 = g.e[i].v2->name;

		ltmp = g.e[i].v1->L;
		while (ltmp->next != NULL) {

			if (ltmp->next->e->v1->name == v1) {
				if (ltmp->next->e->v2->name > v2)
					break;
			}

			else {
				if (ltmp->next->e->v1->name > v2)
					break;
			}

			ltmp = ltmp->next;

		}

		lttmp = getL();
		lttmp->e = g.e + i;

		lttmp->next = ltmp->next;
		ltmp->next = lttmp;

		if (v1 != v2) {

			ltmp = g.e[i].v2->L;
			while (ltmp->next != NULL) {

				if (ltmp->next->e->v1->name == v2) {
					if (ltmp->next->e->v2->name > v1)
						break;
				}

				else {
					if (ltmp->next->e->v1->name > v1)
						break;
				}

				ltmp = ltmp->next;

			}

			lttmp = getL();
			lttmp->e = g.e + i;

			lttmp->next = ltmp->next;
			ltmp->next = lttmp;

		}

	}		

	Dijkstra(&g, s, n); // 최단거리 찾기 함수 호출

	for (i = 0; i < n; i++) {

		if (g.v[i].name != s && g.v[i].d != INT_MAX) // 정점 중 출발 정점과 연결되지 않은 정점을 제외하고 이름과 거리 출력
			printf("%d %d\n", g.v[i].name, g.v[i].d);

	}

	for (i = 0; i < n; i++) { // 인접리스트에 사용된 메모리 할당 해제

		ltmp = g.v[i].L;

		while (ltmp != NULL) {

			lttmp = ltmp->next;
			free(ltmp);
			ltmp = lttmp;

		}

	}

}

inList* getL() { // 인접리스트의 노드 할당 함수

	inList* newnode;

	newnode = (inList*)malloc(sizeof(inList)); // 새로운 노드를 할당하고 내부를 NULL로 초기화 해준 뒤 반환
	newnode->e = NULL;
	newnode->next = NULL;

	return newnode;

}

void Dijkstra(G* g, int s, int n) { // Dijkstra 알고리즘을 이용한 최단거리 찾기 함수

	V* H[101], * u, * v;
	inList* tmp;
	int i, heap_n;

	heap_n = n;

	for (i = 0; i < n; i++) { // 힙에 정점 정보 입력

		H[i + 1] = (g->v) + i;
		((g->v) + i)->loc = i + 1;

	}

	upHeap(&H, s); // upHeap을 사용해 출발 정점의 위치를 루트로 옮겨준다.
	
	while (heap_n >= 1) { // 힙의 모든 정점에 대한 최단거리를 찾을 때까지 반복

		u = removeMin(&H, &heap_n); // 해당 차례의 최단 거리 정점을 힙에서 삭제 후 반환

		tmp = u->L->next;
		while (tmp != NULL) { // 해당 정점에 인접한 정점들의 거리 비교 후 최신화

			if (tmp->e->v1->name == u->name)
				v = tmp->e->v2;
			else
				v = tmp->e->v1;

			if (u->d + tmp->e->weight < v->d) {				

				v->d = u->d + tmp->e->weight;
				replaceKey(&H, v->loc);

			}

			tmp = tmp->next;

		}

	}

}

void downHeap(V** H, int loc, int n) { // 힙에서 loc에 위치한 정점을 제자리로 내려보내는 함수

	int smaller_idx;
	V* tmp;

	if (loc * 2 > n) return; // 이미 가장 아래에 있으면 종료

	smaller_idx = loc * 2;
	if (loc * 2 + 1 <= n && (*(H + (loc * 2)))->d > (*(H + (loc * 2 + 1)))->d) { // 자식 노드 중 더 작은 거리를 가진 자식의 index 저장
		smaller_idx = loc * 2 + 1;
	}

	if ((*(H + loc))->d < (*(H + smaller_idx))->d) return; // 자식 노드보다 거리가 가까울 경우 종료

	else { // 자식 노드보다 거리가 멀 경우 힙에서의 위치를 서로 바꾸고 loc 최신화

		tmp = *(H + loc);
		*(H + loc) = *(H + smaller_idx);
		*(H + smaller_idx) = tmp;

		(*(H + loc))->loc = loc;
		(*(H + smaller_idx))->loc = smaller_idx;

	}

	downHeap(H, smaller_idx, n); // 바뀐 자리에서 downHeap 재귀 호출

}

void upHeap(V** H, int loc) { // 힙에서 loc에 위치한 정점을 제자리로 올려보내는 함수

	V* tmp;

	if (loc == 1 || (*(H + loc))->d > (*(H + (loc / 2)))->d) return; // 이미 루트거나 부모보다 거리가 멀 경우 종료

	if ((*(H + loc))->d < (*(H + (loc / 2)))->d) { // 부모노드보다 거리가 가까울 경우 힙에서의 위치를 서로 바꾸고 loc 최신화

		tmp = *(H + loc);
		*(H + loc) = *(H + (loc / 2));
		*(H + (loc / 2)) = tmp;

		(*(H + loc))->loc = loc;
		(*(H + (loc / 2)))->loc = loc / 2;

	}

	upHeap(H, loc / 2); // 바뀐 자리에서 upHeap 재귀 호출

}

V* removeMin(V** H, int* n) { // 힙에서 최단 거리를 가진 정점 삭제 후 반환

	V* u;

	u = *(H + 1);

	*(H + 1) = *(H + *n); // 가장 마지막에 위치한 정점을 루트로 옮겨주고 n을 1 감소
	(*n)--;

	downHeap(H, 1, *n); // 루트로 옮겨진 정점에 대해 downHeap

	return u; // 삭제된 정점 반환

}

void replaceKey(V** H, int loc) { // 힙과 거리 정보가 바뀐 정점의 loc를 인자로 받아 힙에서의 위치를 최신화 해주는 함수

	upHeap(H, loc);

}