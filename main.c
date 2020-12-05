#include "main.h"
int main()
{
	menu();
	char comd = getchar();
	if (comd == '1') {
		sprint("亲  请选择你要压缩的文件呢", 200);
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
		sprint("亲  您要的文件已经压缩好了呢\n就保存在", 200);
		sprint(outfile, 200);
		sprint("了哦  如果觉得人家好用的话  记得分享给你身边的朋友哦  谢谢亲  么么哒", 200);
		return 0;
	}
	else if (comd == '2') {
		int weight[MAXCHARSIZE] = { 0 };
		sprint("亲  请选择你要解压的文件呢", 200);
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
				perror("解压文件时发生错误");
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
		sprint("亲  您要的文件已经解压好了呢\n就保存在", 200);
		sprint(outfile, 200);
		sprint("了哦  如果觉得人家好用的话  记得分享给你身边的朋友哦  谢谢亲  么么哒", 200);
		return 0;
	}
	else if (comd == '3') {
		int weight[MAXCHARSIZE] = { 0 };
		sprint("亲  请选择你要解压的文件呢", 200);
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
				perror("解压文件时发生错误");
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
		sprint("请输入要查找的关键词，以换行符结束：\n",200);
		char b[200] = { 0 };
		char bcode[400] = { 0 };
		scanf("%s", b);
		int i;
		for (i = 0; b[i] != '\0'; i++) {
			if (code[b[i]].StrCode[0] != '\0') {
				strcat(bcode, code[b[i]].StrCode);
			}
			else {
				printf("未搜索到该关键词！");
				return 0;
			}
		}
		truebytes = truebytes - ftell(OutFile);
		char* buffer = (char*)malloc(sizeof(char) * truebytes * 8);
		if (buffer == NULL) {
			perror("动态分配内存失败");
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
			sprint("亲 真的要退出了嘛 人家好舍不得你呢  不留下来再看看人家嘛？o(*////▽////*)q\n", 30);
			sprint("留下了请按1，离开我请按2，是走是留，你自己决定吧╭(╯^╰)╮\n", 30);
			if (getchar() == '1')
				break;
		}
		sprint("你还是退出吧，留你也没啥用，慢走，不送", 20);
		return 0;
	}
}
void menu() {
	sprint("亲 欢迎使用男同文", 200);
	Sleep(200);
	printf("\r亲 欢迎使用男同 ");
	Sleep(200);
	printf("\r亲 欢迎使用男 ");
	Sleep(200);
	printf("\r亲 欢迎使用 ");
	printf("\r亲 欢迎使用");
	sprint("哈夫曼文件压缩解压程序\n", 200);
	//哈夫曼文件压缩程序\n
	sprint("压缩文件要按1哦", 200);
	printf("~\(≧▽≦)/~\n");
	sprint("解压文件请按2呢", 200);
	printf("╮(╯▽╰)╭\n");
	sprint("在压缩文档中查找关键词请按3", 200);
	printf("╭(╯^╰)╮\n");
	sprint("退出程序得按4呐\n", 200);
}