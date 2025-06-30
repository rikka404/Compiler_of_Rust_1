    .globl _main
    .extern _input
    .extern _output
    .text

_main:
    call L106             # L98
    xor %eax, %eax
    ret

# ===== 函数 L100 =====
L100:
    push %ebp             # build 栈帧建立
    mov %esp, %ebp

    sub $4, %esp          # L101: push 4 bytes临时空间

    mov 8(%ebp), %eax     # [-8] → 8(%ebp)
    add 12(%ebp), %eax    # [-12] → 12(%ebp)
    mov %eax, -4(%ebp)    # [4] → -4(%ebp)

    mov -4(%ebp), %eax    # return 值
    mov %eax, 16(%ebp)   # [-16] → -16(%ebp)

    leave                 # L104
    ret

# ===== 函数 L106 (main体) =====
L106:
    push %ebp             # build
    mov %esp, %ebp

    sub $4, %esp          # L107 为 input 结果分配空间
    call _input           # L108
    mov %eax, -4(%ebp)    # [4] → -4(%ebp)

    sub $4, %esp          # L109 为 sea 结果分配空间
    leal -4(%ebp), %eax   # sea 计算：4 → -4(%ebp)
    mov %eax, -8(%ebp)    # [8] → -8(%ebp)

    sub $4, %esp          # L111 为表达式结果分配空间
    mov -4(%ebp), %eax
    add $5, %eax
    mov %eax, -12(%ebp)   # [12] → -12(%ebp)

    sub $4, %esp          # L113 为条件预留空间
    mov -12(%ebp), %eax
    cmpl $10, %eax
    setg %al
    movzbl %al, %eax
    mov %eax, -16(%ebp)   # [16] → -16(%ebp)

    cmpl $0, -16(%ebp)    # jt [16], L125
    je L125               # L115

    sub $4, %esp          # L116
    mov -4(%ebp), %eax
    push %eax             # L117
    mov -4(%ebp), %eax
    push %eax             # L118
    call L100             # L119

    add $4, %esp          # L120
    add $4, %esp          # L121

    push -20(%ebp)        # L122 输出函数参数
    call _output
    add $4, %esp

    add $4, %esp          # L123 pop
    jmp L128              # L124

L125:
    mov -8(%ebp), %eax
    movl $10, (%eax)

    push -4(%ebp)         # L126
    call _output
    add $4, %esp

L127:
    # null 什么都不做

L128:
    add $16, %esp         # L129 清理空间
    leave
    ret
