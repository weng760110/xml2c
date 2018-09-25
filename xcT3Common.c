#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"


extern void die(char *msg);
extern int _getDepthTree (xmlNodePtr cur, P_XC_TREE_T pxcTree, int depth);

extern XC_TREE_T* g_pThrdTree;
extern char g_T3IndexList[65536];


void _getTreeStr(int index, char* str)
{
	int i=0;
	for(; g_pThrdTree->dep[index]->name[i][0] != 0; i++) {
		strcat(str, g_pThrdTree->dep[index]->name[i]);
	}
}

enum OBJ_TYPE_T _getObjType(char* strType)
{
	enum OBJ_TYPE_T enumRet = OBJ_TYPE_UNKOWN;

	if (strcmp(strType, "int") == 0) {
		return OBJ_TYPE_INT;
	}
	else if (strcmp(strType, "char") == 0) {
		return OBJ_TYPE_CHAR;
	}
	else if (strcmp(strType, "long") == 0) {
		return OBJ_TYPE_LONG;
	}
	
	return enumRet;
}

enum T3_CLASS_T _getT3Class(xmlNodePtr cur)
{
	enum T3_CLASS_T enumRet = T3_UNKOWN;
	xmlNodePtr pNode = cur;
	if (pNode == NULL) {
		return T3_UNKOWN;
	}
	for(; pNode != NULL; pNode = pNode->next) {
		if (xmlStrcmp(pNode->name, (xmlChar*)"SET") == 0) {
			return T3_SET;
		}
		else if (xmlStrcmp(pNode->name, (xmlChar*)"CALL") == 0) {
			return T3_CALL;
		}	
		else if (xmlStrcmp(pNode->name, (xmlChar*)"IF") == 0) {
			return T3_IF;
		}	
		else if (xmlStrcmp(pNode->name, (xmlChar*)"SWITCH") == 0) {
			return T3_SWITCH;
		}	
		else if (xmlStrcmp(pNode->name, (xmlChar*)"LOOP") == 0) {
			return T3_LOOP;
		}	
		else {
			return T3_UNKOWN;
		}
	}
	return enumRet;
}

/* tree */
int _getT3Index(int index)
{
	int i = -1;
	if (index <= 0 || index > 65536) {
		i = 0;
	}
	else {
		i = index;
	}
			if (strcmp(g_pThrdTree->dep[i]->name[0], "FUNC") == 0 &&
				strcmp(g_pThrdTree->dep[i]->name[1], "EVN1") == 0 &&
				strcmp(g_pThrdTree->dep[i]->name[2], "T3") == 0) {
				
			}
			else break;
		}
	return -1;
}

void _getT3IndexList()
{
	int index = 0;

	while(index >=0 && index <=65566) {
		index = _getT3Index(index);
		if (index == -1) {
			return;
		}
		else if (index <= 0 || index > 65536) {
			return;
		}
		else {
			g_T3IndexList[index] = '1';
		}
		index++;
	}
}


xmlNodePtr _getNodePtr(xmlNodePtr cur, int index)
{
	int i = 0;
	bool bFlag = false;
	xmlNodePtr pNode = NULL;
	xmlNodePtr pRet = NULL;

	if (index < 0) {
		printf("xmlNodePtr is NULL!!!\n");
		return NULL;
	}

	pNode = cur;

	for(i = 0; g_pThrdTree->dep[index]->name[i][0] != 0 && pNode != NULL; pNode = pNode->children, i++) {
		for(; pNode != NULL; pNode = pNode->next) {
			if (xmlStrcmp(pNode->name, (xmlChar*)g_pThrdTree->dep[index]->name[i]) == 0) {
				bFlag = true;
				pRet = pNode;
				break;
			}
			else {
				bFlag = false;
			}
		}
	}

	if (bFlag == false) {
		printf("bFlag == false!!!\n");
		return NULL;
	}

	return pRet;
}

