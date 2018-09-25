/* FUNC Xml Tree define */

/*
FUNC,
FUNC.ENV
FUNC.OBJ
FUNC.OBJ.PARAM
FUNC.OBJ.LOCAL
FUNC.EVN1.T1
FUNC.EVN1.T1.DEFINE
FUNC.EVN1.T2
FUNC.EVN1.T2.INIT
FUNC.EVN1.T3
FUNC.EVN1.T3.CALL
FUNC.EVN1.T3.CALL.PARAM
FUNC.EVN1.T3.CALL.RETURN
FUNC.EVN1.T3.SET
FUNC.EVN1.T3.IF
FUNC.EVN1.T3.CONDITION
FUNC.EVN1.T3.ELSE
FUNC.EVN1.T3.ELSE.SWITCH
FUNC.EVN1.T3.ELSE.SWITCH.CASE
FUNC.EVN1.T3.ELSE.SWITCH.CASE.SET
FUNC.EVN1.T3.ELSE.SWITCH.DEFAULT
FUNC.EVN1.T3.ELSE.SWITCH.DEFAULT.SET
FUNC.EVN1.T4
FUNC.EVN1.T4.RETURN
*/

#ifndef __XML2C_OCCUPIEDDEFINE__
#define __XML2C_OCCUPIEDDEFINE__

#define XC_DEFINE_DEPTH_NAME_LEN		(16)
#define XC_DEFINE_DEPTH_TREE_DEPTH		(16)
#define XC_DEFINE_DEPTH_COUNT			(10240)

#define XC_DEFINE_ITEM_LEN				(32)
#define XC_DEFINE_CONTENT_LEN			(8192)

#define XC_FUNC_PARAM_COUNT				(16)
#define XC_FUNC_ENV_COUNT				(16)
#define XC_FUNC_OBJ_COUNT				(128)


enum XC_CLASS_T {
	XC_ENV = 1,
	XC_OBJ,
	XC_EVN,
	XC_T
};

enum T3_CLASS_T {
	T3_SET = 1,
	T3_CALL,
	T3_IF,
	T3_SWITCH,
	T3_LOOP,
	T3_UNKOWN = 99
};

enum OBJ_TYPE_T {
	OBJ_TYPE_INT = 1,
	OBJ_TYPE_CHAR,
	OBJ_TYPE_LONG,
	OBJ_TYPE_UNKOWN = 99
};

/* P: Param G: global L: local */
enum OBJ_PGL_T {
	OBJ_PGL_P=1,
	OBJ_PGL_G,
	OBJ_PGL_L,
	OBJ_PGL_UNKOWN = 99
};


/*
XC_DEFINE_LEVEL_T  g_xcDefineDepthTree[XC_DEFINE_LEVEL_COUNT] = 
{
	{"FUNC"},
	{"FUNC", "ENV"},
	{"FUNC", "OBJ"},
	{"FUNC", "OBJ", "PARAM"},
	{"FUNC", "OBJ", "LOCAL"},
	{"FUNC", "EVN1", "T1"},
	{"FUNC", "EVN1", "T1", "DEFINE"},
	{"FUNC", "EVN1", "T2"},
	{"FUNC", "EVN1", "T2", "INIT"},
	{"FUNC", "EVN1", "T3"},
	{"FUNC", "EVN1", "T3", "CALL"},
	{"FUNC", "EVN1", "T3", "CALL", "PARAM"},
	{"FUNC", "EVN1", "T3", "CALL", "RETURN"},
	{"FUNC", "EVN1", "T3", "SET"},
	{"FUNC", "EVN1", "T3", "IF"},
	{"FUNC", "EVN1", "T3", "CONDITION"},
	{"FUNC", "EVN1", "T3", "ELSE"},
	{"FUNC", "EVN1", "T3", "ELSE", "SWITCH"},
	{"FUNC", "EVN1", "T3", "ELSE", "SWITCH", "CASE"},
	{"FUNC", "EVN1", "T3", "ELSE", "SWITCH", "CASE", "SET"},
	{"FUNC", "EVN1", "T3", "ELSE", "SWITCH", "DEFAULT"},
	{"FUNC", "EVN1", "T3", "ELSE", "SWITCH", "DEFAULT", "SET"},
	{"FUNC", "EVN1", "T4"},
	{"FUNC", "EVN1", "T4", "RETURN"}
};
*/

