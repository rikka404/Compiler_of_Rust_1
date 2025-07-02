    .globl _main
    .extern _input
    .extern _output
    .extern _output
    .text
_main:
    call L260
    xor %eax, %eax
    ret
L100:
    pushl %ebp
    movl %esp, %ebp
    pushl $0
    movl 16(%ebp), %eax
    addl 20(%ebp), %eax
    movl %eax,-4(%ebp)
    movl -4(%ebp), %eax
    movl $2, %ecx
    cltd
    idivl %ecx, %eax
    movl %eax,-4(%ebp)
    pushl $0
    movl 16(%ebp), %eax
    movl %eax, -8(%ebp)
    pushl $0
    movl -4(%ebp), %eax
    addl $1, %eax
    movl %eax,-12(%ebp)
    pushl $0
    movl 16(%ebp), %eax
    movl %eax, -16(%ebp)
L110:
    pushl $0
    movl -8(%ebp), %eax
    cmpl -4(%ebp), %eax
    setle %al
    movzbl %al, %eax
    movl %eax,-20(%ebp)
    movl -20(%ebp), %eax
    cmpl $0, %eax
    je L121
    pushl $0
    movl -12(%ebp), %eax
    cmpl 20(%ebp), %eax
    setle %al
    movzbl %al, %eax
    movl %eax,-24(%ebp)
    movl -24(%ebp), %eax
    cmpl $0, %eax
    je L123
    addl $8, %esp
    pushl $0
    movl $1, %eax
    movl %eax, -20(%ebp)
    jmp L127
L121:
    addl $4, %esp
    jmp L125
L123:
    addl $8, %esp
    jmp L125
L125:
    pushl $0
    movl $0, %eax
    movl %eax, -20(%ebp)
L127:
    movl -20(%ebp), %eax
    cmpl $0, %eax
    je L162
    pushl $0
    movl $4, %eax
    imull -8(%ebp), %eax
    movl %eax,-24(%ebp)
    movl 8(%ebp), %eax
    subl -24(%ebp), %eax
    movl %eax,-24(%ebp)
    pushl $0
    movl $4, %eax
    imull -12(%ebp), %eax
    movl %eax,-28(%ebp)
    movl 8(%ebp), %eax
    subl -28(%ebp), %eax
    movl %eax,-28(%ebp)
    pushl $0
    movl -24(%ebp), %ebx
    movl (%ebx), %eax
    movl -28(%ebp), %ebx
    cmpl (%ebx), %eax
    setle %al
    movzbl %al, %eax
    movl %eax,-32(%ebp)
    movl -32(%ebp), %eax
    cmpl $0, %eax
    je L148
    pushl $0
    movl $4, %eax
    imull -16(%ebp), %eax
    movl %eax,-36(%ebp)
    movl 12(%ebp), %eax
    subl -36(%ebp), %eax
    movl %eax,-36(%ebp)
    pushl $0
    movl $4, %eax
    imull -8(%ebp), %eax
    movl %eax,-40(%ebp)
    movl 8(%ebp), %eax
    subl -40(%ebp), %eax
    movl %eax,-40(%ebp)
    movl -40(%ebp), %ebx
    movl (%ebx), %eax
    movl -36(%ebp), %ebx
    movl %eax, (%ebx)
    movl -16(%ebp), %eax
    addl $1, %eax
    movl %eax,-16(%ebp)
    movl -8(%ebp), %eax
    addl $1, %eax
    movl %eax,-8(%ebp)
    addl $8, %esp
    jmp L159
L148:
    pushl $0
    movl $4, %eax
    imull -16(%ebp), %eax
    movl %eax,-36(%ebp)
    movl 12(%ebp), %eax
    subl -36(%ebp), %eax
    movl %eax,-36(%ebp)
    pushl $0
    movl $4, %eax
    imull -12(%ebp), %eax
    movl %eax,-40(%ebp)
    movl 8(%ebp), %eax
    subl -40(%ebp), %eax
    movl %eax,-40(%ebp)
    movl -40(%ebp), %ebx
    movl (%ebx), %eax
    movl -36(%ebp), %ebx
    movl %eax, (%ebx)
    movl -16(%ebp), %eax
    addl $1, %eax
    movl %eax,-16(%ebp)
    movl -12(%ebp), %eax
    addl $1, %eax
    movl %eax,-12(%ebp)
    addl $8, %esp
L159:
    addl $12, %esp
    addl $4, %esp
    jmp L110
