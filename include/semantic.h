#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include "data_type.h"

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
    bool operator<(const symbolEntry& sym) const
    {
        return name < sym.name;
    }
};

class attribute
{
public:
    std::map<std::string, int> values;
    element_type type; // 类型
};

class quaternary
{
public:
    std::string op, arg1, arg2, result;

    quaternary(){};
    quaternary(std::string a, std::string b, std::string c, std::string d) : op(a), arg1(b), arg2(c), result(d){};
};

class Semantic
{
public:
    // 语义动作函数指针
    static std::vector<void (Semantic::*)(std::vector<attribute> &, attribute &)> semanticActions;
    // 终结符动作函数指针
    static std::vector<void (Semantic::*)(attribute &)> semanticTerminalActions;

    std::set<functionEntry> functionTable; // 函数表
    std::map<std::string, symbolEntry> symbolTable;     // 符号表
    std::stack<symbolEntry> symbolStack;
    std::stack<int> c_ebp; //不知道什么时候变，应该是读到{、}的时候？但是也不一定，比如函数传参
    int c_esp = 0; //其实目前不知道有什么用，因为好像只需要这个符号的名字就好了，不需要真的模拟它在内存中的位置
    std::vector<quaternary> codes;           // 中间代码
    std::vector<attribute> attributes;      //把每个语法分析树节点的attr都存下来，与语法分析同步
    const int begin_quad_num = 100;
    int quad_num;

    void init();

    // 可复用函数

    // 语义动作函数
    void act0_(std::vector<attribute> &args, attribute &result);
    void act1_(std::vector<attribute> &args, attribute &result);
    void act2_(std::vector<attribute> &args, attribute &result);
    void act3_(std::vector<attribute> &args, attribute &result);
    void act4_(std::vector<attribute> &args, attribute &result);
    void act5_(std::vector<attribute> &args, attribute &result);
    void act6_(std::vector<attribute> &args, attribute &result);
    void act7_(std::vector<attribute> &args, attribute &result);
    void act8_(std::vector<attribute> &args, attribute &result);
    void act9_(std::vector<attribute> &args, attribute &result);
    void act10_(std::vector<attribute> &args, attribute &result);
    void act11_(std::vector<attribute> &args, attribute &result);
    void act12_(std::vector<attribute> &args, attribute &result);
    void act13_(std::vector<attribute> &args, attribute &result);
    void act14_(std::vector<attribute> &args, attribute &result);
    void act15_(std::vector<attribute> &args, attribute &result);
    void act16_(std::vector<attribute> &args, attribute &result);
    void act17_(std::vector<attribute> &args, attribute &result);
    void act18_(std::vector<attribute> &args, attribute &result);
    void act19_(std::vector<attribute> &args, attribute &result);
    void act20_(std::vector<attribute> &args, attribute &result);
    void act21_(std::vector<attribute> &args, attribute &result);
    void act22_(std::vector<attribute> &args, attribute &result);
    void act23_(std::vector<attribute> &args, attribute &result);
    void act24_(std::vector<attribute> &args, attribute &result);
    void act25_(std::vector<attribute> &args, attribute &result);
    void act26_(std::vector<attribute> &args, attribute &result);
    void act27_(std::vector<attribute> &args, attribute &result);
    void act28_(std::vector<attribute> &args, attribute &result);
    void act29_(std::vector<attribute> &args, attribute &result);
    void act30_(std::vector<attribute> &args, attribute &result);
    void act31_(std::vector<attribute> &args, attribute &result);
    void act32_(std::vector<attribute> &args, attribute &result);
    void act33_(std::vector<attribute> &args, attribute &result);
    void act34_(std::vector<attribute> &args, attribute &result);
    void act35_(std::vector<attribute> &args, attribute &result);
    void act36_(std::vector<attribute> &args, attribute &result);
    void act37_(std::vector<attribute> &args, attribute &result);
    void act38_(std::vector<attribute> &args, attribute &result);
    void act39_(std::vector<attribute> &args, attribute &result);
    void act40_(std::vector<attribute> &args, attribute &result);
    void act41_(std::vector<attribute> &args, attribute &result);
    void act42_(std::vector<attribute> &args, attribute &result);
    void act43_(std::vector<attribute> &args, attribute &result);
    void act44_(std::vector<attribute> &args, attribute &result);
    void act45_(std::vector<attribute> &args, attribute &result);
    void act46_(std::vector<attribute> &args, attribute &result);
    void act47_(std::vector<attribute> &args, attribute &result);
    void act48_(std::vector<attribute> &args, attribute &result);
    void act49_(std::vector<attribute> &args, attribute &result);
    void act50_(std::vector<attribute> &args, attribute &result);

    // 终结符动作函数
    void tact0_(attribute &result);
    void tact1_(attribute &result);
    void tact2_(attribute &result);
    void tact3_(attribute &result);
    void tact4_(attribute &result);
    void tact5_(attribute &result);
    void tact6_(attribute &result);
    void tact7_(attribute &result);
    void tact8_(attribute &result);
    void tact9_(attribute &result);
    void tact10_(attribute &result);
    void tact11_(attribute &result);
    void tact12_(attribute &result);
    void tact13_(attribute &result);
    void tact14_(attribute &result);
    void tact15_(attribute &result);
    void tact16_(attribute &result);
    void tact17_(attribute &result);
    void tact18_(attribute &result);
    void tact19_(attribute &result);
    void tact20_(attribute &result);
    void tact21_(attribute &result);
    void tact22_(attribute &result);
    void tact23_(attribute &result);
    void tact24_(attribute &result);
    void tact25_(attribute &result);
    void tact26_(attribute &result);
    void tact27_(attribute &result);
    void tact28_(attribute &result);
    void tact29_(attribute &result);
    void tact30_(attribute &result);
    void tact31_(attribute &result);
    void tact32_(attribute &result);
    void tact33_(attribute &result);
    void tact34_(attribute &result);
    void tact35_(attribute &result);
    void tact36_(attribute &result);
    void tact37_(attribute &result);
    void tact38_(attribute &result);
    void tact39_(attribute &result);
    void tact40_(attribute &result);
    void tact41_(attribute &result);
    void tact42_(attribute &result);
    void tact43_(attribute &result);
    void tact44_(attribute &result);
    void tact45_(attribute &result);
    void tact46_(attribute &result);
    void tact47_(attribute &result);
    void tact48_(attribute &result);
    void tact49_(attribute &result);
    void tact50_(attribute &result);

    
};