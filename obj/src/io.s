	.file	"io.c"
	.text
	.section .rdata,"dr"
LC0:
	.ascii "%d\0"
	.text
	.globl	_input
	.def	_input;	.scl	2;	.type	32;	.endef
_input:
LFB105:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_scanf
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE105:
	.section .rdata,"dr"
LC1:
	.ascii "%d\12\0"
	.text
	.globl	_output
	.def	_output;	.scl	2;	.type	32;	.endef
_output:
LFB106:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE106:
	.ident	"GCC: (MinGW-W64 i686-ucrt-posix-dwarf, built by Brecht Sanders, r2) 15.1.0"
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
