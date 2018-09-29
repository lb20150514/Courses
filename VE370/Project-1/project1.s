	.file	"project1.c"
	.text
	.globl	Pass
	.type	Pass, @function
Pass:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	cmpl	$59, -4(%rbp)
	jle	.L2
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$0, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	Pass, .-Pass
	.globl	Fail
	.type	Fail, @function
Fail:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	cmpl	$59, -4(%rbp)
	jg	.L5
	movl	$1, %eax
	jmp	.L6
.L5:
	movl	$0, %eax
.L6:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	Fail, .-Fail
	.globl	countArray
	.type	countArray, @function
countArray:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	$0, -4(%rbp)
	movl	-28(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.L8
.L12:
	movl	-32(%rbp), %eax
	cmpl	$49, %eax
	jne	.L14
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %edi
	call	Pass
	addl	%eax, -4(%rbp)
	jmp	.L11
.L14:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %edi
	call	Fail
	addl	%eax, -4(%rbp)
.L11:
	subl	$1, -8(%rbp)
.L8:
	cmpl	$0, -8(%rbp)
	jg	.L12
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	countArray, .-countArray
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$20, -108(%rbp)
	movl	$55, -96(%rbp)
	movl	$83, -92(%rbp)
	movl	$30, -88(%rbp)
	movl	$94, -84(%rbp)
	movl	$22, -80(%rbp)
	movl	$51, -76(%rbp)
	movl	$54, -72(%rbp)
	movl	$32, -68(%rbp)
	movl	$69, -64(%rbp)
	movl	$96, -60(%rbp)
	movl	$80, -56(%rbp)
	movl	$27, -52(%rbp)
	movl	$61, -48(%rbp)
	movl	$59, -44(%rbp)
	movl	$100, -40(%rbp)
	movl	$72, -36(%rbp)
	movl	$66, -32(%rbp)
	movl	$18, -28(%rbp)
	movl	$6, -24(%rbp)
	movl	$42, -20(%rbp)
	movl	-108(%rbp), %ecx
	leaq	-96(%rbp), %rax
	movl	$1, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	countArray
	movl	%eax, -104(%rbp)
	movl	-108(%rbp), %ecx
	leaq	-96(%rbp), %rax
	movl	$-1, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	countArray
	movl	%eax, -100(%rbp)
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L17
	call	__stack_chk_fail@PLT
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
