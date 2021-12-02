#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct vertex { // 정점 구조체

	char name; // 정점의 이름	
	struct incidenceList* L; // 인접리스트
	int d, loc; // MST로부터의 최단거리를 나타내는 d와 우선순위 큐(힙)에서의 위치를 나타내는 loc
	struct edge* p; // MST에 포함되는 간선

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
int primJarnikMST();
void downHeap();
void upHeap();
V* removeMin();
void replaceKey();

void main() {

	G g;
	int i, tmp, n, m, v1, v2, weight;
	inList* ltmp, * lttmp;

	scanf("%d %d", &n, &m); // 정점과 간선의 개수 입력

	for (i = 0; i < n; i++) { // 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].L = getL();

		g.v[i].d = INT_MAX;
		g.v[i].p = NULL;

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

	for (i = 0; i < m; i++) { // 주어진 간선 정보를 정점의 인접리스트에 입력

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

	i = primJarnikMST(&g, n); // Prin-Jarnik MST 함수 호출
	printf("%d\n", i); // 반환 받은 MST 총무게

	for (i = 0; i < n; i++) { // 정점의 인접리스트로 사용된 노드들 메모리 할당 해제

		ltmp = g.v[i].L;

		while (ltmp != NULL) {
			lttmp = ltmp->next;
			free(ltmp);
			ltmp = lttmp;
		}

	}

}

inList* getL() { // 인접리스트 노드 할당 함수

	inList* newnode;

	newnode = (inList*)malloc(sizeof(inList)); // 새로운 노드를 할당 후 내부 값을 NULL로 초기화하여 반환

	newnode->e = NULL;
	newnode->next = NULL;

	return newnode;

}

int primJarnikMST(G* g, int n) { // Prim-Jarnik 알고리즘을 이용해 MST를 구하는 함수

	(g->v)->d = 0; // 1번 정점의 d 값을 0으로 초기화

	V* H[101], * u, * z;
	inList* ltmp;
	int i, sum = 0;

	for (i = 0; i < n; i++) { // 힙에 정점 정보 삽입

		H[i + 1] = (g->v) + i;
		((g->v) + i)->loc = i + 1;

	}

	while (n > 0) { // 힙의 모든 정점이 삭제될 때까지 반복

		u = removeMin(&H, &n); // 최단거리 경로의 정점 삭제 후 저장

		sum += u->d; // MST 총무게를 구하기 위해 sum에 더해준다.
		u->loc = 0; // 힙에서 빠져나온 것을 표시
		printf(" %d", u->name); // 해당 순서에 MST에 추가된 정점의 이름 출력

		ltmp = u->L->next;

		while (ltmp != NULL) { // 정점의 모든 간선 탐색

			if (ltmp->e->v1->name == u->name) { // 간선 반대편 정점 저장
				z = ltmp->e->v2;
			}
			else {
				z = ltmp->e->v1;
			}

			if (z->loc != 0 && ltmp->e->weight < z->d) { // 반대편의 정점이 아직 MST에 추가되지 않았고 현재 간선의 가중치가 이전보다 작을 경우 최신화
				z->d = ltmp->e->weight;
				z->p = ltmp->e;
				replaceKey(&H, z->loc, n); // 힙 내에서의 위치 최신화
			}

			ltmp = ltmp->next;

		}

	}

	printf("\n");

	return sum; // MST의 총무게 반환

}

void downHeap(V** H, int i, int n) { // 힙에서 키 값에 맞는 위치를 찾아 정점을 내려보내는 함수

	int smaller_idx;
	V* tmp;

	if (i * 2 > n) { // 자식 노드가 없는 경우 힙에서의 위치를 설정 후 종료
		(*(H + i))->loc = i;
		return;
	}

	smaller_idx = i * 2; // 왼쪽 자식을 더 작은 키 값을 가진 정점으로 일단 초기화

	if (i * 2 + 1 <= n && (*(H + (i * 2)))->d > (*(H + (i * 2) + 1))->d) { // 오른쪽 자식 노드가 존재하고 왼쪽보다 작을 경우 더 작은 값으로 초기화

		smaller_idx = i * 2 + 1;

	}

	if ((*(H + i))->d < (*(H + smaller_idx))->d) { // 자식 노드 중 작은 값보다 자신이 더 작으면 정지
		(*(H + i))->loc = i;
		return;
	}

	else { // 자식 노드 중 작은 값이 자신의 key보다 작으면 위치 변경

		tmp = *(H + i);
		*(H + i) = *(H + smaller_idx);
		*(H + smaller_idx) = tmp;

		(*(H + i))->loc = i; // 변경된 정점의 loc 최신화
		(*(H + smaller_idx))->loc = smaller_idx;

	}

	downHeap(H, smaller_idx, n); // 바뀐 위치에서 다시 자식 노드와 비교를 위해 재귀 호출

}

void upHeap(V** H, int i) { // i 위치에 있는 정점의 위치를 찾아 올려 보내 주는 함수

	V* tmp;

	if (i == 1 || (*(H + (i / 2)))->d < (*(H + i))->d) { // 루트거나 부모보다 키가 크면 정지
		(*(H + i))->loc = i;
		return;
	}

	if ((*(H + (i / 2)))->d > (*(H + i))->d) { // 부모보다 정점의 키가 더 작으면 위치 변경

		tmp = *(H + (i / 2));
		*(H + (i / 2)) = *(H + i);
		*(H + i) = tmp;

		(*(H + i))->loc = i; // 변경된 정점의 loc 최신화
		(*(H + (i / 2)))->loc = i / 2;

	}

	upHeap(H, i / 2); // 다시 바뀐 위치의 부모와 비교를 위해 재귀 호출

}

V* removeMin(V** H, int* n) { // 힙에서 최단거리의 정점을 삭제하여 반환하는 함수

	V* u;

	u = *(H + 1); // 삭제될 정점 저장

	*(H + 1) = *(H + *n); // 힙에서 가장 마지막에 위치한 정점을 루트로 이동
	(*n)--;	// n을 1 감소

	downHeap(H, 1, *n); // 루트로 이동한 정점의 위치 이동

	return u; // 삭제된 정점 반환

}

void replaceKey(V** H, int loc, int n) { // 최단거리 정보가 변경된 정점의 위치를 찾아주는 함수

	upHeap(H, loc);

}