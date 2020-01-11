#ifndef _lightEidt_h
#define _lightEidt_h

#include <stdbool.h>
#include <stdlib.h>

#include "cvector.h"

#include "./debug/memwatch.h"

V_Define(char, String);

V_Define(VCT_String *, FileLine);

bool Edit_OpenFile(char *name);
bool Edit_CloseFile(char *name);

void Edit_showLine(int n);
void Edit_deleteLine(int n);
void Edit_copyLineToUp(int des, int src);
void Edit_copyLineToDown(int des, int src);
void Edit_replaceAll(char *des, char *src);
void Edit_replace(int line, int row, int charCnt, char *des, char *src);
void Edit_instert(int line, int row, char *str);
void Edit_deleteAllStr(char *str);
void Edit_deleteStr(int line, int row, int n, char *str);

bool Edit_check(void);

#endif // _lightEidt_h