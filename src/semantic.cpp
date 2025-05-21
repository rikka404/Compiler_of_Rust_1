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
        if (*std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"]) != *std::any_cast<std::shared_ptr<data_type>>(args[1]["returnType"]))
        {
            std::cout << "[ERROR] [SEMANTIC] return type \"" << *std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"])
                      << "\" and \"" << *std::any_cast<std::shared_ptr<data_type>>(args[1]["returnType"]) << "\" not match" << std::endl;
            exit(0);
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
    // 检查函数重定义
    if (functionTable.count(functionEntry{0, std::any_cast<std::string>(args[1]["name"]), {}, {}}))
    {
        std::cout << "[ERROR] [SEMANTIC] function \"" << std::any_cast<std::string>(args[1]["name"]) << "\" is redefined" << std::endl;
        exit(0);
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
    // 语句块 -> M { 语句串 }
    int num = std::any_cast<int>(args[2]["symbolNum"]);
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
    if (args[2].count("returnType"))
    {
        result["returnType"] = args[2]["returnType"];
    }
    result["breakList"] = std::any_cast<int>(args[2]["breakList"]);
    result["continueList"] = std::any_cast<int>(args[2]["continueList"]);
}
void Semantic::act8_(std::vector<attribute> &args, attribute &result) {
    // 语句串 -> /zero
    result["symbolNum"] = 0;
    result["breakList"] = 0;
    result["continueList"] = 0;
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
    result["breakList"] = args[1]["breakList"];
    result["continueList"] = args[1]["continueList"];
    if(args[0].count("breakList"))
    {
        int l1 = std::any_cast<int>(args[0]["breakList"]);
        int l2 = std::any_cast<int>(args[1]["breakList"]);
        codes[l1].result.value = l2;
        result["breakList"] = l1;
    }
    if(args[0].count("continueList"))
    {
        int l1 = std::any_cast<int>(args[0]["continueList"]);
        int l2 = std::any_cast<int>(args[1]["continueList"]);
        codes[l1].result.value = l2;
        result["continueList"] = l1;
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
    // 检查函数重定义
    if (functionTable.count(functionEntry{0, std::any_cast<std::string>(args[1]["name"]), {}, {}}))
    {
        std::cout << "[ERROR] [SEMANTIC] function \"" << std::any_cast<std::string>(args[1]["name"]) << "\" is redefined" << std::endl;
        exit(0);
    }
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
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) 
        << "\":" << *std::any_cast<element_type>(args[0]["elementType"]).dataType << " and " 
        << "\"" << std::any_cast<std::string>(args[2]["name"]) << "\":"
        << *std::any_cast<element_type>(args[2]["elementType"]).dataType << " are not same type" << std::endl;
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
    
    // 检查类型相同
    if (*std::any_cast<element_type>(args[5]["elementType"]).dataType != *ele_type.dataType)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << name 
        << "\":" << *ele_type.dataType << " and " << "\"" << std::any_cast<std::string>(args[5]["name"]) << "\":"
        << *std::any_cast<element_type>(args[5]["elementType"]).dataType << " are not same type" << std::endl;
        exit(0);
    }
    if (std::any_cast<element_type>(args[5]["elementType"]).readType == TEMPORARY)
    {
        // 优化:直接使用临时变量地址
        assert(symbolStack.back().type.readType == TEMPORARY && symbolStack.back().name == std::any_cast<std::string>(args[5]["name"]));
        // 只是在编译模拟中将临时变量改为一般变量
        symbolEntry sym;
        sym.name = name, sym.type = ele_type;
        sym.relativeAddress = symbolStack.back().relativeAddress;
        popSymbol();
        c_esp += ele_type.dataType->siz;
        pushSymbol(sym);

        // 可能有临时变量计数
        result["symbolNum"] = std::any_cast<int>(args[5]["symbolNum"]);
    }
    else
    {
        // 需要声明变量
        // 声明一个变量
        symbolEntry sym;
        sym.name = name, sym.type = ele_type;
        sym.relativeAddress = c_esp;
        c_esp += ele_type.dataType->siz;
        pushSymbol(sym);

        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, ele_type.dataType->siz}, Operand{Literal, 0}));

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
    
}
void Semantic::act33_(std::vector<attribute> &args, attribute &result) {
    // 变量声明赋值语句 -> /let 变量声明内部 = 表达式 /semicolon
    element_type ele_type;
    ele_type.dataType = std::any_cast<element_type>(args[3]["elementType"]).dataType;
    ele_type.readType = std::any_cast<read_type>(args[1]["readType"]);
    std::string name = std::any_cast<std::string>(args[1]["name"]);

    if (std::any_cast<element_type>(args[3]["elementType"]).readType == TEMPORARY)
    {
        // 优化:直接使用临时变量地址
        assert(symbolStack.back().type.readType == TEMPORARY && symbolStack.back().name == std::any_cast<std::string>(args[3]["name"]));
        // 只是在编译模拟中将临时变量改为一般变量
        symbolEntry sym;
        sym.name = name, sym.type = ele_type;
        sym.relativeAddress = symbolStack.back().relativeAddress;
        popSymbol();
        c_esp += ele_type.dataType->siz;
        pushSymbol(sym);

        // 可能有临时变量计数
        result["symbolNum"] = std::any_cast<int>(args[3]["symbolNum"]);
    }
    else
    {
        // 声明一个变量
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
void Semantic::act44_(std::vector<attribute> &args, attribute &result) {
    // 表达式 -> 表达式 or M OR表达式
    /**
     * code a
     * code M :
     *      jnz A - AT
     * code b
     * 这以上的都是规约之前就做好的
     * jnz B BT
     * pop B + A
     * push c
     * c := 0
     * j next
     * AT: pop A
     * j T
     * BT: pop B + A
     * T: push c
     * c := 1
     * next:
     */
    // 检查两个都要是bool
    if (std::any_cast<element_type>(args[0]["elementType"]).dataType->type != BOOL_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not a BOOL " << std::endl;
        exit(0);
    }
    if (std::any_cast<element_type>(args[3]["elementType"]).dataType->type != BOOL_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[3]["name"]) << "\" is not a BOOL " << std::endl;
        exit(0);
    }
    int a_offset = std::any_cast<int>(args[0]["address"]);
    int b_offset = std::any_cast<int>(args[3]["address"]);
    int a_symbolNum = std::any_cast<int>(args[0]["symbolNum"]);
    int b_symbolNum = std::any_cast<int>(args[3]["symbolNum"]);
    int a_siz = 0, b_siz = 0;
    for (int i = 0; i < b_symbolNum; i++)
    {
        b_siz += symbolStack.back().type.dataType->siz;
        popSymbol(); 
    }
    for (int i = 0; i < a_symbolNum; i++)
    {
        a_siz += symbolStack.back().type.dataType->siz;
        popSymbol(); 
    }
    // 声明临时变量
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = data_type::create(BOOL_TYPE);
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp;
    c_esp += 1;
    pushTempSymbol(sym);

    int M = std::any_cast<int>(args[2]["codeID"]);
    std::vector<int> AT_list, BT_list, T_list, next_list;
    int AT, BT, T, next;
    codes[M] = quaternary{"jnz", Operand{Offset, a_offset}, Operand{Literal, 0}, Operand{Lable, 0}};
    AT_list.push_back(M);
    BT_list.push_back(codes.size());
    codes.push_back(quaternary{"jnz", Operand{Offset, b_offset}, Operand{Literal, 0}, Operand{Lable, 0}});
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, b_siz + a_siz}, Operand{Literal, 0}});
    codes.push_back(quaternary{"push", Operand{Literal, 0}, Operand{Literal, 1}, Operand{Literal, 0}});
    codes.push_back(quaternary{":=", Operand{Literal, 0}, Operand{Literal, 1}, Operand{Offset, sym.relativeAddress}});
    next_list.push_back(codes.size());
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    AT = codes.size();
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, a_siz}, Operand{Literal, 0}});
    T_list.push_back(codes.size());
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    BT = codes.size();
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, b_siz + a_siz}, Operand{Literal, 0}});
    T_list.push_back(codes.size());
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    T = codes.size();
    codes.push_back(quaternary{"push", Operand{Literal, 0}, Operand{Literal, 1}, Operand{Literal, 0}});
    codes.push_back(quaternary{":=", Operand{Literal, 1}, Operand{Literal, 1}, Operand{Offset, sym.relativeAddress}});
    next = codes.size();
    for (int x : AT_list)
    {
        codes[x].result.value = AT;
    }
    for (int x : BT_list)
    {
        codes[x].result.value = BT;
    }
    for (int x : T_list)
    {
        codes[x].result.value = T;
    }
    for (int x : next_list)
    {
        codes[x].result.value = next;
    }
    result["symbolNum"] = 1; //儿子全部清空
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
}
void Semantic::act45_(std::vector<attribute> &args, attribute &result) {
    // OR表达式 -> OR表达式 and M AND表达式
    /**
     * code a
     * code M :
     *      jnz A - AF
     * code b
     * 这以上的都是规约之前就做好的
     * jnz B BF
     * pop B + A
     * push c
     * c := 1
     * j next
     * AF: pop A
     * j T
     * BF: pop B + A
     * F: push c
     * c := 0
     * next:
     */
    // 检查两个都要是bool
    if (std::any_cast<element_type>(args[0]["elementType"]).dataType->type != BOOL_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not a BOOL " << std::endl;
        exit(0);
    }
    if (std::any_cast<element_type>(args[3]["elementType"]).dataType->type != BOOL_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[3]["name"]) << "\" is not a BOOL " << std::endl;
        exit(0);
    }
    int a_offset = std::any_cast<int>(args[0]["address"]);
    int b_offset = std::any_cast<int>(args[3]["address"]);
    int a_symbolNum = std::any_cast<int>(args[0]["symbolNum"]);
    int b_symbolNum = std::any_cast<int>(args[3]["symbolNum"]);
    int a_siz = 0, b_siz = 0;
    for (int i = 0; i < b_symbolNum; i++)
    {
        b_siz += symbolStack.back().type.dataType->siz;
        popSymbol(); 
    }
    for (int i = 0; i < a_symbolNum; i++)
    {
        a_siz += symbolStack.back().type.dataType->siz;
        popSymbol(); 
    }
    // 声明临时变量
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = data_type::create(BOOL_TYPE);
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp;
    c_esp += 1;
    pushTempSymbol(sym);

    int M = std::any_cast<int>(args[2]["codeID"]);
    std::vector<int> AF_list, BF_list, F_list, next_list;
    int AF, BF, F, next;
    codes[M] = quaternary{"jz", Operand{Offset, a_offset}, Operand{Literal, 0}, Operand{Lable, 0}};
    AF_list.push_back(M);
    BF_list.push_back(codes.size());
    codes.push_back(quaternary{"jz", Operand{Offset, b_offset}, Operand{Literal, 0}, Operand{Lable, 0}});
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, b_siz + a_siz}, Operand{Literal, 0}});
    codes.push_back(quaternary{"push", Operand{Literal, 0}, Operand{Literal, 1}, Operand{Literal, 0}});
    codes.push_back(quaternary{":=", Operand{Literal, 1}, Operand{Literal, 1}, Operand{Offset, sym.relativeAddress}});
    next_list.push_back(codes.size());
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    AF = codes.size();
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, a_siz}, Operand{Literal, 0}});
    F_list.push_back(codes.size());
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    BF = codes.size();
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, b_siz + a_siz}, Operand{Literal, 0}});
    F_list.push_back(codes.size());
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    F = codes.size();
    codes.push_back(quaternary{"push", Operand{Literal, 0}, Operand{Literal, 1}, Operand{Literal, 0}});
    codes.push_back(quaternary{":=", Operand{Literal, 0}, Operand{Literal, 1}, Operand{Offset, sym.relativeAddress}});
    next = codes.size();
    for (int x : AF_list)
    {
        codes[x].result.value = AF;
    }
    for (int x : BF_list)
    {
        codes[x].result.value = BF;
    }
    for (int x : F_list)
    {
        codes[x].result.value = F;
    }
    for (int x : next_list)
    {
        codes[x].result.value = next;
    }
    result["symbolNum"] = 1; //儿子全部清空
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
}
void Semantic::act46_(std::vector<attribute> &args, attribute &result) {
    // AND表达式 -> AND表达式 比较运算符 加法表达式
    // TODO: 这是之后的事情，第一版可以不实现，这里同时记录原始的式子，在规约到上层的时候可以尝试归于成jeq, j<之类的
    std::string op = std::any_cast<std::string>(args[1]["opSymbol"]);
    if(op == "==" || op == "!=")
    {
        if(std::any_cast<element_type>(args[0]["elementType"]).dataType->type != I32_TYPE && 
            std::any_cast<element_type>(args[0]["elementType"]).dataType->type != BOOL_TYPE)
        {
            std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" is not a int or a bool." << std::endl;
            exit(0);
        }
        if(std::any_cast<element_type>(args[2]["elementType"]).dataType->type != I32_TYPE && 
            std::any_cast<element_type>(args[2]["elementType"]).dataType->type != BOOL_TYPE)
        {
            std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[2]["name"]) << "\" is not a int or a bool." << std::endl;
            exit(0);
        }
        if (*std::any_cast<element_type>(args[0]["elementType"]).dataType != *std::any_cast<element_type>(args[2]["elementType"]).dataType)
        {
            std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\" and " << "\"" << std::any_cast<std::string>(args[2]["name"]) << "\" are not same type" << std::endl;
            exit(0);
        }
    }
    else
    {
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
    }
    // 声明临时变量
    symbolEntry sym;
    // 优化：如果两个中有一个是临时变量，并且是bool，结果直接用临时变量的地址
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == TEMPORARY && std::any_cast<element_type>(args[0]["elementType"]).dataType->type == BOOL_TYPE)
    {
        sym.name = std::any_cast<std::string>(args[0]["name"]);
        sym.type = std::any_cast<element_type>(args[0]["elementType"]);
        sym.relativeAddress = std::any_cast<int>(args[0]["address"]);
        result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
    }
    else if (std::any_cast<element_type>(args[2]["elementType"]).readType == TEMPORARY && std::any_cast<element_type>(args[2]["elementType"]).dataType->type == BOOL_TYPE)
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
        sym.type.dataType = data_type::create(BOOL_TYPE);
        sym.type.readType = TEMPORARY;
        sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += sym.type.dataType->siz;
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
        c_esp += sym.type.dataType->siz;
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

    // 优化：如果两个都是临时变量，释放在栈顶那些临时变量(断言是后面那个)
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == TEMPORARY &&
        std::any_cast<element_type>(args[2]["elementType"]).readType == TEMPORARY)
    {
        assert(symbolStack.back().type.readType == TEMPORARY && symbolStack.back().name == std::any_cast<std::string>(args[2]["name"]));
        int sum_siz = 0;
        for (int i = 0; i < std::any_cast<int>(args[2]["symbolNum"]); i++)
        {
            sum_siz += symbolStack.back().type.dataType->siz;
            popSymbol();
        }
        if (sum_siz != 0)
            codes.push_back(quaternary("pop", Operand{Literal, 0}, Operand{Literal, sum_siz}, Operand{Literal, 0}));
        result["symbolNum"] = std::any_cast<int>(result["symbolNum"]) - std::any_cast<int>(args[2]["symbolNum"]);
    }
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
        c_esp += sym.type.dataType->siz;
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

    // 优化：如果两个都是临时变量，释放在栈顶那些临时变量(断言是后面那个)
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == TEMPORARY &&
        std::any_cast<element_type>(args[2]["elementType"]).readType == TEMPORARY)
    {
        assert(symbolStack.back().type.readType == TEMPORARY && symbolStack.back().name == std::any_cast<std::string>(args[2]["name"]));
        int sum_siz = 0;
        for (int i = 0; i < std::any_cast<int>(args[2]["symbolNum"]); i++)
        {
            sum_siz += symbolStack.back().type.dataType->siz;
            popSymbol();
        }
        if (sum_siz != 0)
            codes.push_back(quaternary("pop", Operand{Literal, 0}, Operand{Literal, sum_siz}, Operand{Literal, 0}));
        result["symbolNum"] = std::any_cast<int>(result["symbolNum"]) - std::any_cast<int>(args[2]["symbolNum"]);
    }
}
void Semantic::act49_(std::vector<attribute> &args, attribute &result) {
    // 比较运算符 -> <
    result["opSymbol"] = (std::string)"<";
}
void Semantic::act50_(std::vector<attribute> &args, attribute &result) {
    // 比较运算符 -> <=
    result["opSymbol"] = (std::string)"<=";
}
void Semantic::act51_(std::vector<attribute> &args, attribute &result) {
    // 比较运算符 -> >
    result["opSymbol"] = (std::string)">";
}
void Semantic::act52_(std::vector<attribute> &args, attribute &result) {
    // 比较运算符 -> >=
    result["opSymbol"] = (std::string)">=";
}
void Semantic::act53_(std::vector<attribute> &args, attribute &result) {
    // 比较运算符 -> ==
    result["opSymbol"] = (std::string)"==";
}
void Semantic::act54_(std::vector<attribute> &args, attribute &result) {
    // 比较运算符 -> !=
    result["opSymbol"] = (std::string)"!=";
}
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
        c_esp += sym.type.dataType->siz;
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
void Semantic::act61_(std::vector<attribute> &args, attribute &result) {
    // 因子 -> not 因子
    // 默认只能对bool类型取not？
    if(std::any_cast<element_type>(args[1]["elementType"]).dataType->type != BOOL_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[1]["name"]) << "\" is not a bool." << std::endl;
        exit(0);
    }
    symbolEntry sym;
    // 优化：如果原来是临时变量，结果直接用临时变量的地址
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
        sym.type.dataType = data_type::create(BOOL_TYPE);
        sym.type.readType = TEMPORARY;
        sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += sym.type.dataType->siz;
        pushTempSymbol(sym);
        result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]) + 1;
    }
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;
    // 运算四元式
    quaternary quat;
    quat.op = "not";
    if(std::any_cast<element_type>(args[1]["elementType"]).readType == LITERAL)
        quat.arg1 = Operand{Literal, std::any_cast<int>(args[1]["val"])}; //但是我们好像没有true false 关键字
    else if (args[1].count("address"))
        quat.arg1 = Operand{Offset, std::any_cast<int>(args[1]["address"])};
    else
        quat.arg1 = Operand{Address, std::any_cast<int>(args[1]["absoluteAddress"])};
    quat.arg2 = Operand{Literal, 0};
    quat.result = Operand{Offset, sym.relativeAddress};
    codes.push_back(quat);
}
void Semantic::act62_(std::vector<attribute> &args, attribute &result) {
    // 因子 -> /false
    result["name"] = "false";
    result["elementType"] = element_type{data_type::create(BOOL_TYPE), LITERAL};
    result["val"] = 0;
    result["symbolNum"] = 0;
}
void Semantic::act63_(std::vector<attribute> &args, attribute &result) {
    // 因子 -> /ture
    result["name"] = "true";
    result["elementType"] = element_type{data_type::create(BOOL_TYPE), LITERAL};
    result["val"] = 1;
    result["symbolNum"] = 0;
}
void Semantic::act64_(std::vector<attribute> &args, attribute &result) {
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
    if (func->returnType.type.dataType->type != VOID_TYPE)
    {
        // 为返回值申请临时变量
        symbolEntry sym;
        sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
        sym.type.dataType = func->returnType.type.dataType;
        sym.type.readType = TEMPORARY;
        sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += sym.type.dataType->siz;
        pushTempSymbol(sym);
        result["name"] = sym.name;
        result["elementType"] = sym.type;
        result["address"] = sym.relativeAddress;
        // 实参列表也可能有临时变量计数
        result["symbolNum"] = std::any_cast<int>(args[2]["symbolNum"]) + 1;
    }
    else
    {
        result["name"] = "null";
        result["elementType"] = element_type{func->returnType.type.dataType, TEMPORARY};
        result["address"] = -1;
        result["symbolNum"] = std::any_cast<int>(args[2]["symbolNum"]);
    }

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
void Semantic::act65_(std::vector<attribute> &args, attribute &result) {
    // 实参列表 -> 空
    std::vector<std::pair<element_type, std::pair<bool, int>>> para_list; // bool 是否为绝对地址 int 是字面量的值或偏移量
    result["actualParameter"] = para_list;
    result["symbolNum"] = 0;
}
void Semantic::act66_(std::vector<attribute> &args, attribute &result) {
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
void Semantic::act67_(std::vector<attribute> &args, attribute &result) {
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
void Semantic::act68_(std::vector<attribute> &args, attribute &result) {
    // M -> /zero
    result["codeID"] = (int)codes.size();
    codes.push_back(quaternary{"", Operand{Offset, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    // 通过先插入M的方式解决“需要规约到上层才知道要往里面加入语句”的问题和需要回填的问题
}
void Semantic::act69_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> IF语句
    result = args[0];
}
void Semantic::act70_(std::vector<attribute> &args, attribute &result) {
    // IF语句 -> if 表达式 M 语句块 M else部分
    /**
     * 表达式code
     * M1code jz 表达式 M2 + 1
     * M1 + 1 : 语句块code
     * M2code j L
     * M2 + 1 : else部分code
     * L 
     * 
     * 诶好像不需要加新的语句了
     */
    int M1 = std::any_cast<int>(args[2]["codeID"]), M2 = std::any_cast<int>(args[4]["codeID"]);
    int L = codes.size();
    if(std::any_cast<element_type>(args[1]["elementType"]).readType == LITERAL)
        codes[M1] = quaternary{"jz", Operand{Literal, std::any_cast<int>(args[1]["val"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    else if (args[1].count("address"))
        codes[M1] = quaternary{"jz", Operand{Offset, std::any_cast<int>(args[1]["address"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    else
        codes[M1] = quaternary{"jz", Operand{Address, std::any_cast<int>(args[1]["absoluteAddress"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    codes[M2] = quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, L + 1}};
    codes.push_back(quaternary{"null", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}});
    // 计数临时变量
    result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]) + std::any_cast<int>(args[5]["symbolNum"]);
    
    // 继承breakList和continueList
    {
    int l1 = std::any_cast<int>(args[3]["breakList"]);
    int l2 = std::any_cast<int>(args[5]["breakList"]);
    codes[l1].result.value = l2;
    result["breakList"] = l1;
    }

    {
    int l1 = std::any_cast<int>(args[3]["continueList"]);
    int l2 = std::any_cast<int>(args[5]["continueList"]);
    codes[l1].result.value = l2;
    result["continueList"] = l1;
    }
}
void Semantic::act71_(std::vector<attribute> &args, attribute &result) {
    // /else /if 表达式 M 语句块 M else部分
    int M1 = std::any_cast<int>(args[3]["codeID"]), M2 = std::any_cast<int>(args[5]["codeID"]);
    int L = codes.size();
    if(std::any_cast<element_type>(args[2]["elementType"]).readType == LITERAL)
        codes[M1] = quaternary{"jz", Operand{Literal, std::any_cast<int>(args[2]["val"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    else if (args[2].count("address"))
        codes[M1] = quaternary{"jz", Operand{Offset, std::any_cast<int>(args[2]["address"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    else
        codes[M1] = quaternary{"jz", Operand{Address, std::any_cast<int>(args[2]["absoluteAddress"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    codes[M2] = quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, L + 1}};
    codes.push_back(quaternary{"null", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}});
    // 计数临时变量
    result["symbolNum"] = std::any_cast<int>(args[2]["symbolNum"]) + std::any_cast<int>(args[6]["symbolNum"]);

    // 继承breakList和continueList
    {
    int l1 = std::any_cast<int>(args[4]["breakList"]);
    int l2 = std::any_cast<int>(args[6]["breakList"]);
    codes[l1].result.value = l2;
    result["breakList"] = l1;
    }

    {
    int l1 = std::any_cast<int>(args[4]["continueList"]);
    int l2 = std::any_cast<int>(args[6]["continueList"]);
    codes[l1].result.value = l2;
    result["continueList"] = l1;
    }
}
void Semantic::act72_(std::vector<attribute> &args, attribute &result) {
    // else部分 -> else 语句块
    result["symbolNum"] = 0;
    result["breakList"] = std::any_cast<int>(args[1]["breakList"]);
    result["continueList"] = std::any_cast<int>(args[1]["continueList"]);
}
void Semantic::act73_(std::vector<attribute> &args, attribute &result) {
    // else部分 -> 空
    result["symbolNum"] = 0;
    result["breakList"] = 0;
    result["continueList"] = 0;
}
void Semantic::act74_(std::vector<attribute> &args, attribute &result) {
    // 语句 ->循环语句
    result = args[0];
}
void Semantic::act75_(std::vector<attribute> &args, attribute &result) {
    // 循环语句 -> WHILE语句
    result = args[0];
}
void Semantic::act76_(std::vector<attribute> &args, attribute &result) {
    // WHILE语句 -> while M 表达式 M 语句块
    /**
     * M1 : null
     * 表达式code
     * M2code : jz A L
     * 语句块code
     * C: pop A
     * j M1
     * L: pop A
     * 
     */
    int M1 = std::any_cast<int>(args[1]["codeID"]), M2 = std::any_cast<int>(args[3]["codeID"]);
    int a_offset = std::any_cast<int>(args[2]["address"]);
    // TODO: 所有的jz jnz之类的，寻址方式有三种
    codes[M1] = quaternary{"null", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}};
    codes[M2] = quaternary{"jz", Operand{Offset, a_offset}, Operand{Literal, 0}, Operand{Lable, 0}};
    int a_symbolNum = std::any_cast<int>(args[2]["symbolNum"]);
    int a_siz = 0;
    for (int i = 0; i < a_symbolNum; i++)
    {
        a_siz += symbolStack.back().type.dataType->siz;
        popSymbol(); 
    }
    int C = codes.size();
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, a_siz}, Operand{Literal, 0}});
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, M1}});
    int L = codes.size();
    codes.push_back(quaternary{"pop", Operand{Literal, 0}, Operand{Literal, a_siz}, Operand{Literal, 0}});
    codes[M2].result.value = L;
    // 回填breakList和continueList
    int breakList = std::any_cast<int>(args[4]["breakList"]);
    while (breakList)
    {
        int nxt = codes[breakList].result.value;
        codes[breakList].result.value = L;
        breakList = nxt;
    }
    int continueList = std::any_cast<int>(args[4]["continueList"]);
    while (continueList)
    {
        int nxt = codes[continueList].result.value;
        codes[continueList].result.value = C;
        continueList = nxt;
    }
    // 计数临时变量
    result["symbolNum"] = 0;
}
void Semantic::act77_(std::vector<attribute> &args, attribute &result) {
    // 循环语句 -> FOR语句
}
void Semantic::act78_(std::vector<attribute> &args, attribute &result) {
    // FOR语句 -> FOR语句声明 M_FOR 语句块
    /**
     * FOR语句声明code:声明e并赋初值end,声明i并赋初值beg-1
     * M_FOR : null
     * M:M_FOR : i++
     * M_FOR : j>= i end - L
     * 语句块code
     * j M
     * L pop所有变量
     * 语句块内的变量已经释放掉了，无需再次释放
     *
     * 考虑数组:
     * FOR语句声明code:声明一个存储 当前数组元素绝对地址-siz 的a和结束处的a_end、一个存储数组元素的变量x
     * M:M_FOR : a+=siz
     * M_FOR : j> a a_end - L
     * M_FOR : x:=*a
     * 语句块code
     * j M
     * L pop所有变量
     */
    element_type ele_type;
    ele_type.dataType = std::any_cast<std::shared_ptr<data_type>>(args[0]["IterativeDataType"]);

    int M, L;
    if (ele_type.dataType->type == I32_TYPE)
    {
        M = std::any_cast<int>(args[1]["codeID"]) + 1;
        int address = std::any_cast<int>(args[0]["address"]);
        int addressEnd = std::any_cast<int>(args[0]["endAddress"]);

        codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, M}});
        L = codes.size();
        // 回填
        codes[M] = quaternary{"+", Operand{Offset, address}, Operand{Literal, 1}, Operand{Offset, address}};
        codes[M + 1] = quaternary{"j>=", Operand{Offset, address}, Operand{Offset, addressEnd}, Operand{Lable, L}};
    }
    else 
    {
        M = std::any_cast<int>(args[1]["codeID"]);
        int address = std::any_cast<int>(args[0]["address"]);
        int addressRefer = std::any_cast<int>(args[0]["referAddress"]);
        int addressReferEnd = std::any_cast<int>(args[0]["referEndAddress"]);

        codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, M}});
        L = codes.size();
        // 回填
        codes[M] = quaternary{"+", Operand{Offset, addressRefer}, Operand{Literal, ele_type.dataType->get_sub_class(0)->siz}, Operand{Offset, addressRefer}};
        codes[M + 1] = quaternary{"j>", Operand{Offset, addressRefer}, Operand{Offset, addressReferEnd}, Operand{Lable, L}};
        codes[M + 2] = quaternary{":=", Operand{Address, addressRefer}, Operand{Literal, ele_type.dataType->get_sub_class(0)->siz}, Operand{Offset, address}};
    }
        
    int num = std::any_cast<int>(args[0]["symbolNum"]);
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
    // 回填breakList和continueList
    int breakList = std::any_cast<int>(args[2]["breakList"]);
    while (breakList)
    {
        int nxt = codes[breakList].result.value;
        codes[breakList].result.value = L;
        breakList = nxt;
    }
    int continueList = std::any_cast<int>(args[2]["continueList"]);
    while (continueList)
    {
        int nxt = codes[continueList].result.value;
        codes[continueList].result.value = M;
        continueList = nxt;
    }
    
}
void Semantic::act79_(std::vector<attribute> &args, attribute &result) {
    // FOR语句声明 -> for 变量声明内部 in 可迭代结构
    element_type ele_type;
    ele_type.dataType = std::any_cast<std::shared_ptr<data_type>>(args[3]["IterativeDataType"]);
    ele_type.readType = std::any_cast<read_type>(args[1]["readType"]);
    std::string name = std::any_cast<std::string>(args[1]["name"]);
    if (ele_type.dataType->type == I32_TYPE)
    {
        // i32..i32
        {
            // 声明一个计数器int变量
            symbolEntry sym;
            sym.name = name, sym.type = ele_type;
            sym.relativeAddress = c_esp;
            c_esp += ele_type.dataType->siz;
            pushSymbol(sym);
            result["address"] = sym.relativeAddress;
            result["name"] = name;
            result["IterativeDataType"] = ele_type.dataType;

            codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));

            // 赋初值
            if (args[3].count("rangeBeginVal"))
            {
                codes.push_back(quaternary(":=", Operand{Literal, std::any_cast<int>(args[3]["rangeBeginVal"])}, Operand{Literal, sym.type.dataType->siz}, Operand{Offset, sym.relativeAddress}));
            }
            else if (args[3].count("rangeBeginAddress"))
            {
                codes.push_back(quaternary(":=", Operand{Offset, std::any_cast<int>(args[3]["rangeBeginAddress"])}, Operand{Literal, sym.type.dataType->siz}, Operand{Offset, sym.relativeAddress}));
            }
            else
            {
                codes.push_back(quaternary(":=", Operand{Address, std::any_cast<int>(args[3]["rangeBeginAbsoluteAddress"])}, Operand{Literal, sym.type.dataType->siz}, Operand{Offset, sym.relativeAddress}));
            }
            // 要-1
            codes.push_back(quaternary("-", Operand{Offset, sym.relativeAddress}, Operand{Literal, 1}, Operand{Offset, sym.relativeAddress}));
        }
        
        // 声明临时变量存end，rust是这样的
        {
            symbolEntry sym;
            sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
            sym.type.dataType = ele_type.dataType;
            sym.type.readType = TEMPORARY;
            sym.relativeAddress = c_esp;
            codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
            c_esp += sym.type.dataType->siz;
            pushTempSymbol(sym);
            result["endAddress"] = sym.relativeAddress;
            
            // 赋初值
            if (args[3].count("rangeEndVal"))
            {
                codes.push_back(quaternary(":=", Operand{Literal, std::any_cast<int>(args[3]["rangeEndVal"])}, Operand{Literal, 0}, Operand{Offset, sym.relativeAddress}));
            }
            else if (args[3].count("rangeBeginAddress"))
            {
                codes.push_back(quaternary(":=", Operand{Offset, std::any_cast<int>(args[3]["rangeEndAddress"])}, Operand{Literal, 0}, Operand{Offset, sym.relativeAddress}));
            }
            else
            {
                codes.push_back(quaternary(":=", Operand{Address, std::any_cast<int>(args[3]["rangeEndAbsoluteAddress"])}, Operand{Literal, 0}, Operand{Offset, sym.relativeAddress}));
            }
        }

        // 临时变量计数 + 声明变量2
        result["symbolNum"] = std::any_cast<int>(args[3]["symbolNum"]) + 2;
    }
    else
    {
        // 数组
        {
            // 声明一个存储数组变量的x
            symbolEntry sym;
            sym.name = name, sym.type = ele_type;
            sym.type.dataType = ele_type.dataType->get_sub_class(0);
            sym.relativeAddress = c_esp;
            c_esp += sym.type.dataType->siz;
            pushSymbol(sym);
            result["address"] = sym.relativeAddress;
            result["name"] = name;
            result["IterativeDataType"] = ele_type.dataType;

            codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        }

        // 声明临时变量a存当前数组元素绝对地址，初始是a-siz
        {
            symbolEntry sym;
            sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
            sym.type.dataType = data_type::create(REFER_TYPE, ele_type.dataType->get_sub_class(0)); //这个并不重要
            sym.type.readType = TEMPORARY;
            sym.relativeAddress = c_esp;
            codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
            c_esp += sym.type.dataType->siz;
            pushTempSymbol(sym);
            result["referAddress"] = sym.relativeAddress;

            // 取绝对地址
            if (args[3].count("arrayAddress"))
            {
                codes.push_back(quaternary("sea", Operand{Literal, std::any_cast<int>(args[3]["arrayAddress"])}, Operand{Literal, 0}, Operand{Offset, sym.relativeAddress}));
            }
            else
            {
                codes.push_back(quaternary(":=", Operand{Offset, std::any_cast<int>(args[3]["arrayAbsoluteAddress"])}, Operand{Literal, sym.type.dataType->siz}, Operand{Offset, sym.relativeAddress}));
            }
            // a减去siz
            codes.push_back(quaternary("-", Operand{Offset, sym.relativeAddress}, Operand{Literal, ele_type.dataType->get_sub_class(0)->siz}, Operand{Offset, sym.relativeAddress}));

            int a_relativeAddress = sym.relativeAddress;

            // 声明临时变量a_end存最后数组元素绝对地址
            sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
            sym.relativeAddress = c_esp;
            codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
            c_esp += sym.type.dataType->siz;
            pushTempSymbol(sym);
            result["referEndAddress"] = sym.relativeAddress;

            // a_end:=a+数组大小
            codes.push_back(quaternary("+", Operand{Offset, a_relativeAddress}, Operand{Literal, ele_type.dataType->siz}, Operand{Offset, sym.relativeAddress}));
        }

        // 临时变量计数 + 声明变量3
        result["symbolNum"] = std::any_cast<int>(args[3]["symbolNum"]) + 3;
    }
        
    
    // TODO: 如果右边是临时变量，可以直接使用这个临时变量作为变量的地址，改一下readtype
}
void Semantic::act80_(std::vector<attribute> &args, attribute &result) {
    // 可迭代结构 -> 表达式 , 表达式
    if (*std::any_cast<element_type>(args[0]["elementType"]).dataType != *std::any_cast<element_type>(args[2]["elementType"]).dataType)
    {
        std::cout << "[ERROR] [SEMANTIC] " << std::any_cast<std::string>(args[0]["name"]) << " and " << std::any_cast<std::string>(args[2]["name"]) << " are not same type" << std::endl;
        exit(0);
    }
    // 必须是i32
    if (std::any_cast<element_type>(args[0]["elementType"]).dataType->type != I32_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] " << std::any_cast<std::string>(args[0]["name"]) << " and " << std::any_cast<std::string>(args[2]["name"]) << " are not int" << std::endl;
        exit(0);
    }

    // 用于指示是int..int还是某个数组
    result["IterativeDataType"] = data_type::create(I32_TYPE);
    
    if(std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
        result["rangeBeginVal"] = args[0]["val"];
    else if (args[0].count("address"))
        result["rangeBeginAddress"] = args[0]["address"];
    else
        result["rangeBeginAbsoluteAddress"] = args[0]["absoluteAddress"];

    if(std::any_cast<element_type>(args[2]["elementType"]).readType == LITERAL)
        result["rangeEndVal"] = args[2]["val"];
    else if (args[2].count("address"))
        result["rangeEndAddress"] = args[2]["address"];
    else
        result["rangeEndAbsoluteAddress"] = args[2]["absoluteAddress"];
    
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
}
void Semantic::act81_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act82_(std::vector<attribute> &args, attribute &result) {
    // LOOP语句 -> loop M 语句块
    /**
     * M: null
     * 语句块code
     * j M
     * L
     */
    int M = std::any_cast<int>(args[1]["codeID"]);
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, M}});
    int L = codes.size();
    codes[M] = quaternary{"null", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}};
    codes.push_back(quaternary{"null", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}});
    // 回填breakList和continueList
    int breakList = std::any_cast<int>(args[2]["breakList"]);
    while (breakList)
    {
        int nxt = codes[breakList].result.value;
        codes[breakList].result.value = L;
        breakList = nxt;
    }
    int continueList = std::any_cast<int>(args[2]["continueList"]);
    while (continueList)
    {
        int nxt = codes[continueList].result.value;
        codes[continueList].result.value = M;
        continueList = nxt;
    }
}
void Semantic::act83_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> break;
    int L = codes.size();
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    result["breakList"] = L;
}
void Semantic::act84_(std::vector<attribute> &args, attribute &result) {
    // 语句 -> continue;
    int L = codes.size();
    codes.push_back(quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    result["continueList"] = L;
}
void Semantic::act85_(std::vector<attribute> &args, attribute &result) {
    // 变量声明内部 -> /id
    result["name"] = args[0]["name"]; // 这里左右都是std::any，就可以直接赋值，不用cast
    result["readType"] = CONSTANT;
}
void Semantic::act86_(std::vector<attribute> &args, attribute &result) {
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
        c_esp += temp_sym.type.dataType->siz;
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
void Semantic::act87_(std::vector<attribute> &args, attribute &result) {
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
    c_esp += sym.type.dataType->siz;
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
void Semantic::act88_(std::vector<attribute> &args, attribute &result) {
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
    c_esp += sym.type.dataType->siz;
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
void Semantic::act89_(std::vector<attribute> &args, attribute &result)
{
    // 类型 -> /& /mut 类型
    result["dataType"] = data_type::create(MUT_REFER_TYPE, std::any_cast<std::shared_ptr<data_type>>(args[2]["dataType"]));
}
void Semantic::act90_(std::vector<attribute> &args, attribute &result) {
    // 类型 -> /& 类型
    result["dataType"] = data_type::create(REFER_TYPE, std::any_cast<std::shared_ptr<data_type>>(args[1]["dataType"]));
}
void Semantic::act91_(std::vector<attribute> &args, attribute &result) {
    // 表达式 -> 函数表达式语句块
    result["symbolNum"] = args[0]["symbolNum"];
    result["address"] = args[0]["retAddress"];
    result["elementType"] = args[0]["retElementType"];
}
void Semantic::act92_(std::vector<attribute> &args, attribute &result) {
    // 函数表达式语句块 -> M { 函数表达式语句串 }
    /**
     * M中一个int存放当前的esp，也就是整个语句块启示的时候的esp
     * 规约到这里的时候，M - esp就是整个语句串占用的空间
     * 我们让esp += 返回值的空间大小，然后把返回值copy到M的位置，之后释放所有变量
     * 这样最后就是M之上是一个返回值，且esp在这个返回值的上面
     */
    int retAddress = std::any_cast<int>(args[2]["returnExpAddress"]);
    int tRetAddress = std::any_cast<int>(args[0]["Address"]);
    element_type retElementType = std::any_cast<element_type>(args[2]["returnExpElementType"]);
    codes.push_back(quaternary{":=", Operand{Offset, retAddress},
                               Operand{Literal, retElementType.dataType->siz}, 
                               Operand{Offset, tRetAddress}});
    c_esp += retElementType.dataType->siz;
    codes.push_back(quaternary{"push", Operand{Literal, 0}, Operand{Literal, retElementType.dataType->siz}, Operand{Literal, 0}});

    int num = std::any_cast<int>(args[2]["symbolNum"]);
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
    // 里面的变量都释放掉了，这时候返回值的临时变量只是“在那里”，但是还没有创建
    // 声明临时变量
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = data_type::create(*retElementType.dataType);
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp - retElementType.dataType->siz; //就是此时栈顶
    pushTempSymbol(sym);

    result["symbolNum"] = 1; //这一个返回值
    result["retAddress"] = sym.relativeAddress;
    result["retElementType"] = retElementType;
}
void Semantic::act93_(std::vector<attribute> &args, attribute &result) {
    // 函数表达式语句串 -> 表达式
    // 这里也简单一点，不管表达式是立即数还是临时变量，都变成一个临时变量，方便后面复制
    element_type elementType = std::any_cast<element_type>(args[0]["elementType"]);
    result["symbolNum"] = 0;
    int address;
    if(elementType.readType == LITERAL)
    {
        // 声明临时变量
        symbolEntry sym;
        sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
        sym.type.dataType = data_type::create(*elementType.dataType);
        sym.type.readType = TEMPORARY;
        sym.relativeAddress = c_esp;
        codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
        c_esp += sym.type.dataType->siz;
        pushTempSymbol(sym);
        address = sym.relativeAddress;
        // 暂时认为立即数只有int
        assert(sym.type.dataType->type == I32_TYPE);
        codes.push_back(quaternary{":=", Operand{Literal, std::any_cast<int>(args[0]["val"])}, Operand{Literal, sym.type.dataType->siz}, Operand{Offset, sym.relativeAddress}});
        result["symbolNum"] = std::any_cast<int>(result["symbolNum"]) + 1;
    }
    else
    {
        address = std::any_cast<int>(args[0]["address"]);
    }
    result["returnExpAddress"] = address;
    result["returnExpElementType"] = elementType;
    result["symbolNum"] = std::any_cast<int>(result["symbolNum"]) + std::any_cast<int>(args[0]["symbolNum"]);
}
void Semantic::act94_(std::vector<attribute> &args, attribute &result) {
    // 函数表达式语句串 -> 语句 函数表达式语句串
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[1]["symbolNum"]);
    result["breakList"] = 0;
    result["continueList"] = 0;
    result["returnExpAddress"] = std::any_cast<int>(args[1]["returnExpAddress"]);
    result["returnExpElementType"] = std::any_cast<element_type>(args[1]["returnExpElementType"]);
}
void Semantic::act95_(std::vector<attribute> &args, attribute &result) {
    // M -> /zero
    // // 声明临时变量
    // symbolEntry sym;
    // sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    // sym.type.dataType = data_type::create(I32_TYPE);
    // sym.type.readType = TEMPORARY;
    // sym.relativeAddress = c_esp;
    // codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
    // c_esp += 4;
    // pushTempSymbol(sym);
    // // 将esp赋给临时变量，是绝对地址
    // codes.push_back(quaternary{":=", Operand{Register, ESP}, Operand{Literal, 4}, Operand{Offset, sym.relativeAddress}});
    // 是偏移量
    // 如果我不声明变量，而是直接记录esp呢，这里的c_esp就是一个偏移量
    result["Address"] = c_esp;
}
void Semantic::act96_(std::vector<attribute> &args, attribute &result) {
    // 函数声明 -> 函数头声明 函数表达式语句块
    // result["symbolNum"] = 1; //这一个返回值
    // result["retAddress"] = sym.relativeAddress;
    // result["retElementType"] = retElementType;
    // 检查返回类型
    if (!args[1].count("retElementType")){ // 必须有返回类型
        std::cout << "[ERROR] [SEMANTIC] return type \"" << *std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"]) << "\" and \"void\" not match" << std::endl;
        exit(0);
    }
    else
    {
        if (*std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"]) != *std::any_cast<element_type>(args[1]["retElementType"]).dataType)
        {
            std::cout << "[ERROR] [SEMANTIC] return type \"" << *std::any_cast<std::shared_ptr<data_type>>(args[0]["returnType"])
                        << "\" and \"" << *std::any_cast<std::shared_ptr<data_type>>(args[1]["retElementType"]) << "\" not match" << std::endl;
            exit(0);
        }
        result["returnType"] = args[0]["returnType"];
    }
    // 由于没有return语句，需要这时候把返回值复制到return的地方
    this->codes.push_back(quaternary("return",
            Operand{Offset, std::any_cast<int>(args[1]["retAddress"])},
            Operand{Literal, std::any_cast<element_type>(args[1]["retElementType"]).dataType->siz},
            Operand{Offset, this->nowFunctionRetAddress}));
    this->codes.push_back(quaternary{"leave", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}});
    //先把返回的临时变量删了
    popSymbol();
    // 注意这时在编译中需要把形参pop出去
    int argsnum = std::any_cast<int>(args[0]["symbolNum"]);
    for (int i = 0; i < argsnum; i++)
    {
        popSymbol();
    }

}
void Semantic::act97_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act98_(std::vector<attribute> &args, attribute &result) {
    // IF表达式 -> if 表达式 M1 函数表达式语句块 M2 else 函数表达式语句块
    /**
     * 表达式code
     * M1code jz 表达式 M2 + 1
     * M1 + 1 : 语句块code
     * M2code j L
     * M2 + 1 : else部分code
     * L 
     */
    /**
     * 在实际执行过程中，两个函数表达式语句块返回的地址应该是一样的，但是在编译的过程中用于模拟的c_esp不一样，因为相当于前一个函数表达式语句块的内容还没有释放完全
     * 
     */
    // result["symbolNum"] = args[0]["symbolNum"];
    // result["address"] = args[0]["retAddress"];
    // result["elementType"] = args[0]["retElementType"];

    // result["symbolNum"] = 1; //这一个返回值
    // result["retAddress"] = sym.relativeAddress;
    // result["retElementType"] = retElementType;
    int M1 = std::any_cast<int>(args[2]["codeID"]), M2 = std::any_cast<int>(args[4]["codeID"]);
    int address1 = std::any_cast<int>(args[3]["retAddress"]), address2 = std::any_cast<int>(args[6]["retAddress"]);
    std::cerr << address1 << ' ' << address2 << std::endl;
    assert(address1 == address2);
    return;

    element_type elementType1 = std::any_cast<element_type>(args[4]["retElementType"]);
    element_type elementType2 = std::any_cast<element_type>(args[8]["retElementType"]);
    // 如果这俩类型不一样直接报错，我不管了
    if(*elementType1.dataType != *elementType2.dataType)
    {
        std::cout << "[ERROR] [SEMANTIC] type \"" << elementType1.dataType << "\" and \"" << elementType2.dataType << "\" not match" << std::endl;
        exit(0);
    }
    int L = codes.size();
    if(std::any_cast<element_type>(args[1]["elementType"]).readType == LITERAL)
        codes[M1] = quaternary{"jz", Operand{Literal, std::any_cast<int>(args[1]["val"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    else
        codes[M1] = quaternary{"jz", Operand{Offset, std::any_cast<int>(args[1]["address"])}, Operand{Literal, 0}, Operand{Lable, M2 + 1}};
    codes[M2] = quaternary{"j", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Lable, L + 1}};
    codes.push_back(quaternary{"null", Operand{Literal, 0}, Operand{Literal, 0}, Operand{Literal, 0}});
}
void Semantic::act99_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act100_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act101_(std::vector<attribute> &args, attribute &result) {
    // M_FOR -> /zero
    result["codeID"] = (int)codes.size();
    codes.push_back(quaternary{"null", Operand{Offset, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    codes.push_back(quaternary{"null", Operand{Offset, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    codes.push_back(quaternary{"null", Operand{Offset, 0}, Operand{Literal, 0}, Operand{Lable, 0}});
    // 通过先插入M的方式解决“需要规约到上层才知道要往里面加入语句”的问题和需要回填的问题
}
void Semantic::act102_(std::vector<attribute> &args, attribute &result) {
    // 类型 -> /[ 类型 /; /int /]
    if (std::any_cast<int>(args[3]["val"]) <= 0)
    {
        std::cout << "[ERROR] [SEMANTIC] array size must be greater than 0." << std::endl;
        exit(0);
    }
    result["dataType"] = data_type::create(ARRAY_TYPE,
        std::any_cast<int>(args[3]["val"]),
        std::any_cast<std::shared_ptr<data_type>>(args[1]["dataType"]));
}
void Semantic::act103_(std::vector<attribute> &args, attribute &result) {
    // 元素 -> /[ 数组元素列表 /]
    // 检查数组元素列表不为空
    auto array_list = std::any_cast<std::vector<std::pair<element_type, std::pair<bool, int>>>>(args[1]["arrayList"]);
    if (array_list.empty())
    {
        std::cout << "[ERROR] [SEMANTIC] array element list is empty." << std::endl;
        exit(0);
    }
    // 注意原本是反的
    reverse(array_list.begin(), array_list.end());

    // 为整个数组申请临时变量
    std::shared_ptr<data_type> baseType = array_list[0].first.dataType;
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = data_type::create(ARRAY_TYPE, (int)array_list.size(), baseType);
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp;
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
    c_esp += sym.type.dataType->siz;
    pushTempSymbol(sym);
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;

    // 检查所有数据类型是否相同的同时复制到新增临时变量
    int nowRelativeAddress = sym.relativeAddress;
    for (int i = 0; i < (int)array_list.size(); i++)
    {
        if (*array_list[i].first.dataType != *baseType)
        {
            std::cout << "[ERROR] [SEMANTIC] array element type is not same." << std::endl;
            exit(0);
        }
        if (array_list[i].first.readType == LITERAL)
        {
            codes.push_back(quaternary(":=", Operand{Literal, array_list[i].second.second}, Operand{Literal, array_list[i].first.dataType->siz}, Operand{Offset, nowRelativeAddress}));
        }
        else if (array_list[i].second.first)
        {
            codes.push_back(quaternary(":=", Operand{Address, array_list[i].second.second}, Operand{Literal, array_list[i].first.dataType->siz}, Operand{Offset, nowRelativeAddress}));
        }
        else
        {
            codes.push_back(quaternary(":=", Operand{Offset, array_list[i].second.second}, Operand{Literal, array_list[i].first.dataType->siz}, Operand{Offset, nowRelativeAddress}));
        }
        nowRelativeAddress += array_list[i].first.dataType->siz;
    }

    // 数组列表也有临时变量计数
    result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]) + 1;

}
void Semantic::act104_(std::vector<attribute> &args, attribute &result) {
    // 数组元素列表 -> 空
    std::vector<std::pair<element_type, std::pair<bool, int>>> array_list; // bool 是否为绝对地址 int 是字面量的值或偏移量
    result["arrayList"] = array_list;
    result["symbolNum"] = 0;
}
void Semantic::act105_(std::vector<attribute> &args, attribute &result) {
    // 数组元素列表 -> 表达式
    std::vector<std::pair<element_type, std::pair<bool, int>>> array_list; // bool 是否为绝对地址 int 是字面量的值或偏移量
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
    {
        array_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["val"]))));
    }
    else if (args[0].count("address"))
    {
        array_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["address"]))));
    }
    else
    {
        array_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(true, std::any_cast<int>(args[0]["absoluteAddress"]))));
    }
    result["arrayList"] = array_list; // 倒着插入的
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]);
}
void Semantic::act106_(std::vector<attribute> &args, attribute &result) {
    // 数组元素列表 -> 表达式 /, 数组元素列表
    auto array_list = std::any_cast<std::vector<std::pair<element_type, std::pair<bool, int>>>>(args[2]["arrayList"]);
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
    {
        array_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["val"]))));
    }
    else if (args[0].count("address"))
    {
        array_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["address"]))));
    }
    else
    {
        array_list.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(true, std::any_cast<int>(args[0]["absoluteAddress"]))));
    }
    result["arrayList"] = array_list; // 倒着插入的
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
}
void Semantic::act107_(std::vector<attribute> &args, attribute &result) {
    // 元素 -> 元素 /[ 表达式 /]
    // 检查是否可以数组下标
    element_type src_ele_type = std::any_cast<element_type>(args[0]["elementType"]);
    element_type index_ele_type = std::any_cast<element_type>(args[2]["elementType"]);
    if (src_ele_type.dataType->type != ARRAY_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\":" << 
        *src_ele_type.dataType << " is not a array." << std::endl;
        exit(0);
    }
    if (index_ele_type.dataType->type != I32_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[2]["name"]) << "\":" << 
        *index_ele_type.dataType << " is not a int." << std::endl;
        exit(0);
    }

    element_type result_type;
    result_type.readType = std::any_cast<element_type>(args[0]["elementType"]).readType;
    if (index_ele_type.readType == LITERAL)
        result_type.dataType = src_ele_type.dataType->get_sub_class(std::any_cast<int>(args[2]["val"]));
    else
        result_type.dataType = src_ele_type.dataType->get_sub_class(0);

    result["elementType"] = result_type;

    // 声明临时变量存储该数组元素绝对地址
    symbolEntry temp_sym;
    temp_sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    temp_sym.type.dataType = data_type::create(REFER_TYPE, result_type.dataType); // 这些信息没有用处
    temp_sym.type.readType = TEMPORARY;
    temp_sym.relativeAddress = c_esp;
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, temp_sym.type.dataType->siz}, Operand{Literal, 0}));
    c_esp += temp_sym.type.dataType->siz;
    pushTempSymbol(temp_sym);

    result["absoluteAddress"] = temp_sym.relativeAddress;
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]) + 1;
    result["name"] = std::any_cast<std::string>(args[0]["name"]) + "[]";
    
    if (args[0].count("address"))
    {
        // 计算该地址的四元式
        quaternary quat;
        // 1 计算元素相对ebp偏移量,先乘再加
        quat.op = "*";
        quat.arg1 = Operand{Literal, result_type.dataType->siz};
        if (args[2].count("val"))
        {
            quat.arg2 = Operand{Literal, std::any_cast<int>(args[2]["val"])};
        }
        else if (args[2].count("address"))
        {
            quat.arg2 = Operand{Offset, std::any_cast<int>(args[2]["address"])};
        }
        else
        {
            quat.arg2 = Operand{Address, std::any_cast<int>(args[2]["absoluteAddress"])};
        }
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);

        quat.op = "+";
        quat.arg1 = Operand{Offset, temp_sym.relativeAddress};
        quat.arg2 = Operand{Literal, std::any_cast<int>(args[0]["address"])};
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);
        
        // 2 计算数组绝对地址到临时变量(加一个ebp)
        quat.op = "sea";
        quat.arg1 = Operand{Offset, temp_sym.relativeAddress};
        quat.arg2 = Operand{Literal, 0};
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);
        
    }
    else
    {
        // 计算该地址的四元式
        quaternary quat;
        // 1 计算元素相对数组起始偏移量,乘
        quat.op = "*";
        quat.arg1 = Operand{Literal, result_type.dataType->siz};
        if (args[2].count("val"))
        {
            quat.arg2 = Operand{Literal, std::any_cast<int>(args[2]["val"])};
        }
        else if (args[2].count("address"))
        {
            quat.arg2 = Operand{Offset, std::any_cast<int>(args[2]["address"])};
        }
        else
        {
            quat.arg2 = Operand{Address, std::any_cast<int>(args[2]["absoluteAddress"])};
        }
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);

        // 2 计算数组绝对地址到临时变量(加数组绝对地址)
        quat.op = "+";
        quat.arg1 = Operand{Offset, temp_sym.relativeAddress};
        quat.arg2 = Operand{Offset, std::any_cast<int>(args[0]["absoluteAddress"])};
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);
    }
}
void Semantic::act108_(std::vector<attribute> &args, attribute &result) {
    // 可迭代结构 -> 表达式
    // 必须是数组
    element_type ele_type = std::any_cast<element_type>(args[0]["elementType"]);
    if (ele_type.dataType->type != ARRAY_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] " << std::any_cast<std::string>(args[0]["name"]) << " are not array" << std::endl;
        exit(0);
    }

    // 用于指示是int..int还是某个数组
    result["IterativeDataType"] = ele_type.dataType;

    if (args[0].count("address"))
        result["arrayAddress"] = args[0]["address"];
    else
        result["arrayAbsoluteAddress"] = args[0]["absoluteAddress"];

    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]);
}
void Semantic::act109_(std::vector<attribute> &args, attribute &result) {
    // 类型 -> /[ 元组类型内部 /]
    auto dataTypeList = std::any_cast<std::vector<std::shared_ptr<data_type>>>(args[1]["dataTypeList"]);
    // 注意是反的
    reverse(dataTypeList.begin(), dataTypeList.end());
    result["dataType"] = data_type::create(TUPLE_TYPE, (int)dataTypeList.size(), dataTypeList);
}
void Semantic::act110_(std::vector<attribute> &args, attribute &result) {
    // 元组类型内部 -> 类型 /, 类型列表
    auto dataTypeList = std::any_cast<std::vector<std::shared_ptr<data_type>>>(args[2]["dataTypeList"]);
    dataTypeList.push_back(std::any_cast<std::shared_ptr<data_type>>(args[0]["dataType"]));
    result["dataTypeList"] = dataTypeList;
}
void Semantic::act111_(std::vector<attribute> &args, attribute &result) {
    // 类型列表 -> 空
    result["dataTypeList"] = std::vector<std::shared_ptr<data_type>>();
}
void Semantic::act112_(std::vector<attribute> &args, attribute &result) {
    // 类型列表 -> 类型
    result["dataTypeList"] = std::vector<std::shared_ptr<data_type>>{std::any_cast<std::shared_ptr<data_type>>(args[0]["dataType"])};
}
void Semantic::act113_(std::vector<attribute> &args, attribute &result) {
    // 类型列表 -> 类型 /, 类型列表
    auto dataTypeList = std::any_cast<std::vector<std::shared_ptr<data_type>>>(args[2]["dataTypeList"]);
    dataTypeList.push_back(std::any_cast<std::shared_ptr<data_type>>(args[0]["dataType"]));
    result["dataTypeList"] = dataTypeList;
}
void Semantic::act114_(std::vector<attribute> &args, attribute &result) {
    // 元素 -> /( 元组赋值内部 /)
    // 检查数组元素列表不为空
    auto tuple_list = std::any_cast<std::vector<std::pair<element_type, std::pair<bool, int>>>>(args[1]["tupleList"]);
    // 注意原本是反的
    reverse(tuple_list.begin(), tuple_list.end());
    // 为整个元组申请临时变量
    std::vector<std::shared_ptr<data_type>> typeList;
    for (auto &[ele, _] : tuple_list)
    {
        typeList.push_back(ele.dataType);
    }
    symbolEntry sym;
    sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    sym.type.dataType = data_type::create(TUPLE_TYPE, (int)tuple_list.size(), typeList);
    sym.type.readType = TEMPORARY;
    sym.relativeAddress = c_esp;
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, sym.type.dataType->siz}, Operand{Literal, 0}));
    c_esp += sym.type.dataType->siz;
    pushTempSymbol(sym);
    result["name"] = sym.name;
    result["elementType"] = sym.type;
    result["address"] = sym.relativeAddress;

    // 全部复制到新增临时变量
    int nowRelativeAddress = sym.relativeAddress;
    for (int i = 0; i < (int)tuple_list.size(); i++)
    {
        if (tuple_list[i].first.readType == LITERAL)
        {
            codes.push_back(quaternary(":=", Operand{Literal, tuple_list[i].second.second}, Operand{Literal, tuple_list[i].first.dataType->siz}, Operand{Offset, nowRelativeAddress}));
        }
        else if (tuple_list[i].second.first)
        {
            codes.push_back(quaternary(":=", Operand{Address, tuple_list[i].second.second}, Operand{Literal, tuple_list[i].first.dataType->siz}, Operand{Offset, nowRelativeAddress}));
        }
        else
        {
            codes.push_back(quaternary(":=", Operand{Offset, tuple_list[i].second.second}, Operand{Literal, tuple_list[i].first.dataType->siz}, Operand{Offset, nowRelativeAddress}));
        }
        nowRelativeAddress += tuple_list[i].first.dataType->siz;
    }

    // 元组列表也有临时变量计数
    result["symbolNum"] = std::any_cast<int>(args[1]["symbolNum"]) + 1;
}
void Semantic::act115_(std::vector<attribute> &args, attribute &result) {
    // 元组赋值内部 -> 表达式 /, 元组赋值列表
    auto tupleList = std::any_cast<std::vector<std::pair<element_type, std::pair<bool, int>>>>(args[2]["tupleList"]);
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["val"]))));
    }
    else if (args[0].count("address"))
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["address"]))));
    }
    else
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(true, std::any_cast<int>(args[0]["absoluteAddress"]))));
    }
    result["tupleList"] = tupleList;
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
}
void Semantic::act116_(std::vector<attribute> &args, attribute &result) {
    // 元组赋值列表 -> 空
    result["tupleList"] = std::vector<std::pair<element_type, std::pair<bool, int>>>();
    result["symbolNum"] = 0;
}
void Semantic::act117_(std::vector<attribute> &args, attribute &result) {
    // 元组赋值列表 -> 表达式
    std::vector<std::pair<element_type, std::pair<bool, int>>> tupleList;
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["val"]))));
    }
    else if (args[0].count("address"))
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["address"]))));
    }
    else
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(true, std::any_cast<int>(args[0]["absoluteAddress"]))));
    }
    result["tupleList"] = tupleList;
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]);
}
void Semantic::act118_(std::vector<attribute> &args, attribute &result) {
    // 元组赋值列表 -> 表达式 /, 元组赋值列表
    auto tupleList = std::any_cast<std::vector<std::pair<element_type, std::pair<bool, int>>>>(args[2]["tupleList"]);
    if (std::any_cast<element_type>(args[0]["elementType"]).readType == LITERAL)
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["val"]))));
    }
    else if (args[0].count("address"))
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(false, std::any_cast<int>(args[0]["address"]))));
    }
    else
    {
        tupleList.push_back(std::make_pair(std::any_cast<element_type>(args[0]["elementType"]),
        std::make_pair(true, std::any_cast<int>(args[0]["absoluteAddress"]))));
    }
    result["tupleList"] = tupleList;
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + std::any_cast<int>(args[2]["symbolNum"]);
}
void Semantic::act119_(std::vector<attribute> &args, attribute &result) {
    // 元素 -> 元素 /. /int
    // 检查是否是元组
    element_type src_ele_type = std::any_cast<element_type>(args[0]["elementType"]);
    if (src_ele_type.dataType->type != TUPLE_TYPE)
    {
        std::cout << "[ERROR] [SEMANTIC] \"" << std::any_cast<std::string>(args[0]["name"]) << "\":" << *src_ele_type.dataType << " is not a tuple." << std::endl;
        exit(0);
    }

    int tupleEleOffset = 0;
    element_type result_type;
    result_type.readType = std::any_cast<element_type>(args[0]["elementType"]).readType;
    result_type.dataType = src_ele_type.dataType->get_sub_class(std::any_cast<int>(args[2]["val"]), tupleEleOffset);

    result["elementType"] = result_type;

    // 声明临时变量存储该元组元素绝对地址
    symbolEntry temp_sym;
    temp_sym.name = "TEMP" + std::to_string(tempSymbolIDTable.size());
    temp_sym.type.dataType = data_type::create(REFER_TYPE, result_type.dataType); // 这些信息没有用处
    temp_sym.type.readType = TEMPORARY;
    temp_sym.relativeAddress = c_esp;
    codes.push_back(quaternary("push", Operand{Literal, 0}, Operand{Literal, temp_sym.type.dataType->siz}, Operand{Literal, 0}));
    c_esp += temp_sym.type.dataType->siz;
    pushTempSymbol(temp_sym);

    result["absoluteAddress"] = temp_sym.relativeAddress;
    result["symbolNum"] = std::any_cast<int>(args[0]["symbolNum"]) + 1;
    result["name"] = std::any_cast<std::string>(args[0]["name"]) + "." + std::to_string(std::any_cast<int>(args[2]["val"]));

    if (args[0].count("address"))
    {
        // 计算该地址的四元式
        quaternary quat;
        // 1 计算元素相对ebp偏移量,加
        quat.op = "+";
        quat.arg1 = Operand{Literal, tupleEleOffset};
        quat.arg2 = Operand{Literal, std::any_cast<int>(args[0]["address"])};
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);

        // 2 计算元组绝对地址到临时变量(加一个ebp)
        quat.op = "sea";
        quat.arg1 = Operand{Offset, temp_sym.relativeAddress};
        quat.arg2 = Operand{Literal, 0};
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);
    }
    else
    {
        // 计算该地址的四元式
        quaternary quat;
        // 1 计算数组绝对地址到临时变量(加数组绝对地址)
        quat.op = "+";
        quat.arg1 = Operand{Literal, tupleEleOffset};
        quat.arg2 = Operand{Offset, std::any_cast<int>(args[0]["absoluteAddress"])};
        quat.result = Operand{Offset, temp_sym.relativeAddress};
        codes.push_back(quat);
    }
}
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