L162:
    addl $4, %esp
L163:
    pushl $0
    movl -8(%ebp), %eax
    cmpl -4(%ebp), %eax
    setle %al
    movzbl %al, %eax
    movl %eax,-20(%ebp)
    movl -20(%ebp), %eax
    cmpl $0, %eax
    je L179
    pushl $0
    movl $4, %eax
    imull -16(%ebp), %eax
    movl %eax,-24(%ebp)
    movl 12(%ebp), %eax
    subl -24(%ebp), %eax
    movl %eax,-24(%ebp)
    pushl $0
    movl $4, %eax
    imull -8(%ebp), %eax
    movl %eax,-28(%ebp)
    movl 8(%ebp), %eax
    subl -28(%ebp), %eax
    movl %eax,-28(%ebp)
    movl -28(%ebp), %ebx
    movl (%ebx), %eax
    movl -24(%ebp), %ebx
    movl %eax, (%ebx)
    movl -16(%ebp), %eax
    addl $1, %eax
    movl %eax,-16(%ebp)
    movl -8(%ebp), %eax
    addl $1, %eax
    movl %eax,-8(%ebp)
    addl $8, %esp
    addl $4, %esp
    jmp L163
L179:
    addl $4, %esp
L180:
    pushl $0
    movl -12(%ebp), %eax
    cmpl 20(%ebp), %eax
    setle %al
    movzbl %al, %eax
    movl %eax,-20(%ebp)
    movl -20(%ebp), %eax
    cmpl $0, %eax
    je L196
    pushl $0
    movl $4, %eax
    imull -16(%ebp), %eax
    movl %eax,-24(%ebp)
    movl 12(%ebp), %eax
    subl -24(%ebp), %eax
    movl %eax,-24(%ebp)
    pushl $0
    movl $4, %eax
    imull -12(%ebp), %eax
    movl %eax,-28(%ebp)
    movl 8(%ebp), %eax
    subl -28(%ebp), %eax
    movl %eax,-28(%ebp)
    movl -28(%ebp), %ebx
    movl (%ebx), %eax
    movl -24(%ebp), %ebx
    movl %eax, (%ebx)
    movl -16(%ebp), %eax
    addl $1, %eax
    movl %eax,-16(%ebp)
    movl -12(%ebp), %eax
    addl $1, %eax
    movl %eax,-12(%ebp)
    addl $8, %esp
    addl $4, %esp
    jmp L180
L196:
    addl $4, %esp
    pushl $0
    movl 20(%ebp), %eax
    addl $1, %eax
    movl %eax,-20(%ebp)
    pushl $0
    movl 16(%ebp), %eax
    movl %eax, -24(%ebp)
    movl -24(%ebp), %eax
    subl $1, %eax
    movl %eax,-24(%ebp)
    pushl $0
    movl -20(%ebp), %eax
    movl %eax, -28(%ebp)
L205:
    movl -24(%ebp), %eax
    addl $1, %eax
    movl %eax,-24(%ebp)
    movl -24(%ebp), %eax
    cmpl -28(%ebp), %eax
    jge L216
    pushl $0
    movl $4, %eax
    imull -24(%ebp), %eax
    movl %eax,-32(%ebp)
    movl 8(%ebp), %eax
    subl -32(%ebp), %eax
    movl %eax,-32(%ebp)
    pushl $0
    movl $4, %eax
    imull -24(%ebp), %eax
    movl %eax,-36(%ebp)
    movl 12(%ebp), %eax
    subl -36(%ebp), %eax
    movl %eax,-36(%ebp)
    movl -36(%ebp), %ebx
    movl (%ebx), %eax
    movl -32(%ebp), %ebx
    movl %eax, (%ebx)
    addl $8, %esp
    jmp L205
L216:
    addl $12, %esp
    addl $16, %esp
    leave
    ret
L219:
    pushl %ebp
    movl %esp, %ebp
    pushl $0
    movl 16(%ebp), %eax
    cmpl 20(%ebp), %eax
    setl %al
    movzbl %al, %eax
    movl %eax,-4(%ebp)
    movl -4(%ebp), %eax
    cmpl $0, %eax
    je L257
    pushl $0
    movl 16(%ebp), %eax
    addl 20(%ebp), %eax
    movl %eax,-8(%ebp)
    movl -8(%ebp), %eax
    movl $2, %ecx
    cltd
    idivl %ecx, %eax
    movl %eax,-8(%ebp)
    pushl -8(%ebp)
    pushl 16(%ebp)
    pushl 12(%ebp)
    pushl 8(%ebp)
    call L219
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    pushl $0
    movl -8(%ebp), %eax
    addl $1, %eax
    movl %eax,-12(%ebp)
    pushl 20(%ebp)
    pushl -12(%ebp)
    pushl 12(%ebp)
    pushl 8(%ebp)
    call L219
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    pushl 20(%ebp)
    pushl 16(%ebp)
    pushl 12(%ebp)
    pushl 8(%ebp)
    call L100
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    addl $8, %esp
    jmp L258
