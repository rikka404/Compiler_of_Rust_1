#include <test.h>

static char mem[100000];

int test()
{
    void* ebp = mem + 50, *esp = mem + 100;
    int eip = 98;
    const std::vector<quaternary> &code = *codes;
    while (code[eip].op != "end")
    {
        // std::cerr << eip << std::endl;
        // std::cerr << eip << std::endl;
        auto [op, arg1, arg2, result] = code[eip];
        if(op == "call")
        {
            *(int *)esp = eip + 1;
            esp += 4;
            *(int *)esp = (char*)ebp - mem;
            ebp = esp;
            esp += 4;
            eip = result.value;
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
        else if(op == "leave")
        {
            eip = *(int *)(ebp - 4);
            esp = ebp - 4;
            ebp = mem + *(int *)ebp;
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
            if(op == "jnz")
                c = a;
            else if(op == "jz")
                c = !a;
            else if(op == "j>=")
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
        else if(op == "out")
        {
            if(arg1.type == Offset)
                std::cout << *(int *)(ebp + arg1.value) << std::endl;
            else if(arg1.type == Address)
                std::cout << *(int *)(mem + *(int*)(ebp + arg1.value)) << std::endl;
            else 
                std::cout << arg1.value << std::endl;
            eip++;
        }
    }
    return 0;
}
