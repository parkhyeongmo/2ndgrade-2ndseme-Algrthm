/*
 char형 이름과 int형 label, isOrdered 그리고 인접리스트 포인터 하나를 인자로 하는 구조체 vertex를 정점으로 사용하고
두 개의 정점 포인터 주소를 인자로 하는 구조체 edge를 간선으로 사용하는 자료구조를 이용해 그래프를 구현하였습니다.

 그래프는 크기 10의 정점 배열, 크기 100의 간선 배열, 위상순서를 저장할 int형 배열 top_num과 위상순서를 부여하기 위한 변수 n을
인자로 하는 구조체를 사용하였습니다.

 각 정점에 해당하는 간선 정보를 저장하기 위해 인접리스트를 사용하였습니다. 인접리스트에 사용된 노드는 간선 포인터 주소를 저장하고
다음 노드를 가리키는 next 포인터를 인자로 가지는 구조체를 사용했습니다.

 위상정렬 함수는 주어진 문자 s를 이름으로 갖는 정점부터 탐색하도록 했으며 첫 과정에서 연결요소가 되지 못한 정점은 이후 탐색하여
다시 위상정렬 함수를 호출해 탐색했습니다.

 위상정렬 재귀 함수는 DFS 기법을 활용하여 연결 요소 중 가장 큰 깊이를 가진 정점을 n번째 순서를 부여하며 빠져나오면서 0번째 index까지
top_num 배열을 채웠으며 중간에 이미 방문되었으나 위상순서를 부여받지 못한 정점 발견 시 (label == 1 && isOrdered == 0 인 경우)
cycle이 있는 것으로 판단하여 n을 100으로 초기화한 후 예외처리하여 프로그램을 종료하였습니다.

 해당 기법은 DFS 탐색의 구조를 그대로 사용하며 그 순서의 역순을 위상순서로 정하는 방식만 더해진 것이므로 시간복잡도는 O(n + m) 시간이 소요됩니다.
*/


#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex { // 정점 구조체

	char name; // 정점의 이름
	int label, isOrdered; // label이 0이면 Fresh, 1이면 Visited / isOrdered가 0이면 위상 순서가 부여되지 않은 상태, 1이면 위상 순서가 부여된 상태
	struct incidenceList* L; // 진출인접리스트

}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2; // 시작 정점과 도착 정점의 주소 저장

}E;

typedef struct incidenceList { // 인접리스트에 사용되는 노드

	struct edge* e; // 간선 주소 저장
	struct incidenceList* next; // 다음 노드를 가리키는 포인터

}inList;

typedef struct graph { // 그래프 구조체

	struct vertex v[10]; // 정점 10개를 저장할 수 있는 정점 배열
	struct edge e[100]; // 간선 100개를 저장할 수 있는 간선 배열
	int top_num[10]; // 위상정렬 순서를 저장할 배열
	int n; // 위상순서를 부여하기 위한 변수 n

}G;

inList* getL() { // 인접리스트 노드 할당 함수

	inList* newnode;

	newnode = (inList*)malloc(sizeof(inList)); // 새로운 노드를 할당 후 내부 값을 NULL로 초기화하여 반환

	newnode->e = NULL;
	newnode->next = NULL;

	return newnode;

}

int index(G g, char name, int n) { // 주어진 이름을 가진 정점의 index를 반환하는 함수

	int i;

	for (i = 0; i < n; i++) { // 정점 배열을 탐색하여 index 반환

		if (g.v[i].name == name)
			return i;

	}

	return -1; // 없을 시 -1 반환

}

void topologicalSortDFS(G* g, char s, int n) { // DFS를 이용한 위상정렬 함수

	rTopologicalSortDFS(g, index(*g, s, n), n); // 주어진 이름을 가진 정점으로부터 위상정렬 시작

	if (g->n == 100) return; // 이전에 실행된 위상정렬로부터 사이클이 발견되면 종료

	for (int i = 0; i < n; i++) { // 위상정렬 실행 후 위상순서를 부여받지 못한 정점을 탐색하여 다시 위상정렬 시작

		if (((g->v) + i)->label == 0)
			rTopologicalSortDFS(g, i, n);

	}

}

