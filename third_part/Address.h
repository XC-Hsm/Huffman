#pragma once
#include "Shlobj.h"
#include "tchar.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
char* SetFile();
void TcharToChar(const TCHAR* tchar, char* _char);
void sprint(char* string, int sleeptime);