    .globl _main
    .extern _input
    .extern _output
    .extern _output
    .text
_main:
L98:
    call L106
    xor %eax, %eax
    ret
    pushl %ebp
    movl %esp, %ebp
    pushl $0
    movl 8(%ebp), %eax
    addl 12(%ebp), %eax
    movl %eax,-4(%ebp)
    movl -4(%ebp), %eax
    movl %eax, 16(%ebp)
    leave
    ret
    addl $4, %esp
    pushl %ebp
    movl %esp, %ebp
    pushl $0
    call _input
    movl %eax,-4(%ebp)
    pushl $0
    leal -4(%ebp), %eax
    movl %eax,-8(%ebp)
    pushl $0
    movl -4(%ebp), %eax
    addl %ecx, %eax
    movl %eax,-12(%ebp)
    pushl $0
    movl -12(%ebp), %eax
    cmpl $10, %eax
    setg %al
    movzbl %al, %eax
    movl %eax,-16(%ebp)
    movl -16(%ebp), %eax
    cmpl eax, $0
    je L125
    pushl $0
    pushl -4(%ebp)
    pushl -4(%ebp)
    call L100
    addl $4, %esp
    addl $4, %esp
    leal -20(%ebp), %ebx
    push (ebx)
    call _output
    add $4, %esp
    addl $4, %esp
    jmp L128
    movl $10, %eax
    leal -8(%ebp), %ebx
    movl %eax, (%ebx)
    leal -4(%ebp), %ebx
    push (ebx)
    call _output
    add $4, %esp
    addl $16, %esp
    leave
    ret
