#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <any>
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

class functionEntry
{
public:
    int code_pos;                       //函数的四元式起始位置
    std::string name;                    // 函数名
    std::vector<symbolEntry> argsTypes; // 形参列表
    symbolEntry returnType;             // 返回值类型
    
    bool operator<(const functionEntry &f) const
    {
        return name < f.name;
    }
};

// class attribute
// {
// public:
//     std::map<std::string, std::any> values;
//     // element_type type; // 类型
// };
// attr.value["type"]
using attribute = std::map<std::string, std::any>;

enum arg_type
{
    Literal,    //立即数
    Address,    //内存地址
    Lable       //中间代码标号
};
struct Operand {
    arg_type type;
    int value;  // 地址偏移 or 立即数值 or label编号
};

class quaternary
{
public:
    std::string op;
    Operand arg1, arg2, result;

    quaternary(){};
    quaternary(std::string a, Operand b, Operand c, Operand d) : op(a), arg1(b), arg2(c), result(d){};
};

/**
 * 事已至此，写一下目前我想的四元式的定义吧
 * 首先，放弃四个参数都是字符串的形式，因为我们既然有偏移量了，没有必要再用变量名了
 * 然后就会有个问题：(+, 100, 200, 300)，这个300表示内存偏移是没有歧义的，但是前面的100,200，不知道是立即数还是内存偏移量，所以需要一个枚举来区分
 * 输出的时候可以用100和[100]来区分
 * 这样我们就实现了后三个参数都使用int来做了
 * 
 * 目前的四元式
 * (:=, x, siz, a) //a:= x， 类型大小为x
 * += -= *= /=只能对i32使用
 * (+ / - / * / /, a, b, c)
 * (j, 0, 0, to)
 * (jt, a, 0, to) //我觉得不需要j<这类东西，因为实际上是由表达式规约出来的
 * (push, a, siz, 0) //需要带大小的push
 * (call, 0, 0, to) //带ebp esp的跳转
 * (return, a, siz, 0) //把a地址开始，siz大小的内容放到返回值的地方
 * (leave, 0, 0, 0) //退出call
 */

class Semantic
{
public:
    // 语义动作函数指针
    static std::vector<void (Semantic::*)(std::vector<attribute> &, attribute &)> semanticActions;
    // 终结符动作函数指针
    static std::vector<void (Semantic::*)(attribute &)> semanticTerminalActions;

    std::set<functionEntry> functionTable; // 函数表
    std::map<std::string, symbolEntry> symbolTable;     // 符号表，我觉得可以每到一个新函数的时候clear这个表
    // 这里用map有个问题：如果有变量重名，那么销毁一个变量就会全部销毁
    std::stack<symbolEntry> symbolStack;                //模拟那个栈，从后面出站的时候要在符号表里面也删掉
    std::stack<int> c_ebp; //不知道什么时候变，应该是读到{、}的时候？但是也不一定，比如函数传参，并不是ebp，只是表示作用域
    int c_esp = 0; //有用了，需要模拟相对内存位置，是esp
    std::vector<quaternary> codes;           // 中间代码
    std::vector<attribute> attributes;      //把每个语法分析树节点的attr都存下来，与语法分析同步
    const int begin_quad_num = 100;
    int quad_num;
    int nowFunctionRetAddress;

    bool have_error = 0;

