	.file	"struct_return.cc"
	.text
	.globl	_Z1fv
	.type	_Z1fv, @function
_Z1fv:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rax, %rcx
	orq	$1, %rcx
	movq	%rcx, %rax
	movq	%rax, %rcx
	andq	$-3, %rcx
	movq	%rcx, %rax
	movl	$2, %edx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z1fv, .-_Z1fv
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	call	_Z1fv
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movzbl	-32(%rbp), %eax
	andl	$1, %eax
	testb	%al, %al
	setne	%al
	movb	%al, -1(%rbp)
	movzbl	-32(%rbp), %eax
	andl	$2, %eax
	testb	%al, %al
	setne	%al
	movb	%al, -2(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
