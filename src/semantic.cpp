#include "semantic.h"
#include <iostream>
#include <fstream>

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
    &Semantic::act50_
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


void Semantic::init()
{
    quad_num = begin_quad_num;
    codes.resize(quad_num);
}

void Semantic::act0_(std::vector<attribute> &args, attribute &result)
{
    // PROGRAM -> SHENG_MING_CHUAN
    
    // 检查是否含有main函数
    // if (!this->functionTable.count({"main", {}, {}}))
    // {
    //     std::cout << "[ERROR] [SEMANTIC] No main function" << std::endl;
    //     exit(0);
    // }
    
    // 输出中间代码
    const std::string filename = "parse/intermediate.code";
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
        std::cout << "[ERROR] [SEMANTIC] " << filename << " is not exist" << std::endl;
        exit(0);
    }

    // 1 调用main函数 (栈压入返回值空间、函数返回地址、函数参数空间)
    fout << "push" << std::endl;
    // 2

    this->functionTable.clear(); // 清空函数表
    
    fout.close();
}

// GPT发力了
void Semantic::act1_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act2_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act3_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act4_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act5_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act6_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act7_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act8_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act9_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act10_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act11_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act12_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act13_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act14_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act15_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act16_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act17_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act18_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act19_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act20_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act21_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act22_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act23_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act24_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act25_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act26_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act27_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act28_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act29_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act30_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act31_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act32_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act33_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act34_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act35_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act36_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act37_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act38_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act39_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act40_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act41_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act42_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act43_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act44_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act45_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act46_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act47_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act48_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act49_(std::vector<attribute> &args, attribute &result) {}
void Semantic::act50_(std::vector<attribute> &args, attribute &result) {}


void Semantic::tact0_(attribute &result) {}
void Semantic::tact1_(attribute &result) {}
void Semantic::tact2_(attribute &result) {
    std::cerr << "test:tact2_" << std::endl; 
}
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