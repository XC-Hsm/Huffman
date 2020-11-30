#pragma once
#pragma once
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"../SeqStack/seqstack.h"
#include "../Address/Address.h"
#define O(ch,i) ch |= 1<<i
#define Z(ch,i) ch &= ~(1<<i)
typedef struct CharInfo {
	char c;
	int weight;
}CharInfo, * PtrcInfo;
typedef struct HuffmanNode {
	char c;
	int weight;
	struct HuffmanNode* next;
	struct HuffmanNode* Lchild;
	struct HuffmanNode* Rchild;
	struct HuffmanNode* Parent;

}HuffmanNode, * PtrHuff;

typedef struct {
	char StrCode[MAXCHARSIZE];
}CodeNode;
CodeNode code[MAXCHARSIZE];

void InitHuff(PtrHuff ptr);
void SeekMin(PtrHuff L, PtrHuff ptrMin1, PtrHuff ptrMin2);
PtrHuff DelNode(PtrHuff L, char c);
void HuffCode(PtrHuff L, struct CodeNode* code, char* strcode);
void InitList(int* weight, PtrHuff* ptr);
void InitArray(char* f, int* w);
void WCharInfo(PtrcInfo pinfo, char* file, long long* pbytes);
void Huff(char* infile, char* outfile, CodeNode* code);
void InitCharInfo(PtrcInfo pinfo, int* weight);
void EnHuff(FILE* InFile, char* outfile, PtrHuff L, long long inbytes);