{\rtf1\ansi\ansicpg949\cocoartf2636
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;\f1\fnil\fcharset129 AppleSDGothicNeo-Regular;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 // IP : 112.149.113.193\
#pragma warning(disable:4996)\
#include <stdio.h>\
#include <stdlib.h>\
#include <limits.h>\
\
typedef struct node\{\
\
	int data;\
\
	struct node* left;\
	struct node* right;\
\
	int height;\
\
\} NODE;\
\
NODE* newNode(int data)\{\
\
	NODE* node = (NODE*)malloc(sizeof(NODE));\
\
	node->data = data;\
\
	node->left = NULL;\
	node->right = NULL;\
\
	return(node);\
\}\
\
void calcHeight(NODE* v) \{\
\
	if (v->left == NULL && v->right == NULL) \{\
\
		v->height = 1;\
		return;\
\
	\}\
\
	if (v->left != NULL)\
		calcHeight(v->left);\
\
	if (v->right != NULL)\
		calcHeight(v->right);\
\
	int bigger_height = 1;\
\
	if (v->left != NULL)\
		bigger_height = v->left->height;\
\
	if (v->right != NULL && v->right->height > bigger_height)\
		bigger_height = v->right->height;\
\
	v->height = bigger_height + 1;\
\
\}\
\
int isBalanced(NODE* root, int data) \{\
\
	calcHeight(root);\
\
	int sub;\
\
	if (root->left == NULL && root->right != NULL)\
		sub = root->right->height;\
\
	else if (root->left != NULL && root->right == NULL)\
		sub = root->left->height;\
\
	else\
		sub = root->left->height - root->right->height;\
\
	if (sub < 0) sub *= -1;\
\
	if (sub > 1) \
		return 0;\
\
	else\
		return 1;\
\
\}\
\
int main()\{\
\
	int n, data, balanced;\
\
	NODE* root = NULL;\
\
	scanf("%d %d", &n, &data);    // 
\f1 \'c6\'ae\'b8\'ae
\f0  
\f1 \'b9\'f8\'c8\'a3
\f0  , 
\f1 \'c5\'b0\'b0\'aa
\f0  \
\
	if (n == 1)	\{\
\
		// No. 1\
\
		root = newNode(4);\
\
		root->left = newNode(2);\
\
		root->right = newNode(5);\
\
		root->left->left = newNode(1);\
\
		root->left->right = newNode(3);\
\
	\}\
\
	else if (n == 2) \{\
\
		// No. 2\
\
		root = newNode(5);\
\
		root->left = newNode(2);\
\
		root->left->left = newNode(1);\
\
		root->left->right = newNode(4);\
\
	\}\
\
	else if (n == 3) \{\
\
		// No. 3\
\
		root = newNode(3);\
\
		root->left = newNode(2);\
\
		root->right = newNode(7);\
\
		root->right->left = newNode(6);\
\
		root->right->left->left = newNode(5);\
\
	\}\
\
\
	// 
\f1 \'bf\'a9\'b1\'e2
\f0  
\f1 \'c0\'db\'be\'f7
\f0  
\f1 \'c7\'d4\'bc\'f6
\f0  
\f1 \'c8\'a3\'c3\'e2
\f0  
\f1 \'b9\'ae\'c0\'cc
\f0  
\f1 \'b5\'e9\'be\'ee\'b0\'a3\'b4\'d9
\f0 \
	balanced = isBalanced(root, data);\
\
	printf("%d", balanced);\
\
\
\
	return 0;\
\
\}\
\
\
\
\
\
}