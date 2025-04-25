#include <iostream>
#include <fstream>
#include "lexical.h"
#include "rust_parser.h"

int main()
{
    // /* 预处理 */
    // std::string filename = "test/test2.rs";
    // std::ifstream fin(filename);
    // std::string s;
    // if (!fin.is_open())
    // {
    //     std::cout << "[ERROR] [FILE] " << filename << " is not exist" << std::endl;
    //     return 0;
    // }

    // /* 词法分析 */
    // lexical_analyzer lex_analyzer;
    // int linecnt = 0;
    // while (std::getline(fin, s))
    // {
    //     ++linecnt;
    //     s += '\n';
    //     if (lex_analyzer.analyse(s))
    //     {
    //         std::cout << "[ERROE] [LEXICAL] at line " << linecnt << std::endl;
    //         return 0;
    //     }
    // }
    // if (lex_analyzer.analyse(" "))
    // {
    //     std::cout << "[ERROE] [LEXICAL] at line " << linecnt << std::endl;
    //     return 0;
    // }
    // std::cout << "[LOG] [LEXICAL] Complete lexical analyse at " << filename << std::endl;
    // for (auto [s, _] : lex_analyzer.lex)
    // {
    //     std::cout << s << std::endl;
    // }

    Rules::init(false);
    Rules::saveRules();
    Rules::saveFirstSet();

    return 0;
}
