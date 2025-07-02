    .globl _main
    .extern _input
    .extern _output
    .extern _output
    .text
_main:
    call L254
    xor %eax, %eax
    ret
L100:
    pushl %ebp
    movl %esp, %ebp
    pushl $114514
    call _output
    addl $4, %esp
    subl $8, %esp
    std
    movl $2, %ecx
    movl %esp, %eax
    addl $4, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    movl $0, %eax
    movl %eax, -4(%ebp)
    movl $0, %eax
    movl %eax, -8(%ebp)
    subl $8, %esp
    std
    movl $2, %ecx
    movl %esp, %eax
    addl $4, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    movl $0, %eax
    movl %eax, -12(%ebp)
    movl $0, %eax
    movl %eax, -16(%ebp)
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    std
    leal -4(%ebp), %esi
    leal -20(%ebp), %edi
    movl $2, %ecx
    rep movsl
    cld
    std
    leal -12(%ebp), %esi
    leal -28(%ebp), %edi
    movl $2, %ecx
    rep movsl
    cld
    pushl $0
    movl $0, %eax
    movl %eax, -36(%ebp)
    movl -36(%ebp), %eax
    subl $1, %eax
    movl %eax,-36(%ebp)
    pushl $0
    movl $2, %eax
    movl %eax, -40(%ebp)
L117:
    movl -36(%ebp), %eax
    addl $1, %eax
    movl %eax,-36(%ebp)
    movl -36(%ebp), %eax
    cmpl -40(%ebp), %eax
    jge L165
    pushl $0
    movl $0, %eax
    movl %eax, -44(%ebp)
    movl -44(%ebp), %eax
    subl $1, %eax
    movl %eax,-44(%ebp)
    pushl $0
    movl $2, %eax
    movl %eax, -48(%ebp)
L125:
    movl -44(%ebp), %eax
    addl $1, %eax
    movl %eax,-44(%ebp)
    movl -44(%ebp), %eax
    cmpl -48(%ebp), %eax
    jge L163
    pushl $0
    movl $0, %eax
    movl %eax, -52(%ebp)
    movl -52(%ebp), %eax
    subl $1, %eax
    movl %eax,-52(%ebp)
    pushl $0
    movl $2, %eax
    movl %eax, -56(%ebp)
L133:
    movl -52(%ebp), %eax
    addl $1, %eax
    movl %eax,-52(%ebp)
    movl -52(%ebp), %eax
    cmpl -56(%ebp), %eax
    jge L161
    pushl $0
    movl $8, %eax
    imull -36(%ebp), %eax
    movl %eax,-60(%ebp)
    movl -60(%ebp), %eax
    addl $20, %eax
    movl %eax,-60(%ebp)
    movl -60(%ebp), %eax
    negl %eax
    addl %ebp, %eax
    movl %eax,-60(%ebp)
    pushl $0
    movl $4, %eax
    imull -44(%ebp), %eax
    movl %eax,-64(%ebp)
    movl -60(%ebp), %eax
    subl -64(%ebp), %eax
    movl %eax,-64(%ebp)
    pushl $0
    movl $8, %eax
    imull -36(%ebp), %eax
    movl %eax,-68(%ebp)
    movl -68(%ebp), %eax
    addl $-20, %eax
    movl %eax,-68(%ebp)
    movl -68(%ebp), %eax
    negl %eax
    addl %ebp, %eax
    movl %eax,-68(%ebp)
    pushl $0
    movl $4, %eax
    imull -52(%ebp), %eax
    movl %eax,-72(%ebp)
    movl -68(%ebp), %eax
    subl -72(%ebp), %eax
    movl %eax,-72(%ebp)
    pushl $0
    movl $8, %eax
    imull -52(%ebp), %eax
    movl %eax,-76(%ebp)
    movl -76(%ebp), %eax
    addl $-36, %eax
    movl %eax,-76(%ebp)
    movl -76(%ebp), %eax
    negl %eax
    addl %ebp, %eax
    movl %eax,-76(%ebp)
    pushl $0
    movl $4, %eax
    imull -44(%ebp), %eax
    movl %eax,-80(%ebp)
    movl -76(%ebp), %eax
    subl -80(%ebp), %eax
    movl %eax,-80(%ebp)
    pushl $0
    movl -72(%ebp), %ebx
    movl (%ebx), %eax
    movl -80(%ebp), %ebx
    imull (%ebx), %eax
    movl %eax,-84(%ebp)
    movl -64(%ebp), %ebx
    movl (%ebx), %eax
    addl -84(%ebp), %eax
    movl %eax, (%ebx)
    addl $28, %esp
    jmp L133
L161:
    addl $8, %esp
    jmp L125
L163:
    addl $8, %esp
    jmp L117
L165:
    addl $8, %esp
    std
    leal -20(%ebp), %esi
    leal 52(%ebp), %edi
    movl $4, %ecx
    rep movsl
    cld
    leave
    ret
    addl $32, %esp
