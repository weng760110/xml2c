#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xml2c_OccupiedDefine.h"


extern void die(char *msg);

void printxcObjGlobal(P_OBJ_T pxcObj)
{
	int i = 0;

	if (pxcObj == NULL) {
		printf("OBJ define is nothing ERROR.!!!\n");
		return;
	}
	if (pxcObj->globalCount > 0) {
		printf("/* global define B. */\n");
		for(i=0; i<pxcObj->globalCount; i++) {
			if (pxcObj->global[i] == NULL || 
				pxcObj->global[i]->type[0] == 0 || 
				pxcObj->global[i]->name[0] == 0) {
				return;
			}
			else {
				if (pxcObj->local[i]->pointer != 0) {
					printf("\t%s*  %s", pxcObj->local[i]->type, pxcObj->local[i]->name);
				}
				else {
					printf("\t%s  %s", pxcObj->local[i]->type, pxcObj->local[i]->name);
				}
				if (pxcObj->local[i]->len[0] != 0) {
					printf("[%s];\n", pxcObj->local[i]->len);
				}
				else {
					printf(";\n");
				}
			}
		}
		printf("/* global define E. */\n");
	}
	else {
		printf("/* global value define nothing. */\n");
		return;
	}
}

void printxcObjLocal(P_OBJ_T pxcObj)
{
	int i = 0;

	if (pxcObj == NULL) {
		printf("OBJ define is nothing ERROR.!!!\n");
		return;
	}
	if (pxcObj->localCount > 0) {
		printf("\t/* local define B. */\n");
		for(i=0; i<pxcObj->localCount; i++) {
			if (pxcObj->local[i] == NULL || 
				pxcObj->local[i]->type[0] == 0 || 
				pxcObj->local[i]->name[0] == 0) {
				return;
			}
			else {
				if (pxcObj->local[i]->pointer != 0) {
					printf("\t%s*  %s", pxcObj->local[i]->type, pxcObj->local[i]->name);
				}
				else {
					printf("\t%s  %s", pxcObj->local[i]->type, pxcObj->local[i]->name);
				}
				if (pxcObj->local[i]->len[0] != 0) {
					printf("[%s];\n", pxcObj->local[i]->len);
				}
				else {
					printf(";\n");
				}
			}
		}
		printf("\t/* local define E. */\n");
	}
	else {
		printf("\t/* local value define nothing. */\n");
		return;
	}
}

