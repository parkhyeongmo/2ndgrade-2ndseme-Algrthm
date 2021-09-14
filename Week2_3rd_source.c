#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void SelectionSort();
void InsertionSort();
void Reverse_InsertionSort();

void main() {

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	int* Apq, * Bpq, n, i;

	scanf("%d", &n); // �迭�� ũ�� n �Է�

	Apq = (int*)malloc(sizeof(int) * n); // ũ�Ⱑ n�� �迭 �����Ҵ�
	Bpq = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));

	for (i = 0; i < n; i++) { // n���� ������ �ΰ��� �迭�� �Է�

		*(Apq + i) = *(Bpq + i) = rand();

	}

	Reverse_InsertionSort(Apq, n); // C ����� ������ ���� ������ �Լ� ȣ��	
	Reverse_InsertionSort(Bpq, n);	

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start); // �ð� ���� ����
	SelectionSort(Apq, n); // �������� �Լ� ȣ��
	QueryPerformanceCounter(&end); // �ð� ���� ����
	
	diff.QuadPart = end.QuadPart - start.QuadPart; // ���������κ��� ����ð� ���	
	printf("\n�������� %.12f ms\n", (double)(diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start); // �ð� ���� ����
	InsertionSort(Bpq, n); // �������� �Լ� ȣ��
	QueryPerformanceCounter(&end); // �ð� ���� ����

	diff.QuadPart = end.QuadPart - start.QuadPart; // ���������κ��� ����ð� ���
	printf("�������� %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	free(Apq); // �迭�� ���� �޸� �Ҵ� ����
	free(Bpq);

}

void SelectionSort(int* pq, int n) { // �迭�� �迭�� ũ�⸦ ���ڷ� �ϴ� �������� �Լ�

	int i, j, tmp, tmp_max;
	
	tmp_max = 0; // �迭�� ù��° ���ڸ�(index 0) �ִ밪���� �ʱ�ȭ 

	for (j = n - 1; j > 0; j--) { // �迭�� ���������� �ִ밪���� ä�������� ���� j�� �迭�� ������ ���� ��ġ�� n - 1�� ������ 1�� ����

		tmp_max = 0; // �� ���ึ�� �迭�� ù��° ���ڸ� �ִ밪���� �ʱ�ȭ		

		for (i = 0; i <= j; i++) { // ù��° ���ں��� �ش� ���࿡���� ���������� ��ȸ�ϸ� �ִ밪 Ž��
			if (*(pq + tmp_max) < *(pq + i)) {				
				tmp_max = i;
			}
		}

		tmp = *(pq + tmp_max); // �ش� ������ �ִ밪�� ������ ���ڿ� ��ü
		*(pq + tmp_max) = *(pq + j); 
		*(pq + j) = tmp;

	}

}

void InsertionSort(int* pq, int n) { // �迭�� �迭�� ũ�⸦ ���ڷ� �ϴ� �������� �Լ�

	int i, j, tmp;

	for (i = 1; i < n; i++) { // �迭�� �� �� �ΰ� ���Һ��� �����ϵ��� ����

		tmp = *(pq + i);
		j = i - 1;

		while (j >= 0 && *(pq + j) > tmp) { // �� ������ ������ ���Һ��� ù��° ���ұ��� ũ�⸦ ���ϸ� ��ġ�� �ű�� ���� ���Ұ� �� ���� ��� �ݺ��� ����

			*(pq + j + 1) = *(pq + j);
			j--;

		}

		*(pq + j + 1) = tmp; // �ش� ������ ��ġ�� ����

	}

}

void Reverse_InsertionSort(int* pq, int n) { // C ����� �м��� ���� �迭�� ������ �ϴ� �Լ�

	int i, j, tmp;

	for (i = 1; i < n; i++) { // �迭�� �� �� �ΰ� ���Һ��� �����ϵ��� ����

		tmp = *(pq + i);
		j = i - 1;

		while (j >= 0 && *(pq + j) < tmp) { // �� ������ ������ ���Һ��� ù��° ���ұ��� ũ�⸦ ���ϸ� ��ġ�� �ű�� ���� ���Ұ� �� ū ��� �ݺ��� ����

			*(pq + j + 1) = *(pq + j);
			j--;

		}

		*(pq + j + 1) = tmp; // �ش� ������ ��ġ�� ����

	}

}