#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"


void die(char *msg)
{
  fprintf(stderr, "%s", msg);
  return;
}

void printxcTree(P_XC_TREE_T pxcTree)
{
	int line = 0;
	int depth = 0;
	if (pxcTree->count <= 0) {
		printf("Tree is nothing!!!");
		return;
	}
	for(; line < pxcTree->count; line++) {
		printf("%d: ", line);
		for(depth = 0; pxcTree->dep[line]->name[depth][0] != 0; depth++) {
			printf(".%s", pxcTree->dep[line]->name[depth]);
		}
		printf("\n");
	}
}

int
_getDepthTree (xmlNodePtr cur, P_XC_TREE_T pxcTree, int depth)
{
	static int level = 0;

	int i=0;
	int j=0;

	for (; cur != NULL; cur = cur->next) {

		if (cur->type != XML_ELEMENT_NODE) {
			continue;
		}

		P_XC_DEFINE_DEPTH_T depItem = malloc(sizeof(XC_DEFINE_DEPTH_T));

		memset(depItem, 0x00, sizeof(XC_DEFINE_DEPTH_T));

		pxcTree->dep[level] = depItem;

		if (level > 0 && depth > 0) {
			memcpy(pxcTree->dep[level]->name, pxcTree->dep[level-1]->name, XC_DEFINE_DEPTH_NAME_LEN*depth); 
		}
		memcpy(pxcTree->dep[level]->name[depth], cur->name, xmlStrlen(cur->name)); 

		//printf("XXXXXXXXXXXdepth[%d][%d]=[%s]xxxxxxxxxxxxxx\n", level, depth, cur->name);

		level++;

		depth++;

        _getDepthTree(cur->children, pxcTree, depth);

		depth--;

    }

    return level;
}

int
getDepthTree (char *docname, P_XC_TREE_T pxcTree)
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr cur;

	int ret = 0;

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

	memset(pxcTree, 0x00, sizeof(XC_TREE_T));

	ret = _getDepthTree(cur, pxcTree, 0);

	pxcTree->count = ret;

    xmlFreeDoc(doc);

    return ret;
}

