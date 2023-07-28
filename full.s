	.text
	.file	"more-maths.c"
	.globl	add                     # -- Begin function add
	.p2align	4, 0x90
	.type	add,@function
add:                                    # @add
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	addl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	add, .Lfunc_end0-add
	.cfi_endproc
                                        # -- End function
	.globl	sub                     # -- Begin function sub
	.p2align	4, 0x90
	.type	sub,@function
sub:                                    # @sub
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	subl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	sub, .Lfunc_end1-sub
	.cfi_endproc
                                        # -- End function

	.globl	maths                   # -- Begin function maths
	.p2align	4, 0x90
	.type	maths,@function
maths:                                  # @maths
	.cfi_startproc
# %bb.0:                                # %block0start
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
# %bb.1:                                # %block1start
	jmp	.LBB0_2
.LBB0_2:                                # %block2start
	movl	-28(%rbp), %eax
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, %rsp
	movl	%eax, -16(%rcx)
	movl	-16(%rcx), %eax
	testl	%eax, %eax
	sete	%sil
	movq	%rsp, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	andb	$1, %sil
	movb	%sil, (%rcx)
	testb	$1, (%rcx)
	jne	.LBB0_8
# %bb.3:                                # %block2startelse
	movl	-32(%rbp), %eax
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, %rsp
	movl	%eax, -16(%rcx)
	movl	-36(%rbp), %eax
	movq	%rsp, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	%eax, (%rcx)
	movl	(%rcx), %eax
	addl	(%rdx), %eax
	movl	%eax, (%rdx)
	movl	(%rdx), %eax
	movl	%eax, -28(%rbp)
# %bb.4:                                # %block3start
	movl	-32(%rbp), %eax
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, %rsp
	movl	%eax, -16(%rcx)
	movl	-16(%rcx), %eax
	testl	%eax, %eax
	sete	%sil
	movq	%rsp, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	andb	$1, %sil
	movb	%sil, (%rcx)
	testb	$1, (%rcx)
	jne	.LBB0_6
# %bb.5:                                # %block3startelse
	movl	-28(%rbp), %eax
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, %rsp
	movl	%eax, -16(%rcx)
	movl	-36(%rbp), %eax
	movq	%rsp, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	%eax, (%rcx)
	movl	(%rcx), %eax
	addl	(%rdx), %eax
	movl	%eax, (%rdx)
	movl	(%rdx), %eax
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.LBB0_6:                                # %block2end
	.cfi_def_cfa %rbp, 16
	movl	-36(%rbp), %eax
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, %rsp
	movl	%eax, -16(%rcx)
	movl	-16(%rcx), %eax
	testl	%eax, %eax
	sete	%sil
	movq	%rsp, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	andb	$1, %sil
	movb	%sil, (%rcx)
	testb	$1, (%rcx)
	jne	.LBB0_9
# %bb.7:                                # %block2endelse
	movl	-28(%rbp), %eax
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, %rsp
	movl	%eax, -16(%rcx)
	movq	%rsp, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	$0, (%rcx)
	movl	(%rcx), %eax
	addl	(%rdx), %eax
	movl	%eax, (%rdx)
	movl	(%rdx), %eax
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.LBB0_8:                                # %block1end
	.cfi_def_cfa %rbp, 16
	movq	%rsp, %rax
	movq	%rax, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	$0, -16(%rax)
	movl	-32(%rbp), %edx
	movq	%rsp, %rax
	addq	$-16, %rax
	movq	%rax, %rsp
	movl	%edx, (%rax)
	movl	(%rax), %edx
	addl	(%rcx), %edx
	movl	%edx, (%rcx)
	movl	(%rcx), %edx
	movl	%edx, -28(%rbp)
.LBB0_9:                                # %block0end
	movl	-28(%rbp), %eax
	movq	%rsp, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	%eax, (%rcx)
	movl	(%rcx), %eax
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	maths, .Lfunc_end2-maths
	.cfi_endproc
                                        # -- End function

	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$1, %edi
	movl	$2, %esi
	movl	$3, %edx
	callq	maths
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 10.0.0-4ubuntu1 "
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym add
	.addrsig_sym sub
	.addrsig_sym maths