void rTopologicalSortDFS(G* g, int s, int n) { // DFS를 사용하여 위상정렬을 하는 재귀 함수

	inList* tmp;
	V* w;

	((g->v) + s)->label = 1; // 해당 순서의 정점 방문 label 갱신

	tmp = ((g->v) + s)->L->next; // 해당 정점의 인접리스트 위치 저장

	while (tmp != NULL) { // 연결된 모든 간선 탐색

		w = tmp->e->v2; // 해당 간선의 반대편 도착 정점

		if (w->label == 0) { // 아직 미방문 상태인 경우 DFS 재귀 호출
			rTopologicalSortDFS(g, index(*g, w->name, n), n);
		}

		else if (w->isOrdered == 0) { // 이미 방문된 정점인데 위상순서가 부여되지 않은 경우 사이클이 발견됐으므로 그래프 구조체의 n을 100으로 초기화 후 종료

			g->n = 100;
			return;

		}

		if (g->n == 100) return; // 이전 동작에서 사이클이 발견된 경우 종료

		tmp = tmp->next; // 다음 간선으로 이동

	}	

	*(g->top_num + g->n) = s; // 위상순서를 저장하는 배열 top_num에 해당 정점의 index를 n 위치에 저장
	((g->v) + s)->isOrdered = 1; // 위상순서를 부여했다고 표시

	g->n -= 1; // n을 1 감소

}

void main() {

	G g;
	int n, i, m, j;
	char s, v1, v2;
	inList* ltmp, * lttmp;

	scanf("%d %d", &n, &m); // 정점과 간선의 개수 입력
	getchar();
	scanf("%c", &s); // 시작 정점의 이름 입력
	getchar();
	
	g.n = n - 1; // 그래프 구조체 내의 top_num 배열 index로 사용될 n을 1 감소하여 저장 (배열 index로 사용하기 위함)

	for (i = 0; i < n; i++) { // 정점 정보 입력

		scanf("%c", &v1);
		getchar();

		g.v[i].name = v1;
		g.v[i].label = 0;
		g.v[i].isOrdered = 0;
		g.v[i].L = getL(); // 인접리스트 헤더노드 할당

	}

	for (i = 0; i < m; i++) { // 간선 정보 입력

		scanf("%c %c", &v1, &v2);
		getchar();

		g.e[i].v1 = g.v + index(g, v1, n);
		g.e[i].v2 = g.v + index(g, v2, n);		

	}

	for (i = 0; i < m; i++) { // 주어진 간선 정보를 정점의 인접리스트에 입력

		v2 = g.e[i].v2->name;
		ltmp = g.e[i].v1->L;

		if (ltmp->next == NULL) { // 최초 입력되는 정보일 경우 헤더 노드의 바로 뒤에 연결

			lttmp = getL();
			lttmp->e = g.e + i;

			lttmp->next = ltmp->next;
			ltmp->next = lttmp;

			continue;
		}

		ltmp = ltmp->next;

		while (ltmp->next != NULL) {

			if (ltmp->e->v2->name > v2) break;

			ltmp = ltmp->next;

		}

		lttmp = getL();
		lttmp->e = g.e + i;

		lttmp->next = ltmp->next;
		ltmp->next = lttmp;

	}

	topologicalSortDFS(&g, s, n); // 위상정렬 함수 호출

	if (g.n == 100) printf("-1\n"); // 사이클이 발견된 경우 -1 출력

	else { // 위상정렬 결과 출력

		for (i = 0; i < n; i++) {
			printf("%c ", g.v[g.top_num[i]].name);
		}

	}

	for (i = 0; i < n; i++) { // 정점의 인접리스트로 사용된 노드들 메모리 할당 해제

		ltmp = g.v[i].L;

		while (ltmp != NULL) {
			lttmp = ltmp->next;
			free(ltmp);
			ltmp = lttmp;
		}

	}

}
