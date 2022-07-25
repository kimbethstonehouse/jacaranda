# Jacaranda

The infrastructure is currently split into three main sections: the repository, the runtime and the compiler.

## JacarandaRepository

See ```src/repository/repository.cpp```

A stub for the central code repository. At the moment, the compiler requests code for a particular WebAssembly module and function, and the respository reads the code from a local file, parses it, and sends it via gRPC. In the future, this will likely be more sophisticated.

## JacarandaRuntime

See ```src/runtime/runtime.cpp```

Responsible for allocating memory, initialising jump tables and handling the execution of the native code provided by the compiler, function-by-function. The assembly files are specific to x86, so they will be the first thing to update when porting to ARM.

## JacarandaCompiler

See ```src/compiler/compiler.cpp```

Handles the actual compilation of the WebAssembly binary code. Currently responds with precompiled code until LLVM is integrated.

## JacarandaEnvoys

See ```src/*/*envoy.cpp```

Handle the communication between services. Responsible for serialising and deserialising information into protocol buffers and making remote procedure calls via stubs. Communication is done via gRPC as it allows bidirectional communication, rather than unidirectional procedure calls from client to server only.

## Trampolines

The trampoline functions in trampoline.S facilitate moving between x86 code and C++ code. The C++ code will be compiled by gcc (or clang) to x86 code that follows the System V ABI, which is not always what we want. 

## Building

```
git clone git@github.com:kimbethstonehouse/jacaranda.git
cd jacaranda
mkdir build && cd build
cmake ..
make
```

## Executing

Currently, the compiler does nothing but return precompiled x86 code for a very basic addition program. The expected output is the sum of the two program arguments, e.g. ```./exe/runtime add.wasm 5 6``` should output ```11```. The corresponding C code is:

```
int atoi(char *c) {
    return *c-0x30;
}

int main(int argc, char **argv) {
    return atoi(argv[1]) + atoi(argv[2]);
}
```

In x86, assuming all arguments are on the stack, we get:

```
.text

.align 16
.type atoi,%function
atoi:
    push %rbp
    mov %rsp, %rbp

    mov 16(%rbp), %rax
    mov (%rax), %al

    // Subtract 0x30 to convert ASCII to number
    sub $0x30, %al
    movzx %al, %eax

    leave
    ret

.align 16
.type main,%function
// rdi contains function index
// rsi contains ptr to jump table base
main:
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
```

To execute, open three separate terminals. Follow this order, since each component depends on the previous service being up and running.

```
./exe/repository
./exe/compiler
```

You can then execute wasm programs using the runtime executable. Note that currently, although the code repository has a fully functional parser that sends individual WebAssembly functions to the compiler, the compiler ignores this and returns precompiled code, so the file.wasm input makes no difference to the program output.

```
./exe/runtime [file.wasm] [program arguments]
```

This triggers a sequence of events. Firstly, the runtime ```run``` function is called, which requests information from the central code repository about the total number of functions in the WebAssembly module and the index of the start function (usually main). Run also initialises the jump table, which is an array of pointers to executable code, one per function. All entries in the jump table initially point to the compile function, and then once a function has been compiled for the first time, the jump table entry is updated to point to the compiled code. This means that the process of invoking a function is always exactly the same, regardless of whether the function has been compiled yet: simply begin executing at the address in the relevant jump table entry. Generated application code does not need to check if a function has been compiled yet, it can just call the function and compilation will be handled if necessary.

Run then requests compiled code for the starting function, copies the compiler response into executable memory, and updates the jump table pointer before calling ```trampoline_to_execute```. The purpose of this trampoline function is to move the function parameters into an expected location, according to the calling convention in use. Since this requires manipulating registers and the stack, the trampoline must be implemented in assembly. The trampoline function then jumps to the address held in the jump table entry for the relevant function index. Should the function in question not have been compiled yet, the compile function will need to be invoked with the function index as an argument. This requires preserving the function arguments so that the function can be reinvoked after compilation has finished, which is handled by ```trampoline_to_compile```.

## Calling convention

Note that ```trampoline_to_execute``` will be called for the start function for every WebAssembly module. Each of these start functions may require a different function signature, which would ordinarily be used by the compiler to implement the calling convention for us. Since this function cannot have multiple function signature, it uses an argc argv pattern to handle all start functions. The trampoline function is then responsible for parsing this argc argv pattern into a calling convention that the rest of the application code can expect. Ideally, this would be something standard like System V. However, for implementation simplicity, we currently pass all parameters on the stack, and only use registers to store the current function index (used by the compiler to determine what function was being invoked when compilation was triggered) and the pointer to the jump table (used to call a particular function). However, the cost of this simplicity is twofold: passing arguments on the stack is slow, and when we move back into C++ code (for example, to call the compiler), we must transition back to System V. For this reason, this calling convention will probably change in future. 
