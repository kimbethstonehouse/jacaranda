.align 16
.globl trampoline_to_execute
.globl trampoline_to_compile
.globl request_compilation
.type request_compilation,%function

.type trampoline_to_execute,%function
// The System V ABI calling convention for x86 enforces that parameters to functions are passed
// in registers rdi, rsi, rdx, rcx, r8, r9, and further values are passed on the stack in reverse order, so:
// rdi contains function index
// rsi contains ptr to jump table base
// rdx contains argc
// rcx contains ptr to argv
// r8 contains ptr to runtime

// This trampoline is responsible for moving function arguments (of an unknown type and quantity) into an expected
// location, before calling the jump table entry (which could be the function itself or the compile function)
trampoline_to_execute:
        // Frame pointer
        push %rbp

        // Save the callee saved registers
        push %rbx
        push %r12
        push %r13
        push %r14
        push %r15

        // Use rbp to preserve the current stack pointer
        mov %rsp, %rbp

// Our calling convention: pass all parameters on the stack in reverse order. This will likely be
// optimised in future, but we are using it for now to keep the implementation simple.
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
// rdi contains function index
// rsi contains ptr to jump table base
// r8 contains ptr to runtime
trampoline_to_compile:
        // Preserve these values, because once compilation has finished, we will invoke this function again
        push %rbp
        push %rsi
        push %r8

        mov %rsp, %rbp

        // The do_request_compilation function will expect System V,
        // so we must shift the runtime pointer from r8 to rsi
        mov %r8, %rsi

        // An x86 optimisation that requires the stack to be 16 byte aligned before a call
        // The stack is currently 8 byte aligned, so pushing a random 8 byte value prevents a segfault
        push %r9
        and $0xfffffffffffffff0, %rsp
        // This calls a C++ stub
        call do_request_compilation
        pop %r9

        mov %rbp, %rsp

        pop %r8
        pop %rsi
        pop %rbp

        // Return value is the function pointer, so this transfers control to the compiled code
        jmp *%rax
.size trampoline_to_compile,.-trampoline_to_compile



/*
.text

.align 16
.globl invoke_function
invoke_function:
    push %rbp
    push %r12
    push %r13
    push %r14
    push %r15

    call *(%rdi, %rsi, 8)

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbp

    ret
*/
