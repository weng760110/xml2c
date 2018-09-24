#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml2c_OccupiedDefine.h"



void print_tab(int tab)
{
	int i = 0;
	for(; i < tab; i++) {
		printf("\t");
	}
}

void print_lf()
{
	printf("\n");
}

void print_int(char* name, int val)
{
	if (name == NULL) {
		return;
	}

	printf("%s = %d;", name, val);
}


void print_memcpy(char* name, char* val, int len)
{
	if (name == NULL ||
		val == NULL ) {
		return;
	}

	printf("memcpy(%s, %s, %d);", name, val, len);
}

void print_memset(char* name, int8_t val, int len)
{
	if (name == NULL) {
		return;
	}

	printf("memcpy(%s, %02X, %d);", name, val, len);
}

