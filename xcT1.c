#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"


extern void die(char *msg);

void printxcT1(P_T1_T pT1)
{
	int i = 0;

	if (pT1 == NULL) {
		printf("T1 define is nothing ERROR.!!!\n");
		return;
	}
	if (pT1->spec != NULL) {
		printf("\n\t/*");
		printf("\n\t** EVN1.T1 spec define");
		printf("\n\t*/\n");
		for(i=0; i<pT1->specCount; i++) {
			if (pT1->spec[i] == NULL || 
				pT1->spec[i]->type[0] == 0 || 
				pT1->spec[i]->name[0] == 0) {
				break;
			}
			else {
				printf("\t%s  %s;\n", pT1->spec[i]->type, pT1->spec[i]->name);
			}
		}
	}
	else {
		printf("\t/* EVN1.T1 spec define nothing. */\n");
		return;
	}
}

int
_getT1 (xmlNodePtr cur, P_T1_T pT1)
{
	bool bFlag = false;
	int i = 0;
	xmlNodePtr pNode = NULL;
	xmlChar* name = NULL;
	xmlChar* text = NULL;

	pNode = cur->children;

	for(; pNode != NULL; pNode = pNode->next) {
		if (xmlStrcmp(pNode->name, (xmlChar*)"EVN1") == 0) {
			pNode = pNode->children;
			for(; pNode != NULL; pNode = pNode->next) {
				if (xmlStrcmp(pNode->name, (xmlChar*)"T1") == 0) {
					bFlag = true;
					break;
				}
			}
			if (bFlag) {
				break;
			}
		}
	}

	if (bFlag) {
		for(i = 0; pNode != NULL; pNode = pNode->next) {
			if (pNode->type != XML_ELEMENT_NODE) {
				continue;
			}
			if (xmlStrcmp(pNode->name, (xmlChar*)"DEFINE") == 0) {
				name = xmlGetProp(pNode, (xmlChar*)"from");
				if (name != NULL) {
					if (xmlStrcmp(name, (xmlChar*)"FUNC.OBJ.LOCAL") == 0) {
						pT1->localFlag = 1;
					}
					else if (xmlStrcmp(name, (xmlChar*)"FUNC.OBJ.PARAM") == 0) {
						pT1->paramFlag = 1;
					}
					else if (xmlStrcmp(name, (xmlChar*)"FUNC.OBJ.GLOBAL") == 0) {
						pT1->globalFlag = 1;
					}
					else {
						printf("ENV.T1.DEFINE ERROR!!!\n");
					}
				}
			}
			else if (xmlStrcmp(pNode->name, (xmlChar*)"DEFINE") == 0) {
				pT1->spec[i] = (P_VALUE_T)malloc(sizeof(VALUE_T));	
				memset(pT1->spec[i], 0x00, sizeof(VALUE_T));
				memcpy(pT1->spec[i]->type, pNode->name, xmlStrlen(pNode->name));
				name = xmlGetProp(pNode, (xmlChar*)"name");
				if (name != NULL) {
					memcpy(pT1->spec[i]->name, name, xmlStrlen(name));
					if (pNode->children != NULL &&
						pNode->children->type == XML_TEXT_NODE) {
						text = xmlNodeListGetString(pNode->doc, pNode->children, 0);
						if (text != NULL) {
							memcpy(pT1->spec[i]->text, text, xmlStrlen(text));
						}
					}
				}
				i++;
			}
		}
		pT1->specCount = i;
	}

    return 0;
}

/* Get define Info */
int
getT1 (char *docname, P_T1_T pT1)
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

	memset(pT1, 0x00, sizeof(T1_T));
	
	_getT1(cur, pT1);

    xmlFreeDoc(doc);

    return ret;
}

