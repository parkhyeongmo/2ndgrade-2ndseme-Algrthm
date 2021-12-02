#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct vertex { // 정점 구조체

	char name; // 정점의 이름	
	int d; // 최단거리를 나타내는 d
	
}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2; // 양 끝 정점의 주소 저장
	int weight; // 간선 가중치

}E;



typedef struct graph { // 그래프 구조체

	struct vertex v[100]; // 정점 100개를 저장할 수 있는 정점 배열
	struct edge e[1000]; // 간선 1000개를 저장할 수 있는 간선 배열		

}G;

void BellmanFord();

void main() {

	G g;
	int i, tmp, n, m, s, v1, v2, weight;

	scanf("%d %d %d", &n, &m, &s); // 정점과 간선의 개수 입력
	
	for (i = 0; i < n; i++) { // 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].d = INT_MAX;

	}

	for (i = 0; i < m; i++) { // 간선 정보 입력

		scanf("%d%d%d", &v1, &v2, &weight);
		
		g.e[i].v1 = g.v + v1 - 1; // 출발 정점
		g.e[i].v2 = g.v + v2 - 1; // 도착 정점
		g.e[i].weight = weight;

	}

	BellmanFord(&g, s, n, m);

	for (i = 0; i < n; i++) {

		if (g.v[i].name != s && g.v[i].d != INT_MAX) // 정점 중 출발 정점과 연결되지 않은 정점을 제외하고 이름과 거리 출력
			printf("%d %d\n", g.v[i].name, g.v[i].d);

	}	

}

void BellmanFord(G* g, int s, int n, int m) { // BellmanFord 알고리즘을 이용한 최단 거리 찾기 함수

	E* tmp;
	V* u, * z;
	int i, j;

	((g->v) + s - 1)->d = 0; // 출발 정점의 거리를 0으로 설정해준다.

	for (i = 0; i < n - 1; i++) { // 정점의 개수 n보다 1 적게 반복

		for (j = 0; j < m; j++) { // 반복 시 마다 모든 간선을 순회하며 최신화해준다.

			tmp = (g->e) + j;

			u = tmp->v1;
			z = tmp->v2;

			if (u->d == INT_MAX) continue; // 해당 간선의 출발 정점까지의 거리가 아직 구해지지 않은 경우 continue

			if (z->d > u->d + tmp->weight) // 이전 회차보다 거리가 줄어들었을 경우 최신화해준다.
				z->d = u->d + tmp->weight;
			
		}

	}

}