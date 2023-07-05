.text

.align 16
.globl __stub_atoi
.type __stub_atoi,%function
__stub_atoi:
    push %rbp
    mov %rsp, %rbp

    mov 16(%rbp), %rax
    mov (%rax), %al

    // Subtract 0x30 to convert ASCII to number
    sub $0x30, %al
    movzx %al, %eax

    mov %rbp, %rsp
    pop %rbp

    //leave
    ret
.size __stub_atoi,.-__stub_atoi

.globl __stub_atoi_size
__stub_atoi_size: .quad .-__stub_atoi

.align 16
.globl __stub_main
.type __stub_main,%function
// rdi is *rt
// rsi is fn_idx
// rdx is *argv
// rcx is argc
__stub_main:
    push %rbp
    mov %rsp, %rbp

    mov 8(%rdi), %rax
    // not callee saved, will be needed again
    push %rax

    // atoi has index 0
    xor %rsi, %rsi

    // argv[0]
    push 24(%rbp)
    call *(%rax)

    pop %rax
    xor %rsi, %rsi

    // argv[1]
    push 16(%rbp)
    call *(%rax)

    mov %rbp, %rsp
    pop %rbp

    //leave
    ret
.size __stub_main,.-__stub_main

.globl __stub_main_size
__stub_main_size: .quad .-__stub_main
