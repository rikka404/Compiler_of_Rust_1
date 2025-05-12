#include "rust_parser.h"
#include <fstream>
#include <iostream>
#include <assert.h>

std::vector<production> Rules::rules;                                                // 产生式规则 初始和运行都需要
std::vector<int> Rules::ruleToSemantic;                                              // 产生式id到语义动作函数编号的映射 初始和运行都需要
std::map<symbol, std::vector<int>> Rules::leftRules;                                 // 用于辅助查找的map 初始需要
std::map<std::string, int> Rules::nonTerminalType;                                   // 非终结符编号 初始和运行都需要
std::vector<std::string> Rules::nonTerminalStr;                                      // 非终结符编号到字符串的映射 初始和运行都需要

std::map<symbol, std::set<int>> Rules::firstSet; // 所有first集 初始需要

std::vector<std::set<item>> Rules::itemSet;      // 项目集编号->项目集 初始需要
std::map<std::set<item>, int> Rules::mapItemSet; // 项目集->项目集编号 初始需要
std::vector<std::map<symbol, int>> Rules::dfa;   // 项目集图结构 初始需要

std::vector<std::map<symbol, action>> Rules::actionTable; // LR(1)分析表 初始运行需要 可以保存读取

int Rules::findAndAdd(const std::string &s)
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

int Rules::findNotAdd(const std::string &s)
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

void Rules::init(bool is_read, bool tmp_print)
{
    Rules::initRules(is_read);
    Rules::initNonTerminalStr();
    if (!is_read)
    {
        Rules::initFirstSet();
        // 这个阶段需要把产生式右边为空的/zero符号删掉
        Rules::deleteZero();
        Rules::initDFA();
        if (tmp_print)
        {
            Rules::printRules();
            Rules::printFirstSet();
            Rules::printDFA();
        }
        Rules::calActionTable();
        Rules::saveActionTable();
        if (tmp_print)
        {
            Rules::printActionTable();
        }
    }
    else
    {
        Rules::deleteZero();
        Rules::loadActionTable();
    }
}

