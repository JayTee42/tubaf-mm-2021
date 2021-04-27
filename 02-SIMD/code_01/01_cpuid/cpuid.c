#include <stdio.h>

// Checks if specific bit in interger is set
int isBitSet(unsigned int num, int bit)
{
    //TODO:
    return 0;
}

int main(void) {

    /////////////////////////////////////////
    // Let the CPU introduce itself        //
    // https://en.wikipedia.org/wiki/CPUID //
    /////////////////////////////////////////

    // Create 4 integer variables to store register outputs (RAX, RBX, RCX, RDX):

    // CPUID Version
    // ====ASM==== Set RAX to 0, call 'cpuid', receive outputs (RAX, RBX, RCX, RDX):


    // The CPUID Version is placed in RAX, print it:


    // Manufacturer String
    // This is stored as ASCII-chars in RBX, RDX and RCX
    // Print all the 12 chars:


    // If the CPUID Version is below 1, CPUID is not supported by the CPU -> close programm here


    // CPUID Features
    // ====ASM==== Set RAX to 1, call 'cpuid', receive outputs (RAX, RBX, RCX, RDX):


    // Print the features:
    printf("CPU supports: \n");

    // RDX 23 = MMX

    // RDX 25 = SSE

    // RDX 26 = SSE2

    // RCX 19 = SSE4.1

    // RCX 20 = SSE4.2

    // RCX 25 = AES

    // RCX 28 = AVX

    // RCX 28 = FMA3


    // Check if extended features are available (version >= 2):


    // CPUID Extended Features
    // ====ASM==== Set RAX to 2 and rcx to 0, call 'cpuid', receive outputs (RAX, RBX, RCX, RDX):

    // RBX 5 = AVX2

    // RBX 16 = AVX512-Foundation

    return 0;
}