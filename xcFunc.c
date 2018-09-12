#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"


extern void die(char *msg);

void printxcFunc(P_FUNC_T pxcFunc)
{
	int i = 0;

	if (pxcFunc == NULL) {
		printf("FUNC define is nothing!!!\n");
		return;
	}
	if (pxcFunc->returnValue.type[0] != 0 &&
		pxcFunc->returnValue.name[0] != 0 &&
		pxcFunc->name[0] != 0 &&
		pxcFunc->count >= 0) {
		for(i=0; i<pxcFunc->count; i++) {
			if (pxcFunc->param[i] == NULL || 
				pxcFunc->param[i]->type[0] == 0 || 
				pxcFunc->param[i]->name[0] == 0) {
				printf("FUNC`s param define Error 001. !!!\n");
				return;
			}
		}
		printf("%s\n%s ", pxcFunc->returnValue.type, pxcFunc->name);
	}
	else {
		printf("FUNC define Error 001. !!!\n");
		return;
	}
	if (pxcFunc->count == 0) {
		printf("( void ) {\n");
	}
	else if (pxcFunc->count > 0) {
		printf("(\n");
		for(i=0; i<pxcFunc->count; i++) {
			printf("%s %s", pxcFunc->param[i]->type, pxcFunc->param[i]->name);
			if (i == pxcFunc->count - 1) {
				printf(") {\n");
			}
			else {
				printf(",\n");
			}
		}
	}
}

int
getFunc (char *docname, P_FUNC_T pxcFunc)
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr cur = NULL;
	xmlNodePtr child = NULL;

	xmlChar* funcName = NULL;
	xmlChar* paramCount = NULL;
	xmlChar* paramName = NULL;
	xmlChar* text = NULL;
	xmlChar* returnType = NULL;
	xmlChar* returnName = NULL;

	int i=0;

	bool bFlag = false;

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

	cur = root;
	if (cur != NULL && 
		xmlStrcmp(cur->name, "FUNC") == 0) {

		funcName = xmlGetProp(cur, "name");
		paramCount = xmlGetProp(cur, "param_count");
		returnType = xmlGetProp(cur, "return_type");
		if (funcName == NULL) {
			printf("func name is not defined!!!\n");
			return -1;
		}
		else {
			memcpy(pxcFunc->name, funcName, xmlStrlen(funcName));
		}
		if (paramCount == NULL) {
			printf("func`s param count is not defined!!!\n");
			return -1;
		}
		else {
			pxcFunc->count = atoi(paramCount);
		}
		if (returnType == NULL) {
			printf("func`s return type is not defined!!!\n");
			return -1;
		}
		else {
			memcpy(pxcFunc->returnValue.type, returnType, xmlStrlen(returnType));
		}
		cur = root->children;
		for (; cur != NULL; cur = cur->next) {
			if (xmlStrcmp(cur->name, (xmlChar*)"OBJ") == 0) {
				child = cur->children;
				for (; child != NULL; child = child->next) {
					if (xmlStrcmp(child->name, (xmlChar*)"PARAM") == 0) {
						bFlag = true;
						break;
					}
				}
				if (bFlag) break;
			}
		}

		if (bFlag) {

			for (i = 0; i < pxcFunc->count; i++) {
				pxcFunc->param[i] = (P_VALUE_T)malloc(sizeof(VALUE_T));
				memset(pxcFunc->param[i], 0x00, sizeof(VALUE_T));
			}

			child = child->children;
			for (i=0; child != NULL; child = child->next) {
				if (child->type != XML_ELEMENT_NODE) {
					continue;
				}
				memcpy(pxcFunc->param[i]->type, child->name, xmlStrlen(child->name));
				paramName = xmlGetProp(child, "name");
				memcpy(pxcFunc->param[i]->name, paramName, xmlStrlen(paramName));
				if (child->children != NULL &&
					child->children->type == XML_TEXT_NODE) {
					text = xmlNodeListGetString(doc, child->children, 0);
					if (text != NULL) {
						memcpy(pxcFunc->param[i]->text, text, xmlStrlen(text));
					}
				}
				i++;
				if (paramName != NULL) {
					xmlFree(paramName);
					paramName = NULL;
				}
			}
		}
	
		bFlag = false;
		child = NULL;

		cur = root->children;
		for (; cur != NULL; cur = cur->next) {
			if (xmlStrcmp(cur->name, (xmlChar*)"OBJ") == 0) {
				child = cur->children;
				for (; child != NULL; child = child->next) {
					if (xmlStrcmp(child->name, (xmlChar*)"LOCAL") == 0) {
						bFlag = true;
						break;
					}
				}
				if (bFlag) break;
			}
		}

		if (bFlag) {

			child = child->children;
			for (; child != NULL; child = child->next) {
				if (child->type != XML_ELEMENT_NODE) {
					continue;
				}
				returnName = xmlGetProp(child, "name");
				if (returnName != NULL &&
					xmlStrcmp(returnName, (xmlChar*)"returnValue") == 0) {
					if (xmlStrcmp(pxcFunc->returnValue.type, child->name) != 0) {
						printf("FUNC`s return_type to LOCAL.returnValue define not same error.\n\n");
						return -1;
					}
					memcpy(pxcFunc->returnValue.type, child->name, xmlStrlen(child->name));
					memcpy(pxcFunc->returnValue.name, returnName, xmlStrlen(returnName));
					if (child->children != NULL &&
						child->children->type == XML_TEXT_NODE) {
						text = xmlNodeListGetString(doc, child->children, 0);
						if (text != NULL) {
							memcpy(pxcFunc->returnValue.text, text, xmlStrlen(text));
						}
					}
					break;
				}
			}
		}
	}

	return 0;
}


