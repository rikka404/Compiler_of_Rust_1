#pragma once
#include <string>
#include <vector>
#include <string.h>

enum lexical_type
{
    ZERO, 
    UNDEF, 

    LET, 
    MUT, 

    ADD, 
    ASSIGN, 
    EQU, 
    SEP,  //分号
    UDL,

    ID, 
    INT
};

struct lexical
{
    std::string s;
    lexical_type type;
    // lexical(std::string _s, lexical_type _type) {
    //     s = _s, type = _type;
    // }
};

const std::vector<lexical> key_word = {
    {"let", LET},
    {"mut", MUT}
};
const std::vector<lexical> key_symbol = {
    {"+", ADD},
    {"=", ASSIGN},
    {"==", EQU},
    {";", SEP},
    {"_", UDL}
};

const int MAXCHAR = 128;

const int OPT_RETRACT = 1;
const int OPT_UPDLEX = 2;
const int OPT_SKIP = 4;

struct TrieNode
{
    lexical_type type;
    int son[MAXCHAR]; //这里必须用int，用指针写法的话pushback的时候会乱掉
    int opt[MAXCHAR];
    TrieNode(){
        memset(son, -1, sizeof(son));
        memset(opt, 0, sizeof(opt));
    }
};

class lexical_analyzer
{
private:

std::vector<TrieNode> trie;


int ptr;
std::string nowstr;

public:
    std::vector<lexical> lex;
    
    lexical_analyzer();
    int analyse(const std::string &s);
};