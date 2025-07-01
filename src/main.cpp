#include <fstream>
#include "lexical.h"
#include "rust_parser.h"
#include "data_type.h"
#include "generation.h"

int main(int argc, char *argv[])
{
    /* 预处理 */
    argParser arg_parser;
    arg_parser.parse(argc, argv);

    // 现阶段使用默认参数
    arg_parser.args["i"] = "test/test6.rs";
    arg_parser.args["m"] = "x86";

    if (!arg_parser.args.count("i"))
    {
        std::cout << "[ERROR] [ARGUMENT] No input file specified" << std::endl;
        return 0;
    }
    if (!arg_parser.args.count("m"))
    {
        std::cout << "[ERROR] [ARGUMENT] No mode specified" << std::endl;
        return 0;
    }
    if (!arg_parser.args.count("o") && arg_parser.args["m"] != "interpreter")
    {
        arg_parser.args["o"] = arg_parser.args["i"] + ".s";
    }

    // 开始执行
    std::string filename = arg_parser.args["i"];
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
        if (lex_analyzer.analyse(s, linecnt))
        {
            std::cout << "[ERROE] [LEXICAL] at line " << linecnt << std::endl;
            return 0;
        }
    }
    if (lex_analyzer.analyse(" ", linecnt))
    {
        std::cout << "[ERROE] [LEXICAL] at line " << linecnt << std::endl;
        return 0;
    }
    std::cout << "[LOG] [LEXICAL] Complete lexical analyse at " << filename << std::endl;
    int i = 0;
    for (auto [s, tp, _] : lex_analyzer.lex)
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
    std::vector<int> linelist;
    std::vector<std::string> strList;
    for (auto [s, tp, lncnt] : lex_analyzer.lex)
    {
        sym.push_back(symbol(1, tp, s));
        linelist.push_back(lncnt);
        strList.push_back(s);
    }
    sym.push_back({1, END});
    linelist.push_back(linecnt);

    Rules rules;
    rules.analysis(sym, linelist, semantic);

    rules.drawParserTree(std::cout, strList);

    semantic.printCodes(std::cout);
    
    /* 目标代码生成 / 解释执行 */
    if (arg_parser.args["m"] == "itp")
    {
        std::cout << "[LOG] [GENRETION] Start interpreter" << std::endl;
        interpreter(semantic.codes);
        std::cout << "[LOG] [GENRETION] Interpreter finished" << std::endl;
    }
    else if (arg_parser.args["m"] == "x86")
    {
        std::cout << "[LOG] [GENRETION] Start compile to win_x86" << std::endl;
        GeneratorX86 generator;
        generator.generate(semantic.codes);
        std::cout << "[LOG] [GENRETION] Write to file " << arg_parser.args["o"] << std::endl;
    }
    else if (arg_parser.args["m"] == "arm")
    {
        std::cout << "[LOG] [GENRETION] Start compile to android_arm" << std::endl;
        
        std::cout << "[LOG] [GENRETION] Write to file " << arg_parser.args["o"] << std::endl;
    }
    

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
