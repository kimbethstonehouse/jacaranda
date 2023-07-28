.text

.align 16
.globl invoke_function
invoke_function:
    push %rbp
    mov %rsp, %rbp

    mov 8(%rdi), %rax

    push %rdi
    push %rsi
    push %rdx
    push %rcx

    call *(%rax, %rsi, 8)

    pop %rcx
    pop %rdx
    pop %rsi
    pop %rdi

    mov %rbp, %rsp
    pop %rbp

    ret
