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

    leave
    ret
.size __stub_atoi,.-__stub_atoi

.globl __stub_atoi_size
__stub_atoi_size: .quad .-__stub_atoi

.align 16
.globl __stub_main
.type __stub_main,%function
// rdi contains function index
// rsi contains ptr to jump table base
__stub_main:
    push %rbp
    mov %rsp, %rbp

    // atoi has index 0
    xor %edi, %edi

    push 24(%rbp)
    call *0(%rsi)
    add $8, %rsp

    mov %rax, %rdx

    xor %edi, %edi

    push 16(%rbp)
    call *0(%rsi)
    add $8, %rsp

    add %rdx, %rax

    leave
    ret
.size __stub_main,.-__stub_main

.globl __stub_main_size
__stub_main_size: .quad .-__stub_main
