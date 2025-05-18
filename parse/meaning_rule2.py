START -> PROGRAM [ -1 ] #
#
# 1.1 基础程序
PROGRAM -> SHENG_MING_CHUAN [ 0 ] #
SHENG_MING_CHUAN -> /zero [ 1 ] | SHENG_MING SHENG_MING_CHUAN [ 2 ] #
SHENG_MING -> HAN_SHU_SHENG_MING [ 3 ] #
HAN_SHU_SHENG_MING -> HAN_SHU_TOU_SHENG_MING YU_JU_KUAI [ 4 ] #
HAN_SHU_TOU_SHENG_MING -> /fn /id /lpra XING_CAN_LIE_BIAO /rpra [ 5 ] #
XING_CAN_LIE_BIAO -> /zero [ 6 ] #
YU_JU_KUAI -> /lbra YU_JU_CHUAN /rbra [ 7 ] #
YU_JU_CHUAN -> /zero [ 8 ] #
#
# 1.2 语句
YU_JU_CHUAN -> YU_JU YU_JU_CHUAN [ 9 ] #
YU_JU -> /semicolon [ -1 ] #
YU_JU -> YU_JU_KUAI [ 10 ] #
#
# 1.3 返回语句
YU_JU -> FAN_HUI_YU_JU [ 11 ] #
FAN_HUI_YU_JU -> /return /semicolon [ 12 ] #
#
# 0.1 变量声明内部
BIAN_LIANG_SHENG_MING_NEI_BU -> /mut /id [ 13 ] #
#
# 0.2 类型
LEI_XING -> /i32 [ 14 ] #
#
# 0.3 可赋值元素
#
# 1.4 函数输入
XING_CAN_LIE_BIAO -> XING_CAN [ 15 ] | XING_CAN /comma XING_CAN_LIE_BIAO [ 16 ] #
XING_CAN -> BIAN_LIANG_SHENG_MING_NEI_BU /colon LEI_XING [ 17 ] #
#
# 1.5 函数输出
HAN_SHU_TOU_SHENG_MING -> /fn /id /lpra XING_CAN_LIE_BIAO /rpra /arrow LEI_XING [ 18 ] #
FAN_HUI_YU_JU -> /return BIAO_DA_SHI /semicolon [ 19 ] #
#
# 2.1 变量声明语句
YU_JU -> BIAN_LIANG_SHENG_MING_YU_JU [ 20 ] #
BIAN_LIANG_SHENG_MING_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /colon LEI_XING /semicolon [ 21 ] #
BIAN_LIANG_SHENG_MING_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /semicolon [ 22 ] #
#
# 2.2 赋值语句
YU_JU -> FU_ZHI_YU_JU [ 23 ] #
FU_ZHI_YU_JU -> BIAO_DA_SHI FU_ZHI_YUN_SUAN_FU BIAO_DA_SHI /semicolon [ 24 ] #
FU_ZHI_YUN_SUAN_FU -> /assign [ 25 ] | /addassign [ 26 ] | /subassign [ 27 ] | /mulassign [ 28 ] | /divassign [ 29 ] | /modassign [ 30 ] #
#
# 2.3 变量声明赋值语句
YU_JU -> BIAN_LIANG_SHENG_MING_FU_ZHI_YU_JU [ 31 ] #
BIAN_LIANG_SHENG_MING_FU_ZHI_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /colon LEI_XING /assign BIAO_DA_SHI /semicolon [ 32 ] #
BIAN_LIANG_SHENG_MING_FU_ZHI_YU_JU -> /let BIAN_LIANG_SHENG_MING_NEI_BU /assign BIAO_DA_SHI /semicolon [ 33 ] #
#
# 3.1 基本表达式
YU_JU -> BIAO_DA_SHI /semicolon [ 34 ] #
BIAO_DA_SHI -> OR_BIAO_DA_SHI [ 35 ] #
OR_BIAO_DA_SHI -> AND_BIAO_DA_SHI [ 36 ] #
AND_BIAO_DA_SHI -> JIA_FA_BIAO_DA_SHI [ 37 ] #
JIA_FA_BIAO_DA_SHI -> XIANG [ 38 ] #
XIANG -> YIN_ZI [ 39 ] #
YIN_ZI -> YUAN_SU [ 40 ] #
YUAN_SU -> /int [ 41 ] | /id [ 42 ] | /lpra BIAO_DA_SHI /rpra [ 43 ] #
#
# 3.2 表达式计算与比较
BIAO_DA_SHI -> BIAO_DA_SHI /or OR_BIAO_DA_SHI [ 44 ] #
OR_BIAO_DA_SHI -> OR_BIAO_DA_SHI /and AND_BIAO_DA_SHI [ 45 ] #
AND_BIAO_DA_SHI -> AND_BIAO_DA_SHI BI_JIAO_YUN_SUAN_FU JIA_FA_BIAO_DA_SHI [ 46 ] #
JIA_FA_BIAO_DA_SHI -> JIA_FA_BIAO_DA_SHI JIA_JIAN_YUN_SUAN_FU XIANG [ 47 ] #
XIANG -> XIANG CHENG_CHU_YUN_SUAN_FU YIN_ZI [ 48 ] #
BI_JIAO_YUN_SUAN_FU -> /lt [ 49 ] | /le [ 50 ] | /gt [ 51 ] | /ge [ 52 ] | /equ [ 53 ] | /ne [ 54 ] #
JIA_JIAN_YUN_SUAN_FU -> /add [ 55 ] | /sub [ 56 ] #
CHENG_CHU_YUN_SUAN_FU -> /mul [ 57 ] | /div [ 58 ] | /mod [ 59 ] #
#
YIN_ZI -> /sub YIN_ZI [ 60 ] | /not YIN_ZI [ 61 ] #
#
# 3.3 函数调用
YUAN_SU -> /id /lpra SHI_CAN_LIE_BIAO /rpra [ 62 ] #
SHI_CAN_LIE_BIAO -> /zero [ 63 ] | BIAO_DA_SHI [ 64 ] | BIAO_DA_SHI /comma SHI_CAN_LIE_BIAO [ 65 ] #
#
# 4.1 选择结构
YU_JU -> IF_YU_JU [ -1 ] #
IF_YU_JU -> /if BIAO_DA_SHI YU_JU_KUAI ELSE_BU_FEN [ -1 ] #
# ELSE_BU_FEN -> /zero | /else YU_JU_KUAI #
#
# 4.2 增加 else if
ELSE_BU_FEN -> /else /if BIAO_DA_SHI YU_JU_KUAI ELSE_BU_FEN [ -1 ] | /else YU_JU_KUAI [ -1 ] | /zero [ -1 ] #
#
# 5.1 while循环结构
YU_JU -> XUN_HUAN_YU_JU [ -1 ] #
XUN_HUAN_YU_JU -> WHILE_YU_JU [ -1 ] #
WHILE_YU_JU -> /while BIAO_DA_SHI YU_JU_KUAI [ -1 ] #
#
# 5.2 for循环结构
XUN_HUAN_YU_JU -> FOR_YU_JU [ -1 ] #
FOR_YU_JU -> FOR_YU_JU_SHENG_MING YU_JU_KUAI [ -1 ] #
FOR_YU_JU_SHENG_MING -> /for BIAN_LIANG_SHENG_MING_NEI_BU /in KE_DIE_DAI_JIE_GOU [ -1 ] #
KE_DIE_DAI_JIE_GOU -> BIAO_DA_SHI /ddot BIAO_DA_SHI [ -1 ] #
#
# 5.3 loop循环结构
XUN_HUAN_YU_JU -> LOOP_YU_JU [ -1 ] #
LOOP_YU_JU -> /loop YU_JU_KUAI [ -1 ] #
#
# 5.4 break和continue语句
YU_JU -> /break /semicolon [ -1 ] | /continue /semicolon [ -1 ] #
#
# 6.1 声明不可变变量
BIAN_LIANG_SHENG_MING_NEI_BU -> /id [ -1 ] #
#
# 6.2 借用和引用
YIN_ZI -> /mul YIN_ZI [ 83 ] | /refer /mut YIN_ZI [ 84 ] | /refer YIN_ZI [ 85 ] #
LEI_XING -> /refer /mut LEI_XING [ 86 ] | /refer LEI_XING [ 87 ] #
#
# 7.1 函数表达式块
BIAO_DA_SHI -> HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI [ -1 ] #
HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI -> /lbra HAN_SHU_BIAO_DA_SHI_YU_JU_CHUAN /rbra [ -1 ] #
HAN_SHU_BIAO_DA_SHI_YU_JU_CHUAN -> BIAO_DA_SHI [ -1 ] | YU_JU HAN_SHU_BIAO_DA_SHI_YU_JU_CHUAN [ -1 ] #
#
# 7.2 函数表达式块作为函数体
HAN_SHU_SHENG_MING -> HAN_SHU_TOU_SHENG_MING HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI [ -1 ] #
#
# 7.3 选择表达式
BIAO_DA_SHI -> XUAN_ZE_BIAO_DA_SHI [ -1 ] #
XUAN_ZE_BIAO_DA_SHI -> /if BIAO_DA_SHI HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI /else HAN_SHU_BIAO_DA_SHI_YU_JU_KUAI [ -1 ] #
#
# 7.4 循环表达式
# BIAO_DA_SHI -> XUN_HUAN_BIAO_DA_SHI #
# XUN_HUAN_BIAO_DA_SHI ->  /loop XUN_HUAN_BIAO_DA_SHI_YU_JU_KUAI #
# XUN_HUAN_BIAO_DA_SHI_YU_JU_KUAI -> /lbra XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN /rbra #
# XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN -> YU_JU XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN | XUN_HUAN_FAN_HUI_YU_JU YU_JU_CHUAN #
# XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN -> XUN_HUAN_FAN_HUI_YU_JU XUN_HUAN_BIAO_DA_SHI_YU_JU_CHUAN #
# XUN_HUAN_FAN_HUI_YU_JU -> /break BIAO_DA_SHI /semicolon #
#
BIAO_DA_SHI -> LOOP_YU_JU [ -1 ] #
YU_JU -> /break BIAO_DA_SHI /semicolon [ -1 ] #
#
# 8.1 数组
LEI_XING -> /lsqb LEI_XING /semicolon /int /rsqb [ -1 ] #
YUAN_SU -> /lsqb SHU_ZU_YUAN_SU_LIE_BIAO /rsqb [ -1 ] #
SHU_ZU_YUAN_SU_LIE_BIAO -> /zero [ -1 ] | BIAO_DA_SHI [ -1 ] | BIAO_DA_SHI /comma SHU_ZU_YUAN_SU_LIE_BIAO [ -1 ] #

