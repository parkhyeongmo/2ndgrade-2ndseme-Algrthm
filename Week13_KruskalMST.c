#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex { // 정점 구조체

	char name; // 정점의 이름
	int sack;

}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2; // 양 끝 정점의 주소 저장
	int weight; // 간선 가중치
	int label; // label이 1이면 TreeEdge

}E;


typedef struct graph { // 그래프 구조체

	struct vertex v[100]; // 정점 100개를 저장할 수 있는 정점 배열
	struct edge e[1000]; // 간선 1000개를 저장할 수 있는 간선 배열	
	
}G;

int kruskalMST();
void buildHeap();
void downHeap();
E* removeMin();
void setUnion();

void main() {

	G g;
	int i, tmp, n, m, v1, v2, weight;

	scanf("%d %d", &n, &m); // 정점과 간선의 개수 입력

	for (i = 0; i < n; i++) { // 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].sack = i + 1;

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
		g.e[i].label = 0;

	}

	i = kruskalMST(&g, n, m); // KruskalMST 함수 호출
	printf("%d\n", i); // 반환 받은 MST 총무게	

}

int kruskalMST(G* g, int n, int m) { // Kruskal 알고리즘으로 MST를 구하는 함수

	E* H[1001], * tmp; // 힙과 함수 내에서 사용될 변수들 선언
	int i, sum = 0;

	for (i = 0; i < m; i++) { // 배열에 간선 정보를 입력해준다.

		H[i + 1] = (g->e) + i;

	}

	buildHeap(&H, m); // 간선 정보가 입력된 배열을 힙으로 만들어준다. 

	i = 0;
	while (i != n - 1) { // MST는 정점의 개수보다 1개 적은 간선을 가지므로 n - 1개의 간선이 MST에 추가될 때까지 반복

		tmp = removeMin(&H, &m); // 가장 작은 가중치를 가진 간선을 힙에서 삭제 후 반환받는다.

		if (tmp->v1->sack != tmp->v2->sack) { // 간선에 연결된 정점들이 아직 연결되지 않은 분리집합의 정점들일 경우	MST에 추가		
			
			printf(" %d", tmp->weight); // 추가된 간선의 가중치 출력
			setUnion(g->v, tmp->v1->sack, tmp->v2->sack, n); // 두 분리집합을 합쳐준다.

			tmp->label = 1; // 해당 간선을 Tree 간선으로 표시해준다.
			sum += tmp->weight; // 가중치의 총합을 구하기 위해 sum에 더 해준다.
			i++; // 간선 개수 1 증가

		}

	}

	printf("\n");

	return sum; // MST 총무게 반환

}

void buildHeap(E** H, int n) { // 상향식 힙생성 함수

	int i;

	for (i = n / 2; i >= 1; i--)  // 마지막 내부노드부터 루트까지 downHeap을 해가며 정렬해준다.
		downHeap(H, i, n);	

}

void downHeap(E** H, int i, int n) { // 힙에서 키 값에 맞는 위치를 찾아 간선을 내려보내는 함수

	int smaller_idx;
	E* tmp;

	if (i * 2 > n) // 자식 노드가 없는 경우 힙에서의 위치를 설정 후 종료
		return;	

	smaller_idx = i * 2; // 왼쪽 자식을 더 작은 키 값을 가진 간선으로 일단 초기화

	if (i * 2 + 1 <= n && (*(H + (i * 2)))->weight > (*(H + (i * 2) + 1))->weight)  // 오른쪽 자식 노드가 존재하고 왼쪽보다 작을 경우 더 작은 값으로 초기화
		smaller_idx = i * 2 + 1;	

	if ((*(H + i))->weight < (*(H + smaller_idx))->weight) // 자식 노드 중 작은 값보다 자신이 더 작으면 정지
		return;	

	else { // 자식 노드 중 작은 값이 자신의 key보다 작으면 위치 변경

		tmp = *(H + i);
		*(H + i) = *(H + smaller_idx);
		*(H + smaller_idx) = tmp;

	}

	downHeap(H, smaller_idx, n); // 바뀐 위치에서 다시 자식 노드와 비교를 위해 재귀 호출

}

E* removeMin(E** H, int* n) { // 힙에서 가중치가 가장 작은 간선을 삭제하여 반환하는 함수

	E* u;

	u = *(H + 1); // 삭제될 간선 저장

	*(H + 1) = *(H + *n); // 힙에서 가장 마지막에 위치한 간선을 루트로 이동
	(*n)--;	// n을 1 감소

	downHeap(H, 1, *n); // 루트로 이동한 간선의 위치 이동

	return u; // 삭제된 간선 반환

}

void setUnion(V* g, int u, int v, int n) { // 분리집합 합집합 시켜주는 함수

	int i;

	for (i = 0; i < n; i++) { // 전체 정점을 순회하며 하나의 집합으로 합쳐준다.

		if ((g + i)->sack == v) 
			(g + i)->sack = u;
		
	}

}