/*
 정수 name과 label을 인자로 하는 구조체 vertex를 정점으로 사용하고
두 개의 정점 포인터 주소와 정수 weight와 label을 인자로 하는 구조체 edge를 간선으로 사용하는
자료구조를 이용해 그래프를 구현하였습니다.

 그래프 또한 구조체를 이용해 구현했으며 정점 정보를 저장하는 vertex 배열과 
간선 정보를 저장하는 edge 배열을 사용했고 배열 크기는 문제 조건인 정점 100개, 간선 1000개로 설정하였습니다.

 각 정점에 해당하는 간선 정보를 저장하기 위해 인접리스트를 사용하였습니다. 인접리스트에 사용된 노드는 간선 포인터 주소를 저장하고
다음 노드를 가리키는 next 포인터를 인자로 가지는 구조체를 사용했습니다.

 BFS 방문 함수에서는 레벨별 순회를 구현하기 위해 int형 배열을 동적 할당하여 Queue로 사용하였고 배열의 크기는 정점의
최대 개수인 n으로 할당했습니다.

 BFS 방문은 최초 방문 정점으로부터 연결된 간선을 통해 이웃한 노드들을 방문하여 Queue에 enqueue하고 이 때 사용된 간선의
label을 Tree 간선으로 설정 후 가중치를 더하였습니다. 이후 Queue가 빌 때까지 dequeue하며 이웃한 정점들이 미방문 상태일 경우
Tree 간선으로 설정 후 enqueue하고 가중치를 더했으며 이미 방문한 정점일 경우 label을 cross 간선으로 변경 후 양 끝 정점 정보를 출력하였습니다.
최종적으로 Queue가 비었을 때 구해놓은 가중치의 총 합을 반환하며 함수를 빠져나오고 이를 출력하며 프로그램을 종료했습니다.

 인접그래프를 사용한 그래프기 때문에 BFS의 시간복잡도는 O(n + m) 시간이 소요됩니다.

*/

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex { // 정점 구조체

	int name, label; // label : 0 (Fresh), 1 (Visited)	
	struct incidenceList* L;

}V;

typedef struct edge { // 간선 구조체

	struct vertex* v1, * v2;
	int weight; // 가중치
	int label; // label : 0 (Fresh), 1 (Tree), 2 (cross)

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
int BFS();
void enqueue();
int dequeue();
int isFull();
int isEmpty();

void main() {

	G g;
	int i, j, n, m, s, v1, v2, treeWeight_sum, w;
	inList* ltmp, * lttmp;
	
	scanf("%d%d%d", &n, &m, &s); // 정점, 간선의 개수와 순회 시작 정점 번호 입력

	for (i = 0; i < n; i++) { // 입력된 정점의 개수 n만큼 그래프에 정점 정보 초기화

		g.v[i].name = i + 1;
		g.v[i].label = 0; // 초기 방문 label을 Fresh로 초기화
		g.v[i].L = getL(); // 인접리스트 헤더노드 할당

	}

	for (i = 0; i < m; i++) { // 입력된 간선의 개수 m만큼 그래프의 간선 정보 초기화

		scanf("%d%d%d", &v1, &v2, &w);		

		g.e[i].v1 = g.v + v1 - 1;
		g.e[i].v2 = g.v + v2 - 1;
		g.e[i].label = 0;
		g.e[i].weight = w;

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


	treeWeight_sum = BFS(g, g.v + s - 1, n); // 너비 우선 탐색 함수 호출 후 가중치 총 합을 반환받아 저장

	printf("%d\n", treeWeight_sum); // 반환받은 가중치 총 합 출력

	for (i = 0; i < n; i++) { // 각 정점의 인접리스트 메모리 할당 해제

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

int BFS(G g, V* v, int n) { // 너비 우선 탐색 함수

	int* Q, rear, front, i, sum = 0, vtmp;
	inList* etmp;

	Q = (int*)malloc(sizeof(int) * n); // 큐로 사용할 배열 동적할당
	rear = n - 1; front = 0; // 큐의 rear와 front 초기화

	enqueue(Q, &rear, front, v->name, n); // 순회 시작 정점의 이름을 큐에 입력
	v->label = 1; // 순회 시작 정점의 label을 Visited로 변경

	while (!isEmpty(rear, front, n)) { // 큐가 빌 때까지 반복

		vtmp = dequeue(Q, rear, &front, n);	// dequeue된 정점의 이름 저장

		etmp = g.v[vtmp - 1].L->next; // 해당 차례 부착 간선 주소 저장

		while(etmp != NULL) { // dequeue된 정점의 부착 간선을 조사					

			if (etmp->e->label == 0) { // 해당 간선의 방문 여부를 확인하고 탐색

				if (etmp->e->v1->name == vtmp) { // 간선 반대편의 정점이 Fresh 상태일 경우 방문하고 label을 Visited 상태로 수정
					if (etmp->e->v2->label == 0) {

						etmp->e->v2->label = 1;
						enqueue(Q, &rear, front, etmp->e->v2->name, n);

						sum += etmp->e->weight; // BFS Tree 간선의 가중치 총합을 구하기 위해 해당 간선의 가중치를 더해준다.

						etmp->e->label = 1; // 간선의 label을 Tree 상태로 수정

					}

					else { // 이미 방문된 정점일 경우 간선의 양 끝 정점을 출력하고 해당 간선의 label을 cross 상태로 수정

						printf("%d %d\n", etmp->e->v1->name, etmp->e->v2->name);					
						etmp->e->label = 2;

					}
					
				}

				else {

					if (etmp->e->v1->label == 0) { // 간선 반대편의 정점이 Fresh 상태일 경우 방문하고 label을 Visited 상태로 수정
						
						etmp->e->v1->label = 1;
						enqueue(Q, &rear, front, etmp->e->v1->name, n);

						sum += etmp->e->weight; // BFS Tree 간선의 가중치 총합을 구하기 위해 해당 간선의 가중치를 더해준다.
												
						etmp->e->label = 1; // 간선의 label을 Tree 상태로 수정 

					}

					else { // 이미 방문된 정점일 경우 간선의 양 끝 정점을 출력하고 해당 간선의 label을 cross 상태로 수정

						printf("%d %d\n", etmp->e->v1->name, etmp->e->v2->name); 						
						etmp->e->label = 2;

					}

				}				

			}

			etmp = etmp->next;

		}

	}
	
	free(Q); // 함수 내에서 사용한 배열 메모리 할당 해제

	return sum; // Tree 간선의 가중치 총 합 반환

}

void enqueue(int* Q, int* rear, int front, int* value, int n) { // Queue에 원소를 삽입하는 함수

	if (isFull(*rear, front, n)) return; // 큐가 가득 찼을 경우 예외처리

	*rear = (*rear + 1) % n;
	*(Q + *rear) = value; // rear 위치에 삽입

}

int dequeue(int* Q, int rear, int* front, int n) { // Queue의 원소를 삭제하는 함수

	if (isEmpty(rear, *front, n)) return -1; // 큐가 비었을 경우 예외처리

	int e = *(Q + *front); // 삭제되는 원소를 반환하기 위해 저장

	*front = (*front + 1) % n; // front 위치 갱신

	return e; // 삭제된 원소 반환

}

int isFull(int rear, int front, int n) { // Queue가 가득 차있는 상태인지 아닌지 여부 반환

	return (rear + 2) % n == front;

}

int isEmpty(int rear, int front, int n) { // Queue가 비어있는지 여부 반환

	return (rear + 1) % n == front;

}