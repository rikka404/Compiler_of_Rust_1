#include "lexical.h"
#include <iostream>

std::vector<TrieNode> lexical_analyzer::trie;

void lexical_analyzer::init()
{
    trie.push_back(TrieNode());// 0，初始节点
    trie.push_back(TrieNode());// 1, 出错了的节点
    trie.push_back(TrieNode());// 2, ID节点
    trie.push_back(TrieNode());// 3, 数字节点

    trie[0].type = ZERO;
    trie[0].son[' '] = 0;
    trie[0].son['\n'] = 0;
    trie[0].son['\r'] = 0;
    trie[0].son['\t'] = 0;
    trie[0].opt[' '] |= OPT_SKIP;
    trie[0].opt['\n'] |= OPT_SKIP;
    trie[0].opt['\r'] |= OPT_SKIP;
    trie[0].opt['\t'] |= OPT_SKIP;

    // 已经分析出错了，就一直错着
    trie[1].type = UNDEF;
    for (int i = 0; i < MAXCHAR; i++)
    {
        trie[1].son[i] = 1;
    }

    // ID节点，如果是'_'或字母或数字，可以接着匹配，否则需要倒退一字符回到0
    trie[2].type = ID;
    for (int i = 0; i < MAXCHAR; i++)
    {
        if (i == '_' || islower(i) || isupper(i) || isdigit(i))
            trie[2].son[i] = 2;
        else
        {
            trie[2].son[i] = 0;
            trie[2].opt[i] |= OPT_RETRACT;
            trie[2].opt[i] |= OPT_UPDLEX;
        }
    }

    // 数字节点，如果还是数字或者'_'(没错rust允许数字之间有_)就还是数字，否则就回退并到0
    trie[3].type = INT;
    for (int i = 0; i < MAXCHAR; i++)
    {
        if (isdigit(i) || i == '_')
        {
            trie[3].son[i] = 3;
            if (i == '_')
                trie[3].opt[i] |= OPT_SKIP;
        }
        else
        {
            trie[3].son[i] = 0;
            trie[3].opt[i] |= OPT_RETRACT;
            trie[3].opt[i] |= OPT_UPDLEX;
        }
    }

    const int idnode = 2;
    // 对于关键字建立trie树，这些如果失配后可以到ID节点
    for (auto [s, tp, _] : key_word)
    {
        int p = 0;
        for (int ch : s)
        {
            if (trie[p].son[ch] == -1)
            {
                trie[p].son[ch] = trie.size();
                trie.push_back(TrieNode());
                trie.back().type = ID; //如果没有匹配到关键字，就认为是用户ID
            }
            p = trie[p].son[ch];
        }
        trie[p].type = tp;
    }
    // 如果是其他字母数字下划线，则转到ID节点，否则就是结束了，回退并到0
    for (int i = 4; i < (int)trie.size(); i++)
    {
        for (int j = 0; j < MAXCHAR; j++)
        {
            if (trie[i].son[j] != -1)
                continue;
            if (islower(j) || isupper(j) || isdigit(j) || j == '_')
                trie[i].son[j] = idnode;
            else
            {
                trie[i].son[j] = 0;
                trie[i].opt[j] |= OPT_RETRACT;
                trie[i].opt[j] |= OPT_UPDLEX;
            }
        }
    }

    // 对符号关键字建立trie树，如果失配则只能直接返回0
    int oldsize = trie.size();
    for (auto [s, tp, _] : key_symbol)
    {
        int p = 0;
        for (int ch : s)
        {
            if (trie[p].son[ch] == -1)
            {
                trie[p].son[ch] = trie.size();
                trie.push_back(TrieNode());
                trie.back().type = UNDEF; //如果没有匹配到关键字，只能认为是失败了
            }
            p = trie[p].son[ch];
        }
        trie[p].type = tp;
    }
    //单行注释，在trie树中走到//这个地方就说明进了注释，之后读的所有东西都不看，直到读到'\n'
    {
        std::string oneLineAnno = "//";
        int p = 0;
        for (int ch : oneLineAnno)
        {
            if (trie[p].son[ch] == -1)
            {
                trie[p].son[ch] = trie.size();
                trie.push_back(TrieNode());
                trie.back().type = UNDEF; //如果没有匹配到关键字，只能认为是失败了
            }
            p = trie[p].son[ch];
        }
        for (int j = 0; j < MAXCHAR; j++)
        {
            trie[p].son[j] = p;
            trie[p].opt[j] |= OPT_SKIP;
        }
        trie[p].son['\n'] = 0;
        trie[p].opt['\n'] |= OPT_CLEARSTR;
    }
    /*
     * 多行注释，依然是在trie树中走到"/ *"
     * 出来的时候，由于是两个字符，所以相当于是要再自动机上识别一个字符串，其实就是AC自动机
     * 但是这里由于只有两个字符"* /"所以就偷懒直接手动建了
     */
    {
        std::string mulLineAnnoLeft = "/*";
        std::string mulLineAnnoRight = "*/";
        int p = 0;
        for (int ch : mulLineAnnoLeft)
        {
            if (trie[p].son[ch] == -1)
            {
                trie[p].son[ch] = trie.size();
                trie.push_back(TrieNode());
                trie.back().type = UNDEF; //如果没有匹配到关键字，只能认为是失败了
            }
            p = trie[p].son[ch];
        }
        int p1 = trie.size();
        trie[p].son['*'] = trie.size();
        trie.push_back(TrieNode());
        for (int j = 0; j < MAXCHAR; j++)
        {
            if(trie[p].son[j] != -1)
                continue;
            trie[p].son[j] = p;
        }
        int p2 = trie.size();
        trie[p1].son['/'] = trie.size();
        trie.push_back(TrieNode());
        for (int j = 0; j < MAXCHAR; j++)
        {
            if(trie[p1].son[j] != -1)
                continue;
            trie[p1].son[j] = p;
        }
        for (int j = 0; j < MAXCHAR; j++)
        {
            trie[p2].son[j] = 0;
            trie[p2].opt[j] |= OPT_CLEARSTR;
        }
    }
    for (int i = oldsize; i < (int)trie.size(); i++)
    {
        for (int j = 0; j < MAXCHAR; j++)
        {
            if (trie[i].son[j] != -1)
                continue;
            trie[i].son[j] = 0;
            trie[i].opt[j] |= OPT_RETRACT;
            trie[i].opt[j] |= OPT_UPDLEX;
        }
    }
    
    //对0节点特判，字母直接到ID，数字直接到数字
    for (int i = 0; i < MAXCHAR; i++)
    {
        if (trie[0].son[i] != -1)
            continue;
        if (islower(i) || isupper(i) || i == '_')
            trie[0].son[i] = 2;
        else if (isdigit(i))
            trie[0].son[i] = 3;
        else
            trie[0].son[i] = 1;
    }

    // 其他一律按照出错处理
    for (int i = 1; i < (int)trie.size(); i++)
    {
        for (int j = 0; j < MAXCHAR; j++)
        {
            if (trie[i].son[j] == -1)
                trie[i].son[j] = 1;
        }
    }
}

int lexical_analyzer::analyse(const std::string& s, int line)
{
    for (int i = 0; i < (int)s.length(); i++)
    {
        int ch = s[i];
        if (trie[ptr].opt[ch] & OPT_UPDLEX)
        {
            lex.push_back({nowstr, trie[ptr].type, line});
            nowstr.clear();
        }
        if (trie[ptr].opt[ch] & OPT_RETRACT)
            i--;
        else if (!(trie[ptr].opt[ch] & OPT_SKIP))
            nowstr.push_back(s[i]);
        if (trie[ptr].opt[ch] & OPT_CLEARSTR)
            nowstr.clear();
        ptr = trie[ptr].son[ch];
    }
    if (ptr == 1)
        return 1;
    return 0;
}