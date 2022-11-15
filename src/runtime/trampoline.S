.text

.align 16
.globl invoke_function
invoke_function:
    push %rbp
    push %r12
    push %r13
    push %r14
    push %r15

    mov 8(%rdi), %r15

    call *(%r15, %rsi, 8)

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbp

    ret