# 8.2 数组元素
YUAN_SU -> YUAN_SU /lsqb BIAO_DA_SHI /rsqb [ -1 ] #
KE_DIE_DAI_JIE_GOU -> BIAO_DA_SHI [ -1 ] #

# 9.1 元组
LEI_XING -> /lpra YUAN_ZU_LEI_XING_NEI_BU /rpra [ -1 ] #
YUAN_ZU_LEI_XING_NEI_BU -> /zero [ -1 ] | LEI_XING /comma LEI_XING_LIE_BIAO [ -1 ] #
LEI_XING_LIE_BIAO -> /zero [ -1 ] | LEI_XING [ -1 ] | LEI_XING /comma LEI_XING_LIE_BIAO [ -1 ] #
YUAN_SU -> /lpra YUAN_ZU_FU_ZHI_NEI_BU /rpra [ -1 ] #
YUAN_ZU_FU_ZHI_NEI_BU -> /zero [ -1 ] | BIAO_DA_SHI /comma YUAN_ZU_YUAN_SU_LIE_BIAO [ -1 ] #
YUAN_ZU_YUAN_SU_LIE_BIAO -> /zero [ -1 ] | BIAO_DA_SHI [ -1 ] | BIAO_DA_SHI /comma YUAN_ZU_YUAN_SU_LIE_BIAO [ -1 ] #

# 9.2 元组元素
YUAN_SU -> YUAN_SU /dot /int [ -1 ] #
