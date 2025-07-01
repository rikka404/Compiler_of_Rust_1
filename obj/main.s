    .globl _main
    .extern _input
    .extern _output
    .extern _output
    .text
_main:
    call L100
    xor %eax, %eax
    ret
L100:
    pushl %ebp
    movl %esp, %ebp
    subl $16, %esp
    movl $1, %eax
    movl %eax, -4(%ebp)
    movl $2, %eax
    movl %eax, -8(%ebp)
    movl $3, %eax
    movl %eax, -12(%ebp)
    movl $4, %eax
    movl %eax, -16(%ebp)
    subl $20, %esp
    movl $5, %eax
    movl %eax, -20(%ebp)
    cld
    leal -4(%ebp), %esi
    leal -24(%ebp), %edi
    movl $16, %ecx
    rep movsb
    pushl $0
    movl $4, %eax
    addl $20, %eax
    movl %eax,-40(%ebp)
    movl -40(%ebp), %eax
    negl %eax
    addl %ebp, %eax
    movl %eax,-40(%ebp)
    pushl $0
    movl $4, %eax
    imull $1, %eax
    movl %eax,-44(%ebp)
    movl -40(%ebp), %eax
    subl -44(%ebp), %eax
    movl %eax,-44(%ebp)
    movl -44(%ebp), %ebx
    push (%ebx)
    call _output
    add $4, %esp
    addl $44, %esp
    leave
    ret
