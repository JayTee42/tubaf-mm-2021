#include <stdio.h>

// Checks if specific bit in interger is set
int isBitSet(unsigned int num, int bit)
{
    //TODO:
    return 0;
}

void printFeature(const char* feature, unsigned int num, unsigned int bit)
{
    if (isBitSet(num, bit))
    {
        printf("%s ... available\n", feature);
    }
    else
    {
        printf("%s ... not available\n", feature);
    }
  
}

int main(void) {

    /////////////////////////////////////////
    // Let the CPU introduce itself        //
    // https://en.wikipedia.org/wiki/CPUID //
    /////////////////////////////////////////

    // Create 4 integer variables to store register outputs (RAX, RBX, RCX, RDX):
    unsigned int rax, rbx, rcx, rdx;

    // CPUID Version
    // ====ASM==== Set RAX to 0, call 'cpuid', receive outputs (RAX, RBX, RCX, RDX):
    __asm__ __volatile__ (
        ".intel_syntax noprefix \n"
        "mov rax, 0             \n"
        "cpuid                  \n"
        ".att_syntax prefix     \n"
        :"=a"(rax), "=b"(rbx), "=c"(rcx), "=d"(rdx)
    );

    // The CPUID Version is placed in RAX, print it:
    unsigned int version = rax;
    printf("CPUID Version %d\n", version);

    // If the CPUID Version is below 1, CPUID is not supported by the CPU -> close programm here
    if (version < 1){
        return 0;
    }

    // Manufacturer String
    // This is stored as ASCII-chars in RBX, RDX and RCX
    // Print all the 12 chars:
    // char vendor_string[13];
    // memset(vendor_string, 0, 13);

    // memcpy(vendor_string + 0, &rbx, 4);
    // memcpy(vendor_string + 4, &rdx, 4);
    // memcpy(vendor_string + 8, &rcx, 4);

    // printf("%s\n", vendor_string);
    unsigned int manufacturer_i[4] = { rbx, rdx, rcx, 0 };
    printf("Manufacturer: %s\n", (char*) &manufacturer_i[0]);

    // CPUID Features
    // ====ASM==== Set RAX to 1, call 'cpuid', receive outputs (RAX, RBX, RCX, RDX):
    __asm__ __volatile__ (
        ".intel_syntax noprefix \n"
        "mov rax, 1             \n"
        "cpuid                  \n"
        ".att_syntax prefix     \n"
        :"=a"(rax), "=b"(rbx), "=c"(rcx), "=d"(rdx)
    );

    // Print the features:
    printf("CPU supports: \n");

    // RDX 23 = MMX

    // RDX 25 = SSE

    // RDX 26 = SSE2

    // RCX 19 = SSE4.1

    // RCX 20 = SSE4.2

    // RCX 25 = AES

    // RCX 28 = AVX

    // RCX 12 = FMA3


    // Check if extended features are available (version >= 2):


    // CPUID Extended Features
    // ====ASM==== Set RAX to 7 and rcx to 0, call 'cpuid', receive outputs (RAX, RBX, RCX, RDX):

    // RBX 5 = AVX2

    // RBX 16 = AVX512-Foundation

    return 0;
}