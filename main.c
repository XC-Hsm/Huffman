#include"./Huff/Huffcode.h"
int main()
{
	//SetFile();
	sprint("亲 欢迎使用哈夫曼文件压缩程序\n",200);
	sprint("压缩文件要按1哦", 200);
	printf("~\(≧▽≦)/~\n");
	sprint("解压文件请按2呢", 200);
	printf("╮(╯▽╰)╭\n");
	sprint("退出程序得按3呐", 200);
	printf("╭(╯^╰)╮\n");
	char comd = getchar();
	if (comd == '1') {
		sprint("亲  请选择你要压缩的文件呢", 200);
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
		strcpy(outfile, "D:\\put.txt");
		EnHuff(OutFile, outfile, H, bytes);
		return 0;
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