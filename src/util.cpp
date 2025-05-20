#include "util.h"

std::map<std::string, enum lexical_type> Util::terminalType =
    {
        {"zero", ZERO},
        {"undef", UNDEF},

        {"let", LET},
        {"mut", MUT},
        {"i32", I32},
        {"if", IF},
        {"else", ELSE},
        {"while", WHILE},
        {"return", RETURN},
        {"fn", FN},
        {"for", FOR},
        {"in", IN},
        {"loop", LOOP},
        {"break", BREAK},
        {"continue", CONTINUE},
        {"false", FALSE},
        {"true", TRUE},

        {"assign", ASSIGN},
        {"add", ADD},
        {"sub", SUB},
        {"mul", MUL},
        {"div", DIV},
        {"mod", MOD},
        {"addassign", ADDASSIGN},
        {"subassign", SUBASSIGN},
        {"mulassign", MULASSIGN},
        {"divassign", DIVASSIGN},
        {"modassign", MODASSIGN},
        {"equ", EQU},
        {"gt", GT},
        {"ge", GE},
        {"lt", LT},
        {"le", LE},
        {"ne", NE},

        {"lpra", LPRA},
        {"rpra", RPRA},
        {"lbra", LBRA},
        {"rbra", RBRA},
        {"lsqb", LSQB},
        {"rsqb", RSQB},

        {"semicolon", SEMICOLON},
        {"colon", COLON},
        {"comma", COMMA},

        {"arrow", ARROW},
        {"dot", DOT},
        {"ddot", DDOT},

        {"id", ID},
        {"int", INT},
        
        {"refer", REFER},
        {"and", AND},
        {"or", OR},
        {"not", NOT},
        
        {"end", END} // 结束符
};

std::vector<std::string> Util::terminalStr; // 终结符字符串