void Rules::initRules(bool is_read)
{
    const std::string filename = "parse/meaning_rule2.py";
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
                if (right == "[")
                {
                    int temp = 0;
                    fin >> temp; // 读入语义动作函数编号
                    Rules::ruleToSemantic.push_back(temp);
                    fin >> right; // 读入]
                    fin >> right; // 读入下一个符号

                    if (right == "|")
                    {
                        if (!p_copy.right.empty())
                        {
                            // 对leftRules和rules进行添加
                            if (!is_read)
                                Rules::leftRules[p_copy.left].push_back(Rules::rules.size());
                            Rules::rules.push_back(p_copy);
                        }
                        break;
                    }
                    else if (right[0] == '#')
                    {
                        is_line_end = true;
                        std::getline(fin, left); // 读到行尾
                        if (!p_copy.right.empty())
                        {
                            // 对leftRules和rules进行添加
                            if (!is_read)
                                Rules::leftRules[p_copy.left].push_back(Rules::rules.size());
                            Rules::rules.push_back(p_copy);
                        }

                        break;
                    }
                    else
                    {
                        std::cout << "[ERROR] [RULES] at line " << linecnt << ", no end of rule" << std::endl;
                        std::cout << left << "-->" << right << std::endl;
                        exit(0);
                    }
                }
                

                // 检查名称
                symbol s;
                if (right[0] == '/')
                {
                    s.is_terminal = true;
                    s.type = Util::getTerminalType(right.substr(1));
                    if (s.type == UNDEF)
                    {
                        std::cout << "[ERROR] [RULES] at line " << linecnt << ", no terminal name: " << right.substr(1) << std::endl;
                        std::cout << left << "-->" << right << std::endl;
                        exit(0);
                    }
                }
                else
                {
                    if (!(islower(right[0]) || isupper(right[0])))
                    {
                        std::cout << "[ERROR] [RULES] at line " << linecnt << ", non-terminal can not name as " << right << std::endl;
                        std::cout << left << "-->" << right << std::endl;
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

void Rules::printRules()
{
    const std::string filename = "parse/rules.tmp";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }
    // 输出确认
    for (auto &rule : Rules::rules)
    {
        fout << Rules::nonTerminalStr[rule.left.type] << " -> ";
        for (auto &s : rule.right)
        {
            if (s.is_terminal)
                fout << "/" << Util::terminalStr[s.type] << " ";
            else
                fout << Rules::nonTerminalStr[s.type] << " ";
        }
        fout << std::endl;
    }
    fout.close();
}

void Rules::initNonTerminalStr()
{
    if (!Rules::nonTerminalStr.empty())
        return;
    Rules::nonTerminalStr.resize(Rules::nonTerminalType.size());
    for (auto [s, tp] : Rules::nonTerminalType)
    {
        Rules::nonTerminalStr[tp] = s;
    }
}

void Rules::initFirstSet()
{
    const std::string filename = "parse/first.set";

    symbol s;
    // 初始化非终结符set为空
    for (int i = 0; i < (int)Rules::nonTerminalType.size(); ++i)
    {
        s.is_terminal = false;
        s.type = i;
        Rules::firstSet[s] = std::set<int>();
    }
    // 初始化终结符set为自身
    for (int i = 0; i < (int)Util::terminalType.size(); ++i)
    {
        s.is_terminal = true;
        s.type = i;
        Rules::firstSet[s] = std::set<int>();
        Rules::firstSet[s].insert(i);
    }

    // 计算first集合
    int old_size = -1;
    int new_size = 0;
    while (old_size != new_size)
    {
        old_size = new_size;
        for (production &rule : Rules::rules)
        {
            symbol left = rule.left;
            std::vector<symbol> right = rule.right;

            for (int i = 0; i < (int)right.size(); ++i)
            {
                symbol s = right[i];
                if (s.is_terminal)
                {
                    // 如果是终结符，加入first集 退出
                    Rules::firstSet[left].insert(s.type);
                    break;
                }
                else
                {
                    // 如果是非终结符，加入first集
                    bool exists_zero = false;
                    for (int first : Rules::firstSet[s])
                    {
                        if (first == ZERO)
                        {
                            // 如果含有空串，可以继续下一个符号
                            exists_zero = true;
                            if (i == (int)right.size() - 1)
                            {
                                // 如果是最后一个非终结符含有空串，才加入空串
                                Rules::firstSet[left].insert(ZERO);
                            }
                        }
                        else
                        {
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
        for (auto &[s, first] : Rules::firstSet)
        {
            new_size += first.size();
        }
    }

    std::cout << "[LOG] [RULES] Complete calculate first set" << std::endl;
}

void Rules::printFirstSet()
{
    const std::string filename = "parse/first.tmp";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }

    fout << Rules::nonTerminalType.size() << std::endl;
    // 只输出前面一部分
    for (auto &[s, first] : Rules::firstSet)
    {
        if (s.is_terminal)
            break; // 只输出非终结符的first集
        fout << Rules::nonTerminalStr[s.type] << " " << first.size() << std::endl;
        for (int firstSymbolType : first)
        {
            fout << '/' << Util::terminalStr[firstSymbolType] << " ";
        }
        fout << std::endl;
    }

    fout.close();
}

void Rules::calFirstSet(const std::vector<symbol> &sententialForm, std::set<int> &sententFirst)
{
    for (int i = 0; i < (int)sententialForm.size(); ++i)
    {
        symbol s = sententialForm[i];
        if (s.is_terminal)
        {
            // 如果是终结符，加入first集 退出
            sententFirst.insert(s.type);
            break;
        }
        else
        {
            // 如果是非终结符，加入first集
            bool exists_zero = false;
            for (int first : Rules::firstSet[s])
            {
                if (first == ZERO)
                {
                    // 如果含有空串，可以继续下一个符号
                    exists_zero = true;
                    if (i == (int)sententialForm.size() - 1)
                    {
                        // 如果是最后一个非终结符含有空串，才加入空串
                        sententFirst.insert(ZERO);
                    }
                }
                else
                {
                    sententFirst.insert(first);
                }
            }
            if (!exists_zero)
                break;
        }
    }
}

void Rules::deleteZero()
{
    // 删除产生式右部的/zero符号
    for (int i = 0; i < (int)Rules::rules.size(); ++i)
    {
        if (Rules::rules[i].right.size() == 1)
        {
            symbol s = Rules::rules[i].right[0];
            if (s.is_terminal && s.type == ZERO)
            {
                // 删除/zero
                Rules::rules[i].right.clear();
            }
        }
    }
}

std::pair<bool, int> Rules::closeure(std::set<item> &items)
{
    std::queue<item> q; // 存储当前未应用闭包方法的项目

    for (auto &item : items)
    {
        q.push(item); // 将初始项目集加入队列
    }

    // 闭包集结果
    while (!q.empty())
    {
        item nowItem = q.front(); // 当前项目
        q.pop();

        if (nowItem.dot_pos >= (int)Rules::rules[nowItem.rule_id].right.size())
            continue; // 点在最后，跳过

        symbol s = Rules::rules[nowItem.rule_id].right[nowItem.dot_pos]; // 点后面的符号

        // 如果是非终结符，应用闭包方法
        if (!s.is_terminal)
        {
            // 计算新的lookahead
            std::set<int> sententFirst;
            std::vector<symbol> sententialForm;
            if (nowItem.dot_pos + 1 < (int)Rules::rules[nowItem.rule_id].right.size())
                sententialForm = {Rules::rules[nowItem.rule_id].right.begin() + nowItem.dot_pos + 1, Rules::rules[nowItem.rule_id].right.end()};
            sententialForm.push_back(symbol(true, nowItem.lookahead));
            Rules::calFirstSet(sententialForm, sententFirst);
            
            // 把所有s在左边的产生式加入结果集
            auto it = Rules::leftRules.find(s);
            if (it != Rules::leftRules.end())
            {
                for (int rid : it->second)
                {
                    // 若项目[A→α·Bβ, a]属于CLOSURE(I)，B→ξ 是一个产生式，
                    // 那么，对于FIRST(βa)中的每个终结符b，如果[B→·ξ, b]
                    // 原来不在CLOSURE(I) 中，则把它加进去
                    
                    for (int first : sententFirst)
                    {
                        if (first == ZERO)
                        {
                            std::cout << "[ERROR] [RULES] look ahead can not be empty string" << std::endl;
                            exit(0); // 不可能有空串
                        }
                        // 计算新的项目集
                        item newItem(rid, 0, first); // 新项目集
                        if (items.find(newItem) == items.end())
                        {
                            items.insert(newItem); // 加入结果集
                            q.push(newItem);       // 加入队列
                        }
                    }
                }
            }
            else
            {
                std::cout << "[ERROR] [RULES] no left rules for " << Rules::nonTerminalStr[s.type] << std::endl;
                exit(0);
            }
        }
    }

    // 检查该项目集是否已经存在
    auto it = Rules::mapItemSet.find(items);
    if (it != Rules::mapItemSet.end())
    {
        return {false, it->second}; // 已存在，返回false和编号
    }
    else
    {
        int id = Rules::itemSet.size();                // 新项目集编号
        Rules::mapItemSet[items] = id;                 // 存储id
        Rules::itemSet.push_back(items);               // 存储项目集
        Rules::dfa.push_back(std::map<symbol, int>()); // 新建DFA的边集合
        return {true, id};                             // 返回true和新编号
    }
}

void Rules::initDFA()
{
    std::queue<int> q; // 存储当前未计算GOTO的项目集编号

    std::set<item> begItemSet = {item(0, 0, END)}; // 初始项目集
    auto result = Rules::closeure(begItemSet);     // 计算闭包集
    if (result.first)
    {
        q.push(result.second); // 将初始项目集编号加入队列
    }

    while (!q.empty())
    {
        int nowSetId = q.front(); // 当前项目集编号
        q.pop();

        std::map<symbol, std::set<item>> gotoSet; // 存储GOTO到的J项目集

        // 遍历查找，若有可以输入的符号，改动后塞进转移到的项目集中
        for (auto &nowItem : Rules::itemSet[nowSetId])
        {
            if (nowItem.dot_pos >= (int)Rules::rules[nowItem.rule_id].right.size())
                continue; // 点在最后，跳过

            symbol s = Rules::rules[nowItem.rule_id].right[nowItem.dot_pos]; // 可以输入的符号

            // 将点后移一位的项目加入GOTO结果
            gotoSet[s].insert(item(nowItem.rule_id, nowItem.dot_pos + 1, nowItem.lookahead));
        }

        // 遍历GOTO结果，计算闭包集
        for (auto &[s, items] : gotoSet)
        {
            auto result = Rules::closeure(items); // 计算闭包集

            Rules::dfa[nowSetId][s] = result.second; // 更新DFA

            if (result.first)
            {
                q.push(result.second); // 将新项目集编号加入队列
            }
        }
    }
    
    std::cout << "[LOG] [RULES] Complete calculate DFA" << std::endl;
}

void Rules::printDFA() 
{
    const std::string filename = "parse/dfa.tmp";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }

    // 输出图结构
    for (int i = 0; i < (int)Rules::dfa.size(); ++i)
    {
        fout << "DFA[" << i << "]:" << std::endl;
        for (auto &[s, id] : Rules::dfa[i])
        {
            if (s.is_terminal)
                fout << Util::terminalStr[s.type] << "->" << id << ' ';
            else
                fout << Rules::nonTerminalStr[s.type] << "->" << id << ' ';
        }
        fout << std::endl;
    }

    fout << std::endl;

    // 输出项目集
    for (int i = 0; i < (int)Rules::itemSet.size(); ++i)
    {
        fout << "ITEMSET[" << i << "]:" << std::endl;
        for (auto &item : Rules::itemSet[i])
        {
            fout << Rules::nonTerminalStr[Rules::rules[item.rule_id].left.type] << "->";
            for (int j = 0; j < (int)Rules::rules[item.rule_id].right.size(); ++j)
            {
                if (j == item.dot_pos)
                    fout << "· ";
                if (Rules::rules[item.rule_id].right[j].is_terminal)
                    fout << "/" << Util::terminalStr[Rules::rules[item.rule_id].right[j].type] << " ";
                else
                    fout << Rules::nonTerminalStr[Rules::rules[item.rule_id].right[j].type] << " ";
            }
            if (item.dot_pos == (int)Rules::rules[item.rule_id].right.size())
                fout << "· ";
            fout << ", " << Util::terminalStr[item.lookahead] << std::endl;
        }
        fout << std::endl;
    }

    fout.close();
}

void Rules::calActionTable()
{
    assert(dfa.size() == itemSet.size());
    actionTable.clear(), actionTable.resize(dfa.size());
    for (int i = 0; i < (int)dfa.size(); i++)
    {
        // for (item itt : itemSet[i])
        // {
        //     std::cerr << itt << std::endl;
        // }
        // std::cerr << std::endl;
        for (auto [sym, to] : dfa[i])
        {
            assert(!actionTable[i].count(sym));
            actionTable[i][sym] = {SHIFT, -1, to};
        }
        for (item it : itemSet[i])
        {
            auto& [rule_id, dot_pos, lookahead] = it;
            if (dot_pos != (int)rules[rule_id].right.size())
                continue;
            // 移进规约冲突
            if(actionTable[i].count({1, lookahead}))
            {
                std::cout << "[LOG] [RULES] Conflict, state=" << i << ", lookahead=" << Util::terminalStr[lookahead]
                        << " this rules is abandoned:" << rules[rule_id] << std::endl;
                // std::cout << "i=" << i << std::endl;
                // // for (item itt : itemSet[i])
                // // {
                // //     std::cout << itt << std::endl;
                // // }
                // std::cout << "look ahead = " << Util::terminalStr[lookahead] << std::endl;
                // std::cout << "1:" << std::endl;
                // std::cout << rules[rule_id] << std::endl;
                // std::cout << "2:" << std::endl;
                // std::cout << rules[actionTable[i][{1, lookahead}].rule_id] << std::endl;
                continue;
            }
            assert(!actionTable[i].count({1, lookahead}));
            actionTable[i][{1, lookahead}] = {REDUCE, rule_id, -1};
        }
    }
    actionTable[1][{1, END}] = {ACCEPTED, -1, -1};

    std::cout << "[LOG] [RULES] Complete calculate action table" << std::endl;
}

void Rules::saveActionTable() 
{
    const std::string filename = "parse/action.table";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }
    
    fout << Rules::actionTable.size() << std::endl;
    // 保存action表
    for (int i = 0; i < (int)Rules::actionTable.size(); ++i)
    {
        fout << Rules::actionTable[i].size() << std::endl;
        for (auto &[s, act] : Rules::actionTable[i])
        {
            fout <<  s.is_terminal << " " << s.type << " " << act.type << " " << act.rule_id << " " << act.next_state << std::endl;
        }
    }
}

void Rules::loadActionTable() 
{
    const std::string filename = "parse/action.table";
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }
    int size = 0;
    fin >> size;
    actionTable.clear(), actionTable.resize(size);
    for (int i = 0; i < size; ++i)
    {
        int cnt = 0;
        fin >> cnt;
        for (int j = 0; j < cnt; ++j)
        {
            symbol s;
            action act;
            int act_type;
            fin >> s.is_terminal >> s.type >> act_type >> act.rule_id >> act.next_state;
            act.type = (action_type)act_type;
            actionTable[i][s] = act;
        }
    }
    
    fin.close();

    std::cout << "[LOG] [RULES] Complete load action table" << std::endl;
}

void Rules::printActionTable() 
{
    const std::string filename = "parse/action.tmp";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [RULES] " << filename << " can not open" << std::endl;
        exit(0);
    }

    std::string actionStr[3] = {"SHIFT", "REDUCE", "ACCEPTED"};

    // 输出action表
    for (int i = 0; i < (int)Rules::actionTable.size(); ++i)
    {
        fout << "ACTION[" << i << "]:" << std::endl;
        for (auto &[s, act] : Rules::actionTable[i])
        {
            if (s.is_terminal)
                fout << Util::terminalStr[s.type] << " : " << actionStr[act.type] << ' ';
            else
                fout << Rules::nonTerminalStr[s.type] << " : " << actionStr[act.type] << ' ';
            
            if (act.type == SHIFT)
                fout << act.next_state << std::endl;
            else if (act.type == REDUCE)
                fout << act.rule_id << std::endl;
        }
        fout << std::endl;
    }

    fout.close();
}

int Rules::analysis(const std::vector<symbol> &lexSymbols)
{
    // 最后一个是end
    assert(lexSymbols.back().type == END);
    std::vector<int> state;
    std::vector<symbol> SRSequence;
    std::vector<int> nodeID;
    state.push_back(0), SRSequence.push_back({1, END});
    for (int pos = 0; pos < (int)lexSymbols.size(); pos++)
    {
        symbol a = lexSymbols[pos];
        // 必须含有此项
        if (!actionTable[state.back()].count(a))
        {
            std::cout << "[ERROR] [RULES] " << "parser analysis not accepted at pos " << pos << std::endl;
            exit(0);
        }
        action act = actionTable[state.back()][a];
        if (act.type == SHIFT)
        {
            state.push_back(act.next_state);
            SRSequence.push_back(a);
            nodeID.push_back(parserTree.size());
            parserTree.push_back({a, -1, {}, pos});
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
            assert(actionTable[state.back()].count(rules[act.rule_id].left) && actionTable[state.back()][rules[act.rule_id].left].type == SHIFT);
            state.push_back(actionTable[state.back()][rules[act.rule_id].left].next_state);
            SRSequence.push_back(rules[act.rule_id].left);
            nodeID.push_back(parserTree.size());
            std::vector<int> vt(dq.begin(), dq.end());
            parserTree.push_back({rules[act.rule_id].left, -1, vt, -1});
            pos--;
        }
        else
        {
            assert(nodeID.size() == 1);
            root = nodeID[0];
            std::cout << "[LOG] [RULES] " << "parser analysis accepted" << std::endl;
            return nodeID[0];
        }
    }
    std::cout << "[ERROR] [RULES] " << "parser analysis not accepted" << std::endl;
    return -1;
}

void Rules::drawParserTree(std::ostream &out, std::vector<std::string> &strList)
{
    // ANSI 转义序列
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string RESET = "\033[0m"; // 重置颜色
    
    auto draw = [&](auto self, int cur, std::string pre, bool islast) ->void
    {
        if (parserTree[cur].current.is_terminal)
        {
            out << BLUE << pre;
            out << YELLOW << Util::terminalStr[parserTree[cur].current.type];
            out << BLUE << " --- ";
            out << YELLOW << strList[parserTree[cur].char_pos] << RESET << std::endl;
        }
            
        else
        {
            out << BLUE << pre;
            out << GREEN << Rules::nonTerminalStr[parserTree[cur].current.type];
            out << RESET << std::endl;
        }
        for (int i = 0; i < (int)parserTree[cur].children.size(); i++)
        {
            std::string newpre = pre;
            for (int t = 0; t < 4; t++)
            {
                newpre.pop_back();
            }
            if (!islast)
            {
                newpre += "|   ";
            }
            else
            {
                newpre += "    ";
            }
            newpre += (i == (int)parserTree[cur].children.size() - 1) ? "\\-- " : "|-- ";
            self(self, parserTree[cur].children[i], newpre, i == (int)parserTree[cur].children.size() - 1);
        }
    };
    draw(draw, root, "\\-- ", 1);
}

std::ostream& operator<<(std::ostream& out, const symbol& sym)
{
    if(sym.is_terminal)
    {
        out << Util::terminalStr[sym.type];
    }
    else
    {
        out << Rules::nonTerminalStr[sym.type];
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const production& pro)
{
    out << pro.left << "->";
    for (int i = 0; i < (int)pro.right.size(); i++)
    {
        if(i)
            out << ' ';
        out << pro.right[i];
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const item &it)
{
    out << Rules::rules[it.rule_id].left << "->";
    for (int i = 0; i < it.dot_pos; i++)
    {
        out << Rules::rules[it.rule_id].right[i];
        out << ' ';
    }
    out << ".";
    for (int i = it.dot_pos; i < (int)Rules::rules[it.rule_id].right.size(); i++)
    {
        out << Rules::rules[it.rule_id].right[i];
        out << ' ';
    }
    out << Util::terminalStr[it.lookahead];
    return out;
}