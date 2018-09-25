#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"
#include "xml2c.h"

XC_TREE_T  g_xcTree;
FUNC_T  g_Func;
OBJ_T	g_Obj;
T1_T	g_T1;
T2_T	g_T2;
T3_T	g_T3;

void die(char *msg)
{
  fprintf(stderr, "%s", msg);
  return;
}

int
main(int argc, char **argv)
{
    char *docname;

    if (argc != 2) {
        printf("Usage: %s <docname>\n", argv[0]);
        return(0);
    }

    docname = argv[1];

	memset(&g_xcTree, 0x00, sizeof(XC_TREE_T));
	memset(&g_Func, 0x00, sizeof(FUNC_T));
	memset(&g_Obj, 0x00, sizeof(OBJ_T));
	memset(&g_T1, 0x00, sizeof(T1_T));
	memset(&g_T2, 0x00, sizeof(T2_T));
	memset(&g_T3, 0x00, sizeof(T3_T));

    getDepthTree (docname, &g_xcTree);
	printxcTree(&g_xcTree);

    getObj (docname, &g_Obj);
	printxcObjGlobal(&g_Obj);

    getFunc (docname, &g_Func);
	printxcFunc(&g_Func);

	printxcObjLocal(&g_Obj);

	getT1 (docname, &g_T1);
	printxcT1(&g_T1);

	getT2 (docname, &g_T2);
	printxcT2(&g_T2, &g_Obj, &g_T1);

	getT3 (docname, &g_T3, &g_xcTree, &g_Obj);
	printT3Set(30);

    return (1);
}

