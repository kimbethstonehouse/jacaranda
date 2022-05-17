.align 16
.globl trampoline_to_execute
.globl trampoline_to_compile

.type trampoline_to_execute,%function
trampoline_to_execute: // rdi contains argc, rsi contains argv, rdx contains function_ptr
        // Save the callee saved registers
        push %rbx
        push %rsp
        push %rbp
        push %r12
        push %r13
        push %r14
        push %r15

        // TODO: put arguments where expected
        call %rdx

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
trampoline_to_compile:
        // TODO: this
        // args are where the compiler put them
        // fn idx is on the stack

        // Save the callee saved registers
        push %rbp
        push %rbx
        push %r12
        push %r13
        push %r14
        push %r15

        // TODO: retrieve idx from stack, call compile(idx), ret val is funcptr
        call *(%rsi)

        // Restore runtime state
        pop %r15
        pop %r14
        pop %r13
        pop %r12
        pop %rbx
        pop %rbp

        ret
.size trampoline_to_compile,.-trampoline_to_compile

