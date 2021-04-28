#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pmmintrin.h>

// Print all elements of vector:
void vec_print(float* vec, unsigned int element_count) {
  for (size_t i = 0; i < element_count; i++)
  {
    printf("vec[%zu]=%.2f\n", i, vec[i]);
  }
}

// Set vector 'out' to 1..element_count
// Set all elements of vector 'in' to 2:
void vec_reset(float* out, float* in, unsigned int element_count) {
  for (size_t i = 0; i < element_count; i++)
  {
    out[i] = i + 1;
    in[i] = 2;
  }
}

void mult_c(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // Classic C vector multiplication (for loop):
  // out[i] = out[i] * in[i];

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
  if (argc < 2)
  {
    printf("Missing argument: element count\n");
    printf("E.g.:     vec_mul.out 1000000  \n");
    return 0;
  }

  // Get the vector size:
  unsigned int element_count = atoi(argv[1]);

  // Get the vector size for SSE aka
  // if element_count is not divisible by 4, get the next divider by 4
  unsigned int element_count_sse = 
      element_count % 4 == 0 ? element_count : element_count + (4 - element_count % 4);
//    element_count % 4 == 0 ? element_count : element_count / 4 * 4 + 4);

  // Windows:
  // #include <malloc.h>
  // float* vec_out = (float*) _aligned_malloc(sizeof(float)*element_count_sse, 16);

  // Allocate input and output vector (float) of given size:
  float* vec_out = NULL;
  posix_memalign((void**)&vec_out, 16, sizeof(float)*element_count_sse);

  float* vec_in = NULL;
  posix_memalign((void**)&vec_in, 16, sizeof(float)*element_count_sse);

  // Reset the vectors:
  vec_reset(vec_out, vec_in, element_count_sse);
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
