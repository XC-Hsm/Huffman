#include "main.h"
int main()
{
	menu();
	char comd = getchar();
	if (comd == '1') {
		sprint("��  ��ѡ����Ҫѹ�����ļ���", 200);
		char file[100] = { 0 };
		strcpy(file, SetFile());
		//char file[] = "D:\\input.txt";
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
		sprint("��  ��Ҫ���ļ��Ѿ�ѹ��������\n�ͱ�����", 200);
		sprint(outfile, 200);
		sprint("��Ŷ  ��������˼Һ��õĻ�  �ǵ÷��������ߵ�����Ŷ  лл��  ôô��", 200);
		return 0;
	}
	else if (comd == '2') {
		int weight[MAXCHARSIZE] = { 0 };
		sprint("��  ��ѡ����Ҫ��ѹ���ļ���", 200);
		char outfile[100] = { 0 };
		strcpy(outfile, SetFile());
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
		strcpy(strchr(outfile, '.'), ".txt");
		EnHuff(OutFile, outfile, H, bytes);
		sprint("��  ��Ҫ���ļ��Ѿ���ѹ������\n�ͱ�����", 200);
		sprint(outfile, 200);
		sprint("��Ŷ  ��������˼Һ��õĻ�  �ǵ÷��������ߵ�����Ŷ  лл��  ôô��", 200);
		return 0;
	}
	else if (comd == '3') {
		int weight[MAXCHARSIZE] = { 0 };
		sprint("��  ��ѡ����Ҫ��ѹ���ļ���", 200);
		char outfile[100] = { 0 };
		strcpy(outfile, SetFile());
		long long bytes = 0;
		for (int i = 0; i < MAXCHARSIZE; i++) {
			weight[i] = 0;
		}
		CharInfo* tmp = (CharInfo*)malloc(sizeof(CharInfo));
		FILE* pf = fopen(outfile, "rb+");
		fseek(pf, 0L, SEEK_END);
		long long truebytes = ftell(pf);
		fclose(pf);
		FILE* OutFile = fopen(outfile, "rb+");
		fread(tmp, sizeof(CharInfo), 1, OutFile);
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
		for (int i = 0; i < MAXCHARSIZE; i++) {
			code[i].StrCode[0] = 0;
		}
		HuffCode(H->next, code, at);
		sprint("������Ҫ���ҵĹؼ��ʣ��Ի��з�������\n",200);
		char b[200] = { 0 };
		char bcode[400] = { 0 };
		scanf("%s", b);
		int i;
		for (i = 0; b[i] != '\0'; i++) {
			if (code[b[i]].StrCode[0] != '\0') {
				strcat(bcode, code[b[i]].StrCode);
			}
			else {
				printf("δ�������ùؼ��ʣ�");
				return 0;
			}
		}
		truebytes = truebytes - ftell(OutFile);
		char* buffer = (char*)malloc(sizeof(char) * truebytes * 8);
		if (buffer == NULL) {
			perror("��̬�����ڴ�ʧ��");
			exit(2);
		}
		int ch = fgetc(OutFile);
		int j = 0;
		while (!feof(OutFile)) {
			for (int i = 7; i >= 0; i--) {
				if (((1 << i) & ch) != 0)
					buffer[j] = '1';
				else
					buffer[j] = '0';
				j++;
			}
			ch = fgetc(OutFile);
		}
		buffer[j] = '\0';
		BM(bcode, strlen(bcode), buffer, j - 1);
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
void menu() {
	sprint("�� ��ӭʹ����ͬ��", 200);
	Sleep(200);
	printf("\r�� ��ӭʹ����ͬ ");
	Sleep(200);
	printf("\r�� ��ӭʹ���� ");
	Sleep(200);
	printf("\r�� ��ӭʹ�� ");
	printf("\r�� ��ӭʹ��");
	sprint("�������ļ�ѹ����ѹ����\n", 200);
	//�������ļ�ѹ������\n
	sprint("ѹ���ļ�Ҫ��1Ŷ", 200);
	printf("~\(�R���Q)/~\n");
	sprint("��ѹ�ļ��밴2��", 200);
	printf("�r(�s���t)�q\n");
	sprint("��ѹ���ĵ��в��ҹؼ����밴3", 200);
	printf("�q(�s^�t)�r\n");
	sprint("�˳�����ð�4��\n", 200);
}