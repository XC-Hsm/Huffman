#pragma once
#define MAXCHARSIZE 128
typedef struct SeqStack {
	char code[MAXCHARSIZE];
	int top;
}Stack,*PtrStack;
PtrStack InitStack();
void push(PtrStack Stack, char Element);
void pop(PtrStack Stack);