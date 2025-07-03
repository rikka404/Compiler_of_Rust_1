#include <fstream>
#include <cstdlib>
#include <filesystem>
#include "lexical.h"
#include "rust_parser.h"
#include "data_type.h"
#include "generation.h"

int main(int argc, char *argv[])
{
    // 终端所在目录
    std::string teminal_path = std::filesystem::current_path().string() + "\\";
    // 切换到可执行文件所在目录
    std::filesystem::path exe_dir = std::filesystem::path(argv[0]).parent_path();
    if (!exe_dir.empty())
    {
        std::filesystem::current_path(exe_dir);
    }
    /* 预处理 */
    argParser arg_parser;
    arg_parser.parse(argc, argv);
    // 给输入输出路径加上终端所在目录
    if (arg_parser.args.count("i"))
    {
        arg_parser.args["i"] = teminal_path + arg_parser.args["i"];
    }
    if (arg_parser.args.count("o"))
    {
        arg_parser.args["o"] = teminal_path + arg_parser.args["o"];
    }

    // 现阶段使用默认参数
    // arg_parser.args["i"] = "test/test5.rs";
    // arg_parser.args["m"] = "x86";

    if (!arg_parser.args.count("i"))
    {
        std::cout << "[ERROR] [ARGUMENT] No input file specified" << std::endl;
        return 0;
    }
    if (!arg_parser.args.count("m"))
    {
        arg_parser.args["m"] = "itp"; // 默认模式为解释器
    }
    if (!arg_parser.args.count("o") && arg_parser.args["m"] != "itp")
    {
        arg_parser.args["o"] = arg_parser.args["i"] + ".exe";
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

        // 执行编译命令
        std::string compile_cmd = "obj\\mingw32\\bin\\gcc.exe -m32 obj\\src\\main.s obj\\src\\io.s -o " + arg_parser.args["o"];
        std::cout << "[LOG] [GENRETION] Executing: " << compile_cmd << std::endl;

        int result = system(compile_cmd.c_str());
        if (result == 0)
        {
            std::cout << "[LOG] [GENRETION] Compilation successful, write to file " << arg_parser.args["o"] << std::endl;
        }
        else
        {
            std::cout << "[ERROR] [GENRETION] Compilation failed with code " << result << std::endl;
        }
    }
    else
    {
        std::cout << "[ERROR] [ARGUMENT] Unknown mode: " << arg_parser.args["m"] << std::endl;
        std::cout << "[LOG] please use -h to see help" << std::endl;
        std::cout << "[LOG] [GENRETION] Start interpreter" << std::endl;
        interpreter(semantic.codes);
        std::cout << "[LOG] [GENRETION] Interpreter finished" << std::endl;
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
