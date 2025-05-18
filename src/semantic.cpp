#include "semantic.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>

// 语义动作函数指针
std::vector<void (Semantic::*)(std::vector<attribute>&, attribute&)> Semantic::semanticActions = {
    &Semantic::act0_, &Semantic::act1_, &Semantic::act2_, &Semantic::act3_, &Semantic::act4_,
    &Semantic::act5_, &Semantic::act6_, &Semantic::act7_, &Semantic::act8_, &Semantic::act9_,
    &Semantic::act10_, &Semantic::act11_, &Semantic::act12_, &Semantic::act13_, &Semantic::act14_,
    &Semantic::act15_, &Semantic::act16_, &Semantic::act17_, &Semantic::act18_, &Semantic::act19_,
    &Semantic::act20_, &Semantic::act21_, &Semantic::act22_, &Semantic::act23_, &Semantic::act24_,
    &Semantic::act25_, &Semantic::act26_, &Semantic::act27_, &Semantic::act28_, &Semantic::act29_,
    &Semantic::act30_, &Semantic::act31_, &Semantic::act32_, &Semantic::act33_, &Semantic::act34_,
    &Semantic::act35_, &Semantic::act36_, &Semantic::act37_, &Semantic::act38_, &Semantic::act39_,
    &Semantic::act40_, &Semantic::act41_, &Semantic::act42_, &Semantic::act43_, &Semantic::act44_,
    &Semantic::act45_, &Semantic::act46_, &Semantic::act47_, &Semantic::act48_, &Semantic::act49_,
    &Semantic::act50_, &Semantic::act51_, &Semantic::act52_, &Semantic::act53_, &Semantic::act54_,
    &Semantic::act55_, &Semantic::act56_, &Semantic::act57_, &Semantic::act58_, &Semantic::act59_,
    &Semantic::act60_, &Semantic::act61_, &Semantic::act62_, &Semantic::act63_, &Semantic::act64_,
    &Semantic::act65_, &Semantic::act66_, &Semantic::act67_, &Semantic::act68_, &Semantic::act69_,
    &Semantic::act70_, &Semantic::act71_, &Semantic::act72_, &Semantic::act73_, &Semantic::act74_,
    &Semantic::act75_, &Semantic::act76_, &Semantic::act77_, &Semantic::act78_, &Semantic::act79_,
    &Semantic::act80_, &Semantic::act81_, &Semantic::act82_, &Semantic::act83_, &Semantic::act84_,
    &Semantic::act85_, &Semantic::act86_, &Semantic::act87_, &Semantic::act88_, &Semantic::act89_,
    &Semantic::act90_, &Semantic::act91_, &Semantic::act92_, &Semantic::act93_, &Semantic::act94_,
    &Semantic::act95_, &Semantic::act96_, &Semantic::act97_, &Semantic::act98_, &Semantic::act99_,
    &Semantic::act100_, &Semantic::act101_, &Semantic::act102_, &Semantic::act103_, &Semantic::act104_,
    &Semantic::act105_, &Semantic::act106_, &Semantic::act107_, &Semantic::act108_, &Semantic::act109_,
    &Semantic::act110_, &Semantic::act111_, &Semantic::act112_, &Semantic::act113_, &Semantic::act114_,
    &Semantic::act115_, &Semantic::act116_, &Semantic::act117_, &Semantic::act118_, &Semantic::act119_,
    &Semantic::act120_, &Semantic::act121_, &Semantic::act122_, &Semantic::act123_, &Semantic::act124_,
    &Semantic::act125_, &Semantic::act126_, &Semantic::act127_, &Semantic::act128_, &Semantic::act129_,
    &Semantic::act130_, &Semantic::act131_, &Semantic::act132_, &Semantic::act133_, &Semantic::act134_,
    &Semantic::act135_, &Semantic::act136_, &Semantic::act137_, &Semantic::act138_, &Semantic::act139_,
    &Semantic::act140_, &Semantic::act141_, &Semantic::act142_, &Semantic::act143_, &Semantic::act144_,
    &Semantic::act145_, &Semantic::act146_, &Semantic::act147_, &Semantic::act148_, &Semantic::act149_,
    &Semantic::act150_
};

std::vector<void (Semantic::*)(attribute&)> Semantic::semanticTerminalActions = {
    &Semantic::tact0_, &Semantic::tact1_, &Semantic::tact2_, &Semantic::tact3_, &Semantic::tact4_,
    &Semantic::tact5_, &Semantic::tact6_, &Semantic::tact7_, &Semantic::tact8_, &Semantic::tact9_,
    &Semantic::tact10_, &Semantic::tact11_, &Semantic::tact12_, &Semantic::tact13_, &Semantic::tact14_,
    &Semantic::tact15_, &Semantic::tact16_, &Semantic::tact17_, &Semantic::tact18_, &Semantic::tact19_,
    &Semantic::tact20_, &Semantic::tact21_, &Semantic::tact22_, &Semantic::tact23_, &Semantic::tact24_,
    &Semantic::tact25_, &Semantic::tact26_, &Semantic::tact27_, &Semantic::tact28_, &Semantic::tact29_,
    &Semantic::tact30_, &Semantic::tact31_, &Semantic::tact32_, &Semantic::tact33_, &Semantic::tact34_,
    &Semantic::tact35_, &Semantic::tact36_, &Semantic::tact37_, &Semantic::tact38_, &Semantic::tact39_,
    &Semantic::tact40_, &Semantic::tact41_, &Semantic::tact42_, &Semantic::tact43_, &Semantic::tact44_,
    &Semantic::tact45_, &Semantic::tact46_, &Semantic::tact47_, &Semantic::tact48_, &Semantic::tact49_,
    &Semantic::tact50_
};

int Semantic::EIPoffset = -4; // 返回eip偏移量
int Semantic::EBPoffset = 0; // 返回ebp偏移量

void Semantic::init()
{
    // quad_num = begin_quad_num;
    codes.resize(begin_quad_num);
}

void Semantic::pushSymbol(symbolEntry sym)
{
    symbolIDTable[sym.name].push_back(symbolStack.size());
    symbolStack.push_back(sym);
}
void Semantic::pushTempSymbol(symbolEntry sym)
{
    tempSymbolIDTable.push_back(sym);
    symbolStack.push_back(sym);
}
void Semantic::popSymbol()
{
    int offset = symbolStack.back().relativeAddress;
    
    if(symbolStack.back().type.readType == TEMPORARY)
    {
        tempSymbolIDTable.pop_back();
    }
    else
    {
        symbolIDTable[symbolStack.back().name].pop_back();
        if(symbolIDTable[symbolStack.back().name].empty())
            symbolIDTable.erase(symbolStack.back().name);
    }
    if (offset >= Semantic::EBPoffset + 4) // 只有非形参才影响esp
        c_esp -= symbolStack.back().type.dataType->siz;
    symbolStack.pop_back();

}
symbolEntry Semantic::getSymbol(const std::string &name) const
{
    if(!symbolIDTable.count(name))
        return symbolEntry{"", element_type{}, 0};
    return symbolStack[symbolIDTable.at(name).back()];
}

