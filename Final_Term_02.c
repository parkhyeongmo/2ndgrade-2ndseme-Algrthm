// IP : 112.149.113.193

/*
�ش� �������� �׷����� ������ ������ �� �����ҿ� ���Ե� ������ ������ ���ϴµ� DFS �˰����� ����Ͽ���.
DFS�� ���̸� �켱���� Ž���ϴ� �׷��� ��ȸ ������� ����� ��� ������ Ž���ϰ� �ȴ�. ������ �� �� DFS�� ����� ��
�湮�� ��带 �����ҿ� ���Ե� ������ �����μ� ��ȯ �ް� �� ��� DFS�� ����Ǵ����� �������� �����μ� ��ȯ �޾� ����ϰ� �ȴ�.
DFS�� ��� ��������Ʈ ������ ǥ���� �׷��������� ������ O(n + m)�̱� ������ �ش� ���α׷��� ������ O(n + m)�̴�.

n = ������ ���� / m = ������ ����

�� �����ҿ� ���Ե� ������ ������ ������������ �����ϴ� Sort�� ���������� ����Ͽ����� ä������� �ƴ϶�� �Ͽ� ���� ��꿡��
�����Ͽ����ϴ�. ���������� ���� : O(n^2) (���⼭ n�� ������ ������ �ƴ϶� �����ϴ� �迭 �� ������ �����Դϴ�.)

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

	int connected[100]; // �������� ���� ���� ������ ���� �迭

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