#include <iostream>
#include <vector>
#include <fstream>
#include "semantic.h"

int interpreter(std::vector<quaternary> &code);

class Generator
{
public:
    static std::string dstfilepath;
    static int beginpos;

    std::vector<int> flags;
    int nowfpos = 0;
    
    void generate(std::vector<quaternary> &code);
    virtual void header(std::ofstream &fout) = 0; // 生成头部
    
    // 具体翻译函数
    virtual void genFlag(int flag, std::ofstream &fout) = 0; // 生成标记
    virtual void genJmp(quaternary &quat, std::ofstream &fout) = 0; // 无条件跳转
    virtual void genBuild(std::ofstream &fout) = 0;
    virtual void genEnd(std::ofstream &fout) = 0;
    virtual void genCopy(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genLeave(std::ofstream &fout) = 0;
    virtual void genPush(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genPop(int siz, std::ofstream &fout) = 0;
    virtual void genCal(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genRop(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genAssign(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genJt(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genJrop(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genSea(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genOutput(quaternary &quat, std::ofstream &fout) = 0;
    virtual void genInput(quaternary &quat, std::ofstream &fout) = 0;
    
};


class GeneratorX86 : public Generator
{
    void header(std::ofstream &fout) override;

    void loadValTo(Operand &oper, std::string reg, std::ofstream &fout);
    void loadAdrTo(int address, std::string reg, std::ofstream &fout);

    void genFlag(int flag, std::ofstream &fout) override;
    void genJmp(quaternary &quat, std::ofstream &fout) override;
    void genBuild(std::ofstream &fout) override;
    void genEnd(std::ofstream &fout) override;
    void genCopy(quaternary &quat, std::ofstream &fout) override;
    void genLeave(std::ofstream &fout) override;
    void genPush(quaternary &quat, std::ofstream &fout) override;
    void genPop(int siz, std::ofstream &fout) override;
    void genCal(quaternary &quat, std::ofstream &fout) override;
    void genRop(quaternary &quat, std::ofstream &fout);
    void genAssign(quaternary &quat, std::ofstream &fout) override;
    // void genJt(quaternary &quat, std::ofstream &fout) override;
    // void genJrop(quaternary &quat, std::ofstream &fout) override;
    // void genSea(quaternary &quat, std::ofstream &fout) override;
    // void genOutput(quaternary &quat, std::ofstream &fout) override;
    // void genInput(quaternary &quat, std::ofstream &fout) override;
};