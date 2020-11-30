#include"./Huff/Huffcode.h"
int main()
{
	//SetFile();
	char file[] = "D:\\input.txt";
	char outfile[] = "D:\\output.txt";
	int weight[MAXCHARSIZE] = { 0 };
	CharInfo cInfo[MAXCHARSIZE];
	for (int i = 0; i < MAXCHARSIZE; i++) {
		cInfo[i].weight = 0;
	}
	long long bytes = 0;
	InitArray(file, weight);
	PtrHuff L = (PtrHuff)malloc(sizeof(HuffmanNode));
	InitList(L, weight);
	InitHuff(L);
	PtrStack st = InitStack();
	HuffCode(L->next, code, st);
	InitCharInfo(cInfo, weight);
	WCharInfo(cInfo, outfile, &bytes);
	Huff(file, outfile, code);
	//·Ö¸îÏß
	for (int i = 0; i < MAXCHARSIZE; i++) {
		weight[i] = 0;
	}
	CharInfo* tmp=(CharInfo*)malloc(sizeof(CharInfo));
	FILE* OutFile = fopen(outfile, "r");
	fread(tmp, sizeof(CharInfo), 1, OutFile);
	int i = 0;
	bytes = 0;
	while (tmp->weight != 0 ) {
		weight[tmp->c] = tmp->weight;
		bytes = bytes + tmp->weight;
		fread(tmp, sizeof(CharInfo), 1, OutFile);
	}
	PtrHuff H = (PtrHuff)malloc(sizeof(HuffmanNode));
	InitList(H, weight);
	InitHuff(H);
	PtrStack at = InitStack();
	for (i = 0; i < MAXCHARSIZE; i++) {
		code[i].StrCode[0] = 0;
	}
	HuffCode(H->next, code, at);

	
	strcpy(outfile, "D:\\put.txt");
	EnHuff(OutFile, outfile, H, bytes);
	return 0;
}