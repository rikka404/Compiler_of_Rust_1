#include "rust_parser.h"
#include <fstream>
#include <iostream>
#include <assert.h>

std::vector<production> Rules::rules;  // 产生式规则 初始和运行都需要
std::map<symbol, std::vector<std::pair<std::vector<symbol>, int>>> Rules::leftRules;  // 用于辅助查找的map 初始需要
std::map<std::string, int> Rules::nonTerminalType;                                    // 非终结符编号 初始和运行都需要

std::map<symbol, std::set<int>> Rules::firstSet;  // 所有first集 初始需要

std::vector<std::set<item>> Rules::itemSet;       // 项目集编号->项目集 初始需要
std::map<std::set<item>, int> Rules::mapItemSet;  // 项目集->项目集编号 初始需要
std::vector<std::map<symbol, int>> Rules::dfa;  // 项目集图结构 初始需要

std::vector<std::map<symbol, action>> Rules::actionTable;  // LR(1)分析表 初始运行需要 可以保存读取

int Rules::findAndAdd(const std::string& s)
{
    auto it = Rules::nonTerminalType.find(s);
    if (it == Rules::nonTerminalType.end())
    {
        Rules::nonTerminalType[s] = Rules::nonTerminalType.size();
        return Rules::nonTerminalType.size() - 1;
    }
    else
    {
        return it->second;
    }
}

int Rules::findNotAdd(const std::string& s)
{
    auto it = Rules::nonTerminalType.find(s);
    if (it == Rules::nonTerminalType.end())
    {
        return -1;
    }
    else
    {
        return it->second;
    }
}

void Rules::init(bool is_read)
{
    Rules::initRules(is_read);
    Rules::initFirstSet(is_read);
    
}

void Rules::initRules(bool is_read) {
    const std::string filename = "parse/parse_rule.rule";
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " is not exist" << std::endl;
        exit(0);
    }
    
    std::string left, right;
    int linecnt = 0;
    while (fin >> left)
    {
        ++linecnt;
        if (left.empty() || left[0] == '#')
        {
            std::getline(fin, left); // 读到行尾
            continue;
        }
        
        // 检查加入非终结符
        production p;
        p.left.is_terminal = false;
        p.left.type = Rules::findAndAdd(left);
        
        
        bool is_line_end = false;
        fin >> right; // ->
        // 检查所有右边
        while (!is_line_end)
        {
            production p_copy = p;
            // 检查单个产生式
            while (1)
            {
                fin >> right;
                // 检查结束
                if (right == "|")
                {
                    if (!p_copy.right.empty())
                    {  
                        // 对leftRules和rules进行添加
                        if (!is_read)
                            Rules::leftRules[p_copy.left].push_back({p_copy.right, Rules::rules.size()});
                        Rules::rules.push_back(p_copy);
                    }
                    break;
                }
                else if (right[0] == '#')
                {
                    is_line_end = true;
                    std::getline(fin, left);  // 读到行尾
                    if (!p_copy.right.empty())
                    {
                        // 对leftRules和rules进行添加
                        if (!is_read)
                            Rules::leftRules[p_copy.left].push_back({p_copy.right, Rules::rules.size()});
                        Rules::rules.push_back(p_copy);
                    }
                            
                    break;
                }
                
                // 检查名称
                symbol s;
                if (right[0] == '/')
                {
                    s.is_terminal = true;
                    s.type = Util::getTerminalType(right.substr(1));
                    if (s.type == UNDEF)
                    {
                        std::cout << "[ERROR] [RULES] at line " << linecnt << ", no terminal name " << right.substr(1) << std::endl;
                        exit(0);
                    }
                }
                else 
                {
                    if (!(islower(right[0]) || isupper(right[0])))
                    {
                        std::cout << "[ERROR] [RULES] at line " << linecnt << ", non-terminal can not name as " << right << std::endl;
                        exit(0);
                    }
                    s.is_terminal = false;
                    s.type = Rules::findAndAdd(right);
                }
                
                p_copy.right.push_back(s);
                
            }
        }
    }
    fin.close();
    std::cout << "[LOG] [RULES] Complete read parse_rule.rule, count " << Rules::rules.size() << std::endl;
}

void Rules::saveRules()
{
    const std::string filename = "parse/rules.tmp";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }
    // 输出确认
    for (auto& rule : Rules::rules) {
        fout << rule.left.type << " -> ";
        for (auto& s : rule.right) {
            if (s.is_terminal)
                fout << "/" << s.type << " ";
            else
                fout << s.type << " ";
        }
        fout << std::endl;
    }
}

