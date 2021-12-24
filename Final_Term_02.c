// IP : 112.149.113.193

/*
해당 문제에서 그래프의 연결요소 개수와 각 연결요소에 포함된 정점의 개수를 구하는데 DFS 알고리즘을 사용하였다.
DFS는 깊이를 우선으로 탐색하는 그래프 순회 방식으로 연결된 모든 정점을 탐색하게 된다. 때문에 한 번 DFS가 실행될 때
방문한 노드를 연결요소에 포함된 정점의 개수로서 반환 받고 총 몇번 DFS가 실행되는지는 연결요소의 개수로서 반환 받아 출력하게 된다.
DFS의 경우 인접리스트 구조로 표현된 그래프에서의 성능이 O(n + m)이기 때문에 해당 프로그램의 성능은 O(n + m)이다.

n = 정점의 개수 / m = 간선의 개수

각 연결요소에 포함된 정점의 개수를 내림차순으로 정렬하는 Sort는 버블정렬을 사용하였으며 채점대상이 아니라고 하여 위의 계산에서
제외하였습니다. 버블정렬의 성능 : O(n^2) (여기서 n은 정점의 개수가 아니라 정렬하는 배열 내 원소의 개수입니다.)

*/

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct vertex {

	char name;
	int label;
	struct incidentList* L;

}V;

typedef struct edge {

	struct vertex* v1;
	struct vertex* v2;

	int weight;

}E;

typedef struct incidentList {

	struct edge* e;
	struct incidentList* next;

}inList;

typedef struct graph {

	struct vertex v[100];
	struct edge e[1000];

	int connected[100]; // 연결요소의 정점 개수 저장을 위한 배열

}G;

int index(V* v, char c, int n) {

	int i;

	for (i = 0; i < n; i++) {

		if ((v + i)->name == c)
			break;

	}

	return i;

}

inList* getL();
int DFS();
int rDFS();

void main() {


	int n, m, i, w;
	char v1, v2;
	G g;
	inList* ltmp, * lttmp;

	scanf("%d%d", &n, &m);
	getchar();

	for (i = 0; i < 100; i++) {
		g.connected[i] = 0;
	}

	for (i = 0; i < n; i++) {

		scanf("%c", &v1);
		getchar();

		g.v[i].name = v1;
		g.v[i].L = getL();
		g.v[i].label = 0; // fresh

	}

	for (i = 0; i < m; i++) {

		scanf("%c %c %d", &v1, &v2, &w);
		getchar();

		g.e[i].v1 = g.v + index(g.v, v1, n);
		g.e[i].v2 = g.v + index(g.v, v2, n);
		g.e[i].weight = w;

		ltmp = getL();
		ltmp->e = g.e + i;

		ltmp->next = g.v[index(g.v, v1, n)].L->next;
		g.v[index(g.v, v1, n)].L->next = ltmp;

		ltmp = getL();
		ltmp->e = g.e + i;

		ltmp->next = g.v[index(g.v, v2, n)].L->next;
		g.v[index(g.v, v2, n)].L->next = ltmp;

	}

	w = DFS(&g, n);

	printf("%d\n", w);

	for (i = 0; i < w; i++) {

		printf(" %d", g.connected[i]);

	}

	printf("\n");

	for (i = 0; i < n; i++) {

		ltmp = g.v[i].L;

		while (ltmp != NULL) {

			lttmp = ltmp->next;
			free(ltmp);
			ltmp = lttmp;

		}

	}

}

inList* getL() {

	inList* newnode;

	newnode = (inList*)malloc(sizeof(inList));

	newnode->e = NULL;
	newnode->next = NULL;

	return newnode;

}



int DFS(G* g, int n) {

	int idx = 0, i, j, min, tmp, min_idx;

	*((g->connected) + idx) = rDFS(g, 0, n);
	idx++;

	for (i = 0; i < n; i++) {

		if (((g->v) + i)->label == 0) {
			*((g->connected) + idx) = rDFS(g, i, n);
			idx++;
		}

	}

	for (i = idx - 1; i >= 0; i--) {

		min = *(g->connected);
		min_idx = 0;

		for (j = 0; j <= i; j++) {

			if (min > *((g->connected) + j)) {

				min = *((g->connected) + j);
				min_idx = j;

			}

		}

		tmp = *((g->connected) + i);
		*((g->connected) + i) = min;
		*((g->connected) + min_idx) = tmp;

	}


	return idx;

}

int rDFS(G* g, int s, int n) {

	V* z;
	inList* tmp;
	int vertex_num = 0;

	((g->v) + s)->label = 1; // visited

	tmp = ((g->v) + s)->L->next;

	while (tmp != NULL) {

		if (tmp->e->v1->name == ((g->v) + s)->name)
			z = tmp->e->v2;
		else
			z = tmp->e->v1;

		if (z->label == 0)
			vertex_num += rDFS(g, index(g->v, z->name, n), n);

		tmp = tmp->next;

	}

	return vertex_num + 1;

}