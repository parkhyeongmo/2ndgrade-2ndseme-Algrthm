#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int findElement();

void main() {

	int a, b, n;
	char* str;

	scanf("%d%d%d", &a, &b, &n); // 구간을 나타내는 정수 a, b와 문자열의 길이를 입력

	str = (char*)malloc(sizeof(char) * (n + 1)); // 문자열 크기만큼 배열 동적 할당

	scanf("%s", str); // 문자열 입력

	printf("%d", findElement(a, b, str)); // 함수 호출 및 출력

	free(str); // 문자열 메모리 할당 해제

}

int findElement(int a, int b, char* str) { // 구간 정보와 탐색 정보를 가진 문자열을 인자로 하는 함수

	int i = 0; // 문자열을 탐색할 때 사용할 변수 선언

	while (*(str + i) != NULL) { // 문자열의 마지막까지 반복 탐색

		if (*(str + i) == 'Y') { // 해당 구간 정보가 참일 경우 a를 최신화
			a = (a + b) / 2 + 1;
		}
		else if (*(str + i) == 'N') { // 해당 구간 정보가 거짓일 경우 b를 최신화
			b = (a + b) / 2;
		}

		i++; // 문자열의 다음 문자로 이동

	}

	return a; // 발견된 결과 값 반환

}