#include <iostream>
#include <fstream>
#include "lexical.h"
#include "rust_parser.h"
#include "element_type.h"

int main()
{
    // /* 预处理 */
    // // test是用来测试词法分析的，test2是用来测试语法分析的
    // std::string filename = "test/test3.rs";
    // std::ifstream fin(filename);
    // std::string s;
    // if (!fin.is_open())
    // {
    //     std::cout << "[ERROR] [FILE] " << filename << " is not exist" << std::endl;
    //     return 0;
    // }
    
    // Util::initTerminalStr(); // 初始化终结符字符串

    // /* 词法分析 */
    // // 初始化字典树
    // lexical_analyzer::init();
    
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
    // int i = 0;
    // for (auto [s, _] : lex_analyzer.lex)
    // {
    //     std::cout << i << ":" << s << std::endl;
    //     ++i;
    // }

    // /* 语法分析 */
    // // 初始化分析表
    // Rules::init(false, true);

    // std::vector<symbol> sym;
    // std::vector<std::string> strList;
    // for (auto [s, tp] : lex_analyzer.lex)
    // {
    //     sym.push_back({1, tp});
    //     strList.push_back(s);
    // }
    // sym.push_back({1, END});

    // Rules rules;
    // rules.analysis(sym);

    // rules.drawParserTree(std::cout, strList);

    auto ele1 = element_type::create(I32_TYPE);
    auto ele2 = element_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<element_type>>{ele1, ele1, ele1});
    auto ele3 = element_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<element_type>>{ele1, ele2, ele1});
    auto ele4 = element_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<element_type>>{ele1, ele2, ele3});
    auto ele5 = element_type::create(I32_TYPE);
    auto ele6 = element_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<element_type>>{ele5, ele5, ele5});
    auto ele7 = element_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<element_type>>{ele5, ele6, ele5});
    auto ele8 = element_type::create(ARRAY_TYPE, 3, *ele7);

    std::cout << (*ele4 == *ele7) << std::endl;
    std::cout << (ele5->siz) << std::endl;
    std::cout << (ele6->siz) << std::endl;
    std::cout << (ele7->siz) << std::endl;
    std::cout << (ele8->siz) << std::endl;

    return 0;
}
