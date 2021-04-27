#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pmmintrin.h>

// Print all elements of vector:
void vec_print(float* vec, unsigned int element_count) {

}

// Set vector 'out' to 1..element_count
// Set all elements of vector 'in' to 2:
void vec_reset(float* out, float* in, unsigned int element_count) {

}

void mult_c(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // Classic C vector multiplication (for loop):

  printf("C Loop Multiplication: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void mult_asm(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // Use X87 floating point stack for vector multiplication:

  // Calculate the size of the vector in bytes:

  // ====ASM====

  printf("Old ASM Multiplication: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void mult_intrinsics_sse(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // https://software.intel.com/sites/landingpage/IntrinsicsGuide/
  // Hints: _mm_store_ps, _mm_load_ps, _mm_mul_ps
  
  // Calculating number of iterations needed if we calc 4 floats at a time:

  // Intrinsics multiplication:

  printf("SSE with Intrinsics Multiplication: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void mult_asm_sse(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // Calculate the size of the vector in bytes:

  // ====ASM====
  // 4 floats per loop iteration:

  printf("ASM with SSE Multiplication: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
}

int main(int argc, char** argv) {

  // Check for argument count: (1. argument is path to binary, 2. argument should be element count of vector)

  // Get the vector size:

  // Get the vector size for SSE aka
  // if element_count is not divisible by 4, get the next divider by 4

  // Allocate input and output vector (float) of given size:


  // Reset the vectors:
  // Call classic C multiplication:


  // Reset the vectors:
  // Call assembler multiplication


  // Reset the vectors:
  // Call SSE intrinsics multiplication


  // Reset the vectors:
  // Call SSE assembler multiplication


  // Free the vectors:

  return 0;
}
