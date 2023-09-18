.text

.align 16
.globl invoke_function
// rdi is *rt, rdi+8 is jt
// rsi is fn_idx
// rdx is *argv
// rcx is argc
invoke_function:
    push %rbp
    mov %rsp, %rbp

    mov 8(%rdi), %r8
    call *(%r8, %rsi, 8)

    mov %rbp, %rsp
    pop %rbp

    ret
