#include"seqstack.h"
PtrStack InitStack() {
	PtrStack st = (PtrStack)malloc(sizeof(Stack));
	st->top = 0;
	st->code[0] = 0;
	return st;
}
void push(PtrStack Stack, char Element) {
	Stack->code[Stack->top] = Element;
	Stack->top++;
	Stack->code[Stack->top] = 0;
}
void pop(PtrStack Stack) {
	Stack->top--;
	Stack->code[Stack->top] = 0;
}