int
getObj (char *docname, P_OBJ_T pxcObj)
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr cur = NULL;
	xmlNodePtr child = NULL;

	xmlChar* count = NULL;
	xmlChar* name = NULL;
	xmlChar* text = NULL;
	xmlChar* type = NULL; /* char int long bool */
	xmlChar* typename = NULL; /* struct XXX */
	xmlChar* pointer = NULL;
	xmlChar* len = NULL;

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

		cur = root->children;
		for (; cur != NULL; cur = cur->next) {
			if (xmlStrcmp(cur->name, (xmlChar*)"OBJ") == 0) {
				child = cur->children;
				for (; child != NULL; child = child->next) {
					if (xmlStrcmp(child->name, (xmlChar*)"PARAM") == 0) {
						count = xmlGetProp(child, "count");
						pxcObj->paramCount = atoi(count);
						bFlag = true;
						break;
					}
				}
				if (bFlag) break;
			}
		}

		if (bFlag) {

			for (i = 0; i < pxcObj->paramCount; i++) {
				pxcObj->param[i] = (P_VALUE_T)malloc(sizeof(VALUE_T));
				memset(pxcObj->param[i], 0x00, sizeof(VALUE_T));
			}

			child = child->children;
			for (i=0; child != NULL; child = child->next) {
				if (child->type != XML_ELEMENT_NODE) {
					continue;
				}
				typename = xmlGetProp(child, "typename");
				if (typename != NULL) {
					sprintf(pxcObj->param[i]->type, "%s %s", child->name, typename);
				}
				else {
					sprintf(pxcObj->param[i]->type, "%s", child->name);
				}
				name = xmlGetProp(child, "name");
				pointer = xmlGetProp(child, "pointer");
				len = xmlGetProp(child, "len");
				memcpy(pxcObj->param[i]->name, name, xmlStrlen(name));
				if (pointer != NULL)
					memcpy(pxcObj->param[i]->pointer, pointer, xmlStrlen(pointer));
				if (len != NULL)
					memcpy(pxcObj->param[i]->len, len, xmlStrlen(len));
				if (child->children != NULL &&
					child->children->type == XML_TEXT_NODE) {
					text = xmlNodeListGetString(doc, child->children, 0);
					if (text != NULL) {
						memcpy(pxcObj->param[i]->text, text, xmlStrlen(text));
					}
				}
				i++;
			}
		}
	
		bFlag = false;
		child = NULL;

		cur = root->children;
		for (; cur != NULL; cur = cur->next) {
			if (xmlStrcmp(cur->name, (xmlChar*)"OBJ") == 0) {
				child = cur->children;
				for (; child != NULL; child = child->next) {
					if (xmlStrcmp(child->name, (xmlChar*)"GLOBAL") == 0) {
						count = xmlGetProp(child, "count");
						pxcObj->globalCount = atoi(count);
						bFlag = true;
						break;
					}
				}
				if (bFlag) break;
			}
		}

		if (bFlag) {

			for (i = 0; i < pxcObj->globalCount; i++) {
				pxcObj->global[i] = (P_VALUE_T)malloc(sizeof(VALUE_T));
				memset(pxcObj->global[i], 0x00, sizeof(VALUE_T));
			}

			child = child->children;
			for (i=0; child != NULL; child = child->next) {
				if (child->type != XML_ELEMENT_NODE) {
					continue;
				}
				typename = xmlGetProp(child, "typename");
				if (typename != NULL) {
					sprintf(pxcObj->global[i]->type, "%s %s", child->name, typename);
				}
				else {
					sprintf(pxcObj->global[i]->type, "%s", child->name);
				}
				name = xmlGetProp(child, "name");
				pointer = xmlGetProp(child, "pointer");
				len = xmlGetProp(child, "len");
				memcpy(pxcObj->global[i]->name, name, xmlStrlen(name));
				if (pointer != NULL)
					memcpy(pxcObj->global[i]->pointer, pointer, xmlStrlen(pointer));
				if (len != NULL)
					memcpy(pxcObj->global[i]->len, len, xmlStrlen(len));
				if (child->children != NULL &&
					child->children->type == XML_TEXT_NODE) {
					text = xmlNodeListGetString(doc, child->children, 0);
					if (text != NULL) {
						memcpy(pxcObj->global[i]->text, text, xmlStrlen(text));
					}
				}
				i++;
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
						count = xmlGetProp(child, "count");
						pxcObj->localCount = atoi(count);
						bFlag = true;
						break;
					}
				}
				if (bFlag) break;
			}
		}

		if (bFlag) {

			for (i = 0; i < pxcObj->localCount; i++) {
				pxcObj->local[i] = (P_VALUE_T)malloc(sizeof(VALUE_T));
				memset(pxcObj->local[i], 0x00, sizeof(VALUE_T));
			}

			child = child->children;
			for (i=0; child != NULL; child = child->next) {
				if (child->type != XML_ELEMENT_NODE) {
					continue;
				}
				memcpy(pxcObj->local[i]->type, child->name, xmlStrlen(child->name));
				typename = xmlGetProp(child, "typename");
				if (typename != NULL) {
					sprintf(pxcObj->local[i]->type, "%s %s", child->name, typename);
				}
				else {
					sprintf(pxcObj->local[i]->type, "%s", child->name);
				}
				name = xmlGetProp(child, "name");
				pointer = xmlGetProp(child, "pointer");
				len = xmlGetProp(child, "len");
				memcpy(pxcObj->local[i]->name, name, xmlStrlen(name));
				if (pointer != NULL)
					memcpy(pxcObj->local[i]->pointer, pointer, xmlStrlen(pointer));
				if (len != NULL)
					memcpy(pxcObj->local[i]->len, len, xmlStrlen(len));
				if (child->children != NULL &&
					child->children->type == XML_TEXT_NODE) {
					text = xmlNodeListGetString(doc, child->children, 0);
					if (text != NULL) {
						memcpy(pxcObj->local[i]->text, text, xmlStrlen(text));
					}
				}
				i++;
			}
		}
	
	}

	return 0;
}


