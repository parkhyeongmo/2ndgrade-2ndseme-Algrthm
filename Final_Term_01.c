{\rtf1\ansi\ansicpg949\cocoartf2636
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww28300\viewh16080\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 // IP : 112.149.113.193\
#pragma warning(disable:4996)\
#include <stdio.h>\
#include <stdlib.h>\
#include <limits.h>\
\
void main() \{\
\
	int m[100][100], n, tmp;\
	int i, j, sum = 0, isDirected = 2;\
\
	scanf("%d", &n);\
\
	for (i = 0; i < n; i++) \{\
\
		for (j = 0; j < n; j++) \{\
\
			scanf("%d", &tmp);\
			m[i][j] = tmp;\
\
		\}\
\
	\}\
\
	for (i = 0; i < n; i++) \{\
\
		for (j = 0; j < n; j++) \{\
\
			if (m[i][j] != m[j][i]) isDirected = 1;\
			if (m[i][j] != -1) sum += m[i][j];\
\
		\}\
\
	\}\
\
	if (isDirected == 2) sum /= 2;\
\
	printf("%d\\n%d\\n", isDirected, sum);\
\
\}}