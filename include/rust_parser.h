#pragma once
#include "util.h"
#include <vector>
#include <set>

struct symbol
{
    bool is_terminal;
    int type;
    bool operator<(const symbol& s) const
    {
        if (is_terminal != s.is_terminal)
            return is_terminal < s.is_terminal;
        return type < s.type;
    }
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
    // 用于辅助查找的map
    static std::map<symbol, std::vector<std::pair<std::vector<symbol>, int>>> leftRules;
    static std::map<std::string, int> nonTerminalType;  // 非终结符编号

    static std::map<symbol, std::set<int>> firstSet;  // first集

    static int findAndAdd(const std::string& s);
    static int findNotAdd(const std::string& s);
    static void initRules();   // 读取规则文件
    static void printRules(); // 打印规则
    
    static void initFirstSet(bool is_read); // 初始所有符号的first集，可选读取或计算
};