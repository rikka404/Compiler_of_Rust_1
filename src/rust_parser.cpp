#include "rust_parser.h"
#include <fstream>
#include <iostream>

std::vector<production> Rules::rules; // 产生式规则
std::map<std::string, int> Rules::nonTerminalType;  // 非终结符
int Rules::nonTerminalCount = 0; // 非终结符数量

int Rules::findAndAdd(const std::string& s)
{
    auto it = Rules::nonTerminalType.find(s);
    if (it == Rules::nonTerminalType.end())
    {
        Rules::nonTerminalType[s] = Rules::nonTerminalCount;
        ++Rules::nonTerminalCount;
        return Rules::nonTerminalCount - 1;
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

void Rules::init()
{
    const std::string filename = "parse/parse_rule.rule";
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << "[ERROR] [RULES] filename is not exist" << std::endl;
        return;
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
                        Rules::rules.push_back(p_copy);
                    break;
                }
                else if (right[0] == '#')
                {
                    is_line_end = true;
                    std::getline(fin, left);  // 读到行尾
                    if (!p_copy.right.empty())
                        Rules::rules.push_back(p_copy);
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
    int isdisdc = 0;
}