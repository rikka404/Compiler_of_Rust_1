#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

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
    BOOL,

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

    OUTPUT, // 输出
    INPUT,

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


class argParser
{
public:
    std::map<std::string, std::string> args; // 存储参数键值对
    void parse(int argc, char *argv[])
    {
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg[0] == '-')
            {
                if (arg.substr(1) == "h" || arg.substr(1) == "help")
                {
                    this->help();
                    exit(0);
                }
                
                if (i + 1 < argc && argv[i + 1][0] != '-')
                {
                    args[arg.substr(1)] = argv[++i];
                }
                else
                {
                    args[arg.substr(1)] = "";
                }
            }
        }
    }
    
    void help()
    {
        std::cout << "Usage: program [options]\n";
        std::cout << "Options:\n";
        std::cout << "  -h           Show this help message\n";
        std::cout << "  -m  <mode>   *must* Specify mode (e.g. itp: interpreter, x86: win_x86)\n";
        std::cout << "  -i  <file>   *must* Specify input file\n";
        std::cout << "  -o  <file>   Specify output file\n";
    }
    
};