void Semantic::printCodes(std::ostream& out) const
{
    for (int i = begin_quad_num; i < (int)codes.size(); i++)
    {
        out << "L" << i << ": ";
        out << codes[i].op << ", ";
        if(codes[i].arg1.type == Offset)
        {
            out << '[' << codes[i].arg1.value << "], ";
        }
        else if (codes[i].arg1.type == Address)
        {
            out << "*[" << codes[i].arg1.value << "], ";
        }
        else if (codes[i].arg1.type == Lable)
        {
            out << 'L' << codes[i].arg1.value << ", ";
        }
        else
        {
            out << codes[i].arg1.value << ", ";
        }
        if (codes[i].arg2.type == Offset)
        {
            out << '[' << codes[i].arg2.value << "], ";
        }
        else if (codes[i].arg2.type == Address)
        {
            out << "*[" << codes[i].arg2.value << "], ";
        }
        else if (codes[i].arg2.type == Lable)
        {
            out << 'L' << codes[i].arg2.value << ", ";
        }
        else
        {
            out << codes[i].arg2.value << ", ";
        }
        if(codes[i].result.type == Offset)
        {
            out << '[' << codes[i].result.value << "]";
        }
        else if (codes[i].result.type == Address)
        {
            out << "*[" << codes[i].result.value << "]";
        }
        else if (codes[i].result.type == Lable)
        {
            out << 'L' << codes[i].result.value;
        }
        else
        {
            out << codes[i].result.value;
        }
        out << std::endl;
    }
}

void Semantic::act0_(std::vector<attribute> &args, attribute &result)
{
    // PROGRAM -> SHENG_MING_CHUAN
    
    // 检查是否含有main函数
    auto func = functionTable.find(functionEntry{0, "main", {}, {}});
    if (func == functionTable.end())
    {
        std::cout << "[ERROR] [SEMANTIC] No main function" << std::endl;
        exit(0);
    }
    
    // 输出中间代码
    const std::string filename = "parse/intermediate.code";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [SEMANTIC] " << filename << " is not exist" << std::endl;
        exit(0);
    }
    // 2 标识结束
    begin_quad_num -= 1;
    codes[begin_quad_num] = quaternary("end", 
        Operand{Literal, 0}, 
        Operand{Literal, 0}, 
        Operand{Literal, 0});

    // 1 跳转main函数 (没有参数和返回值)
    begin_quad_num -= 1;
    codes[begin_quad_num] = quaternary("call", 
        Operand{Literal, 0}, 
        Operand{Literal, 0}, 
        Operand{Lable, func->code_pos});
        
    this->printCodes(fout);

    this->functionTable.clear(); // 清空函数表
    
    fout.close();
}