/* VALUE define */
typedef struct _VALUE_T {
	char pointer[2];
	char len[8];
	char type[XC_DEFINE_ITEM_LEN];
	char name[XC_DEFINE_ITEM_LEN];
	char text[XC_DEFINE_CONTENT_LEN];
} VALUE_T, *P_VALUE_T;

/* FUNC define */
typedef struct _FUNC_T {
	char name[XC_DEFINE_ITEM_LEN];
	int count;
	P_VALUE_T param[16];
	VALUE_T returnValue;
} FUNC_T, *P_FUNC_T;

/* ENV define */
typedef struct _ENV_T {
	int count;
	char elem[XC_FUNC_ENV_COUNT][XC_DEFINE_ITEM_LEN];
	char text[XC_FUNC_ENV_COUNT][XC_DEFINE_CONTENT_LEN];
} ENV_T, P_ENV_T;

/* OBJ define */
typedef struct _OBJ_T {
	int globalCount;
	int paramCount;
	int localCount;
	P_VALUE_T global[100];
	P_VALUE_T param[16];
	P_VALUE_T local[100];
} OBJ_T, *P_OBJ_T;

/* ENV define */
/* .T1 local global param special */
typedef struct _T1_T {
	int localFlag;
	int globalFlag;
	int paramFlag;
	int specCount;
	P_VALUE_T spec[100];
} T1_T, *P_T1_T;

/* .T2 local global param special */
typedef struct _T2_T {
	int paramCheckFlag;
	int globalCheckFlag;
	int localSetFlag;
	int globalSetFlag;
	int t1SetFlag;
} T2_T, *P_T2_T;

typedef struct _CALL_T {
	char name[XC_DEFINE_ITEM_LEN];
	char param[XC_FUNC_PARAM_COUNT][XC_DEFINE_ITEM_LEN];
	char text[XC_FUNC_PARAM_COUNT][XC_DEFINE_CONTENT_LEN];
	char ret[XC_DEFINE_ITEM_LEN];
} CALL_T, *P_CALL_T;
typedef struct _CONDITION_IF_T {
	char text[XC_DEFINE_ITEM_LEN];
	char equal[4];
} CONDITION_IF_T, *P_CONDITION_IF_T;
typedef struct _IF_T {
	char name[XC_DEFINE_ITEM_LEN];
	CONDITION_IF_T ifCond[8];
} IF_T, *P_IF_T;
typedef struct _SWITCH_CASE_T {
	char text[XC_DEFINE_ITEM_LEN];
} SWITCH_CASE_T, *P_SWITCH_CASE_T;
typedef struct _SWITCH_T {
	char name[XC_DEFINE_ITEM_LEN];
	SWITCH_CASE_T swCase[32];
} SWITCH_T, *P_SWITCH_T;
typedef struct _CONDITION_LOOP_T {
	char text[XC_DEFINE_ITEM_LEN];
	char equal[4];
} CONDITION_LOOP_T, *P_CONDITION_LOOP_T;
typedef struct _LOOP_T {
	char name[XC_DEFINE_ITEM_LEN];
	CONDITION_LOOP_T loopCond;
} LOOP_T, *P_LOOP_T;
typedef struct _SET_T {
	char from[XC_DEFINE_ITEM_LEN];
	char to[XC_DEFINE_ITEM_LEN];
	char name[XC_DEFINE_ITEM_LEN];
	char text[XC_DEFINE_ITEM_LEN];
} SET_T, *P_SET_T;
typedef struct _T3_T {
	P_CALL_T pCall;
	P_IF_T pIf;
	P_SWITCH_T pSwitch;
	P_LOOP_T pLoop;
	P_SET_T pSet;
} T3_T, *P_T3_T;

typedef struct _XC_DEFINE_DEPTH_T {
	char name[XC_DEFINE_DEPTH_TREE_DEPTH][XC_DEFINE_DEPTH_NAME_LEN];
	T3_T t3;
}XC_DEFINE_DEPTH_T, *P_XC_DEFINE_DEPTH_T;

typedef struct _XC_TREE {
	int count;
	P_XC_DEFINE_DEPTH_T dep[XC_DEFINE_DEPTH_COUNT];
}XC_TREE_T, *P_XC_TREE_T;



#endif   /* __XML2C_OCCUPIEDDEFINE__ */
