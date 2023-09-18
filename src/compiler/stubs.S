.text

.align 16
.globl __stub_atoi
.type __stub_atoi,%function
__stub_atoi:
    push %rbp
    mov %rsp, %rbp

    // Subtract 0x30 to convert ASCII to number
    sub $0x30, %bl
    movzx %bl, %eax

    mov %rbp, %rsp
    pop %rbp

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

    push %rbx

    mov 8(%rdi), %r8
    // atoi has index 0
    xor %rsi, %rsi

    push %r8

    mov (%rdx), %rbx
    mov (%rbx), %rbx
    // argv[0]
    call *(%r8, %rsi, 8)

    pop %r8
    xor %rsi, %rsi

    mov %rax, %r9

    mov (%rdx), %rbx
    mov 2(%rbx), %rbx

    // argv[1]
    call *(%r8, %rsi, 8)

    add %r9, %rax

    pop %rbx

    mov %rbp, %rsp
    pop %rbp

    ret
.size __stub_main,.-__stub_main

.globl __stub_main_size
__stub_main_size: .quad .-__stub_main