void Semantic::act1_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act2_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act3_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act4_(std::vector<attribute> &args, attribute &result) {
    // 函数声明 -> 函数头声明 语句块
    // 检查返回类型
    if (!args[1].count("returnType")){
        if (std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"])->type != VOID_TYPE)
        {
            std::cout << "[ERROR] [SEMANTIC] return type \"" << *std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"]) << "\" and \"void\" not match" << std::endl;
            exit(0);
        }
        else
        {
            codes.push_back(quaternary("leave", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}));
            result["returnType"] = args[0]["returnType"];
        }
    }
    else
    {
        if (args[1].count("returnType"))
        {
            if (*std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"]) != *std::any_cast<std::shared_ptr<data_type>>(args[1]["returnType"]))
            {
                std::cout << "[ERROR] [SEMANTIC] return type \"" << *std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"])
                            << "\" and \"" << *std::any_cast<std::shared_ptr<data_type>>(args[1]["returnType"]) << "\" not match" << std::endl;
                exit(0);
            }
        }
        result["returnType"] = args[0]["returnType"];
    }
    // 注意这时在编译中需要把形参pop出去
    int argsnum = std::any_cast<int>(args[0]["symbolNum"]);
    for (int i = 0; i < argsnum; i++)
    {
        popSymbol();
    }

}
void Semantic::act5_(std::vector<attribute> &args, attribute &result) {
    //函数头声明 -> /fn /id /lpra 形参列表 /rpra
    element_type ret_type;
    ret_type.dataType = data_type::create(VOID_TYPE);
    auto para_list = std::any_cast<std::vector<std::pair<element_type, std::string>>>(args[3]["formalParameter"]);
    // 原本是倒过来的
    std::reverse(para_list.begin(), para_list.end());
    std::vector<symbolEntry> para_sym_list;
    // 检查main函数不能有参数
    if (std::any_cast<std::string>(args[1]["name"]) == "main" && !para_list.empty())
    {
        std::cout << "[ERROR] [SEMANTIC] main function can not have parameters" << std::endl;
        exit(0);
    }
    // 从前往后地址不断靠前，实际上要倒着压栈，事实上大部分编译器确实是这么做的
    int offset = EIPoffset;
    for (auto [type, name] : para_list)
    {
        offset -= type.dataType->siz;
        symbolEntry sym{name, type, offset};
        para_sym_list.push_back(sym);
        pushSymbol(sym);
    }
    // 注意这里一定要指明functionEntry类型，不然insert不进去，不知道为什么
    functionTable.insert(functionEntry{(int)this->codes.size(), std::any_cast<std::string>(args[1]["name"]), para_sym_list, symbolEntry{"", ret_type, 0}});
    result["returnType"] = ret_type.dataType;
    result["symbolNum"] = (int)para_list.size();
}
void Semantic::act6_(std::vector<attribute> &args, attribute &result) {
    // 形参列表 -> /zero
    result["formalParameter"] = std::vector<std::pair<element_type, std::string>>{};
}
void Semantic::act7_(std::vector<attribute> &args, attribute &result) {
    // 语句块 -> { 语句串 }
    int num = std::any_cast<int>(args[1]["symbolNum"]);
    std::cerr << num << std::endl;
    std::set<std::string> symName;
    int sizesum = 0;
    for (int i = 0; i < num; i++)
    {
        if(symName.count(symbolStack.back().name))
        {
            std::cout << "[WARN] [SEMANTIC] \"" << symbolStack.back().name << "\" is redeclared" << std::endl;
            // exit(0);
        }
        symName.insert(symbolStack.back().name);
        sizesum += symbolStack.back().type.dataType->siz;
        popSymbol();
    }
    // 生成pop四元式
    if (sizesum > 0)
        codes.push_back(quaternary("pop", Operand{Literal, 0}, Operand{Literal, sizesum}, Operand{Literal, 0}));
    // 返回类型
    if (args[1].count("returnType"))
    {
        result["returnType"] = args[1]["returnType"];
    }
}
void Semantic::act8_(std::vector<attribute> &args, attribute &result) {
    // 语句串 -> /zero
    result["symbolNum"] = 0;
}
void Semantic::act9_(std::vector<attribute> &args, attribute &result) {
    // 语句串 -> 语句 语句串
    int num = 0;
    if(args[0].count("symbolNum"))
        num += std::any_cast<int>(args[0]["symbolNum"]);
    num += std::any_cast<int>(args[1]["symbolNum"]);
    result["symbolNum"] = num;
    // 判断返回类型
    if(args[0].count("returnType"))
    {
        if (args[1].count("returnType"))
        {
            if (*std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"]) != *std::any_cast<std::shared_ptr<data_type>>(args[1]["returnType"]))
            {
                std::cout << "[ERROR] [SEMANTIC] return type \"" << *std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"])
                          << "\" and \"" << *std::any_cast<std::shared_ptr<data_type>>(args[1]["returnType"]) << "\" not match" << std::endl;
                exit(0);
            }
        }
        result["returnType"] = args[0]["returnType"];
    }
    else if (args[1].count("returnType"))
    {
        
        result["returnType"] = args[1]["returnType"];
    }

}
void Semantic::act10_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> 语句块
    result = args[0];
}
void Semantic::act11_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> 返回语句
    result = args[0];
}
void Semantic::act12_(std::vector<attribute> &args, attribute &result) {
    // 返回语句 -> /return /;
    this->codes.push_back(quaternary("leave", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}));
    
    result["returnType"] = data_type::create(VOID_TYPE);
}
void Semantic::act13_(std::vector<attribute> &args, attribute &result) {
    // 变量声明内部 -> /mut /id
    result["name"] = args[1]["name"]; // 这里左右都是std::any，就可以直接赋值，不用cast
    result["readType"] = VARIABLE;
}
void Semantic::act14_(std::vector<attribute> &args, attribute &result) {
    // 类型 -> i32
    result["dataType"] = data_type::create(I32_TYPE);
}
void Semantic::act15_(std::vector<attribute> &args, attribute &result) {
    // 形参列表 -> 形参
    std::vector<std::pair<element_type, std::string>> para_list;
    para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]), std::any_cast<std::string>(args[0]["name"])));
    result["formalParameter"] = para_list;
}
void Semantic::act16_(std::vector<attribute> &args, attribute &result) {
    // 形参列表 -> 形参 , 形参列表
    auto n_para_list = std::any_cast<std::vector<std::pair<element_type, std::string>>>(args[2]["formalParameter"]);
    n_para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]), std::any_cast<std::string>(args[0]["name"])));
    result["formalParameter"] = n_para_list; // 倒着插入的
}
void Semantic::act17_(std::vector<attribute> &args, attribute &result) {
    // 形参 -> 变量声明内部 : 类型
    element_type ele_type;
    ele_type.dataType = std::any_cast<std::shared_ptr<data_type>>(args[2]["dataType"]);
    ele_type.readType = std::any_cast<read_type>(args[0]["readType"]);
    std::string name = std::any_cast<std::string>(args[0]["name"]);
    //这里好像无法得知偏移量，所以只是一个属性而已，真正分配偏移量到函数头声明再做
    result["elementType"] = ele_type;
    result["name"] = name;
}
void Semantic::act18_(std::vector<attribute> &args, attribute &result) {
    //函数头声明 -> /fn /id ( 形参列表 ) -> 类型
    element_type ret_type;
    ret_type.dataType = std::any_cast<std::shared_ptr<data_type>>(args[6]["dataType"]);
    auto para_list = std::any_cast<std::vector<std::pair<element_type, std::string>>>(args[3]["formalParameter"]);
    // 原本是倒过来的
    std::reverse(para_list.begin(), para_list.end());
    std::vector<symbolEntry> para_sym_list;
    // 检查main函数不能有返回值
    if (std::any_cast<std::string>(args[1]["name"]) == "main")
    {
        std::cout << "[ERROR] [SEMANTIC] main function can not have return type" << std::endl;
        exit(0);
    }
    // 从前往后地址不断靠前，实际上要倒着压栈，事实上大部分编译器确实是这么做的
    int offset = EIPoffset;
    for (auto [type, name] : para_list)
    {
        offset -= type.dataType->siz;
        symbolEntry sym{name, type, offset};
        para_sym_list.push_back(sym);
        pushSymbol(sym);
    }
    symbolEntry ret_sym{"", ret_type, 0};
    offset -= ret_type.dataType->siz;
    ret_sym.relativeAddress = offset;
    nowFunctionRetAddress = offset;
    // 注意这里一定要指明functionEntry类型，不然insert不进去，不知道为什么
    functionTable.insert(functionEntry{(int)this->codes.size(), std::any_cast<std::string>(args[1]["name"]), para_sym_list, ret_sym});
    result["returnType"] = ret_type.dataType;
    result["symbolNum"] = (int)para_list.size();
}
void Semantic::act19_(std::vector<attribute> &args, attribute &result) {
    // 返回语句 -> /return 表达式 /;
    if (std::any_cast<element_type>(args[1]["elementType"]).readType == LITERAL)
    {
        this->codes.push_back(quaternary("return",
            Operand{Literal, std::any_cast<int>(args[1]["val"])},
            Operand{Literal, std::any_cast<element_type>(args[1]["elementType"]).dataType->siz},
            Operand{Offset, this->nowFunctionRetAddress}));
        this->codes.push_back(quaternary("leave", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}));
    }
    else if (args[1].count("address"))
    {
        this->codes.push_back(quaternary("return",
            Operand{Offset, std::any_cast<int>(args[1]["address"])},
            Operand{Literal, std::any_cast<element_type>(args[1]["elementType"]).dataType->siz},
            Operand{Offset, this->nowFunctionRetAddress}));
        this->codes.push_back(quaternary("leave", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}));
    }
    else
    {
        this->codes.push_back(quaternary("return",
            Operand{Address, std::any_cast<int>(args[1]["absoluteAddress"])},
            Operand{Literal, std::any_cast<element_type>(args[1]["elementType"]).dataType->siz},
            Operand{Offset, this->nowFunctionRetAddress}));
        this->codes.push_back(quaternary("leave", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}));
    }
    

    result["returnType"] = std::any_cast<element_type>(args[1]["elementType"]).dataType;
    // 可能有临时变量
    result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]);
}
void Semantic::act20_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> 变量声明语句
    int num = std::any_cast<int>(args[0]["symbolNum"]);
    result["symbolNum"] = num;
}
void Semantic::act21_(std::vector<attribute> &args, attribute &result) {
    // 变量声明语句 -> /let 变量声明内部 /colon 类型 /semicolon
    element_type ele_type;
    ele_type.dataType = std::any_cast<std::shared_ptr<data_type>>(args[3]["dataType"]);
    ele_type.readType = std::any_cast<read_type>(args[1]["readType"]);
    std::string name = std::any_cast<std::string>(args[1]["name"]);
    //声明一个变量
    symbolEntry sym;
    sym.name = name, sym.type = ele_type;
    sym.relativeAddress = c_esp;
    c_esp += ele_type.dataType->siz;
    pushSymbol(sym);
    result["symbolNum"] = 1;
    
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, ele_type.dataType->siz}, Operand{Literal, 0}));
}
void Semantic::act22_(std::vector<attribute> &args, attribute &result) {
    // 变量声明语句 -> /let 变量声明内部 /semicolon
    std::cout << "[ERROR] [SEMANTIC] Type inference is not supported" << std::endl;
    exit(0);
    // element_type ele_type;
    // ele_type.dataType = NULL;
    // ele_type.readType = std::any_cast<read_type>(args[1]["readType"]);
    // std::string name = std::any_cast<std::string>(args[1]["name"]);
    // // 声明一个变量
    // symbolEntry sym;
    // sym.name = name, sym.type = ele_type;
    // sym.relativeAddress = EBPoffset; // 无用
    // pushSymbol(sym);
    // result["symbolNum"] = 1;
}
void Semantic::act23_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> 赋值语句
    result = args[0];
}
void Semantic::act24_(std::vector<attribute> &args, attribute &result) {
    // 赋值语句 -> 表达式 赋值元素 表达式 /;

    if (std::any_cast<element_type>(args[0]["elementType"]).readType != VARIABLE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not variable." << std::endl;
        exit(0);
    }
    
    // // 检查变量是否有数据类型(是否分配了地址)
    // if (std::any_cast<int>(args[0]["address"]) == Semantic::EBPoffset)
    // {
    //     if (std::any_cast<std::string>(args[1]["opSymbol"]) != ":=") {
    //         std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" does not have data type." << std::endl;
    //         exit(0);
    //     }
    //     // 分配地址和推断类型
    //     args[0]["address"] = c_esp;
        
    //     int symid = this->symbolIDTable[std::any_cast<std::string>(args[0]["name"])].back();
    //     this->symbolStack[symid].relativeAddress = c_esp;
    //     this->symbolStack[symid].type.dataType = (std::any_cast<element_type>(args[2]["elementType"])).dataType;
        
    //     codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, this->symbolStack[symid].type.dataType->siz}, Operand{Literal, 0}));
        
        
    //     c_esp += std::any_cast<element_type>(args[2]["elementType"]).dataType->siz;
    // }
    else if (*std::any_cast<element_type>(args[0]["elementType"]).dataType != 
        *std::any_cast<element_type>(args[2]["elementType"]).dataType)//注意取*再比较
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" and " << "\"" << std::any_cast<std::string>(args[2]["name"]) << "\" are not same type" << std::endl;
        exit(0);
    }
    
    if (std::any_cast<std::string>(args[1]["opSymbol"]) == ":=")
    {
        // 运算四元式
        quaternary quat;
        quat.op = ":=";
        if (std::any_cast<element_type>(args[2]["elementType"]).readType == LITERAL)
            quat.arg1 = Operand{Literal, std::any_cast<int>(args[2]["val"])};
        else if (args[2].count("address"))
            quat.arg1 = Operand{Offset, std::any_cast<int>(args[2]["address"])};
        else
            quat.arg1 = Operand{Address, std::any_cast<int>(args[2]["absoluteAddress"])};

        quat.arg2 = Operand{Literal, std::any_cast<element_type>(args[2]["elementType"]).dataType->siz};
        
        if (args[0].count("address"))
            quat.result = Operand{Offset, std::any_cast<int>(args[0]["address"])};
        else
            quat.result = Operand{Address, std::any_cast<int>(args[0]["absoluteAddress"])};
        codes.push_back(quat);
    }
    else
    {
        if(std::any_cast<element_type>(args[0]["elementType"]).dataType->type != I32_TYPE)
        {
            std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not a INT " << std::endl;
            exit(0);
        }
        // 运算四元式
        quaternary quat;
        quat.op = std::any_cast<std::string>(std::any_cast<std::string>(args[1]["opSymbol"]));
        if (std::any_cast<element_type>(args[2]["elementType"]).readType == LITERAL)
            quat.arg1 = Operand{Literal, std::any_cast<int>(args[2]["val"])};
        else if (args[2].count("address"))
            quat.arg1 = Operand{Offset, std::any_cast<int>(args[2]["address"])};
        else
            quat.arg1 = Operand{Address, std::any_cast<int>(args[2]["absoluteAddress"])};

        quat.arg2 = Operand{Literal, 0};

        if (args[0].count("address"))
            quat.result = Operand{Offset, std::any_cast<int>(args[0]["address"])};
        else
            quat.result = Operand{Address, std::any_cast<int>(args[0]["absoluteAddress"])};
        codes.push_back(quat);
        
    }
    result = args[0];
    // 可能有临时变量计数 + 临时变量计数
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
}
void Semantic::act25_(std::vector<attribute> &args, attribute &result) {
    // 赋值元素 -> /=
    result["opSymbol"] = (std::string)":=";
}
void Semantic::act26_(std::vector<attribute> &args, attribute &result) {
    // 赋值元素 -> / +=
    result["opSymbol"] = (std::string)"+=";
}
void Semantic::act27_(std::vector<attribute> &args, attribute &result) {
    // 赋值元素 -> / -=
    result["opSymbol"] = (std::string)"-=";
}
void Semantic::act28_(std::vector<attribute> &args, attribute &result) {
    // 赋值元素 -> / *=
    result["opSymbol"] = (std::string)"*=";
}
void Semantic::act29_(std::vector<attribute> &args, attribute &result) {
    // 赋值元素 -> / /=
    result["opSymbol"] = (std::string)"/=";
}
void Semantic::act30_(std::vector<attribute> &args, attribute &result) {
    // 赋值元素 -> / %=
    result["opSymbol"] = (std::string)"%=";
}
void Semantic::act31_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> 变量声明赋值语句
    int num = std::any_cast<int>(args[0]["symbolNum"]);
    result["symbolNum"] = num;
}
void Semantic::act32_(std::vector<attribute> &args, attribute &result) {
    // 变量声明赋值语句 -> /let 变量声明内部 /colon 类型 = 表达式 /semicolon
    element_type ele_type;
    ele_type.dataType = std::any_cast<std::shared_ptr<data_type>>(args[3]["dataType"]);
    ele_type.readType = std::any_cast<read_type>(args[1]["readType"]);
    std::string name = std::any_cast<std::string>(args[1]["name"]);
    //声明一个变量
    symbolEntry sym;
    sym.name = name, sym.type = ele_type;
    sym.relativeAddress = c_esp;
    c_esp += ele_type.dataType->siz;
    pushSymbol(sym);

    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, ele_type.dataType->siz}, Operand{Literal, 0}));
    
    //赋值
    if(*sym.type.dataType != *std::any_cast<element_type>(args[5]["elementType"]).dataType)//注意取*再比较
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(sym.name) 
        << "\":" << *sym.type.dataType << " and " << "\"" << std::any_cast<std::string>(args[5]["name"]) << "\":"
        << *std::any_cast<element_type>(args[5]["elementType"]).dataType << " are not same type" << std::endl;
        exit(0);
    }
    // 运算四元式
    quaternary quat;
    quat.op = ":=";
    if (std::any_cast<element_type>(args[5]["elementType"]).readType == LITERAL)
        quat.arg1 = Operand{Literal, std::any_cast<int>(args[5]["val"])};
    else if (args[5].count("address"))
        quat.arg1 = Operand{Offset, std::any_cast<int>(args[5]["address"])};
    else
        quat.arg1 = Operand{Address, std::any_cast<int>(args[5]["absoluteAddress"])};

    quat.arg2 = Operand{Literal, sym.type.dataType->siz};

    quat.result = Operand{Offset, sym.relativeAddress};
    codes.push_back(quat);
    
    // 可能有临时变量计数 + 声明变量
    result["symbolNum"] = std::any_cast<int>(args[5]["symbolNum"]) + 1;
}
void Semantic::act33_(std::vector<attribute> &args, attribute &result) {
    // 变量声明赋值语句 -> /let 变量声明内部 = 表达式 /semicolon
    element_type ele_type;
    ele_type.dataType = std::any_cast<element_type>(args[3]["elementType"]).dataType;
    ele_type.readType = std::any_cast<read_type>(args[1]["readType"]);
    std::string name = std::any_cast<std::string>(args[1]["name"]);
    //声明一个变量
    symbolEntry sym;
    sym.name = name, sym.type = ele_type;
    sym.relativeAddress = c_esp;
    c_esp += ele_type.dataType->siz;
    pushSymbol(sym);

    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, ele_type.dataType->siz}, Operand{Literal, 0}));

    // 运算四元式
    quaternary quat;
    quat.op = ":=";
    if (std::any_cast<element_type>(args[3]["elementType"]).readType == LITERAL)
        quat.arg1 = Operand{Literal, std::any_cast<int>(args[3]["val"])};
    else if (args[3].count("address"))
        quat.arg1 = Operand{Offset, std::any_cast<int>(args[3]["address"])};
    else
        quat.arg1 = Operand{Address, std::any_cast<int>(args[3]["absoluteAddress"])};

    quat.arg2 = Operand{Literal, sym.type.dataType->siz};

    quat.result = Operand{Offset, sym.relativeAddress};
    codes.push_back(quat);
    // 可能有临时变量计数 + 声明变量
    result["symbolNum"] = std::any_cast<int>(args[3]["symbolNum"]) + 1;
}
void Semantic::act34_(std::vector<attribute> &args, attribute &result) 
{
    // 可能有临时变量计数
    if (args[0].count("symbolNum"))
    {
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]);
    }
}
void Semantic::act35_(std::vector<attribute> &args, attribute &result)
{
    // 表达式 -> OR表达式
    result = args[0];
}
void Semantic::act36_(std::vector<attribute> &args, attribute &result)
{
    // OR表达式 -> AND表达式
    result = args[0];
}
void Semantic::act37_(std::vector<attribute> &args, attribute &result) {
    // AND表达式 -> 加法表达式
    result = args[0];
}
void Semantic::act38_(std::vector<attribute> &args, attribute &result) {
    //加法表达式 -> 项
    result = args[0];
}
void Semantic::act39_(std::vector<attribute> &args, attribute &result) {
    //项 -> 因子
    result = args[0];
}
void Semantic::act40_(std::vector<attribute> &args, attribute &result) {
    //因子 -> 元素
    result = args[0];
}
void Semantic::act41_(std::vector<attribute> &args, attribute &result) {
    //元素 -> /int
    result = args[0];
    result["symbolNum"] = 0;
}
void Semantic::act42_(std::vector<attribute> &args, attribute &result) {
    //元素 -> /id
    symbolEntry sym = getSymbol(std::any_cast<std::string>(args[0]["name"]));
    if (sym.type.readType == NONETYPE)
    {
        // 检查是否是函数名
        if (!this->functionTable.count(functionEntry{0, std::any_cast<std::string>(args[0]["name"]), {}, {}}))
        {
            result["name"] = args[0]["name"];
            result["elementType"] = element_type{data_type::create(FUN_TYPE), NONETYPE};
            return;
        }

        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not declared." << std::endl;
        exit(0);
    }
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    result["symbolNum"] = 0;
}
void Semantic::act43_(std::vector<attribute> &args, attribute &result) {
    // 元素 -> ( 表达式 )
    result = args[1];
}
void Semantic::act44_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act45_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act46_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act47_(std::vector<attribute> &args, attribute &result) {
    // 加法表达式 -> 加法表达式 +/- 项
    if(std::any_cast<element_type>(args[0]["elementType"]).dataType->type != I32_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not a int." << std::endl;
        exit(0);
    }
    if(std::any_cast<element_type>(args[2]["elementType"]).dataType->type != I32_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[2]["name"]) << "\" is not a int." << std::endl;
        exit(0);
    }
    // 声明临时变量
    symbolEntry sym;
    // 优化：如果两个中有一个是临时变量，结果直接用临时变量的地址
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == TEMPORARY)
    {
        sym.name = std::any_cast<std::string>(args[0]["name"]);
        sym.type = std::any_cast<element_type>(args[0]["elementType"]);
        sym.relativeAddress = std::any_cast<int>(args[0]["address"]);
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
    }
    else if (std::any_cast<element_type>(args[2]["elementType"]).readType == TEMPORARY)
    {
        sym.name = std::any_cast<std::string>(args[2]["name"]);
        sym.type = std::any_cast<element_type>(args[2]["elementType"]);
        sym.relativeAddress = std::any_cast<int>(args[2]["address"]);
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
    }
    else
    {
        // 声明临时变量
        sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
        sym.type.dataType = data_type::create(I32_TYPE);
        sym.type.readType = TEMPORARY;
        sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += 4;
        pushTempSymbol(sym);
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]) + 1;
    }
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    // 运算四元式
    quaternary quat;
    quat.op = std::any_cast<std::string>(args[1]["opSymbol"]);
    if(std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
        quat.arg1 = Operand{Literal, std::any_cast<int>(args[0]["val"])};
    else if (args[0].count("address"))
        quat.arg1 = Operand{Offset, std::any_cast<int>(args[0]["address"])};
    else
        quat.arg1 = Operand{Address, std::any_cast<int>(args[0]["absoluteAddress"])};
    if(std::any_cast<element_type>(args[2]["elementType"]).readType == LITERAL)
        quat.arg2 = Operand{Literal, std::any_cast<int>(args[2]["val"])};
    else if (args[2].count("address"))
        quat.arg2 = Operand{Offset, std::any_cast<int>(args[2]["address"])};
    else
        quat.arg2 = Operand{Address, std::any_cast<int>(args[2]["absoluteAddress"])};
    quat.result = Operand{Offset, sym.relativeAddress};
    codes.push_back(quat);
}
void Semantic::act48_(std::vector<attribute> &args, attribute &result) {
    // 项 -> 项 * / % 因子
    if(std::any_cast<element_type>(args[0]["elementType"]).dataType->type != I32_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not a int." << std::endl;
        exit(0);
    }
    if(std::any_cast<element_type>(args[2]["elementType"]).dataType->type != I32_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[2]["name"]) << "\" is not a int." << std::endl;
        exit(0);
    }
    // 声明临时变量
    symbolEntry sym;
    // 优化：如果两个中有一个是临时变量，结果直接用临时变量的地址
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == TEMPORARY)
    {
        sym.name = std::any_cast<std::string>(args[0]["name"]);
        sym.type = std::any_cast<element_type>(args[0]["elementType"]);
        sym.relativeAddress = std::any_cast<int>(args[0]["address"]);
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
    }
    else if (std::any_cast<element_type>(args[2]["elementType"]).readType == TEMPORARY)
    {
        sym.name = std::any_cast<std::string>(args[2]["name"]);
        sym.type = std::any_cast<element_type>(args[2]["elementType"]);
        sym.relativeAddress = std::any_cast<int>(args[2]["address"]);
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
    }
    else
    {
        // 声明临时变量
        sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
        sym.type.dataType = data_type::create(I32_TYPE);
        sym.type.readType = TEMPORARY;
        sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += 4;
        pushTempSymbol(sym);
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]) + 1;
    }
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    // 运算四元式
    quaternary quat;
    quat.op = std::any_cast<std::string>(args[1]["opSymbol"]);
    if(std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
        quat.arg1 = Operand{Literal, std::any_cast<int>(args[0]["val"])};
    else if (args[0].count("address"))
        quat.arg1 = Operand{Offset, std::any_cast<int>(args[0]["address"])};
    else 
        quat.arg1 = Operand{Address, std::any_cast<int>(args[0]["absoluteAddress"])};
    if(std::any_cast<element_type>(args[2]["elementType"]).readType == LITERAL)
        quat.arg2 = Operand{Literal, std::any_cast<int>(args[2]["val"])};
    else if (args[2].count("address"))
        quat.arg2 = Operand{Offset, std::any_cast<int>(args[2]["address"])};
    else
        quat.arg2 = Operand{Address, std::any_cast<int>(args[2]["absoluteAddress"])};
    quat.result = Operand{Offset, sym.relativeAddress};
    codes.push_back(quat);
}
void Semantic::act49_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act50_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act51_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act52_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act53_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act54_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act55_(std::vector<attribute> &args, attribute &result) {
    //+/- -> +
    result["opSymbol"] = (std::string)"+";
}
void Semantic::act56_(std::vector<attribute> &args, attribute &result) {
    //+/- -> -
    result["opSymbol"] = (std::string)"-";
}
void Semantic::act57_(std::vector<attribute> &args, attribute &result) {
    //*///% -> *
    result["opSymbol"] = (std::string)"*";
}
void Semantic::act58_(std::vector<attribute> &args, attribute &result) {
    //*///% -> /
    result["opSymbol"] = (std::string)"/";
}
void Semantic::act59_(std::vector<attribute> &args, attribute &result) {
    //*///% -> %
    result["opSymbol"] = (std::string)"%";
}
void Semantic::act60_(std::vector<attribute> &args, attribute &result) {
    // 因子 -> /- 因子
    if (std::any_cast<element_type>(args[1]["elementType"]).dataType->type != I32_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[1]["name"]) << "\" is not a int." << std::endl;
        exit(0);
    }
    // 声明临时变量
    symbolEntry sym;
    // 优化：如果有一个是临时变量，结果直接用临时变量的地址
    if (std::any_cast<element_type>(args[1]["elementType"]).readType == TEMPORARY)
    {
        sym.name = std::any_cast<std::string>(args[1]["name"]);
        sym.type = std::any_cast<element_type>(args[1]["elementType"]);
        sym.relativeAddress = std::any_cast<int>(args[1]["address"]);
        result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]);
    }
    else
    {
        // 声明临时变量
        sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
        sym.type.dataType = data_type::create(I32_TYPE);
        sym.type.readType = TEMPORARY;
        sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += 4;
        pushTempSymbol(sym);
        result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]) + 1;
    }
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    // 运算四元式
    quaternary quat;
    quat.op = "-";
    quat.arg1 = Operand{Literal, 0};
    if (std::any_cast<element_type>(args[1]["elementType"]).readType == LITERAL)
        quat.arg2 = Operand{Literal, std::any_cast<int>(args[1]["val"])};
    else if (args[1].count("address"))
        quat.arg2 = Operand{Offset, std::any_cast<int>(args[1]["address"])};
    else
        quat.arg2 = Operand{Address, std::any_cast<int>(args[1]["absoluteAddress"])};
    quat.result = Operand{Offset, sym.relativeAddress};
    codes.push_back(quat);
}
void Semantic::act61_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act62_(std::vector<attribute> &args, attribute &result) {
    // 元素->/id /( 实参列表 /)
    
    if (std::any_cast<std::string>(args[0]["name"]) == "main")
    {
        std::cout << "[ERROR] [SEMANTIC] function \"main\" is not callable." << std::endl;
        exit(0);
    }
    // 检查函数是否存在
    if (!this->functionTable.count(functionEntry{0, std::any_cast<std::string>(args[0]["name"]), {}, {}}))
    {
        std::cout << "[ERROR] [SEMANTIC] function \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not declared." << std::endl;
        exit(0);
    }
    
    auto func = this->functionTable.find(functionEntry{0, std::any_cast<std::string>(args[0]["name"]), {}, {}});
    // 为返回值申请临时变量
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = func->returnType.type.dataType;
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp;
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
    c_esp += 4;
    pushTempSymbol(sym);
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    // 实参列表也可能有临时变量计数
    result["symbolNum"] = std::any_cast<int>(args[2]["symbolNum"]) + 1;

    // 检查参数个数类型匹配
    auto para_list = std::any_cast<std::vector<std::pair<element_type, std::pair<bool, int>>>>(args[2]["actualParameter"]);
    if (func->argsTypes.size() != para_list.size())
    {
        std::cout << "[ERROR] [SEMANTIC] function \"" << std::any_cast<std::string>(args[0]["name"]) 
        << "\" expected " << func->argsTypes.size() << " parameters, but got " << para_list.size() << "." << std::endl;
        exit(0);
    }
    // 原本是倒过来的,但是我本来就是要倒着压栈
    int argsnum = func->argsTypes.size();
    for (int i = 0; i < argsnum; i++)
    {
        if (*func->argsTypes[argsnum - i - 1].type.dataType != *para_list[i].first.dataType)
        {
            std::cout << "[ERROR] [SEMANTIC] function \"" << std::any_cast<std::string>(args[0]["name"]) 
            << "\" expected " << *func->argsTypes[argsnum - i - 1].type.dataType << ", but got " << *para_list[i].first.dataType << "." << std::endl;
            exit(0);
        }
        if (para_list[i].first.readType == LITERAL)
        {
            codes.push_back(quaternary("push", Operand{Literal, para_list[i].second.second}, Operand{Literal, para_list[i].first.dataType->siz}, Operand{Literal, 0}));
        }
        else if (para_list[i].second.first)
        {
            codes.push_back(quaternary("push", Operand{Address, para_list[i].second.second}, Operand{Literal, para_list[i].first.dataType->siz}, Operand{Literal, 0}));
        }
        else
        {
            codes.push_back(quaternary("push", Operand{Offset, para_list[i].second.second}, Operand{Literal, para_list[i].first.dataType->siz}, Operand{Literal, 0}));
        }
    }
    // 调用函数
    codes.push_back(quaternary("call", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, func->code_pos}));
    // pop实参
    for (int i = 0; i < argsnum; i++)
    {
        codes.push_back(quaternary("pop", Operand{Literal, 0}, Operand{Literal, para_list[i].first.dataType->siz}, Operand{Literal, 0}));
    }
    
}
void Semantic::act63_(std::vector<attribute> &args, attribute &result) {
    // 实参列表 -> 空
    std::vector<std::pair<element_type, std::pair<bool, int>>> para_list; // bool 是否为绝对地址 int 是字面量的值或偏移量
    result["actualParameter"] = para_list;
    result["symbolNum"] = 0;
}
void Semantic::act64_(std::vector<attribute> &args, attribute &result) {
    // 实参列表 -> 表达式
    std::vector<std::pair<element_type, std::pair<bool, int>>> para_list; // bool 是否为绝对地址 int 是字面量的值或偏移量
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
    {
        para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]), 
        std::make_pair(false, std::any_cast<int>(args[0]["val"]))));
    }
    else if (args[0].count("address"))
    {
        para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["address"]))));
    }
    else
    {
        para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(true, std::any_cast<int>(args[0]["absoluteAddress"]))));
    }
    result["actualParameter"] = para_list;
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]);
}
void Semantic::act65_(std::vector<attribute> &args, attribute &result) {
    // 实参列表 -> 表达式 /, 实参列表
    auto n_para_list = std::any_cast<std::vector<std::pair<element_type, std::pair<bool, int>>>>(args[2]["actualParameter"]);
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
    {
        n_para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["val"]))));
    }
    else if (args[0].count("address"))
    {
        n_para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["address"]))));
    }
    else
    {
        n_para_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(true, std::any_cast<int>(args[0]["absoluteAddress"]))));
    }
    result["actualParameter"] = n_para_list; // 倒着插入的
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
}
void Semantic::act66_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act67_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act68_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act69_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act70_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act71_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act72_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act73_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act74_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act75_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act76_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act77_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act78_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act79_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act80_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act81_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act82_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act83_(std::vector<attribute> &args, attribute &result) {
    // 因子 -> /* 因子
    // 检查是否可以解引用
    if (std::any_cast<element_type>(args[1]["elementType"]).dataType->type != REFER_TYPE
        && std::any_cast<element_type>(args[1]["elementType"]).dataType->type != MUT_REFER_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[1]["name"]) << "\" is not a reference." << std::endl;
        exit(0);
    }

    element_type result_type;
    if (std::any_cast<element_type>(args[1]["elementType"]).dataType->type == REFER_TYPE)
    {
        result_type.readType = CONSTANT;
    }
    else if (std::any_cast<element_type>(args[1]["elementType"]).dataType->type == MUT_REFER_TYPE)
    {
        result_type.readType = VARIABLE;
    }
    result_type.dataType = std::any_cast<element_type>(args[1]["elementType"]).dataType->get_sub_class(0);

    result["elementType"] = result_type;

    symbolEntry tempsym;
    if (args[1].count("address"))
    {
        result["absoluteAddress"] = std::any_cast<int>(args[1]["address"]);
        result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]);
        result["name"] = "* " + std::any_cast<std::string>(args[1]["name"]);
    }
    else
    {
        // 这表示上一个因子也是解引用 申请新临时变量存放一次解引用地址
        // 声明临时变量
        symbolEntry temp_sym;
        temp_sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
        temp_sym.type.dataType = std::any_cast<element_type>(args[1]["elementType"]).dataType;
        temp_sym.type.readType = TEMPORARY;
        temp_sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, temp_sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += 4;
        pushTempSymbol(temp_sym);

        result["absoluteAddress"] = temp_sym.relativeAddress;
        result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]) + 1;
        result["name"] = temp_sym.name;
        // 四元式
        quaternary quat;
        quat.op = ":=";
        quat.arg1 = Operand{Address, std::any_cast<int>(args[1]["absoluteAddress"])};
        quat.arg2 = Operand{Literal, 4};
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);
    }
}
void Semantic::act84_(std::vector<attribute> &args, attribute &result) {
    // 因子 -> /& /mut 因子
    // 检查是否可以可变引用
    if (std::any_cast<element_type>(args[2]["elementType"]).readType != VARIABLE 
        && std::any_cast<element_type>(args[2]["elementType"]).readType != TEMPORARY)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[2]["name"]) << "\" can not be mut reference." << std::endl;
        exit(0);
    }
    // 声明临时变量
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = data_type::create(MUT_REFER_TYPE, std::any_cast<element_type>(args[2]["elementType"]).dataType);
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp;
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
    c_esp += 4;
    pushTempSymbol(sym);
    result["symbolNum"] = std::any_cast<int>(args[2]["symbolNum"]) + 1;
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    // 运算四元式
    quaternary quat;
    if (args[2].count("address"))
    {
        quat.op = "sea";
        quat.arg1 = Operand{Literal, std::any_cast<int>(args[2]["address"])};
        quat.arg2 = Operand{Literal, 0};
        quat.result = Operand{Offset, sym.relativeAddress};
    }
    else
    {
        quat.op = ":=";
        quat.arg1 = Operand{Offset, std::any_cast<int>(args[2]["absoluteAddress"])};
        quat.arg2 = Operand{Literal, 4};
        quat.result = Operand{Offset, sym.relativeAddress};
    }
        
    codes.push_back(quat);
}
void Semantic::act85_(std::vector<attribute> &args, attribute &result) {
    // 因子 -> /& 因子
    // 检查是否可以引用
    if (std::any_cast<element_type>(args[1]["elementType"]).readType != VARIABLE &&
     std::any_cast<element_type>(args[1]["elementType"]).readType != TEMPORARY &&
     std::any_cast<element_type>(args[1]["elementType"]).readType != CONSTANT)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[1]["name"]) << "\" can not be reference." << std::endl;
        exit(0);
    }
    // 声明临时变量
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = data_type::create(REFER_TYPE, std::any_cast<element_type>(args[1]["elementType"]).dataType);
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp;
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
    c_esp += 4;
    pushTempSymbol(sym);
    result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]) + 1;
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    // 运算四元式
    quaternary quat;
    if (args[1].count("address"))
    {
        quat.op = "sea";
        quat.arg1 = Operand{Literal, std::any_cast<int>(args[1]["address"])};
        quat.arg2 = Operand{Literal, 0};
        quat.result = Operand{Offset, sym.relativeAddress};
    }
    else
    {
        quat.op = ":=";
        quat.arg1 = Operand{Offset, std::any_cast<int>(args[1]["absoluteAddress"])};
        quat.arg2 = Operand{Literal, 4};
        quat.result = Operand{Offset, sym.relativeAddress};
    }

    codes.push_back(quat);
}
void Semantic::act86_(std::vector<attribute> &args, attribute &result)
{
    // 类型 -> /& /mut 类型
    result["dataType"] = data_type::create(MUT_REFER_TYPE, std::any_cast<std::shared_ptr<data_type>>(args[2]["dataType"]));
}
void Semantic::act87_(std::vector<attribute> &args, attribute &result) {
    // 类型 -> /& 类型
    result["dataType"] = data_type::create(REFER_TYPE, std::any_cast<std::shared_ptr<data_type>>(args[1]["dataType"]));
}
void Semantic::act88_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act89_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act90_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act91_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act92_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act93_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act94_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act95_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act96_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act97_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act98_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act99_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act100_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act101_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act102_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act103_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act104_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act105_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act106_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act107_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act108_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act109_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act110_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act111_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act112_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act113_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act114_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act115_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act116_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act117_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act118_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act119_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act120_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act121_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act122_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act123_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act124_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act125_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act126_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act127_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act128_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act129_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act130_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act131_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act132_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act133_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act134_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act135_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act136_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act137_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act138_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act139_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act140_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act141_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act142_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act143_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act144_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act145_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act146_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act147_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act148_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act149_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act150_(std::vector<attribute> &args, attribute &result) {}



