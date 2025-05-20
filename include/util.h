#pragma once
#include <string>
#include <vector>
#include <map>

enum lexical_type
{
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
    FALSE,
    TRUE,

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

    SEMICOLON, // 分号
    COLON,     // 冒号
    COMMA,     // 逗号

    ARROW, // ->
    DOT,   // .
    DDOT,  // ..

    ID,
    INT,
    
    REFER, // &
    AND, // &&
    OR,  // ||
    NOT, // !

    END // 结束符
};

class Util
{
public:
    static std::map<std::string, enum lexical_type> terminalType; // 终结符编号
    static std::vector<std::string> terminalStr;                  // 终结符字符串

    static enum lexical_type getTerminalType(const std::string &s)
    {
        auto it = Util::terminalType.find(s);
        if (it != Util::terminalType.end())
            return it->second;
        return UNDEF;
    }

    static void initTerminalStr()
    {
        if (!Util::terminalStr.empty())
            return;
        Util::terminalStr.resize(Util::terminalType.size());
        for (auto [s, tp] : Util::terminalType)
        {
            Util::terminalStr[tp] = s;
        }
    }
};
