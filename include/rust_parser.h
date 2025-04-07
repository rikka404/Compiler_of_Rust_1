#pragma once
#include "util.h"
#include <vector>

struct symbol
{
    bool is_terminal;
    int type;
};

struct production
{
    symbol left; //左部符号
    std::vector<symbol> right; //右部符号
};

class Rules
{
public:
    static std::vector<production> rules; //产生式规则
    static std::map<std::string, int> nonTerminalType; //非终结符
    static int nonTerminalCount; // 非终结符数量

    static int findAndAdd(const std::string& s);
    static int findNotAdd(const std::string& s);
    static void init();
};