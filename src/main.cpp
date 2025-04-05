#include <iostream>
#include <fstream>
#include "lexical.h"

int main()
{
    lexical_analyzer lex_analyzer;
    std::ifstream fin("test.rs");
    std::string s;
    std::getline(fin, s);
    if(lex_analyzer.analyse(s))
    {
        std::cout << "lexical analyze error" << std::endl;
        return 0;
    }
    if(lex_analyzer.analyse(" "))
    {
        std::cout << "lexical analyze error" << std::endl;
        return 0;
    }
    for (auto [s, _] : lex_analyzer.lex)
    {
        std::cout << s << std::endl;
    }
}
