.align 16
.globl trampoline_to_execute
.globl trampoline_to_compile
.globl request_compilation
.type request_compilation,%function

.type trampoline_to_execute,%function
// rdi contains function index
// rsi contains ptr to jump table base
// r8 contains ptr to runtime
// rdx contains argc
// rcx contains ptr to argv
trampoline_to_execute:
        // Save the callee saved registers
        push %rbx
        push %rsp
        push %rbp
        push %r12
        push %r13
        push %r14
        push %r15

        // Push the arguments onto the stack
        imul $8, %rdx
push_args:
        sub $8, %rdx

        cmp $0, %rdx
        jl call_func

        // Double dereference argv[argc]
        mov (%rcx), %rax
        movzxb (%rdx,%rax), %rax
        push %rax
        jmp push_args



call_func:
        // Add the function index and the jump table base and call
        //sub 0x10, %rsp
        add $8, %rsi
        call *(%rsi)
        //call *(%rsi, %rdi, 8)


// todo: who clears up the stack?

        // Restore the callee saved registers
        pop %r15
        pop %r14
        pop %r13
        pop %r12
        pop %rbp
        pop %rsp
        pop %rbx

        ret
.size trampoline_to_execute,.-trampoline_to_execute

.type trampoline_to_compile,%function
// arguments on the stack
// rdi contains function index
// rsi contains ptr to jump table base
// r8 contains ptr to runtime
trampoline_to_compile:
        push %rdi
        push %rsi

        mov %r8, %rsi
        // TODO: rsi + 8 contains runtime ptr, so just need to call runtime.request_compilation somehow

// todo: stack alignment something?

        call do_request_compilation

        pop %rsi
        pop %rdi

        // Return value is the function pointer
        call *(%rax)

        ret
.size trampoline_to_compile,.-trampoline_to_compile

