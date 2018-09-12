#ifdef __XCTREE_H__
#define __XCTREE_H__

#include "xml2c_OccupiedDefine.h"

void getDepthTree (char *docname, P_XC_TREE_T pxcTree);
void printxcTree(P_XC_TREE_T pxcTree);

int getFunc (char *docname, P_FUNC_T pFunc);
void printxcFunc(P_FUNC_T pxcFunc);

int getObj (char *docname, P_OBJ_T pxcObj);
void printxcObjGlobal(P_OBJ_T pxcObj);
void printxcObjLocal(P_OBJ_T pxcObj);

int getT1 (char *docname, P_T1_T pT1);
void printxcT1(P_T1_T pT1);

#endif /* __XCTREE_H__ */
