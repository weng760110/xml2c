#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml2c_OccupiedDefine.h"


enum OBJ_PGL_T _getObjPGL(char* name);

P_VALUE_T _getObjVal(P_OBJ_T pObj, enum OBJ_PGL_T enumPGL, char* name, int len);

