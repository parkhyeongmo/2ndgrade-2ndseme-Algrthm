#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex { // 정점 구조체

	int name, label; // label : 0 (Fresh), 1 (Visited)	

}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2;
	int label; // label : 0 (Fresh), 1 (Tree), 2 (Back)

}E;

typedef struct graph { // 그래프 구조체
	
	struct vertex v[100];
	struct edge e[1000];
	struct edge* adj_matrix[100][100];

}G;

void BFS();

void main() {

	G g;
	int i, j, n, m, s, v1, v2, tmp;
	
	for (i = 0; i < 100; i++) { // 인접행렬 내부 NULL로 초기화
		for (j = 0; j < 100; j++) {
			g.adj_matrix[i][j] = NULL;
		}
	}

	scanf("%d%d%d", &n, &m, &s); // 정점, 간선의 개수와 순회 시작 정점 번호 입력

	for (i = 0; i < n; i++) { // 입력된 정점의 개수 n만큼 그래프에 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].label = 0; // 초기 방문 label을 Fresh로 초기화

	}

	for (i = 0; i < m; i++) { // 입력된 간선의 개수 m만큼 그래프의 간선 정보 초기화

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

	for (i = 0; i < m; i++) { // 인접행렬에 간선 정보 입력

		g.adj_matrix[g.e[i].v1->name - 1][g.e[i].v2->name - 1] = g.e + i;
		g.adj_matrix[g.e[i].v2->name - 1][g.e[i].v1->name - 1] = g.e + i;

	}

	BFS(g, g.v + s - 1, n); // 너비 우선 탐색 함수 호출

}

void BFS(G g, V* v, int n) { // 너비 우선 탐색 함수

	int* L, cnt = 1, current = 0, i;
	E* etmp;

	L = (int*)malloc(sizeof(int) * n); // 탐색 결과를 담을 배열 동적할당

	L[0] = v->name; // 순회 시작 정점의 이름을 배열에 입력
	v->label = 1; // 순회 시작 정점의 label을 Visited로 변경

	while (cnt < n) { // 모든 정점을 탐색할 때까지 반복

		for (i = 0; i < n; i++) { // 해당 차례 정점의 부착 간선을 조사

			etmp = g.adj_matrix[L[current] - 1][i]; // 해당 차례 부착 간선 주소 저장

			if (etmp != NULL) { // 부착 간선이 존재할 경우 방문 여부를 확인하고 탐색

				if (etmp->v1->name == g.v[L[current] - 1].name) { // 간선 반대편의 정점이 Fresh 상태일 경우 방문하고 label을 Visited 상태로 수정
					if (etmp->v2->label == 0) {
						etmp->v2->label = 1;
						L[cnt] = etmp->v2->name;
						cnt++;

						etmp->label = 1; // 간선의 label을 Tree 상태로 수정

					}

					else // 이미 방문된 정점일 경우 해당 간선의 label을 Back 상태로 수정
						etmp->label = 2;

				}

				else {

					if (etmp->v1->label == 0) { // 간선 반대편의 정점이 Fresh 상태일 경우 방문하고 label을 Visited 상태로 수정
						etmp->v1->label = 1;
						L[cnt] = etmp->v1->name;
						cnt++;

						etmp->label = 1; // 간선의 label을 Tree 상태로 수정 

					}

					else // 이미 방문된 정점일 경우 해당 간선의 label을 Back 상태로 수정
						etmp->label = 2;

				}

			}

		}

		current++; // 레벨 순회를 위해 탐색 결과가 저장된 배열의 다음 index로 이동

	}

	for (i = 0; i < n; i++) { // 탐색이 끝난 뒤 결과 출력
		printf("%d\n", L[i]);
	}

	free(L); // 함수 내에서 사용한 배열 메모리 할당 해제

}