void Rules::initFirstSet(bool is_read)
{
    const std::string filename = "parse/first.set";
    if (is_read)
    {
        // std::ifstream fin(filename);
        // if (!fin.is_open()) {
        //     std::cout << "[ERROR] [RULES] " << filename << " is not exist" << std::endl;
        //     exit(0);
        // }
        // // 读取first集
        // int symbol_cnt;
        // fin >> symbol_cnt;
        // symbol left;
        // left.is_terminal = false;
        // for (int i = 0; i < symbol_cnt; ++i) {
        //     int set_cnt;
        //     fin >> left.type >> set_cnt;

        //     Rules::firstSet[left] = std::set<int>();
            
        //     int firstSymbolType;
        //     for (int j = 0; j < set_cnt; ++j) {
        //         fin >> firstSymbolType;
        //         Rules::firstSet[left].insert(firstSymbolType);
        //     }
        // }
        // fin.close();
        // std::cout << "[LOG] [RULES] Complete read first set at " << filename << std::endl;
    }
    else
    {
        symbol s;
        // 初始化非终结符set为空
        for (int i = 0; i < (int)Rules::nonTerminalType.size(); ++i) {
            s.is_terminal = false;
            s.type = i;
            Rules::firstSet[s] = std::set<int>();
        }
        // 初始化终结符set为自身
        for (int i = 0; i < (int)Util::terminalType.size(); ++i) {
            s.is_terminal = true;
            s.type = i;
            Rules::firstSet[s] = std::set<int>();
            Rules::firstSet[s].insert(i);
        }

        // 计算first集合
        int old_size = -1;
        int new_size = 0;
        while (old_size != new_size) {
            old_size = new_size;
            for (production& rule : Rules::rules) {
                symbol left = rule.left;
                std::vector<symbol> right = rule.right;

                for (int i = 0; i < (int)right.size(); ++i) {
                    symbol s = right[i];
                    if (s.is_terminal) {
                        // 如果是终结符，加入first集 退出
                        Rules::firstSet[left].insert(s.type);
                        break;
                    }
                    else {
                        // 如果是非终结符，加入first集
                        bool exists_zero = false;
                        for (int first : Rules::firstSet[s]) {
                            if (first == ZERO) {
                                // 如果含有空串，可以继续下一个非终结符
                                exists_zero = true;
                                if (i == (int)right.size() - 1) {
                                    // 如果是最后一个非终结符含有空串，才加入空串
                                    Rules::firstSet[left].insert(ZERO);
                                }
                            }
                            else {
                                Rules::firstSet[left].insert(first);
                            }
                        }
                        if (!exists_zero)
                            break;
                    }
                }
            }
            // 计算new_size
            new_size = 0;
            for (auto& [s, first] : Rules::firstSet) {
                new_size += first.size();
            }
        }
        
        std::cout << "[LOG] [RULES] Complete calculate first set" << std::endl;
    }
}

void Rules::saveFirstSet()
{
    const std::string filename = "parse/first.tmp";
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }

    fout << Rules::nonTerminalType.size() << std::endl;
    // 只输出前面一部分
    for (auto& [s, first] : Rules::firstSet) {
        if (s.is_terminal)
            break;  // 只输出非终结符的first集
        fout << s.type << " " << first.size() << std::endl;
        for (int firstSymbolType : first) {
            fout << firstSymbolType << " ";
        }
        fout << std::endl;
    }

    fout.close();
}

int Rules::analysis(const std::vector<symbol> &lexSymbols)
{
    assert(lexSymbols.back().type == END);
    std::vector<int> state;
    std::vector<symbol> SRSequence;
    std::vector<int> nodeID;
    state.push_back(0), SRSequence.push_back({1, END});
    for (int pos = 0; pos < lexSymbols.size(); pos++)
    {
        symbol a = lexSymbols[pos];
        action act = actionTable[state.back()][a];
        if(act.type == SHIFT)
        {
            state.push_back(act.next_state);
            SRSequence.push_back(a);
            nodeID.push_back(parserTree.size());
            parserTree.push_back({a, -1, {}});
        }
        else if(act.type == REDUCE)
        {
            int rightsiz = rules[act.rule_id].right.size();
            std::deque<int> dq;
            for (int i = 0; i < rightsiz; i++)
            {
                state.pop_back();
                SRSequence.pop_back();
                dq.push_front(nodeID.back());
                parserTree[nodeID.back()].father = parserTree.size();
                nodeID.pop_back();
            }
            state.push_back(act.next_state);
            SRSequence.push_back(rules[act.rule_id].left);
            nodeID.push_back(parserTree.size());
            std::vector<int> vt(dq.begin(), dq.end());
            parserTree.push_back({rules[act.rule_id].left, -1, vt});
            pos--;
        }
        else
        {
            assert(nodeID.size() == 1);
            return nodeID[0];
        }
    }
    return -1;
}