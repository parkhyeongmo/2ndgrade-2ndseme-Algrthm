#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct pivot {
	int a, b;
}Pivot;

int findPivot();
Pivot inPlacePartition();
void inPlaceQuickSort();

void main() {

	int* A, i, n;

	scanf("%d", &n);

	A = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
	
		scanf("%d", A + i);
	
	}

	inPlaceQuickSort(A, 0, n - 1);

	for (i = 0; i < n; i++) {

		printf(" %d", *(A + i));

	}

	free(A);

}

int findPivot(int* A, int l, int r) {

	int a, b, c;

	a = *(A + l);
	b = *(A + r);
	c = *(A + ((r + l) / 2));

	if (a <= b && a <= c) {

		if (b <= c) return r;
		else return ((r + l) / 2);

	}

	else if (b <= a && b <= c) {

		if (a <= c) return l;
		else return ((r + l) / 2);

	}

	else {

		if (a <= b) return l;
		else return r;

	}

}

void inPlaceQuickSort(int* A, int l, int r) {

	if (l >= r) return;

	int k;
	Pivot pi;

	k = findPivot(A, l, r);

	pi = inPlacePartition(A, l, r, k);

	inPlaceQuickSort(A, l, pi.a - 1);
	inPlaceQuickSort(A, pi.b + 1, r);

}

Pivot inPlacePartition(int* A, int l, int r, int k) {

	Pivot pv;
	int i, j, p, Pi, tmp;

	p = *(A + k);

	tmp = *(A + r);
	*(A + r) = p;
	*(A + k) = tmp;

	i = l;
	j = r - 1;
	Pi = r - 1;

	while (i <= j) {

		while (i <= j && *(A + i) <= p) {

			if (i <= j && *(A + i) == p) {

				tmp = *(A + Pi);
				*(A + Pi) = p;
				*(A + i) = tmp;

				Pi--;
				continue;

			}

			i++;

		}

		while (i <= j && *(A + j) >= p) {

			if (i <= j && *(A + j) == p) {

				tmp = *(A + Pi);
				*(A + Pi) = p;
				*(A + j) = tmp;

				Pi--;
				continue;

			}

			j--;

		}

		if (i < j) {
			tmp = *(A + i);
			*(A + i) = *(A + j);
			*(A + j) = tmp;
		}

	}

	tmp = *(A + i);
	*(A + i) = *(A + r);
	*(A + r) = tmp;

	pv.b = pv.a = i;

	return pv;

}