    void init();
    void printCodes(std::ostream &out) const;

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
    void act51_(std::vector<attribute> &args, attribute &result);
    void act52_(std::vector<attribute> &args, attribute &result);
    void act53_(std::vector<attribute> &args, attribute &result);
    void act54_(std::vector<attribute> &args, attribute &result);
    void act55_(std::vector<attribute> &args, attribute &result);
    void act56_(std::vector<attribute> &args, attribute &result);
    void act57_(std::vector<attribute> &args, attribute &result);
    void act58_(std::vector<attribute> &args, attribute &result);
    void act59_(std::vector<attribute> &args, attribute &result);
    void act60_(std::vector<attribute> &args, attribute &result);
    void act61_(std::vector<attribute> &args, attribute &result);
    void act62_(std::vector<attribute> &args, attribute &result);
    void act63_(std::vector<attribute> &args, attribute &result);
    void act64_(std::vector<attribute> &args, attribute &result);
    void act65_(std::vector<attribute> &args, attribute &result);
    void act66_(std::vector<attribute> &args, attribute &result);
    void act67_(std::vector<attribute> &args, attribute &result);
    void act68_(std::vector<attribute> &args, attribute &result);
    void act69_(std::vector<attribute> &args, attribute &result);
    void act70_(std::vector<attribute> &args, attribute &result);
    void act71_(std::vector<attribute> &args, attribute &result);
    void act72_(std::vector<attribute> &args, attribute &result);
    void act73_(std::vector<attribute> &args, attribute &result);
    void act74_(std::vector<attribute> &args, attribute &result);
    void act75_(std::vector<attribute> &args, attribute &result);
    void act76_(std::vector<attribute> &args, attribute &result);
    void act77_(std::vector<attribute> &args, attribute &result);
    void act78_(std::vector<attribute> &args, attribute &result);
    void act79_(std::vector<attribute> &args, attribute &result);
    void act80_(std::vector<attribute> &args, attribute &result);
    void act81_(std::vector<attribute> &args, attribute &result);
    void act82_(std::vector<attribute> &args, attribute &result);
    void act83_(std::vector<attribute> &args, attribute &result);
    void act84_(std::vector<attribute> &args, attribute &result);
    void act85_(std::vector<attribute> &args, attribute &result);
    void act86_(std::vector<attribute> &args, attribute &result);
    void act87_(std::vector<attribute> &args, attribute &result);
    void act88_(std::vector<attribute> &args, attribute &result);
    void act89_(std::vector<attribute> &args, attribute &result);
    void act90_(std::vector<attribute> &args, attribute &result);
    void act91_(std::vector<attribute> &args, attribute &result);
    void act92_(std::vector<attribute> &args, attribute &result);
    void act93_(std::vector<attribute> &args, attribute &result);
    void act94_(std::vector<attribute> &args, attribute &result);
    void act95_(std::vector<attribute> &args, attribute &result);
    void act96_(std::vector<attribute> &args, attribute &result);
    void act97_(std::vector<attribute> &args, attribute &result);
    void act98_(std::vector<attribute> &args, attribute &result);
    void act99_(std::vector<attribute> &args, attribute &result);
    void act100_(std::vector<attribute> &args, attribute &result);
    void act101_(std::vector<attribute> &args, attribute &result);
    void act102_(std::vector<attribute> &args, attribute &result);
    void act103_(std::vector<attribute> &args, attribute &result);
    void act104_(std::vector<attribute> &args, attribute &result);
    void act105_(std::vector<attribute> &args, attribute &result);
    void act106_(std::vector<attribute> &args, attribute &result);
    void act107_(std::vector<attribute> &args, attribute &result);
    void act108_(std::vector<attribute> &args, attribute &result);
    void act109_(std::vector<attribute> &args, attribute &result);
    void act110_(std::vector<attribute> &args, attribute &result);
    void act111_(std::vector<attribute> &args, attribute &result);
    void act112_(std::vector<attribute> &args, attribute &result);
    void act113_(std::vector<attribute> &args, attribute &result);
    void act114_(std::vector<attribute> &args, attribute &result);
    void act115_(std::vector<attribute> &args, attribute &result);
    void act116_(std::vector<attribute> &args, attribute &result);
    void act117_(std::vector<attribute> &args, attribute &result);
    void act118_(std::vector<attribute> &args, attribute &result);
    void act119_(std::vector<attribute> &args, attribute &result);
    void act120_(std::vector<attribute> &args, attribute &result);
    void act121_(std::vector<attribute> &args, attribute &result);
    void act122_(std::vector<attribute> &args, attribute &result);
    void act123_(std::vector<attribute> &args, attribute &result);
    void act124_(std::vector<attribute> &args, attribute &result);
    void act125_(std::vector<attribute> &args, attribute &result);
    void act126_(std::vector<attribute> &args, attribute &result);
    void act127_(std::vector<attribute> &args, attribute &result);
    void act128_(std::vector<attribute> &args, attribute &result);
    void act129_(std::vector<attribute> &args, attribute &result);
    void act130_(std::vector<attribute> &args, attribute &result);
    void act131_(std::vector<attribute> &args, attribute &result);
    void act132_(std::vector<attribute> &args, attribute &result);
    void act133_(std::vector<attribute> &args, attribute &result);
    void act134_(std::vector<attribute> &args, attribute &result);
    void act135_(std::vector<attribute> &args, attribute &result);
    void act136_(std::vector<attribute> &args, attribute &result);
    void act137_(std::vector<attribute> &args, attribute &result);
    void act138_(std::vector<attribute> &args, attribute &result);
    void act139_(std::vector<attribute> &args, attribute &result);
    void act140_(std::vector<attribute> &args, attribute &result);
    void act141_(std::vector<attribute> &args, attribute &result);
    void act142_(std::vector<attribute> &args, attribute &result);
    void act143_(std::vector<attribute> &args, attribute &result);
    void act144_(std::vector<attribute> &args, attribute &result);
    void act145_(std::vector<attribute> &args, attribute &result);
    void act146_(std::vector<attribute> &args, attribute &result);
    void act147_(std::vector<attribute> &args, attribute &result);
    void act148_(std::vector<attribute> &args, attribute &result);
    void act149_(std::vector<attribute> &args, attribute &result);
    void act150_(std::vector<attribute> &args, attribute &result);


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