#include "generation.h"
#include <algorithm>
#include <assert.h>

int interpreter(std::vector<quaternary> &code)
{
    static char mem[100000];
    
    void* ebp = mem + 50, *esp = mem + 100;
    int eip = 98;
    while (code[eip].op != "end")
    {
        // std::cerr << eip << std::endl;
        // std::cerr << eip << std::endl;
        auto [op, arg1, arg2, result] = code[eip];
        if(op == "call")
        {
            *(int *)esp = eip + 1;
            esp += 4;
            eip = result.value;
        }
        else if (op == "build")
        {
            *(int *)esp = (char*)ebp - mem;
            ebp = esp;
            esp += 4;
            eip++;
        }
        else if(op == "end")
        {
            break;
        }
        else if(op == "leave")
        {
            eip = *(int *)(ebp - 4);
            esp = ebp - 4;
            ebp = mem + *(int *)ebp;
        }
        else if(op == "push")
        {
            void *dst = esp;
            if (arg1.type == Literal)
            {
                *(int *)(dst) = arg1.value;
            }
            else
            {
                void *src = arg1.type == Offset ? ebp + arg1.value : mem + *(int *)(ebp + arg1.value);
                memcpy(dst, src, arg2.value);
            }
            esp += arg2.value;
            eip++;
        }
        else if(op == "pop")
        {
            esp -= arg2.value;
            eip++;
        }
        else if(op == ":=" || op == "return")
        {
            void *dst = result.type == Offset ? ebp + result.value : mem + *(int*)(ebp + result.value);
            if(arg1.type == Literal)
            {
                *(int *)(dst) = arg1.value;
            }
            else
            {
                void *src = arg1.type == Offset ? ebp + arg1.value : mem + *(int*)(ebp + arg1.value);
                memcpy(dst, src, arg2.value);
            }
            eip++;
        }
        else if(op == "+" || op == "-" || op == "*" || op == "/" || op == "%" ||
             op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=")
        {
            int a = arg1.type == Literal ? arg1.value : arg1.type == Offset ? *(int *)(ebp + arg1.value) : *(int *)(mem + *(int*)(ebp + arg1.value));
            int b = arg2.type == Literal ? arg2.value : arg2.type == Offset ? *(int *)(ebp + arg2.value) : *(int *)(mem + *(int*)(ebp + arg2.value));
            int c;
            if(op == "+")
                c = a + b;
            else if(op == "-")
                c = a - b;
            else if(op == "*")
                c = a * b;
            else if(op == "/")
                c = a / b;
            else if(op == "%")
                c = a % b;
            else if(op == "==")
                c = a == b;
            else if(op == "!=")
                c = a != b;
            else if(op == ">")
                c = a > b;
            else if(op == "<")
                c = a < b;
            else if(op == ">=")
                c = a >= b;
            else if(op == "<=")
                c = a <= b;
            if(result.type == Offset)
                *(int *)(ebp + result.value) = c;
            else if(result.type == Address)
                *(int *)(mem + *(int*)(ebp + result.value)) = c;
            eip++;
        }
        else if (op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%=")
        {
            int b = arg1.type == Literal ? arg1.value : arg1.type == Offset ? *(int *)(ebp + arg1.value) : *(int *)(mem + *(int*)(ebp + arg1.value));
            int a = result.type == Literal ? result.value : result.type == Offset ? *(int *)(ebp + result.value) : *(int *)(mem + *(int*)(ebp + result.value));
            int c;
            if(op == "+=")
                c = a + b;
            else if(op == "-=")
                c = a - b;
            else if(op == "*=")
                c = a * b;
            else if(op == "/=")
                c = a / b;
            else if(op == "%=")
                c = a % b;
            if(result.type == Offset)
                *(int *)(ebp + result.value) = c;
            else if(result.type == Address)
                *(int *)(mem + *(int*)(ebp + result.value)) = c;
            eip++;
        }
        else if(op == "j")
        {
            eip = result.value;
        }
        else if (op == "jnz" || op == "jz")
        {
            int a = arg1.type == Literal ? arg1.value : arg1.type == Offset ? *(int *)(ebp + arg1.value) : *(int *)(mem + *(int*)(ebp + arg1.value));
            int c;
            if(op == "jnz")
                c = a;
            else if(op == "jz")
                c = !a;
            if(c)
                eip = result.value;
            else
                eip++;
        }
        else if(op == "j>=" || op == "j<=" || op == "j<" || op == "j>")
        {
            int a = arg1.type == Literal ? arg1.value : arg1.type == Offset ? *(int *)(ebp + arg1.value) : *(int *)(mem + *(int*)(ebp + arg1.value));
            int b = arg2.type == Literal ? arg2.value : arg2.type == Offset ? *(int *)(ebp + arg2.value) : *(int *)(mem + *(int*)(ebp + arg2.value));
            int c;
            if(op == "j>=")
                c = a >= b;
            else if(op == "j<=")
                c = a <= b;
            else if(op == "j<")
                c = a < b;
            else if(op == "j>")
                c = a > b;
            if(c)
                eip = result.value;
            else
                eip++;
        }
        else if(op == "sea")
        {
            // std::cerr << arg1.value << std::endl;
            // std::cerr << arg1.value + (char*)ebp - mem << std::endl;
            int a = arg1.type == Literal ? arg1.value : arg1.type == Offset ? *(int *)(ebp + arg1.value) : *(int *)(mem + *(int*)(ebp + arg1.value));
            if(result.type == Offset)
                *(int *)(ebp + result.value) = a + (char*)ebp - mem;
            else if(result.type == Address)
                *(int *)(mem + *(int *)(ebp + result.value)) = a + (char *)ebp - mem;
            eip++;
        }
        else if(op == "null")
        {
            eip++;
        }
        else if(op == "output")
        {
            if(arg1.type == Offset)
                std::cout << *(int *)(ebp + arg1.value) << std::endl;
            else if(arg1.type == Address)
                std::cout << *(int *)(mem + *(int*)(ebp + arg1.value)) << std::endl;
            else 
                std::cout << arg1.value << std::endl;
            eip++;
        }
        else if(op == "input")
        {
            int a;
            std::cin >> a;
            if (arg1.type == Offset)
                *(int *)(ebp + arg1.value) = a;
            else if (arg1.type == Address)
                *(int *)(mem + *(int *)(ebp + arg1.value)) = a;
            eip++;
        }
    }
    return 0;
}

std::string Generator::dstfilepath = "obj/main.s";
int Generator::beginpos = 98;

void Generator::generate(std::vector<quaternary> &code)
{
    std::ofstream fout(Generator::dstfilepath);
    if (!fout.is_open())
    {
        std::cerr << "[ERROR] [FILE] " << Generator::dstfilepath << " cannot be opened" << std::endl;
        exit(0);
    }
    
    // 文件开始
    this->header(fout);

    // 统计标号
    std::set<int> flags;
    flags.clear();
    for (int i = Generator::beginpos; i < code.size(); ++i)
    {
        if (code[i].op == "call" || code[i].op == "j" || code[i].op == "jz" || code[i].op == "jnz" ||
            code[i].op == "j>=" || code[i].op == "j<=" || code[i].op == "j<" || code[i].op == "j>")
        {
            flags.insert(code[i].result.value);
        }
    }

    //逐句翻译
    auto it = flags.begin();
    for (int i = Generator::beginpos; i < code.size(); ++i)
    {
        auto [op, arg1, arg2, result] = code[i];
        if (i == *it)
        {
            this->genFlag(i, fout);
            ++it;
        }

        if (op == "call" || op == "j")
        {
            this->genJmp(code[i], fout);
        }
        else if (op == "build")
        {
            this->genBuild(fout);
        }
        else if (op == "end")
        {
            this->genEnd(fout);
        }
        else if (op == "leave")
        {
            this->genLeave(fout);
        }
        else if (op == "push")
        {
            this->genPush(code[i], fout);
        }
        else if (op == "pop")
        {
            this->genPop(arg2.value, fout);
        }
        else if (op == ":=" || op == "return")
        {
            this->genCopy(code[i], fout);
        }
        else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%" )
        {
            this->genCal(code[i], fout);
        }
        else if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=")
        {
            this->genRop(code[i], fout);
        }
        else if (op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%=")
        {
            this->genAssign(code[i], fout);
        }
        else if (op == "jnz" || op == "jz")
        {
            this->genJt(code[i], fout);
        }
        else if (op == "j>=" || op == "j<=" || op == "j<" || op == "j>")
        {
            this->genJrop(code[i], fout);
        }
        else if (op == "sea")
        {
            this->genSea(code[i], fout);
        }
        else if (op == "null")
        {
        }
        else if (op == "output")
        {
            this->genOutput(code[i], fout);
        }
        else if (op == "input")
        {
            this->genInput(code[i], fout);
        }
    }
    
    fout.close();
}

void GeneratorX86::header(std::ofstream &fout)
{
    fout << "    .globl _main\n";
    fout << "    .extern _input\n";
    fout << "    .extern _output\n";
    fout << "    .extern _output\n";
    fout << "    .text\n";
    fout << "_main:\n";
}

void GeneratorX86::loadValTo(Operand &oper, std::string reg, std::ofstream &fout)
{
    if (oper.type == Literal)
    {
        fout << "    movl $" << oper.value << ", %" << reg << "\n";
    }
    else if (oper.type == Offset)
    {
        fout << "    movl " << -oper.value << "(%ebp), %" << reg << "\n";
    }
    else if (oper.type == Address)
    {
        fout << "    movl " << -oper.value << "(%ebp), %ebx\n";
        fout << "    movl (%ebx), %" << reg << "\n";
    }
}

void GeneratorX86::loadAdrTo(int address, std::string reg, std::ofstream &fout)
{
    fout << "    movl " << -address << "(%ebp), %" << reg << "\n";
}

void GeneratorX86::storeValTo(Operand &oper, std::string reg, std::ofstream &fout)
{
    if (oper.type == Offset)
        fout << "    movl %" << reg << "," << -oper.value << "(%ebp)\n";
    else if (oper.type == Address)
    {
        this->loadAdrTo(oper.value, "ebx", fout);
        fout << "    movl %" << reg << ", (%ebx)\n";
    }
}

void GeneratorX86::genFlag(int flag, std::ofstream &fout)
{
    fout << "L" << flag << ":\n";
}

void GeneratorX86::genJmp(quaternary &quat, std::ofstream &fout)
{
    if (quat.op == "call")
    {
        fout << "    call L" << quat.result.value << "\n";
    }
    else if (quat.op == "j")
    {
        fout << "    jmp L" << quat.result.value << "\n";
    }
}

void GeneratorX86::genBuild(std::ofstream &fout)
{
    fout << "    pushl %ebp\n";
    fout << "    movl %esp, %ebp\n";
}

void GeneratorX86::genEnd(std::ofstream &fout)
{
    fout << "    xor %eax, %eax\n";
    fout << "    ret\n";
}

void GeneratorX86::genCopy(quaternary &quat, std::ofstream &fout)
{
    if (quat.arg2.value == 4)
    {
        this->loadValTo(quat.arg1, "eax", fout);
        
        if (quat.result.type == Offset)
        {
            fout << "    movl %eax, " << -quat.result.value << "(%ebp)\n";
        }
        else if (quat.result.type == Address)
        {
            this->loadAdrTo(quat.result.value, "ebx", fout);
            fout << "    movl %eax, (%ebx)\n";
        }
    }
    else if (quat.arg2.value > 4)
    {
        fout << "    std\n";
        if(quat.arg1.type == Offset)
            fout << "    leal " << -quat.arg1.value << "(%ebp), %esi\n";
        else
            fout << "    movl " << -quat.arg1.value << "(%ebp), %esi\n";
        if(quat.result.type == Offset)
            fout << "    leal " << -quat.result.value << "(%ebp), %edi\n";
        else
            fout << "    movl " << -quat.result.value << "(%ebp), %edi\n";
        fout << "    movl $" << quat.arg2.value << ", %ecx\n";
        fout << "    rep movsb\n";
    }
}

void GeneratorX86::genLeave(std::ofstream &fout)
{
    fout << "    leave\n";
    fout << "    ret\n";
}

void GeneratorX86::genPush(quaternary &quat, std::ofstream &fout)
{
    if (quat.arg2.value == 4)
    {
        if (quat.arg1.type == Literal)
        {
            fout << "    pushl $" << quat.arg1.value << "\n";
        }
        else if (quat.arg1.type == Offset)
        {
            fout << "    pushl " << -quat.arg1.value << "(%ebp)\n";
        }
        else if (quat.arg1.type == Address)
        {
            fout << "    leal " << -quat.arg1.value << "(%ebp), %eax\n";
            fout << "    pushl (%ebx)\n";
        }
    }
    else if (quat.arg2.value > 4)
    {
        fout << "    subl $" << quat.arg2.value << ", %esp\n";
        if(quat.arg1.type == Offset)
            fout << "    leal " << -quat.arg1.value << "(%ebp), %esi\n";
        else
            fout << "    movl " << -quat.arg1.value << "(%ebp), %esi\n";
        fout << "    movl %esp, %eax\n";
        fout << "    addl $" << quat.arg2.value - 4 << ", %eax\n";
        fout << "    movl %eax, %edi\n";
        fout << "    std\n";
        fout << "    movl $" << quat.arg2.value << ", %ecx\n";
        fout << "    rep movsb\n";
        // if (quat.arg1.type != Literal)
        //     this->genCopy(quat, fout);
    }
}

void GeneratorX86::genPop(int siz, std::ofstream &fout)
{
    fout << "    addl $" << siz << ", %esp\n";
}

void GeneratorX86::genCal(quaternary &quat, std::ofstream &fout)
{
    this->loadValTo(quat.arg1, "eax", fout);
    if (quat.arg2.type == Address)
    {
        this->loadAdrTo(quat.arg2.value, "ebx", fout);
    }
    
    if (quat.op == "/" || quat.op == "%")
    {
        if (quat.arg2.type == Literal)
        {
            // 除法不允许除以立即数,需要先存到ecx
            this->loadValTo(quat.arg2, "ecx", fout);
        }
        fout << "    cltd\n"; // 扩展eax的符号位到edx上
    }

    if (quat.op == "+")
        fout << "    addl ";
    else if (quat.op == "-")
        fout << "    subl ";
    else if (quat.op == "*")
        fout << "    imull ";
    else if (quat.op == "/")
        fout << "    idivl ";
    else if (quat.op == "%")
        fout << "    idivl ";
    
    if (quat.arg2.type == Literal)
    {
        if (quat.op == "/" || quat.op == "%")
            fout << "%ecx";
        else
            fout << "$" << quat.arg2.value;
    }
    else if (quat.arg2.type == Offset)
        fout << -quat.arg2.value << "(%ebp)";
    else if (quat.arg2.type == Address)
        fout << "(%ebx)";
    
    fout << ", %eax\n";

    std::string ansreg = (quat.op == "%" ? "edx" : "eax");
    if (quat.result.type == Offset)
        fout << "    movl %" << ansreg << "," << -quat.result.value << "(%ebp)\n";
    else if (quat.result.type == Address)
    {
        this->loadAdrTo(quat.result.value, "ebx", fout);
        fout << "    movl %" << ansreg << ", (%ebx)\n";
    }
}

void GeneratorX86::genRop(quaternary &quat, std::ofstream &fout)
{
    if (quat.arg1.type == Literal && quat.arg2.type == Literal)
    {
        int result = 0;
        if (quat.op == "<" && quat.arg1.value < quat.arg2.value ||
            quat.op == "<=" && quat.arg1.value <= quat.arg2.value ||
            quat.op == ">" && quat.arg1.value > quat.arg2.value ||
            quat.op == ">=" && quat.arg1.value >= quat.arg2.value ||
            quat.op == "==" && quat.arg1.value == quat.arg2.value ||
            quat.op == "!=" && quat.arg1.value != quat.arg2.value)
        {
            result = 1;
        }
        else
        {
            result = 0;
        }
        if (quat.result.type == Offset)
            fout << "    movl $" << result << ", " << -quat.result.value << "(%ebp)\n";
        else if (quat.result.type == Address)
        {
            this->loadAdrTo(quat.result.value, "ebx", fout);
            fout << "    movl $" << result << ", (%ebx)\n";
        }
        return;
    }
    
    // 立即数不能作为目标操作数
    if (quat.arg1.type == Literal)
    {
        quaternary newquat;
        newquat.arg2 = quat.arg1;
        newquat.arg1 = quat.arg2;
        newquat.op = quat.op == "<" ? ">" : 
                     quat.op == ">" ? "<" : 
                     quat.op == "<=" ? ">=" : 
                     quat.op == ">=" ? "<=" : 
                     quat.op;
        this->genRop(newquat, fout);
        return;
    }

    this->loadValTo(quat.arg1, "eax", fout);
    if (quat.arg2.type == Address)
    {
        this->loadAdrTo(quat.arg2.value, "ebx", fout);
    }

    fout << "    cmpl ";

    if (quat.arg2.type == Literal)
        fout << "$" << quat.arg2.value;
    else if (quat.arg2.type == Offset)
        fout << -quat.arg2.value << "(%ebp)";
    else if (quat.arg2.type == Address)
        fout << "(%ebx)";

    fout << ", %eax\n";

    if (quat.op == "==")
        fout << "    sete %al\n";
    else if (quat.op == "!=")
        fout << "    setne %al\n";
    else if (quat.op == "<")
        fout << "    setl %al\n";
    else if (quat.op == ">")
        fout << "    setg %al\n";
    else if (quat.op == "<=")
        fout << "    setle %al\n";
    else if (quat.op == ">=")
        fout << "    setge %al\n";
        
    fout << "    movzbl %al, %eax\n"; // 将结果从al扩展到eax

    if (quat.result.type == Offset)
        fout << "    movl %eax," << -quat.result.value << "(%ebp)\n";
    else if (quat.result.type == Address)
    {
        this->loadAdrTo(quat.result.value, "ebx", fout);
        fout << "    movl %eax, (%ebx)\n";
    }
}

void GeneratorX86::genAssign(quaternary &quat, std::ofstream &fout)
{
    this->loadValTo(quat.result, "eax", fout);
    if (quat.arg1.type == Address)
    {
        this->loadAdrTo(quat.arg1.value, "ecx", fout);
    }

    if (quat.op == "/=" || quat.op == "%=")
    {
        if (quat.arg1.type == Literal)
        {
            // 除法不允许除以立即数,需要先存到ecx
            this->loadValTo(quat.arg2, "ecx", fout);
        }
        fout << "    cltd\n"; // 扩展eax的符号位到edx上
    }

    if (quat.op == "+=")
        fout << "    addl ";
    else if (quat.op == "-=")
        fout << "    subl ";
    else if (quat.op == "*=")
        fout << "    imull ";
    else if (quat.op == "/=")
        fout << "    idivl ";
    else if (quat.op == "%=")
        fout << "    idivl ";

    if (quat.arg2.type == Literal)
        fout << "%ecx";
    else if (quat.arg2.type == Offset)
        fout << -quat.arg2.value << "(%ebp)";
    else if (quat.arg2.type == Address)
        fout << "(%ecx)";

    fout << ", %eax\n";

    std::string ansreg = (quat.op == "%=" ? "edx" : "eax");
    if (quat.result.type == Offset)
        fout << "    movl %" << ansreg << "," << -quat.result.value << "(%ebp)\n";
    else if (quat.result.type == Address)
    {
        fout << "    movl %" << ansreg << ", (%ebx)\n";
    }
}


void GeneratorX86::genJt(quaternary &quat, std::ofstream &fout)
{
    if(quat.arg1.type == Literal)
    {
        if((quat.arg1.value == 0) == (quat.op == "jz"))
        {
            fout << "    j L" << quat.result.value << '\n';
        }
        return;
    }
    this->loadValTo(quat.arg1, "eax", fout);
    fout << "    cmpl $0, %eax\n";
    if(quat.op == "jz")
        fout << "    je L" << quat.result.value << '\n';
    else
        fout << "    jne L" << quat.result.value << '\n';
}


void GeneratorX86::genJrop(quaternary &quat, std::ofstream &fout)
{
    if (quat.arg1.type == Literal && quat.arg2.type == Literal)
    {
        if(quat.op == "j<" && quat.arg1.value < quat.arg2.value || 
            quat.op == "j<=" && quat.arg1.value <= quat.arg2.value || 
            quat.op == "j>" && quat.arg1.value > quat.arg2.value || 
            quat.op == "j>=" && quat.arg1.value >= quat.arg2.value)
        {
            fout << "    jmp L" << quat.result.value << '\n';
        }
        return;
    }
    
    // 立即数不能作为目标操作数
    if (quat.arg1.type == Literal)
    {
        quaternary newquat;
        newquat.arg2 = quat.arg1;
        newquat.arg1 = quat.arg2;
        newquat.op = quat.op == "<" ? ">" : 
                     quat.op == ">" ? "<" : 
                     quat.op == "<=" ? ">=" : 
                     quat.op == ">=" ? "<=" : 
                     quat.op;
        this->genJrop(newquat, fout);
        return;
    }

    this->loadValTo(quat.arg1, "eax", fout);
    if (quat.arg2.type == Address)
    {
        this->loadAdrTo(quat.arg2.value, "ebx", fout);
    }

    fout << "    cmpl ";

    if (quat.arg2.type == Literal)
        fout << "$" << quat.arg2.value;
    else if (quat.arg2.type == Offset)
        fout << -quat.arg2.value << "(%ebp)";
    else if (quat.arg2.type == Address)
        fout << "(%ebx)";

    fout << ", %eax\n";

    if(quat.op == "j<")
        fout << "    jl L" << quat.result.value << '\n';
    if(quat.op == "j<=")
        fout << "    jle L" << quat.result.value << '\n';
    if(quat.op == "j>")
        fout << "    jg L" << quat.result.value << '\n';
    if(quat.op == "j>=")
        fout << "    jge L" << quat.result.value << '\n';
}

void GeneratorX86::genSea(quaternary &quat, std::ofstream &fout)
{
    if (quat.arg1.type == Literal)
        fout << "    leal " << -quat.arg1.value << "(%ebp), %eax\n";
    else if (quat.arg1.type == Offset)
    {
        fout << "    movl " << -quat.arg1.value << "(%ebp), %eax\n";
        fout << "    negl %eax\n"; // 取反
        fout << "    addl %ebp, %eax\n";
    }
    
    this->storeValTo(quat.result, "eax", fout);
}

void GeneratorX86::genOutput(quaternary &quat, std::ofstream &fout)
{
    if(quat.arg1.type == Literal)
        fout << "    pushl $" << quat.arg1.value << '\n';
    else if(quat.arg1.type == Offset)
        fout << "    pushl " << -quat.arg1.value << "(%ebp)\n";
    else
    {
        this->loadAdrTo(quat.arg1.value, "ebx", fout);
        fout << "    pushl (%ebx)\n";
    }
    fout << "    call _output\n";
    fout << "    addl $4, %esp\n";
}

void GeneratorX86::genInput(quaternary &quat, std::ofstream &fout)
{
    fout << "    call _input\n";
    this->storeValTo(quat.arg1, "eax", fout);
}