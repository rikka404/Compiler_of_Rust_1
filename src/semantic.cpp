#include "semantic.h"
#include <iostream>
#include <fstream>

// 语义动作函数指针
std::vector<void (Semantic::*)(std::vector<attribute> &, attribute &)> Semantic::semanticActions = {
    &Semantic::act0_
};

void Semantic::act0_(std::vector<attribute> &args, attribute &result)
{
    // PROGRAM -> SHENG_MING_CHUAN
    
    // 检查是否含有main函数
    if (!this->functionTable.count({"main", {}, {}}))
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

    // 1 调用main函数 (栈压入返回值空间、函数返回地址、函数参数空间)
    fout << "push" << std::endl;
    // 2

    this->functionTable.clear(); // 清空函数表
    
    fout.close();
}
