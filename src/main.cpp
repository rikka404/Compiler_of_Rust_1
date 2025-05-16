#include <iostream>
#include <fstream>
#include "lexical.h"
#include "rust_parser.h"
#include "data_type.h"

int main()
{
    /* 预处理 */
    // test是用来测试词法分析的，test2是用来测试语法分析的
    std::string filename = "test/test4.rs";
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
    int i = 0;
    for (auto [s, _] : lex_analyzer.lex)
    {
        std::cout << i << ":" << s << std::endl;
        ++i;
    }

    /* 语法分析 + 语义分析 */
    // 初始化分析表
    Rules::init(true, true);
    Semantic semantic;
    semantic.init();

    std::vector<symbol> sym;
    std::vector<std::string> strList;
    for (auto [s, tp] : lex_analyzer.lex)
    {
        sym.push_back(symbol(1, tp, s));
        strList.push_back(s);
    }
    sym.push_back({1, END});

    Rules rules;
    rules.analysis(sym, semantic);

    rules.drawParserTree(std::cout, strList);

    semantic.printCodes(std::cout);

    // // 第一组测试
    // auto ele1 = data_type::create(I32_TYPE);
    // auto ele2 = data_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<data_type>>{ele1, ele1, ele1});
    // auto ele3 = data_type::create(REFER_TYPE, ele2);
    // auto ele4 = data_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<data_type>>{ele1, ele2, ele3});
    // auto ele5 = data_type::create(I32_TYPE);
    // auto ele6 = data_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<data_type>>{ele5, ele5, ele5});
    // auto ele7 = data_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<data_type>>{ele5, ele6, ele5});
    // auto ele8 = data_type::create(ARRAY_TYPE, 100, ele7);
    // auto ele9 = data_type::create(REFER_TYPE, ele8);

    // std::cout << (*ele4 == *ele7) << std::endl;
    // std::cout << *ele4 << std::endl;
    // std::cout << *ele7 << std::endl;
    // std::cout << (ele5->siz) << std::endl;
    // std::cout << (ele6->siz) << std::endl;
    // std::cout << (ele7->siz) << std::endl;
    // std::cout << (ele8->siz) << std::endl;

    // std::cout << (ele9->siz) << std::endl;
    // std::cout << (*ele3 == *ele9) << std::endl;
    // std::cout << *ele3 << std::endl;
    // std::cout << *ele9 << std::endl;

    // // 第二组测试
    // auto ele1 = data_type::create(I32_TYPE);
    // ele1 = data_type::create(BOOL_TYPE);
    // ele1 = data_type::create(I32_TYPE);
    // //成功执行三次析构函数

    // // 第三组测试
    // auto ele1 = data_type::create(I32_TYPE);
    // {
    //     auto ele2 = data_type::create(ARRAY_TYPE, 3, ele1);
    //     ele1 = data_type::create(TUPLE_TYPE, 4, std::vector<std::shared_ptr<data_type>>{ele2, ele2, ele2, ele2});
    // }
    // // 这里三次析构，没问题
    // std::cout << ele1->siz << std::endl;
    // // 这里九次析构，没问题

    // // 第四组测试
    // auto ele0 = data_type::create(BOOL_TYPE);
    // auto ele1 = data_type::create(I32_TYPE);
    // auto ele2 = data_type::create(REFER_TYPE, ele1);
    // auto ele3 = data_type::create(TUPLE_TYPE, 3, std::vector<std::shared_ptr<data_type>>{ele0, ele1, ele1});
    // auto ele4 = data_type::create(ARRAY_TYPE, 3, ele3);

    // std::cout << ele4->type << std::endl;
    // int offset = 0;
    // std::cout << ele4->get_sub_class(2)->type << std::endl;
    // std::cout << offset << std::endl;
    // offset = 0;
    // std::cout << ele4->get_sub_class(2, offset)->get_sub_class(0, offset)->type << std::endl;
    // std::cout << offset << std::endl;
    // offset = 0;
    // std::cout << ele4->get_sub_class(2, offset)->get_sub_class(0, offset)->get_sub_class(0, offset)->type << std::endl;
    // std::cout << offset << std::endl;
    // offset = 0;
    // std::cout << ele4->get_sub_class(2, offset)->get_sub_class(0, offset)->get_sub_class(0, offset)->type << std::endl;
    // std::cout << offset << std::endl;
    // std::cout << *ele4 << std::endl;
    // std::cout << *ele4->get_sub_class(2) << std::endl;
    // std::cout << *ele4->get_sub_class(2)->get_sub_class(0) << std::endl;
    // std::cout << *ele4->get_sub_class(2)->get_sub_class(0)->get_sub_class(0) << std::endl;
    // std::cout << *ele4->get_sub_class(2)->get_sub_class(0)->get_sub_class(1) << std::endl;
    return 0;
}
