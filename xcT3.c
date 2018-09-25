#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"


extern void die(char *msg);
extern int _getDepthTree (xmlNodePtr cur, P_XC_TREE_T pxcTree, int depth);
extern xmlNodePtr _getNodePtr(xmlNodePtr cur, int index);

XC_TREE_T* g_pThrdTree;

P_OBJ_T g_pThrdObj = NULL;

char g_T3IndexList[65536];



int
_getT3 (xmlNodePtr cur, P_T3_T pT3)
{
	enum T3_CLASS_T t3Class = T3_UNKOWN;
	bool bFlag = false;
	int i = 0;
	int index = 0;
	xmlNodePtr pNode = NULL;
	xmlChar* name = NULL;
	xmlChar* text = NULL;

	memset(g_T3IndexList, 0x00, sizeof(g_T3IndexList));
	_getT3IndexList();
	if (g_T3IndexList[0] == 0) {
		printf("XML TREE ERROR!!!\n");
		return -1;
	}

	for(i = 0; g_T3IndexList[i] == '1'; i++) {
		pNode = _getNodePtr(cur, i);
		if (pNode != NULL) {
			t3Class = _getT3Class(pNode);
			switch(t3Class) {
				case T3_SET:
					_T3Set();
					break;
				case T3_CALL:
					//_T3Call();
					break;
				case T3_IF:
					//_T3If();
					break;
				case T3_SWITCH:
					//_T3Switch();
					break;
				case T3_LOOP:
					//_T3Loop();
					break;
				default:
					break;
			}
		}
	}

    return 0;
}

/* Init value */
int
getT3 (char *docname, P_T3_T pT3, XC_TREE_T* pxcTree, P_OBJ_T pxcObj)
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr cur;

	int ret = 0;

	g_pThrdObj = pxcObj;

    doc = xmlParseFile(docname);

    if (doc == NULL ) {
        die("Document parsing failed. \n");
		return -1;
	}

    root = xmlDocGetRootElement(doc); //Gets the root element of the XML Doc

    if (root == NULL) {
        xmlFreeDoc(doc);
        die("Document is Empty!!!\n");
		return -1;
    }

    cur = root;//root->xmlChildrenNode;

	memset(pT3, 0x00, sizeof(T3_T));

	g_pThrdTree = pxcTree;
	
	_getT3(cur, pT3);

    xmlFreeDoc(doc);

    return ret;
}

