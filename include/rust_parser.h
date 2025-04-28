#pragma once
#include "util.h"
#include <set>
#include <queue>

struct symbol
{
    bool is_terminal;
    int type;
    symbol(){}
    symbol(bool s1, int s2)
    {
        is_terminal = s1, type = s2;
    }
    bool operator<(const symbol &s) const
    {
        if (is_terminal != s.is_terminal)
            return is_terminal < s.is_terminal;
        return type < s.type;
    }
};

struct production
{
    symbol left;               // 左部符号
    std::vector<symbol> right; // 右部符号
};

struct item
{
    int rule_id;   // 产生式id
    int dot_pos;   // 点位置(在这个符号的前面)
    int lookahead; // 一位预测终结符id
    item(int rid, int dp, int la) : rule_id(rid), dot_pos(dp), lookahead(la) {}
    item() : rule_id(-1), dot_pos(-1), lookahead(-1) {}
    bool operator<(const item &i) const
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
private:
    static std::vector<production> rules;                                                // 产生式规则 初始和运行都需要
    static std::map<symbol, std::vector<int>> leftRules;                                 // 用于辅助查找的map 初始需要
    static std::map<std::string, int> nonTerminalType;                                   // 非终结符编号 初始和运行?都需要:可能结果输出要人能看
    static std::vector<std::string> nonTerminalStr;                                      // 非终结符编号到字符串的映射 初始和运行都需要

    static std::map<symbol, std::set<int>> firstSet; // 所有first集 初始需要

    static std::vector<std::set<item>> itemSet;      // 项目集编号->项目集 初始需要
    static std::map<std::set<item>, int> mapItemSet; // 项目集->项目集编号 初始需要
    static std::vector<std::map<symbol, int>> dfa;   // 项目集图结构 初始需要

    static std::vector<std::map<symbol, action>> actionTable; // LR(1)分析表 初始运行需要 可以保存读取

    int root = -1;
    std::vector<parserTreeNode> parserTree;

    static int findAndAdd(const std::string& s);
    static int findNotAdd(const std::string& s);  // 查找非终结符编号 -1表示不存在

    static void initRules(bool is_read); // 读取规则文件
    static void printRules();            // 打印规则

    static void initNonTerminalStr(); // 初始化非终结符编号到字符串的映射

    static void initFirstSet();                                                                  // 初始所有符号的first集
    static void printFirstSet();                                                                 // 打印first集
    static void calFirstSet(const std::vector<symbol> &sententialForm, std::set<int> &sententFirst); // 计算一个给定句型的first集

    static void deleteZero(); // 删除产生式右部的/zero符号
    static std::pair<bool, int> closeure(std::set<item> &itemSet); // 计算闭包集 返回是否是新/项目集编号,同时其负责3个数据结构
    static void initDFA();                                         // 初始化项目集图结构
    static void printDFA();                                        // 打印项目集图结构

    static void calActionTable();   // 计算LR(1)分析表
    static void saveActionTable();  // 保存LR(1)分析表
    static void loadActionTable();  // 读取LR(1)分析表
    static void printActionTable(); // 打印LR(1)分析表

public:
    static void init(bool is_read, bool tmp_print); // 完成到最后分析表的所有初始化
    void drawParserTree(std::ostream&);
    int analysis(const std::vector<symbol> &lexSymbols); // 返回一个整数，代表语法树的根节点编号，如果返回-1说明最后没走到acc
};