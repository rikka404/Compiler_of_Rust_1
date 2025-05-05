#include <iostream>
#include <fstream>
#include "lexical.h"
#include "rust_parser.h"

int main()
{
    /* 预处理 */
    // test是用来测试词法分析的，test2是用来测试语法分析的
    std::string filename = "test/test2.rs";
    std::ifstream fin(filename);
    std::string s;
    if (!fin.is_open())
    {
        std::cout << "[ERROR] [FILE] " << filename << " is not exist" << std::endl;
        return 0;
    }
    
    Util::initTerminalStr(); // 初始化终结符字符串

    /* 词法分析 */
    // 初始化字典树
    lexical_analyzer::init();
    
    lexical_analyzer lex_analyzer;
    int linecnt = 0;
    while (std::getline(fin, s))
    {
        ++linecnt;
        s += '\n';
        if (lex_analyzer.analyse(s))
        {
            std::cout << "[ERROE] [LEXICAL] at line " << linecnt << std::endl;
            return 0;
        }
    }
    if (lex_analyzer.analyse(" "))
    {
        std::cout << "[ERROE] [LEXICAL] at line " << linecnt << std::endl;
        return 0;
    }
    std::cout << "[LOG] [LEXICAL] Complete lexical analyse at " << filename << std::endl;
    for (auto [s, _] : lex_analyzer.lex)
    {
        std::cout << s << std::endl;
    }

    /* 语法分析 */
    // 初始化分析表
    Rules::init(false, true);

    std::vector<symbol> sym;
    std::vector<std::string> strList;
    for (auto [s, tp] : lex_analyzer.lex)
    {
        sym.push_back({1, tp});
        strList.push_back(s);
    }
    sym.push_back({1, END});

    Rules rules;
    rules.analysis(sym);

    rules.drawParserTree(std::cout, strList);

    return 0;
}