void Semantic::tact0_(attribute &result) {}
void Semantic::tact1_(attribute &result) {}
void Semantic::tact2_(attribute &result) {}
void Semantic::tact3_(attribute &result) {}
void Semantic::tact4_(attribute &result) {}
void Semantic::tact5_(attribute &result) {}
void Semantic::tact6_(attribute &result) {}
void Semantic::tact7_(attribute &result) {}
void Semantic::tact8_(attribute &result) {}
void Semantic::tact9_(attribute &result) {}
void Semantic::tact10_(attribute &result) {}
void Semantic::tact11_(attribute &result) {}
void Semantic::tact12_(attribute &result) {}
void Semantic::tact13_(attribute &result) {}
void Semantic::tact14_(attribute &result) {}
void Semantic::tact15_(attribute &result) {}
void Semantic::tact16_(attribute &result) {}
void Semantic::tact17_(attribute &result) {}
void Semantic::tact18_(attribute &result) {}
void Semantic::tact19_(attribute &result) {}
void Semantic::tact20_(attribute &result) {}
void Semantic::tact21_(attribute &result) {}
void Semantic::tact22_(attribute &result) {}
void Semantic::tact23_(attribute &result) {}
void Semantic::tact24_(attribute &result) {}
void Semantic::tact25_(attribute &result) {}
void Semantic::tact26_(attribute &result) {}
void Semantic::tact27_(attribute &result) {}
void Semantic::tact28_(attribute &result) {}
void Semantic::tact29_(attribute &result) {}
void Semantic::tact30_(attribute &result) {}
void Semantic::tact31_(attribute &result) {}
void Semantic::tact32_(attribute &result) {}
void Semantic::tact33_(attribute &result) {}
void Semantic::tact34_(attribute &result) {}
void Semantic::tact35_(attribute &result) {}
void Semantic::tact36_(attribute &result) {}
void Semantic::tact37_(attribute &result) {}
void Semantic::tact38_(attribute &result) {}
void Semantic::tact39_(attribute &result) {}
void Semantic::tact40_(attribute &result) {}
void Semantic::tact41_(attribute &result) {}
void Semantic::tact42_(attribute &result) {}
void Semantic::tact43_(attribute &result) {}
void Semantic::tact44_(attribute &result) {}
void Semantic::tact45_(attribute &result) {}
void Semantic::tact46_(attribute &result) {}
void Semantic::tact47_(attribute &result) {}
void Semantic::tact48_(attribute &result) {}
void Semantic::tact49_(attribute &result) {}
void Semantic::tact50_(attribute &result) {}