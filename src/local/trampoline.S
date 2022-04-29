.align 16
.globl do_invoke_function

// variable here called jtableptr

.type do_invoke_function,%function
do_invoke_function:
        // RDI contains exec state
        // RSI contains fn ptr
        
        // Save the callee saved registers
        push %rbp
        push %rbx
        push %r12
        push %r13
        push %r14
        push %r15

        // RDI still has exec state
        // RSI still has fn ptr
        call *(%rsi)

        pop %r15
        pop %r14
        pop %r13
        pop %r12
        pop %rbx
        pop %rbp

        ret
.size do_invoke_function,.-do_invoke_function

.align 16
.globl do_compilation
.type do_compilation,%function
do_compilation_and_invoke:
        // RDI contains exec state

        push %rdi

        // TODO: compile
        call COMPILE_IT

        pop %rdi

        jmp *(%rax)
