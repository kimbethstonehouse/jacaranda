.align 16
.globl trampoline_to_execute
.globl trampoline_to_compile
.globl request_compilation
.type request_compilation,%function

.type trampoline_to_execute,%function
// rdi contains function index
// rsi contains ptr to jump table base
// rdx contains argc
// rcx contains ptr to argv
// r8 contains ptr to runtime
trampoline_to_execute:
        // Frame pointer
        push %rbp

        // Save the callee saved registers
        push %rbx
        push %r12
        push %r13
        push %r14
        push %r15

        // RDX: argc
        // RCX: argv

        mov %rsp, %rbp

push_args:
        push (%rcx)
        add $8, %rcx
        dec %rdx
        jnz push_args

        // Add the function index and the jump table base and call
        call *(%rsi, %rdi, 8)

        mov %rbp, %rsp

        // Restore the callee saved registers
        pop %r15
        pop %r14
        pop %r13
        pop %r12
        pop %rbx

        // Frame pointer
        pop %rbp
        ret
.size trampoline_to_execute,.-trampoline_to_execute

.type trampoline_to_compile,%function
// arguments on the stack
// rdi contains function index
// rsi contains ptr to jump table base
// r8 contains ptr to runtime
trampoline_to_compile:
        push %rbp
        push %rsi
        push %r8

        mov %rsp, %rbp

        mov %r8, %rsi

        //push %r9
        and $0xfffffffffffffff0, %rsp
        call do_request_compilation
        //pop %r9

        mov %rbp, %rsp

        pop %r8
        pop %rsi
        pop %rbp

        // Return value is the function pointer
        jmp *%rax
.size trampoline_to_compile,.-trampoline_to_compile
