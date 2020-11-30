#include"./Huff/Huffcode.h"
int main()
{
	//SetFile();
	sprint("�� ��ӭʹ�ù������ļ�ѹ������\n",200);
	sprint("ѹ���ļ�Ҫ��1Ŷ", 200);
	printf("~\(�R���Q)/~\n");
	sprint("��ѹ�ļ��밴2��", 200);
	printf("�r(�s���t)�q\n");
	sprint("�˳�����ð�3��", 200);
	printf("�q(�s^�t)�r\n");
	char comd = getchar();
	if (comd == '1') {
		sprint("��  ��ѡ����Ҫѹ�����ļ���", 200);
		char file[100] = { 0 };
		strcpy(file, SetFile());
		//char file[] = "D:\\input.txt";
		printf("%s", file);
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
		char outfile[100] = { 0 };
		strcpy(outfile, file);
		strcpy(strchr(outfile, '.'), ".huff");
		WCharInfo(cInfo, outfile, &bytes);
		Huff(file, outfile, code);
		return 0;
	}
	else if (comd == '2') {
		int weight[MAXCHARSIZE] = { 0 };
		char outfile[] = "D:\\output.txt";
		long long bytes = 0;
		for (int i = 0; i < MAXCHARSIZE; i++) {
			weight[i] = 0;
		}
		CharInfo* tmp = (CharInfo*)malloc(sizeof(CharInfo));
		FILE* OutFile = fopen(outfile, "rb+");
		fread(tmp, sizeof(CharInfo), 1, OutFile);
		int i = 0;
		bytes = 0;
		while (tmp->weight != 0) {
			weight[tmp->c] = tmp->weight;
			bytes = bytes + tmp->weight;
			int a = fread(tmp, sizeof(CharInfo), 1, OutFile);
			if (a == 0) {
				perror("��ѹ�ļ�ʱ��������");
			}
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
	else {
		while ((comd = getchar()) != '1') {
			sprint("�� ���Ҫ�˳����� �˼Һ��᲻������  ���������ٿ����˼��o(*////��////*)q\n", 30);
			sprint("�������밴1���뿪���밴2���������������Լ������ɨq(�s^�t)�r\n", 30);
			if (getchar() == '1')
				break;
		}
		sprint("�㻹���˳��ɣ�����Ҳûɶ�ã����ߣ�����", 20);
		return 0;
	}
}