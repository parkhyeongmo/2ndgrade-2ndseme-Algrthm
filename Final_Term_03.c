// IP : 112.149.113.193
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {

	int data;

	struct node* left;
	struct node* right;

	int height;

} NODE;

NODE* newNode(int data) {

	NODE* node = (NODE*)malloc(sizeof(NODE));

	node->data = data;

	node->left = NULL;
	node->right = NULL;

	return(node);
}

void calcHeight(NODE* v) {

	if (v->left == NULL && v->right == NULL) {

		v->height = 1;
		return;

	}

	if (v->left != NULL)
		calcHeight(v->left);

	if (v->right != NULL)
		calcHeight(v->right);

	int bigger_height = 1;

	if (v->left != NULL)
		bigger_height = v->left->height;

	if (v->right != NULL && v->right->height > bigger_height)
		bigger_height = v->right->height;

	v->height = bigger_height + 1;

}

int isBalanced(NODE* root, int data) {

	calcHeight(root);

	int sub;

	if (root->left == NULL && root->right != NULL)
		sub = root->right->height;

	else if (root->left != NULL && root->right == NULL)
		sub = root->left->height;

	else
		sub = root->left->height - root->right->height;

	if (sub < 0) sub *= -1;

	if (sub > 1)
		return 0;

	else
		return 1;

}

int main() {

	int n, data, balanced;

	NODE* root = NULL;

	scanf("%d %d", &n, &data);    // 트리 번호 , 키값 

	if (n == 1) {

		// No. 1

		root = newNode(4);

		root->left = newNode(2);

		root->right = newNode(5);

		root->left->left = newNode(1);

		root->left->right = newNode(3);

	}

	else if (n == 2) {

		// No. 2

		root = newNode(5);

		root->left = newNode(2);

		root->left->left = newNode(1);

		root->left->right = newNode(4);

	}

	else if (n == 3) {

		// No. 3

		root = newNode(3);

		root->left = newNode(2);

		root->right = newNode(7);

		root->right->left = newNode(6);

		root->right->left->left = newNode(5);

	}


	// 여기 작업 함수 호출 문이 들어간다
	balanced = isBalanced(root, data);

	printf("%d", balanced);



	return 0;

}





