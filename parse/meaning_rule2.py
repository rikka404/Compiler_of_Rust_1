# 语义规则：含有set的参数表示设置到的值，含有get的参数表示获取的位置
# 值：0 int 1 bool 2 mut& 3 & 4 数组 5 元组  0 变量 1 常量 2 字面量
START -> PROGRAM #
#
# 1.1 基础程序
PROGRAM -> SHENG_MING_CHUAN #
SHENG_MING_CHUAN -> /zero | SHENG_MING SHENG_MING_CHUAN #
SHENG_MING -> HAN_SHU_SHENG_MING #
HAN_SHU_SHENG_MING -> HAN_SHU_TOU_SHENG_MING YU_JU_KUAI #
HAN_SHU_TOU_SHENG_MING -> /fn /id /lpra XING_CAN_LIE_BIAO /rpra #
XING_CAN_LIE_BIAO -> /zero #
YU_JU_KUAI -> /lbra YU_JU_CHUAN /rbra [ 1 statePop 1 ] #
YU_JU_CHUAN -> /zero [ 1 stateSet 0 ] #
#
# 1.2 语句
YU_JU_CHUAN -> YU_JU YU_JU_CHUAN [ 1 stateSum 0 1 ] #
YU_JU -> /semicolon [ 1 stateSet 0 ] #
#
# 1.3 返回语句
YU_JU -> FAN_HUI_YU_JU [ 1 stateSet 0 ] #
FAN_HUI_YU_JU -> /return /semicolon  #
#
# 0.1 变量声明内部
BIAN_LIANG_SHENG_MING_NEI_BU -> /mut /id [ 2 nameGet 1 readTypeSet 0 ] #
#
# 0.2 类型
LEI_XING -> /i32 [ 1 numTypeSet 0 ] #
#
# 0.3 可赋值元素
#
# 1.4 函数输入
XING_CAN_LIE_BIAO -> XING_CAN | XING_CAN /comma XING_CAN_LIE_BIAO #
XING_CAN -> BIAN_LIANG_SHENG_MING_NEI_BU /colon LEI_XING [ 1 numTypeDel 2 ] #
#
# 1.5 函数输出
HAN_SHU_TOU_SHENG_MING -> /fn /id /lpra XING_CAN_LIE_BIAO /rpra /arrow LEI_XING [ 1 numTypeDel 2 ] #
FAN_HUI_YU_JU -> /return BIAO_DA_SHI /semicolon [ 1 numTypeDel 1 ] #
#
# 2.1 变量声明语句
YU_JU -> BIAN_LIANG_SHENG_MING_YU_JU [ 1 statePush 0 ] #
BIAN_LIANG_SHENG_MING_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /colon LEI_XING /semicolon [ 3 nameGet 1 readTypeGet 1 numTypeGet 3 ] #
BIAN_LIANG_SHENG_MING_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /semicolon [ 2 nameGet 1 readTypeGet 1 ] #
#
# 2.2 赋值语句
YU_JU -> FU_ZHI_YU_JU [ 1 stateSet 0 ] #
FU_ZHI_YU_JU -> BIAO_DA_SHI FU_ZHI_YUN_SUAN_FU BIAO_DA_SHI /semicolon [ 2 assign 0 2 numTypeDel 0 numTypeDel 2 ] #
FU_ZHI_YUN_SUAN_FU -> /assign  | /addassign  | /subassign  | /mulassign  | /divassign  | /modassign #
#
# 2.3 变量声明赋值语句
YU_JU -> BIAN_LIANG_SHENG_MING_FU_ZHI_YU_JU [ 1 statePush 0 ] #
BIAN_LIANG_SHENG_MING_FU_ZHI_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /colon LEI_XING /assign BIAO_DA_SHI /semicolon
[ 5 numTypeEqu 3 5 nameGet 1 readTypeGet 1 numTypeGet 3 numTypeDel 5 ] #
BIAN_LIANG_SHENG_MING_FU_ZHI_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /assign BIAO_DA_SHI /semicolon
[ 4 nameGet 1 readTypeGet 1 numTypeGet 3 ] #
#
# 3.1 基本表达式
YU_JU -> BIAO_DA_SHI /semicolon [ 2 stateSet 0 numTypeDel 0 ] #
BIAO_DA_SHI -> JIA_FA_BIAO_DA_SHI [ 3 readTypeGet 0 numTypeGet 0 nameTryGet 0 ] #
JIA_FA_BIAO_DA_SHI -> XIANG [ 3 readTypeGet 0 numTypeGet 0 nameTryGet 0 ] #
XIANG -> YIN_ZI [ 3 readTypeGet 0 numTypeGet 0 nameTryGet 0 ] #
YIN_ZI -> YUAN_SU [ 3 readTypeGet 0 numTypeGet 0 nameTryGet 0 ] #
YUAN_SU -> /int [ 2 readTypeSet 2 numTypeGet 0 ] | /id [ 1 nameFindGet 0 ] | /lpra BIAO_DA_SHI /rpra [ 3 readTypeGet 0 numTypeGet 0 nameTryGet 0 ] #
#
# 3.2 表达式计算与比较
BIAO_DA_SHI -> BIAO_DA_SHI BI_JIAO_YUN_SUAN_FU JIA_FA_BIAO_DA_SHI [ 3 numTypeCal 0 2 readTypeSet 2 numTypeSet 1 ] #
JIA_FA_BIAO_DA_SHI -> JIA_FA_BIAO_DA_SHI JIA_JIAN_YUN_SUAN_FU XIANG [ 3 numTypeCal 0 2 readTypeSet 2 numTypeSet 1 ] #
XIANG -> XIANG CHENG_CHU_YUN_SUAN_FU YIN_ZI [ 3 numTypeCal 0 2 readTypeSet 2 numTypeSet 1 ] #
BI_JIAO_YUN_SUAN_FU -> /lt | /le | /gt | /ge | /equ | /ne #
JIA_JIAN_YUN_SUAN_FU -> /add | /sub #
CHENG_CHU_YUN_SUAN_FU -> /mul | /div | /mod #
#
# 3.3 函数调用
YUAN_SU -> /id /lpra SHI_CAN_LIE_BIAO /rpra #
SHI_CAN_LIE_BIAO -> /zero | BIAO_DA_SHI [ 1 numTypeDel 0 ] | BIAO_DA_SHI /comma SHI_CAN_LIE_BIAO [ 1 numTypeDel 0 ] #
#
# 4.1 选择结构
YU_JU -> IF_YU_JU [ 1 stateSet 0 ] #
IF_YU_JU -> /if BIAO_DA_SHI YU_JU_KUAI ELSE_BU_FEN [ 2 numTypeCheck 1 1 numTypeDel 1 ] #
# ELSE_BU_FEN -> /zero | /else YU_JU_KUAI #
#
# 4.2 增加 else if
ELSE_BU_FEN -> /else /if BIAO_DA_SHI YU_JU_KUAI ELSE_BU_FEN [ 2 numTypeCheck 2 1 numTypeDel 2 ] | /else YU_JU_KUAI | /zero #
#
# 5.1 while循环结构
YU_JU -> XUN_HUAN_YU_JU [ 1 stateSet 0 ] #
XUN_HUAN_YU_JU -> WHILE_YU_JU #
WHILE_YU_JU -> /while BIAO_DA_SHI YU_JU_KUAI [ 2 numTypeCheck 1 1 numTypeDel 1 ] #
#
# 5.2 for循环结构
XUN_HUAN_YU_JU -> FOR_YU_JU #
FOR_YU_JU -> FOR_YU_JU_SHENG_MING YU_JU_KUAI [ 1 statePop 0 ] #
FOR_YU_JU_SHENG_MING -> /for BIAN_LIANG_SHENG_MING_NEI_BU /in KE_DIE_DAI_JIE_GOU [ 1 iteration 1 ] #
KE_DIE_DAI_JIE_GOU -> BIAO_DA_SHI /ddot BIAO_DA_SHI [ 5 numTypeCheck 0 0 numTypeCheck 2 0 numTypeSet 4 numTypeSon 0 numTypeDel 2 ] #
#
# 5.3 loop循环结构
XUN_HUAN_YU_JU -> LOOP_YU_JU #
LOOP_YU_JU -> /loop YU_JU_KUAI #
#
# 5.4 break和continue语句
YU_JU -> /break /semicolon [ 1 stateSet 0 ] | /continue /semicolon [ 1 stateSet 0 ] #
#
# 6.1 声明不可变变量
BIAN_LIANG_SHENG_MING_NEI_BU -> /id [ 2 nameGet 0 readTypeSet 1 ] #
#
# 6.2 借用和引用
YIN_ZI -> /mul YIN_ZI [ 1 dereference 1 ] | /and /mut YIN_ZI [ 1 mutReference 2 ] | /and YIN_ZI [ 1 reference 1 ] #
LEI_XING -> /and /mut LEI_XING [ 2 numTypeSet 2 numTypeSon 2 ] | /and LEI_XING [ 2 numTypeSet 3 numTypeSon 1 ] #
#
# 7.1 函数表达式块
BIAO_DA_SHI -> HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI [ 2 readTypeGet 0 numTypeGet 0 ] #
HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI -> /lbra HAN_SHU_BIAO_DA_SHI_YU_JU_CHUAN /rbra [ 3 readTypeGet 1 numTypeGet 1 statePop 1 ] #
HAN_SHU_BIAO_DA_SHI_YU_JU_CHUAN -> BIAO_DA_SHI [ 3 stateSet 0 readTypeGet 0 numTypeGet 0 ] | YU_JU HAN_SHU_BIAO_DA_SHI_YU_JU_CHUAN [ 3 stateSum 0 1 readTypeGet 1 numTypeGet 1 ] #
#
# 7.2 函数表达式块作为函数体
HAN_SHU_SHENG_MING -> HAN_SHU_TOU_SHENG_MING HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI [ 1 numTypeDel 1 ] #
#
# 7.3 选择表达式
BIAO_DA_SHI -> XUAN_ZE_BIAO_DA_SHI [ 2 readTypeGet 0 numTypeGet 0 ] #
XUAN_ZE_BIAO_DA_SHI -> /if BIAO_DA_SHI HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI /else HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI
[ 2 numTypeCheck 1 1 numTypeDel 1 numTypeEqu 2 4 readTypeSet !!!todo!!! ] #
#
# 7.4 循环表达式
# BIAO_DA_SHI -> XUN_HUAN_BIAO_DA_SHI #
# XUN_HUAN_BIAO_DA_SHI ->  /loop XUN_HUAN_BIAO_DA_SHI_YU_JU_KUAI #
# XUN_HUAN_BIAO_DA_SHI_YU_JU_KUAI -> /lbra XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN /rbra #
# XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN -> YU_JU XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN | XUN_HUAN_FAN_HUI_YU_JU YU_JU_CHUAN #
# XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN -> XUN_HUAN_FAN_HUI_YU_JU XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN #
# XUN_HUAN_FAN_HUI_YU_JU -> /break BIAO_DA_SHI /semicolon #
#
BIAO_DA_SHI -> LOOP_YU_JU #
YU_JU -> /break BIAO_DA_SHI /semicolon [ 1 stateSet 0 ] #
#
# 8.1 数组
LEI_XING -> /lsqb LEI_XING /semicolon /int /rsqb [ 3 numTypeSet 4 arrayNumGet 3 numTypeSon 1 ] #
YUAN_SU -> /lsqb SHU_ZU_YUAN_SU_LIE_BIAO /rsqb [ 3 numTypeGet 1 arrayNumGet 1 readTypeSet 2 ] #
SHU_ZU_YUAN_SU_LIE_BIAO -> /zero [ 2 numTypeSet 4 arrayNumSet 0 ] | BIAO_DA_SHI [ 3 numTypeSet 4 arrayNumSet 1 numTypeSon 0 ]
| BIAO_DA_SHI /comma SHU_ZU_YUAN_SU_LIE_BIAO [ 1 numTypeArraySon 2 0 ] #

