#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"
#include "pub_xml_api.h"
#include "pub_print.h"


extern void die(char *msg);
extern int _getDepthTree (xmlNodePtr cur, P_XC_TREE_T pxcTree, int depth);
enum OBJ_TYPE_T _getObjType(char* strType);

extern XC_TREE_T* g_pThrdTree;
extern char g_T3IndexList[65536];
extern P_OBJ_T g_pThrdObj;


int printT3Set(int index)
{
	P_SET_T pSet = g_pThrdTree->dep[index]->t3.pSet;

	enum OBJ_TYPE_T enumType = OBJ_TYPE_UNKOWN;
	enum OBJ_PGL_T enumPGLfrom = OBJ_PGL_UNKOWN;
	enum OBJ_PGL_T enumPGLto = OBJ_PGL_UNKOWN;
	P_VALUE_T pVALfrom = NULL;
	P_VALUE_T pVALto = NULL;

	enumPGLfrom = _getObjPGL(pSet->from);

	if (enumPGLfrom == OBJ_PGL_P) {
		pVALfrom = _getObjVal(g_pThrdObj, OBJ_PGL_P, pSet->name, strlen(pSet->name));
	}
	else if (enumPGLfrom == OBJ_PGL_G) {
		pVALfrom = _getObjVal(g_pThrdObj, OBJ_PGL_G, pSet->name, strlen(pSet->name));
	}
	else if (enumPGLfrom == OBJ_PGL_L) {
		pVALfrom = _getObjVal(g_pThrdObj, OBJ_PGL_L, pSet->name, strlen(pSet->name));
	}
	else return -1;

	enumPGLto = _getObjPGL(pSet->to);
	if (enumPGLto == OBJ_PGL_P) {
		pVALto = _getObjVal(g_pThrdObj, OBJ_PGL_P, pSet->name, strlen(pSet->name));
	}
	else if (enumPGLto == OBJ_PGL_G) {
		pVALto = _getObjVal(g_pThrdObj, OBJ_PGL_G, pSet->name, strlen(pSet->name));
	}
	else if (enumPGLto == OBJ_PGL_L) {
		pVALto = _getObjVal(g_pThrdObj, OBJ_PGL_L, pSet->name, strlen(pSet->name));
	}
	else return -1;

	enumType = _getObjType(pVALto->type);
	if (enumType == OBJ_TYPE_INT) {
		if (pSet->to[0] == 0) {
			PRT_INT_VAL(pVALto->name, atoi(pSet->text), 1, 1);
		}
		else {
			PRT_INT_NAME(pVALto->name, pVALfrom->name, 1, 1);
		}
	}
}

int _T3Set(xmlNodePtr cur, int index)
{
	xmlNodePtr pNode = NULL;
	xmlChar* from = NULL;
	xmlChar* to = NULL;
	xmlChar* name = NULL;
	xmlChar* text = NULL;
	char treeStr[256];

	if (cur == NULL) {
		printf("xmlNodePtr is NULL!!!\n");
		return -1;
	}

	pNode = cur;

	from = xmlGetProp(pNode, "from");
	to = xmlGetProp(pNode, "to");
	name = xmlGetProp(pNode, "name");
	text = xmlNodeListGetString(pNode->doc, pNode->children, 0);

	if (from == NULL &&
		to == NULL) {
		memset(treeStr, 0x00, sizeof(treeStr));
		_getTreeStr(index, treeStr);
		printf("[%s].from is NULL or [%s].to is NULL!!!", 
				treeStr,treeStr);
		return -1;
	}
	
	P_SET_T pSet = (P_SET_T)malloc(sizeof(SET_T));
	g_pThrdTree->dep[index]->t3.pSet = pSet;

	memset(pSet, 0x00, sizeof(SET_T));

	memcpy(pSet->from, from, xmlStrlen(from));
	memcpy(pSet->to, to, xmlStrlen(to));
	memcpy(pSet->name, name, xmlStrlen(name));
	memcpy(pSet->text, name, xmlStrlen(text));
	
	return 0;
}

