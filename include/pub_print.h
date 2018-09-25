#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml2c_OccupiedDefine.h"


void print_tab(int tab);

void print_lf();

void print_int(char* name, int val);

void print_memcpy(char* name, char* val, int len);

void print_memset(char* name, int8_t val, int len);


#define PRT_INT_VAL(TARGET,VAL,LF,TAB) \
{ \
	if (TARGET == NULL) { return; } \
	if (LF == -1) { print_lf(); } \
	if (TAB > 0) { print_tab(TAB); } \
	print_int(TARGET,VAL); \
	if (LF == 1) { print_lf(); } \
}
	
#define PRT_INT_NAME(TARGET,SRC,LF,TAB) \
{ \
	if (TARGET == NULL || SRC == NULL) { return; } \
	if (LF == -1) { print_lf(); } \
	if (TAB > 0) { print_tab(TAB); } \
	print_int(TARGET,atoi(SRC)); \
	if (LF == 1) { print_lf(); } \
}
	
	
#define PRT_STR(NAME,VAL,LEN,LF,TAB) \
{ \
	if (NAME == NULL || LEN <= 0) { return; } \
	if (LF == -1) { print_lf(); } \
	if (TAB > 0) { print_tab(TAB); } \
	print_memcpy(NAME, VAL, LEN); \
	if (LF == 1) { print_lf(); } \
}
	
#define PRT_STR_RESET(NAME,VAL,LEN,LF,TAB) \
{ \
	if (NAME == NULL || LEN <= 0) { return; } \
	if (LF == -1) { print_lf(); } \
	if (TAB > 0) { print_tab(TAB); } \
	print_memset(NAME, VAL, LEN); \
	if (LF == 1) { print_lf(); } \
}
	
