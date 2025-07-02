    .syntax unified
    .cpu cortex-m3       @ 或者你的具体 ARM CPU
    .thumb               @ 如果是 thumb 指令集，可选

    .extern input
    .extern output

    .global main

main:
    bl L106             @ 调用主函数体 L106
    mov r0, #0          @ 返回0
    bx lr               @ 返回调用者

@ ===== 函数 L100: 计算两个参数之和，参数：r0, r1，返回 r0 =====
L100:
    push {fp, lr}       @ 保存帧指针和返回地址
    mov fp, sp          @ 建立栈帧

    sub sp, sp, #4      @ 分配4字节临时空间（如果需要）

    add r0, r0, r1      @ r0 = r0 + r1

    add sp, sp, #4      @ 回收临时空间
    pop {fp, pc}        @ 恢复帧指针，返回（pc从lr恢复）

@ ===== 函数 L106 (main体) =====
L106:
    push {fp, lr}       @ 保存帧指针和返回地址
    mov fp, sp          @ 建立栈帧

    sub sp, sp, #4      @ 分配4字节局部变量空间，用于 input 返回值
    bl input           @ 调用 input，结果在 r0
    str r0, [fp, #-4]   @ 保存 input 结果到局部变量 -4(fp)

    sub sp, sp, #4      @ 分配4字节局部变量空间，用于 sea 指针
    add r1, fp, #-4     @ sea = &input_result
    str r1, [fp, #-8]   @ 保存 sea 指针到 -8(fp)

    sub sp, sp, #4      @ 分配4字节局部变量空间，用于表达式结果
    ldr r0, [fp, #-4]   @ r0 = input_result
    add r0, r0, #5      @ r0 = input_result + 5
    str r0, [fp, #-12]  @ 保存表达式结果

    sub sp, sp, #4      @ 分配4字节局部变量空间，用于条件值
    ldr r0, [fp, #-12]  @ r0 = 表达式结果
    cmp r0, #10
    ble label_le       @ 如果 r0 <= 10 跳到 label_le
    mov r0, #1         @ r0 > 10 时执行
    b label_end
label_le:
    mov r0, #0         @ r0 <= 10 时执行
label_end:
    str r0, [fp, #-16]  @ 保存条件结果

    ldr r0, [fp, #-16]
    cmp r0, #0
    beq else_label

    sub sp, sp, #4      @ 分配空间准备参数
    ldr r0, [fp, #-4]   @ 第一个参数 input_result
    push {r0}           @ 入栈（也可用寄存器传递）
    ldr r0, [fp, #-4]   @ 第二个参数 input_result
    push {r0}           @ 入栈
    bl L100             @ 调用函数 L100 (计算和)

    add sp, sp, #8      @ 清理入栈参数空间

    push {r0}           @ 参数传递给 output
    bl output
    add sp, sp, #4      @ 清理参数空间

    b end_label

else_label:
    ldr r1, [fp, #-8]   @ 取 sea 指针
    mov r0, #10
    str r0, [r1]        @ *sea = 10

    ldr r0, [fp, #-4]   @ 参数传给 output
    bl output

end_label:
    add sp, sp, #16     @ 回收所有局部变量空间

    pop {fp, pc}        @ 恢复帧指针和返回地址，返回
