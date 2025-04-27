#pragma once
#include "util.h"
#include <vector>
#include <set>
#include <deque>

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

struct item
{
    int rule_id; // 产生式id
    int dot_pos; // 点位置(在这个符号的前面)
    int lookahead;  // 一位预测终结符id
    bool operator<(const item& i) const
    {
        if (rule_id != i.rule_id)
            return rule_id < i.rule_id;
        if (dot_pos != i.dot_pos)
            return dot_pos < i.dot_pos;
        return lookahead < i.lookahead;
    }
};

enum action_type
{
    SHIFT,
    REDUCE,
    ACCEPTED
};

struct action
{
    action_type type; // 0:移进 1:规约 2:接受
    int rule_id; // 产生式id
    int next_state; // 下一个状态
};

struct parserTreeNode
{
    symbol current;
    int father;
    std::vector<int> children;
};


class Rules
{
public:
    static std::vector<production> rules; //产生式规则 初始和运行都需要
    static std::map<symbol, std::vector<std::pair<std::vector<symbol>, int>>> leftRules;  // 用于辅助查找的map 初始需要
    static std::map<std::string, int> nonTerminalType;  // 非终结符编号 初始和运行?都需要:可能结果输出要人能看

    static std::map<symbol, std::set<int>> firstSet;  // 所有first集 初始需要

    static std::vector<std::set<item>> itemSet;            // 项目集编号->项目集 初始需要
    static std::map<std::set<item>, int> mapItemSet;       // 项目集->项目集编号 初始需要
    static std::vector<std::map<symbol, int>> dfa;         // 项目集图结构 初始需要

    static std::vector<std::map<symbol, action>> actionTable; // LR(1)分析表 初始运行需要 可以保存读取

    std::vector<parserTreeNode> parserTree;

    static int findAndAdd(const std::string& s);
    static int findNotAdd(const std::string& s);  // 查找非终结符编号 -1表示不存在

    static void init(bool is_read); // 完成到最后表格和图的所有初始化

    static void initRules(bool is_read);  // 读取规则文件
    static void saveRules();              // 打印规则

    static void initFirstSet(bool is_read); // 初始所有符号的first集，可选读取或计算
    static void saveFirstSet();            // 打印first集

    static void build();

    int analysis(const std::vector<symbol> &lexSymbols); // 返回一个整数，代表语法树的根节点编号，如果返回-1说明最后没走到acc
};