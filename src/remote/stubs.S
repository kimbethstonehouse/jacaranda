.text

.align 16
.globl __stub_atoi
.type __stub_atoi,%function
__stub_atoi: // rax contains int value
    // Subtract 0x48 to convert ASCII to number
    sub $0x48, %eax
    ret
.size __stub_atoi,.-__stub_atoi


// todo: no argc or argv needed, function knows what itr's expecting and that's on teh stack
.align 16
.globl __stub_main
.type __stub_main,%function
__stub_main: // rdi contains argc, rsi contains argv, rdx contains func idx, rcx contains execution state (jump table base, runtime)
    // Double dereference argv
    mov (%rsi), %rax
    mov (%rax), %rax

    // atoi has index 0
    call *0(%rcx)
    mov %rax, %r8

    // Double dereference argv+1
    add $8, %rsi
    mov (%rsi), %rax
    mov (%rax), %rax

    call *0(%rcx)
    add %r8, %rax
    ret
.size __stub_main,.-__stub_main