L169:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    std
    movl $2, %ecx
    movl %esp, %eax
    addl $4, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    movl $1, %eax
    movl %eax, -4(%ebp)
    movl $0, %eax
    movl %eax, -8(%ebp)
    subl $8, %esp
    std
    movl $2, %ecx
    movl %esp, %eax
    addl $4, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    movl $0, %eax
    movl %eax, -12(%ebp)
    movl $1, %eax
    movl %eax, -16(%ebp)
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    std
    leal -4(%ebp), %esi
    leal -20(%ebp), %edi
    movl $2, %ecx
    rep movsl
    cld
    std
    leal -12(%ebp), %esi
    leal -28(%ebp), %edi
    movl $2, %ecx
    rep movsl
    cld
    std
    leal -20(%ebp), %esi
    leal 20(%ebp), %edi
    movl $4, %ecx
    rep movsl
    cld
    leave
    ret
    addl $32, %esp
L182:
    pushl %ebp
    movl %esp, %ebp
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    call L169
L185:
    pushl $0
    movl 24(%ebp), %eax
    cmpl $0, %eax
    setg %al
    movzbl %al, %eax
    movl %eax,-20(%ebp)
    movl -20(%ebp), %eax
    cmpl $0, %eax
    je L215
    pushl $0
    movl 24(%ebp), %eax
    movl $2, %ecx
    cltd
    idivl %ecx, %eax
    movl %edx,-24(%ebp)
    pushl $0
    movl -24(%ebp), %eax
    cmpl $1, %eax
    sete %al
    movzbl %al, %eax
    movl %eax,-28(%ebp)
    movl -28(%ebp), %eax
    cmpl $0, %eax
    je L203
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    subl $16, %esp
    std
    movl $4, %ecx
    leal 20(%ebp), %esi
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    rep movsl
    cld
    subl $16, %esp
    std
    movl $4, %ecx
    leal -4(%ebp), %esi
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    rep movsl
    cld
    call L100
    addl $16, %esp
    addl $16, %esp
    std
    leal -32(%ebp), %esi
    leal -4(%ebp), %edi
    movl $4, %ecx
    rep movsl
    cld
    addl $16, %esp
    jmp L204
L203:
L204:
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    subl $16, %esp
    std
    movl $4, %ecx
    leal 20(%ebp), %esi
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    rep movsl
    cld
    subl $16, %esp
    std
    movl $4, %ecx
    leal 20(%ebp), %esi
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    rep movsl
    cld
    call L100
    addl $16, %esp
    addl $16, %esp
    std
    leal -32(%ebp), %esi
    leal 20(%ebp), %edi
    movl $4, %ecx
    rep movsl
    cld
    movl 24(%ebp), %eax
    movl $0, %ecx
    cltd
    idivl %ecx, %eax
    movl %eax,24(%ebp)
    addl $24, %esp
    addl $4, %esp
    jmp L185
L215:
    addl $4, %esp
    std
    leal -4(%ebp), %esi
    leal 40(%ebp), %edi
    movl $4, %ecx
    rep movsl
    cld
    leave
    ret
    addl $16, %esp
L219:
    pushl %ebp
    movl %esp, %ebp
    pushl $0
    movl 8(%ebp), %eax
    cmpl $0, %eax
    sete %al
    movzbl %al, %eax
    movl %eax,-4(%ebp)
    movl -4(%ebp), %eax
    cmpl $0, %eax
    je L226
    movl $0, %eax
    movl %eax, 12(%ebp)
    leave
    ret
    jmp L227
L226:
L227:
    subl $8, %esp
    std
    movl $2, %ecx
    movl %esp, %eax
    addl $4, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    movl $1, %eax
    movl %eax, -8(%ebp)
    movl $1, %eax
    movl %eax, -12(%ebp)
    subl $8, %esp
    std
    movl $2, %ecx
    movl %esp, %eax
    addl $4, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    movl $1, %eax
    movl %eax, -16(%ebp)
    movl $0, %eax
    movl %eax, -20(%ebp)
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    std
    leal -8(%ebp), %esi
    leal -24(%ebp), %edi
    movl $2, %ecx
    rep movsl
    cld
    std
    leal -16(%ebp), %esi
    leal -32(%ebp), %edi
    movl $2, %ecx
    rep movsl
    cld
    pushl $0
    movl 8(%ebp), %eax
    subl $1, %eax
    movl %eax,-40(%ebp)
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    pushl -40(%ebp)
    subl $16, %esp
    std
    movl $4, %ecx
    leal -24(%ebp), %esi
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    rep movsl
    cld
    call L182
    addl $4, %esp
    addl $16, %esp
    pushl $0
    movl $8, %eax
    imull $0, %eax
    movl %eax,-60(%ebp)
    movl -60(%ebp), %eax
    addl $44, %eax
    movl %eax,-60(%ebp)
    movl -60(%ebp), %eax
    negl %eax
    addl %ebp, %eax
    movl %eax,-60(%ebp)
    pushl $0
    movl $4, %eax
    imull $0, %eax
    movl %eax,-64(%ebp)
    movl -60(%ebp), %eax
    subl -64(%ebp), %eax
    movl %eax,-64(%ebp)
    movl -64(%ebp), %ebx
    movl (%ebx), %eax
    movl %eax, 12(%ebp)
    leave
    ret
    addl $64, %esp
L254:
    pushl %ebp
    movl %esp, %ebp
    subl $16, %esp
    std
    movl $4, %ecx
    movl %esp, %eax
    addl $12, %eax
    movl %eax, %edi
    movl $0, %eax
    rep stosl
    cld
    call L169
    pushl $0
    pushl $2
    call L219
    addl $4, %esp
    pushl -20(%ebp)
    call _output
    addl $4, %esp
    addl $20, %esp
    leave
    ret