# 8.2 数组元素
YUAN_SU -> YUAN_SU /lsqb BIAO_DA_SHI /rsqb [ 2 numTypeCheck 2 0 arrayIndex 0 ] #
KE_DIE_DAI_JIE_GOU -> BIAO_DA_SHI [ 2 readTypeGet 0 numTypeGet 0 ] #

# 9.1 元组
LEI_XING -> /lpra YUAN_ZU_LEI_XING_NEI_BU /rpra [ 1 numTypeGet 1 ] #
YUAN_ZU_LEI_XING_NEI_BU -> /zero [  1 numTypeSet 5 ] | LEI_XING /comma LEI_XING_LIE_BIAO [ 2 numTypeGet 2 numTypeSon 0 ] #
LEI_XING_LIE_BIAO -> /zero [ 1 numTypeSet 5 ] | LEI_XING [ 2 numTypeSet 5 numTypeSon 0 ] | LEI_XING /comma LEI_XING_LIE_BIAO [ 2 numTypeGet 2 numTypeSon 0 ] #
YUAN_SU -> /lpra YUAN_ZU_FU_ZHI_NEI_BU /rpra [ 2 numTypeGet 1 readTypeSet 2 ] #
YUAN_ZU_FU_ZHI_NEI_BU -> /zero [ 1 numTypeSet 5 ] | BIAO_DA_SHI /comma YUAN_ZU_YUAN_SU_LIE_BIAO [ 2 numTypeGet 2 numTypeSon 0 ] #
YUAN_ZU_YUAN_SU_LIE_BIAO -> /zero [ 1 numTypeSet 5 ] | BIAO_DA_SHI [ 2 numTypeSet 5 numTypeSon 0 ] | BIAO_DA_SHI /comma YUAN_ZU_YUAN_SU_LIE_BIAO [ 2 numTypeGet 2 numTypeSon 0 ] #

# 9.2 元组元素
YUAN_SU -> YUAN_SU /dot /int [ 1 tupleIndex 0 ] #
