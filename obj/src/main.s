    .globl _main
    .extern _input
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
    call _input
    movl %eax,-4(%ebp)
    subl $80, %esp
    std
    movl $20, %ecx
    movl %esp, %eax
    addl $76, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
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
    movl $0, %eax
    movl %eax, -168(%ebp)
    movl -168(%ebp), %eax
    subl $1, %eax
    movl %eax,-168(%ebp)
    pushl $0
    movl -4(%ebp), %eax
    movl %eax, -172(%ebp)
L271:
    movl -168(%ebp), %eax
    addl $1, %eax
    movl %eax,-168(%ebp)
    movl -168(%ebp), %eax
    cmpl -172(%ebp), %eax
    jge L280
    pushl $0
    movl $4, %eax
    imull -168(%ebp), %eax
    movl %eax,-176(%ebp)
    movl -176(%ebp), %eax
    addl $8, %eax
    movl %eax,-176(%ebp)
    movl -176(%ebp), %eax
    negl %eax
    addl %ebp, %eax
    movl %eax,-176(%ebp)
    call _input
    movl -176(%ebp), %ebx
    movl %eax, (%ebx)
    addl $4, %esp
    jmp L271
L280:
    addl $8, %esp
    pushl $0
    leal -8(%ebp), %eax
    movl %eax,-168(%ebp)
    pushl $0
    leal -88(%ebp), %eax
    movl %eax,-172(%ebp)
    pushl $0
    movl -4(%ebp), %eax
    subl $1, %eax
    movl %eax,-176(%ebp)
    pushl -176(%ebp)
    pushl $0
    pushl -172(%ebp)
    pushl -168(%ebp)
    call L219
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    addl $4, %esp
    pushl $0
    movl $0, %eax
    movl %eax, -180(%ebp)
    movl -180(%ebp), %eax
    subl $1, %eax
    movl %eax,-180(%ebp)
    pushl $0
    movl -4(%ebp), %eax
    movl %eax, -184(%ebp)
L302:
    movl -180(%ebp), %eax
    addl $1, %eax
    movl %eax,-180(%ebp)
    movl -180(%ebp), %eax
    cmpl -184(%ebp), %eax
    jge L311
    pushl $0
    movl $4, %eax
    imull -180(%ebp), %eax
    movl %eax,-188(%ebp)
    movl -188(%ebp), %eax
    addl $8, %eax
    movl %eax,-188(%ebp)
    movl -188(%ebp), %eax
    negl %eax
    addl %ebp, %eax
    movl %eax,-188(%ebp)
    movl -188(%ebp), %ebx
    pushl (%ebx)
    call _output
    addl $4, %esp
    addl $4, %esp
    jmp L302
L311:
    addl $8, %esp
    addl $176, %esp
    leave
    ret
