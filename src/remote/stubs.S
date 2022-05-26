.text

.align 16
.globl __stub_atoi
.type __stub_atoi,%function
__stub_atoi:    // RBP: jump table base, args + ret on stack
    // Args: 1x i32 (val)

    // Pop arg
    pop %rax

    // Subtract 0x48 to convert ASCII to number
    sub $0x48, %eax

    // Push result onto stack
    push %rax

    // Done
    ret
.size __stub_atoi,.-__stub_atoi

.align 16
.globl __stub_main
.type __stub_main,%function
__stub_main:    // RBP: jump table base, args + ret on stack
    // Args: 1x i32 (argc), 1x i64 (argv)

    pop %rax    // Get argv

    // Push argv[0]
    mov (%rax), %rcx
    push %rcx

    // Call atoi
    call 8(%rbp)

    // Push argv[1]
    mov 8(%rax), %rcx
    push %rcx

    // Call atoi
    call 8(%rbp)

    pop %rax    // result of first atoi
    pop %rcx    // result of second atoi

    add %rcx, %rax

    push %rax
    ret
.size __stub_main,.-__stub_main