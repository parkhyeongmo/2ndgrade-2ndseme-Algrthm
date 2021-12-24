// IP : 112.149.113.193
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main() {

	int m[100][100], n, tmp;
	int i, j, sum = 0, isDirected = 2;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {

		for (j = 0; j < n; j++) {

			scanf("%d", &tmp);
			m[i][j] = tmp;

		}

	}

	for (i = 0; i < n; i++) {

		for (j = 0; j < n; j++) {

			if (m[i][j] != m[j][i]) isDirected = 1;
			if (m[i][j] != -1) sum += m[i][j];

		}

	}

	if (isDirected == 2) sum /= 2;

	printf("%d\n%d\n", isDirected, sum);

}