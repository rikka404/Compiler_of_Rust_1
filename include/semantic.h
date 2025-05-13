#include <string>
#include <vector>
#include <map>
#include <set>
#include "datapath.h"

enum read_type
{
    NONETYPE,
    VARIABLE,
    CONSTANT,
    LITERAL
};

class element_type
{
public:
    std::shared_ptr<data_type> dataType;    // 数据类型
    enum read_type readType = NONETYPE;     // 读写类型
};

class functionEntry
{
public:
    std::string name;                    // 函数名
    std::vector<element_type> argsTypes; // 参数类型列表
    element_type returnType;             // 返回值类型
    
    bool operator<(const functionEntry &f) const
    {
        return name < f.name;
    }
};

class symbolEntry
{
public:
    std::string name;    // 符号名
    element_type type;   // 类型
    int relativeAddress; // 符号在栈中的相对(ebp)地址
};

class attribute
{
public:
    std::map<std::string, int> values;
    element_type type; // 类型
};

class Semantic
{
public:
    // 语义动作函数指针
    static std::vector<void (Semantic::*)(std::vector<attribute> &, attribute &)> semanticActions;

    std::set<functionEntry> functionTable; // 函数表
    std::vector<symbolEntry> symbolTable;     // 符号表
    std::vector<std::string> codes;           // 中间代码

    // 可复用函数

    // 语义动作函数
    void act0_(std::vector<attribute> &args, attribute &result);
    
};