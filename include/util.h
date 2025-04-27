#pragma once
#include <string>
#include <map>

enum lexical_type {
    ZERO,
    UNDEF,

    LET,
    MUT,
    I32,
    IF,
    ELSE,
    WHILE,
    RETURN,
    FN,
    FOR,
    IN,
    LOOP,
    BREAK,
    CONTINUE,

    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    ADDASSIGN,
    SUBASSIGN,
    MULASSIGN,
    DIVASSIGN,
    MODASSIGN,
    EQU,
    GT,
    GE,
    LT,
    LE,
    NE,

    LPRA,
    RPRA,
    LBRA,
    RBRA,
    LSQB,
    RSQB,

    SEMICOLON,  // 分号
    COLON,      // 冒号
    COMMA,      // 逗号

    ARROW,  // ->
    DOT,    // .
    DDOT,   // ..

    ID,
    INT, 

    END
};

class Util
{
   public:
    static std::map<std::string, enum lexical_type> terminalType; // 终结符编号

    static enum lexical_type getTerminalType(const std::string &s) 
    {
        auto it = terminalType.find(s);
        if (it != terminalType.end())
            return it->second;
        return UNDEF;
    }
};

