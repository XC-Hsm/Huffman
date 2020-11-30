#include"Huffcode.h"
void EnHuff(FILE* InFile, char* outfile, PtrHuff L, long long inbytes) {
	long long bytes = 0;
	FILE* OutFile = fopen(outfile, "wb");
	if (OutFile == NULL) {
		perror("打开输出文件时发生错误");
		return (-1);
	}
	int ch = fgetc(InFile);
	int bit = 7;
	PtrHuff ptr = L->next;
	while (!feof(InFile)) {
		while (ptr->Lchild != NULL && ptr->Rchild != NULL) {
			if (((1 << bit) & ch) != 0)
				ptr = ptr->Rchild;
			else
				ptr = ptr->Lchild;
			bit--;
			if (bit == -1) {
				bit = 7;
				ch = fgetc(InFile);
			}
		}
		fputc(ptr->c, OutFile);
		ptr = L->next;
		bytes++;
		if (bytes == inbytes) {
			fclose(InFile);
			fclose(OutFile);
			return;
		}
	}
}
void Huff(char* infile, char* outfile, CodeNode* code) {
	FILE* OutFile = fopen(outfile, "a+");
	if (OutFile == NULL) {
		perror("打开输出文件时发生错误");
		return (-1);
	}
	FILE* InFile = fopen(infile, "r");
	if (InFile == NULL) {
		perror("打开待压缩文件时发生错误");
		return (-1);
	}
	int ch = fgetc(InFile);
	char c = '0';
	int bit = 7;
	while (!feof(InFile)) {
		for (int i = 0; code[ch].StrCode[i] != '\0'; i++) {
			if (code[ch].StrCode[i] == '1') {
				O(c, bit);
			}
			if (code[ch].StrCode[i] == '0') {
				Z(c, bit);
			} 
			bit--;
			if (bit == -1) {
				fputc(c, OutFile);
				c = '0';
				bit = 7;
			}
		}
		ch = fgetc(InFile);
	}
	while (bit != -1) {
		bit--;
		Z(c, bit);
	}
	fputc(c, OutFile);
	fclose(InFile);
	fclose(OutFile);
}
void WCharInfo(PtrcInfo pinfo, char* file, long long* pbytes) {
	FILE* OutFile = fopen(file, "wb");
	if (OutFile == NULL) {
		perror("打开文件时发生错误");
		return(-1);
	}
	long long bytes = *pbytes;
	for (int i = 0; i < MAXCHARSIZE; i++)
	{
		if (pinfo[i].weight != 0)
		{
			fwrite(&pinfo[i], sizeof(CharInfo), 1, OutFile);
			printf("%c->%d", pinfo[i].c, pinfo[i].weight);
			bytes++;
		}
	}
	CharInfo flag;
	flag.weight = 0;
	fwrite(&flag, sizeof(flag), 1, OutFile);
	bytes++;
	fclose(OutFile);
}

void InitCharInfo(PtrcInfo pinfo, int* weight) {
	for (int i = 0; i < MAXCHARSIZE; i++)
	{
		if (weight[i] != 0)
		{
			pinfo[i].c = i;
			pinfo[i].weight = weight[i];
		}
	}
}

void HuffCode(PtrHuff L, CodeNode* code, PtrStack st) {
	if (L->Lchild == NULL && L->Rchild == NULL) {
		strcpy(code[L->c].StrCode, st->code);
		pop(st);
		return;
	}
	push(st, '0');
	HuffCode(L->Lchild, code, st);
	push(st, '1');
	HuffCode(L->Rchild, code, st);
	pop(st);
	return;
}
void InitArray(char* f, int* w) {
	FILE* InFile = fopen(f, "r");
	if (InFile == NULL)
	{
		perror("打开文件时发生错误");
		return(-1);
	}
	int ch = fgetc(InFile);
	while (!feof(InFile)) {
		if (ch >= 0) {
			w[ch]++;
			ch = fgetc(InFile);
		}
	}
	fclose(InFile);
}
void InitList(PtrHuff L, int* weight) {
	L->next = NULL;
	L->c = '\0';
	L->weight = 0;
	L->Lchild = NULL;
	L->Rchild = NULL;
	PtrHuff ptrTmp = L;
	for (int i = 0; i < MAXCHARSIZE; i++)
		if (weight[i] != 0) {
			ptrTmp->next = (PtrHuff)malloc(sizeof(HuffmanNode));
			ptrTmp = ptrTmp->next;
			ptrTmp->Lchild = NULL;
			ptrTmp->Rchild = NULL;
			ptrTmp->c = i;
			ptrTmp->weight = weight[i];
			ptrTmp->next = NULL;
		}
}
void InitHuff(PtrHuff L) {
	PtrHuff ptrMin1 = NULL, ptrMin2 = NULL, ptrD;
	while (L->next->next != NULL) {
		SeekMin(L, &ptrMin1, &ptrMin2);
		PtrHuff Child = (PtrHuff)malloc(sizeof(HuffmanNode));
		Child->Lchild = ptrMin1->Lchild;
		Child->Rchild = ptrMin1->Rchild;
		ptrMin1->Lchild = Child;
		ptrMin1->Rchild = ptrMin2;
		Child->Parent = ptrMin1;
		ptrMin2->Parent = ptrMin1;
		ptrMin1->Lchild->c = ptrMin1->c;
		ptrMin1->Lchild->weight = ptrMin1->weight;
		ptrMin1->weight = ptrMin1->weight + ptrMin2->weight;
		DelNode(L, &ptrMin2);
	}
}

void SeekMin(PtrHuff L, PtrHuff* ptrMin1, PtrHuff* ptrMin2) {
	PtrHuff i = L->next;
	*ptrMin1 = L->next;
	*ptrMin2 = L->next;
	int Min1 = i->weight, Min2 = ~(unsigned int)0 / 2;
	for (; i != NULL; i = i->next) {
		if (i->weight <= Min1) {
			*ptrMin1 = i;
			Min1 = i->weight;
		}
	}
	for (i = L->next; i != NULL; i = i->next) {
		if (i->weight <= Min2 && i != (*ptrMin1)) {
			*ptrMin2 = i;
			Min2 = i->weight;
		}
	}
}
PtrHuff DelNode(PtrHuff L, PtrHuff* c) {
	PtrHuff ptr, nptr = NULL;
	for (ptr = L; ptr->next != NULL; ptr = ptr->next) {
		if (ptr->next == *c) {
			nptr = ptr->next;
			ptr->next = nptr->next;
			nptr->next = NULL;
			return nptr;
		}
	}
}