L257:
L258:
    addl $4, %esp
    leave
    ret
L260:
    pushl %ebp
    movl %esp, %ebp
    pushl $0
    movl $0, %eax
    subl $61, %eax
    movl %eax,-4(%ebp)
    pushl $0
    movl $0, %eax
    subl $62, %eax
    movl %eax,-8(%ebp)
    pushl $0
    movl $0, %eax
    subl $45, %eax
    movl %eax,-12(%ebp)
    pushl $0
    movl $0, %eax
    subl $95, %eax
    movl %eax,-16(%ebp)
    pushl $0
    movl $0, %eax
    subl $8, %eax
    movl %eax,-20(%ebp)
    pushl $0
    movl $0, %eax
    subl $9, %eax
    movl %eax,-24(%ebp)
    pushl $0
    movl $0, %eax
    subl $23, %eax
    movl %eax,-28(%ebp)
    pushl $0
    movl $0, %eax
    subl $8, %eax
    movl %eax,-32(%ebp)
    pushl $0
    movl $0, %eax
    subl $24, %eax
    movl %eax,-36(%ebp)
    subl $80, %esp
    std
    movl $20, %ecx
    movl %esp, %eax
    addl $76, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    movl $8, %eax
    movl %eax, -40(%ebp)
    movl $5, %eax
    movl %eax, -44(%ebp)
    movl -4(%ebp), %eax
    movl %eax, -48(%ebp)
    movl $84, %eax
    movl %eax, -52(%ebp)
    movl $45, %eax
    movl %eax, -56(%ebp)
    movl -8(%ebp), %eax
    movl %eax, -60(%ebp)
    movl $98, %eax
    movl %eax, -64(%ebp)
    movl $45, %eax
    movl %eax, -68(%ebp)
    movl -12(%ebp), %eax
    movl %eax, -72(%ebp)
    movl $47, %eax
    movl %eax, -76(%ebp)
    movl -16(%ebp), %eax
    movl %eax, -80(%ebp)
    movl -20(%ebp), %eax
    movl %eax, -84(%ebp)
    movl -24(%ebp), %eax
    movl %eax, -88(%ebp)
    movl -28(%ebp), %eax
    movl %eax, -92(%ebp)
    movl $5, %eax
    movl %eax, -96(%ebp)
    movl -32(%ebp), %eax
    movl %eax, -100(%ebp)
    movl $6, %eax
    movl %eax, -104(%ebp)
    movl $75, %eax
    movl %eax, -108(%ebp)
    movl -36(%ebp), %eax
    movl %eax, -112(%ebp)
    movl $91, %eax
    movl %eax, -116(%ebp)
    subl $80, %esp
    std
    movl $20, %ecx
    movl %esp, %eax
    addl $76, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    pushl $0
    leal -40(%ebp), %eax
    movl %eax,-200(%ebp)
    pushl $0
    leal -120(%ebp), %eax
    movl %eax,-204(%ebp)
    pushl $19
    pushl $0
    pushl -204(%ebp)
    pushl -200(%ebp)
    call L219
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    pushl $0
    pushl $0
    leal -40(%ebp), %eax
    movl %eax,-212(%ebp)
    movl -212(%ebp), %eax
    addl $4, %eax
    movl %eax,-212(%ebp)
    pushl $0
    movl -212(%ebp), %eax
    subl $80, %eax
    movl %eax,-216(%ebp)
L320:
    movl -212(%ebp), %eax
    subl $4, %eax
    movl %eax,-212(%ebp)
    movl -212(%ebp), %eax
    cmpl -216(%ebp), %eax
    jl L325
    movl -212(%ebp), %ebx
    movl (%ebx), %eax
    movl %eax, -208(%ebp)
    pushl -208(%ebp)
    call _output
    addl $4, %esp
    jmp L320
L325:
    addl $12, %esp
    addl $204, %esp
    leave
    ret
