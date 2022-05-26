.align 16
.globl trampoline_to_execute
.globl trampoline_to_compile
.globl request_compilation
.type request_compilation,%function

.type trampoline_to_execute,%function
trampoline_to_execute: // rdi contains argc, rsi contains argv, rdx contains func idx, rcx contains execution state (jump table base, runtime)
        // Save the callee saved registers
        push %rbx
        push %rsp
        push %rbp
        push %r12
        push %r13
        push %r14
        push %r15

        // Add the function index and the jump table base and call
        call *(%rcx, %rdx, 8)

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
trampoline_to_compile: // rdi contains argc, rsi contains argv, rdx contains func idx, rcx contains execution state (jump table base, runtime)
        // Make the function index the first argument
        push %rdi
        mov %rdx, %rdi

        // TODO: rcx + 8 contains runtime ptr, so just need to call runtime.request_compilation somehow

        // Restore argc
        pop %rdi

        // Return value is the function pointer
        call *(%rax)

        ret
.size trampoline_to_compile,.-trampoline_to_compile

