    .globl _main
    .extern _input
    .extern _output
    .text
_main:
    call L253
    xor %eax, %eax
    ret
L100:
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
L116:
    movl -36(%ebp), %eax
    addl $1, %eax
    movl %eax,-36(%ebp)
    movl -36(%ebp), %eax
    cmpl -40(%ebp), %eax
    jge L164
    pushl $0
    movl $0, %eax
    movl %eax, -44(%ebp)
    movl -44(%ebp), %eax
    subl $1, %eax
    movl %eax,-44(%ebp)
    pushl $0
    movl $2, %eax
    movl %eax, -48(%ebp)
L124:
    movl -44(%ebp), %eax
    addl $1, %eax
    movl %eax,-44(%ebp)
    movl -44(%ebp), %eax
    cmpl -48(%ebp), %eax
    jge L162
    pushl $0
    movl $0, %eax
    movl %eax, -52(%ebp)
    movl -52(%ebp), %eax
    subl $1, %eax
    movl %eax,-52(%ebp)
    pushl $0
    movl $2, %eax
    movl %eax, -56(%ebp)
L132:
    movl -52(%ebp), %eax
    addl $1, %eax
    movl %eax,-52(%ebp)
    movl -52(%ebp), %eax
    cmpl -56(%ebp), %eax
    jge L160
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
    jmp L132
L160:
    addl $8, %esp
    jmp L124
L162:
    addl $8, %esp
    jmp L116
L164:
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
L168:
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
L181:
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
    call L168
L184:
    pushl $0
    movl 24(%ebp), %eax
    cmpl $0, %eax
    setg %al
    movzbl %al, %eax
    movl %eax,-20(%ebp)
    movl -20(%ebp), %eax
    cmpl $0, %eax
    je L214
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
    je L202
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
    jmp L203
L202:
L203:
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
    movl $2, %ecx
    cltd
    idivl %ecx, %eax
    movl %eax,24(%ebp)
    addl $24, %esp
    addl $4, %esp
    jmp L184
L214:
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
L218:
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
    je L225
    movl $0, %eax
    movl %eax, 12(%ebp)
    leave
    ret
    jmp L226
L225:
L226:
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
    call L181
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
L253:
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
    call L168
    pushl $0
    call _input
    movl %eax,-20(%ebp)
    pushl $0
    pushl -20(%ebp)
    call L218
    addl $4, %esp
    pushl -24(%ebp)
    call _output
    addl $4, %esp
    addl $24, %esp
    leave
    ret
