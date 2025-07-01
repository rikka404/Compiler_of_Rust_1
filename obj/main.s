    .globl _main
    .extern _input
    .extern _output
    .extern _output
    .text
_main:
    call L106
    xor %eax, %eax
    ret
L100:
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
L106:
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
    addl $5, %eax
    movl %eax,-12(%ebp)
    pushl $0
    movl -12(%ebp), %eax
    cmpl $10, %eax
    setg %al
    movzbl %al, %eax
    movl %eax,-16(%ebp)
    movl -16(%ebp), %eax
    cmpl $0, %eax
    je L125
    pushl $0
    pushl -4(%ebp)
    pushl -4(%ebp)
    call L100
    addl $4, %esp
    addl $4, %esp
    push -20(%ebp)
    call _output
    add $4, %esp
    addl $4, %esp
    jmp L128
L125:
    movl $10, %eax
    movl -8(%ebp), %ebx
    movl %eax, (%ebx)
    push -4(%ebp)
    call _output
    add $4, %esp
L128:
    addl $16, %esp
    leave
    ret
