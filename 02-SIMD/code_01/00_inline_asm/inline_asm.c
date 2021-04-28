// https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
// https://www.cs.virginia.edu/~evans/cs216/guides/x86.html
// https://www.complang.tuwien.ac.at/ubvl/amd64/amd64h.html
int main(void){

    //                  Assembler Syntax Flavours
    // +------------------------------+------------------------------------+
    // |       Intel Code             |      AT&T Code                     |
    // +------------------------------+------------------------------------+
    // | mov     eax,1                |  movl    $1,%eax                   |   
    // | mov     ebx,0ffh             |  movl    $0xff,%ebx                |   
    // | int     80h                  |  int     $0x80                     |   
    // | mov     ebx, eax             |  movl    %eax, %ebx                |
    // | mov     eax,[ecx]            |  movl    (%ecx),%eax               |
    // | mov     eax,[ebx+3]          |  movl    3(%ebx),%eax              | 
    // | mov     eax,[ebx+20h]        |  movl    0x20(%ebx),%eax           |
    // | add     eax,[ebx+ecx*2h]     |  addl    (%ebx,%ecx,0x2),%eax      |
    // | lea     eax,[ebx+ecx]        |  leal    (%ebx,%ecx),%eax          |
    // | sub     eax,[ebx+ecx*4h-20h] |  subl    -0x20(%ebx,%ecx,0x4),%eax |
    // +------------------------------+------------------------------------+
    // |                Source-Destination Ordering                        |
    // +------------------------------+------------------------------------+
    // |     Destination Source       |       Source Destination           |
    // +------------------------------+------------------------------------+
    // |                      Register Naming                              |
    // +------------------------------+------------------------------------+
    // |     eax, edx, rax, rdx ...   |    %eax, %edx, %rax, %rdx ...      |
    // +------------------------------+------------------------------------+
    // |                     Immediate Operands                            |
    // +------------------------------+------------------------------------+
    // |    1 , 42, BEEF42h ...       |       $1, $42, $0xBEEF42 ...       |
    // +------------------------------+------------------------------------+
    // |                       Operand Size                                |
    // +------------------------------+------------------------------------+
    // |'byte/word/dword ptr' operand | Op-Code suffix: b, w, l, q         |
    // +------------------------------+------------------------------------+
    // |                        Memory Operands                            |
    // +------------------------------+------------------------------------+
    // | [base + index * scale + off] | off(base, index, scale)//immediate!|
    // +------------------------------+------------------------------------+

    // Ex. 1 -> inline_asm.o.asm
    // int a = 42;
    // int b = a + 1;

    // Inline Assembler
    // __asm__(
    //     "Assembler-Code \n"
    //     "2. Zeile Code  \n"
    //     : output                // optional
    //     : input                 // optional
    //     : clobbered registers   // optional
    // );

    // Ex. 2 -> inline_asm.o.asm
    // __asm__(
    //     ".intel_syntax noprefix \n"
    //     "mov eax, 1\n"
    //     "NOP \n"
    //     ".att_syntax prefix \n"
    // );

    // Ay compiler, leave my asm alone!
    // Code "as is", "where it is", no loop unrolling, no dead code deletion...
    // __asm__ __volatile__("");

    // Ex. 3 Input, Output
    #include <stdio.h>
    int argument = 42;
    int result;

    __asm__ __volatile__(
         ".intel_syntax noprefix \n"
         "add rbx, 8             \n"
         "mov rax, rbx           \n"
         ".att_syntax prefix     \n"
         : "=a" (result)
         : "b" (argument)
         : "xmm0"
    );
    printf("Result: %d\n", result);

    return 0;
}