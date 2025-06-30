#pragma once
#include <string>
#include <vector>
#include <string.h>
#include "util.h"

struct lexical
{
    std::string s;
    lexical_type type;
    int line; // 词法单元所在行号
};

const std::vector<lexical> key_word = {
    {"let", LET, 0},
    {"mut", MUT, 0},
    {"i32", I32, 0},
    {"if", IF, 0},
    {"else", ELSE, 0},
    {"while", WHILE, 0},
    {"return", RETURN, 0},
    {"fn", FN, 0},
    {"for", FOR, 0},
    {"in", IN, 0},
    {"loop", LOOP, 0},
    {"break", BREAK, 0},
    {"continue", CONTINUE, 0},
    {"false", FALSE, 0},
    {"true", TRUE, 0},
    {"bool", BOOL, 0},
    {"output", OUTPUT, 0},
    {"input", INPUT, 0}};
    
const std::vector<lexical> key_symbol = {
    {"=", ASSIGN, 0},
    {"+", ADD, 0},
    {"-", SUB, 0},
    {"*", MUL, 0},
    {"/", DIV, 0},
    {"%", MOD, 0},
    {"+=", ADDASSIGN, 0},
    {"-=", SUBASSIGN, 0},
    {"*=", MULASSIGN, 0},
    {"/=", DIVASSIGN, 0},
    {"%=", MODASSIGN, 0},
    {"==", EQU, 0},
    {">", GT, 0},
    {">=", GE, 0},
    {"<", LT, 0},
    {"<=", LE, 0},
    {"!=", NE, 0},

    {"(", LPRA, 0},
    {")", RPRA, 0},
    {"{", LBRA, 0},
    {"}", RBRA, 0},
    {"[", LSQB, 0},
    {"]", RSQB, 0},

    {";", SEMICOLON, 0},
    {":", COLON, 0},
    {",", COMMA, 0},

    {"->", ARROW, 0},
    {".", DOT, 0},
    {"..", DDOT, 0},

    {"&", REFER, 0},
    {"&&", AND, 0},
    {"||", OR, 0},
    {"!", NOT, 0}

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
    int opt[MAXCHAR];  // son表示经过128个字符到那个儿子节点 op表示这一步需要的附加操作
    TrieNode() {
        memset(son, -1, sizeof(son));
        memset(opt, 0, sizeof(opt));
    }
};

class lexical_analyzer
{
private:

    static std::vector<TrieNode> trie;  // 存储构建的DFA

    int ptr;  // 当前读到的字符偏移
    std::string nowstr;  // 当前分析的词

public:
    std::vector<lexical> lex;   // 存储最终得到的 词法单元 序列
    
    lexical_analyzer() : ptr(0) {}
    static void init();
    int analyse(const std::string &s, int line);
};