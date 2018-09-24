#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml2c_OccupiedDefine.h"


enum OBJ_PGL_T _getObjPGL(char* name)
{
	enum OBJ_PGL_T enumRet = OBJ_PGL_UNKOWN;

	if (name != NULL) {
		if (strstr(name, "PARAM") != NULL) {
			enumRet = OBJ_PGL_P;
		}
		else if (strstr(name, "GLOBAL") != NULL) {
			enumRet = OBJ_PGL_G;
		}
		else if (strstr(name, "LOCAL") != NULL) {
			enumRet = OBJ_PGL_L;
		}
	}

	return enumRet;
}

P_VALUE_T _getObjVal(P_OBJ_T pObj, enum OBJ_PGL_T enumPGL, char* name, int len)
{
	int i = 0;

	if (name != NULL && 
		pObj != NULL &&
		(len > 0 && len < XC_DEFINE_ITEM_LEN)) {

		if (enumPGL == OBJ_PGL_P) {
			for(i = 0; i < pObj->paramCount; i++) {
				if (memcmp(pObj->param[i]->name, name, len) == 0) {
					return pObj->param[i];
					break;
				}
			}
		}
		else if (enumPGL == OBJ_PGL_G) {
			for(i = 0; i < pObj->globalCount; i++) {
				if (memcmp(pObj->global[i]->name, name, len) == 0) {
					return pObj->global[i];
					break;
				}
			}
		}
		else if (enumPGL == OBJ_PGL_L) {
			for(i = 0; i < pObj->localCount; i++) {
				if (memcmp(pObj->local[i]->name, name, len) == 0) {
					return pObj->local[i];
					break;
				}
			}
		}
	}

	return NULL;
}


