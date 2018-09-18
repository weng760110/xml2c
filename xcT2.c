#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"


extern void die(char *msg);

void printxcT2(P_T2_T pT2, P_OBJ_T pObj, P_T1_T pT1)
{
	int i = 0;

	if (pT2 == NULL) {
		printf("T2 define is nothing ERROR.!!!\n");
		return;
	}
	printf("\n\t/*");
	printf("\n\t** EVN1.T2.CHECK Global/Param Value");
	printf("\n\t*/\n");
	if (pT2->globalCheckFlag != 0) {
		for(i=0; i<pObj->globalCount; i++) {
			if (pObj->global[i] == NULL || 
				pObj->global[i]->type[0] == 0 || 
				pObj->global[i]->name[0] == 0) {
				return;
			}
			else {
				if (pObj->global[i]->pointer != 0) {
					printf("\tif ( %s == NULL ) {\n", pObj->global[i]->name);
					printf("\t\treturn (%s);\n\t}\n", pObj->local[pObj->localCount-1]->text);
				}
				else {
					printf("\tif ( %s == NULL ) {\n", pObj->global[i]->name);
					printf("\t\treturn (%s);\n\t}\n", pObj->local[pObj->localCount-1]->text);
				}
			}
		}
	}
	else {
		printf("\t/* EVN1.T2.CHECK Global Check nothing. */\n");
	}
	if (pT2->paramCheckFlag != 0) {
		for(i=0; i<pObj->paramCount; i++) {
			if (pObj->param[i] == NULL || 
				pObj->param[i]->type[0] == 0 || 
				pObj->param[i]->name[0] == 0) {
				return;
			}
			else {
				if (pObj->param[i]->pointer != 0) {
					printf("\tif ( %s == NULL ) {\n", pObj->param[i]->name);
					printf("\t\treturn (%s);\n\t}\n", pObj->local[pObj->localCount-1]->text);
				}
				else {
					printf("\tif ( %s == NULL ) {\n", pObj->param[i]->name);
					printf("\t\treturn (%s);\n\t}\n", pObj->local[pObj->localCount-1]->text);
				}
			}
		}
	}
	else {
		printf("\t/* EVN1.T2.CHECK Param Check nothing. */\n");
	}

	printf("\n\t/*");
	printf("\n\t** EVN1.T2.SET Global/Local/T1 Value");
	printf("\n\t*/\n");
	if (pT2->localSetFlag != 0) {
		for(i=0; i<pObj->localCount; i++) {
			if (pObj->local[i] == NULL || 
				pObj->local[i]->type[0] == 0 || 
				pObj->local[i]->name[0] == 0) {
				break;
			}
			else {
				if (strcasecmp(pObj->local[i]->type, "int") == 0 ||
					strcasecmp(pObj->local[i]->type, "long") == 0 ||
					strcasecmp(pObj->local[i]->type, "char") == 0 ||
					strcasecmp(pObj->local[i]->type, "bool") == 0) {
					if (pObj->local[i]->len[0] != 0) {
						printf("\tmemset(&%s, %s, sizeof(%s)*%s);\n", 
								pObj->local[i]->name, 
								pObj->local[i]->text, 
								pObj->local[i]->type,
								pObj->local[i]->len);
					}
					else {
						printf("\t%s = %s;\n", pObj->local[i]->name, pObj->local[i]->text);
					}
				}
				else {
					if (pObj->local[i]->len[0] != 0) {
						printf("\tmemset(&%s, %s, sizeof(%s)*%s);\n", 
								pObj->local[i]->name, 
								pObj->local[i]->text, 
								pObj->local[i]->type,
								pObj->local[i]->len);
					}
					else {
						printf("\tmemset(&%s, %s, sizeof(%s));\n", 
								pObj->local[i]->name, 
								pObj->local[i]->text, 
								pObj->local[i]->type);
					}
				}
			}
		}
	}
	else {
		printf("\t/* EVN1.T2.SET local Check nothing. */\n");
	}
	if (pT2->t1SetFlag != 0) {
		for(i=0; i<pT1->specCount; i++) {
			if (pT1->spec[i] == NULL || 
				pT1->spec[i]->type[0] == 0 || 
				pT1->spec[i]->name[0] == 0) {
				return;
			}
			else {
				if (strcasecmp(pObj->local[i]->type, "int") == 0 ||
					strcasecmp(pObj->local[i]->type, "long") == 0 ||
					strcasecmp(pObj->local[i]->type, "char") == 0 ||
					strcasecmp(pObj->local[i]->type, "bool") == 0) {
					if (pObj->local[i]->len > 0) {
						printf("\tmemset(&%s, %s, sizeof(%s)*%s);\n", 
								pObj->local[i]->name, 
								pObj->local[i]->text, 
								pObj->local[i]->type,
								pObj->local[i]->len);
					}
					else {
						printf("\t%s = %s;\n", pObj->local[i]->name, pObj->local[i]->text);
					}
				}
				else {
					if (pObj->local[i]->len[0] != 0) {
						printf("\tmemset(&%s, %s, sizeof(%s)*%s);\n", 
								pObj->local[i]->name, 
								pObj->local[i]->text, 
								pObj->local[i]->type,
								pObj->local[i]->len);
					}
					else {
						printf("\tmemset(&%s, %s, sizeof(%s));\n", 
								pObj->local[i]->name, 
								pObj->local[i]->text, 
								pObj->local[i]->type);
					}
				}
			}
		}
	}
	else {
		printf("\t/* EVN1.T2.SET spec set nothing. */\n");
	}
}


int
_getT2 (xmlNodePtr cur, P_T2_T pT2)
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
				if (xmlStrcmp(pNode->name, (xmlChar*)"T2") == 0) {
					pNode = pNode->children;
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
			if (xmlStrcmp(pNode->name, (xmlChar*)"CHECK") == 0) {
				name = xmlGetProp(pNode, (xmlChar*)"from");
				if (name != NULL) {
					if (xmlStrcmp(name, (xmlChar*)"FUNC.OBJ.PARAM") == 0) {
						pT2->paramCheckFlag = 1;
					}
					else if (xmlStrcmp(name, (xmlChar*)"FUNC.OBJ.GLOBAL") == 0) {
						pT2->globalCheckFlag = 1;
					}
					else {
						printf("ENV.T2.CHECK ERROR!!!\n");
					}
				}
			}
			else if (xmlStrcmp(pNode->name, (xmlChar*)"SET") == 0) {
				name = xmlGetProp(pNode, (xmlChar*)"from");
				if (name != NULL) {
					if (xmlStrcmp(name, (xmlChar*)"FUNC.OBJ.LOCAL") == 0) {
						pT2->localSetFlag = 1;
					}
					else if (xmlStrcmp(name, (xmlChar*)"FUNC.OBJ.GLOBAL") == 0) {
						pT2->globalSetFlag = 1;
					}
					else if (xmlStrcmp(name, (xmlChar*)"FUNC.EVN1.T1") == 0) {
						pT2->t1SetFlag = 1;
					}
					else {
						printf("ENV.T2.SET ERROR!!!\n");
					}
				}
			}
			else {
				printf("ENV.T2 ERROR!!!\n");
			}
		}
	}

    return 0;
}

/* Init value */
int
getT2 (char *docname, P_T2_T pT2)
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

	memset(pT2, 0x00, sizeof(T2_T));
	
	_getT2(cur, pT2);

    xmlFreeDoc(doc);

    return ret;
}

