#pragma once
#include <string>
#include <vector>
#include <string.h>
#include "util.h"

struct lexical
{
    std::string s;
    lexical_type type;
};

const std::vector<lexical> key_word = {
    {"let", LET},
    {"mut", MUT}, 
    {"i32", I32}, 
    {"if", IF}, 
    {"else", ELSE}, 
    {"while", WHILE}, 
    {"return", RETURN}, 
    {"fn", FN}, 
    {"for", FOR}, 
    {"in", IN}, 
    {"loop", LOOP}, 
    {"break", BREAK}, 
    {"continue", CONTINUE}
};
const std::vector<lexical> key_symbol = {
    {"=", ASSIGN},
    {"+", ADD},
    {"-", SUB},
    {"*", MUL},
    {"/", DIV},
    {"%", MOD},
    {"+=", ADDASSIGN},
    {"-=", SUBASSIGN},
    {"*=", MULASSIGN},
    {"/=", DIVASSIGN},
    {"%=", MODASSIGN},
    {"==", EQU},
    {">", GT},
    {">=", GE},
    {"<", LT},
    {"<=", LE},
    {"!=", NE},
    
    {"(", LPRA},
    {")", RPRA},
    {"{", LBRA},
    {"}", RBRA},
    {"[", LSQB},
    {"]", RSQB},


    {";", SEMICOLON},
    {":", COLON},
    {",", COMMA}, 

    {"->", ARROW},
    {".", DOT},
    {"..", DDOT}
};

const int MAXCHAR = 128;

const int OPT_RETRACT = 1;
const int OPT_UPDLEX = 2;
const int OPT_SKIP = 4;
const int OPT_CLEARSTR = 8;

struct TrieNode
{
    lexical_type type;
    int son[MAXCHAR]; //这里必须用int，用指针写法的话pushback的时候会乱掉
    int opt[MAXCHAR];
    TrieNode() {
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