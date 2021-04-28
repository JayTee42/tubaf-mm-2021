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
  for (size_t i = 0; i < element_count; i++)
  {
    out[i] = out[i] * in[i];
  }
  
  printf("C Loop Multiplication: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void mult_asm(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // Use X87 floating point stack for vector multiplication:

  // Calculate the size of the vector in bytes:
  size_t byte_length = sizeof(float) * element_count;

  // ====ASM====
  __asm__ __volatile__(
    ".intel_syntax noprefix     \n"
    "my_label1:                 \n"
    "sub rcx, 4                 \n" // set zero flag
    "fld dword ptr [rbx+rcx]    \n"
    "fld dword ptr [rax+rcx]    \n"
    "fmulp st(1), st(0)         \n"
    "fstp dword ptr [rax+rcx]   \n"
    "jnz my_label1              \n" // check zero flag
    ".att_syntax prefix         \n"
    :
    :"a"(out), "b"(in), "c"(byte_length)
    :
  );

  printf("Old ASM Multiplication: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void mult_intrinsics_sse(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // https://software.intel.com/sites/landingpage/IntrinsicsGuide/
  // Hints: _mm_store_ps, _mm_load_ps, _mm_mul_ps
  
  // Calculating number of iterations needed if we calc 4 floats at a time:
  
  // Intrinsics multiplication:
  unsigned int sse_iter = element_count / 4;
  
  for (size_t i = 0; i < sse_iter; i++)
  {
    __m128 out_sse = _mm_load_ps(out + 4 * i);
    __m128 in_sse = _mm_load_ps(in + 4 * i);
    __m128 result = _mm_mul_ps(out_sse, in_sse);
    _mm_store_ps(out + 4 * i, result);
  }

  printf("SSE with Intrinsics Multiplication: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void mult_asm_sse(float* out, float* in, unsigned int element_count) {
  clock_t start = clock();

  // Calculate the size of the vector in bytes:
  size_t byte_length = sizeof(float) * element_count;

  // ====ASM====
  // 4 floats per loop iteration:
  __asm__ __volatile__(
    ".intel_syntax noprefix     \n"
    "my_label2:                 \n"
    "sub rcx, 16                \n"
    "movaps xmm0, [rbx + rcx]   \n"
    "movaps xmm1, [rax + rcx]   \n"
    "mulps xmm0, xmm1           \n"
    "movaps [rax + rcx], xmm0   \n"
    "jnz my_label2              \n"
    ".att_syntax prefix         \n"
    :
    :"a"(out), "b"(in), "c"(byte_length)
    :"xmm0", "xmm1"
  );

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
  mult_c(vec_out, vec_in, element_count_sse);

  // Reset the vectors:
  vec_reset(vec_out, vec_in, element_count_sse);
  // Call assembler multiplication
  mult_asm(vec_out, vec_in, element_count_sse);  

  // Reset the vectors:
  vec_reset(vec_out, vec_in, element_count_sse);
  // Call SSE intrinsics multiplication
  mult_intrinsics_sse(vec_out, vec_in, element_count_sse);  

  // Reset the vectors:
  vec_reset(vec_out, vec_in, element_count_sse);
  // Call SSE assembler multiplication
  mult_asm_sse(vec_out, vec_in, element_count_sse);  

  // Free the vectors:
  free(vec_in);
  free(vec_out);

  return 0;
}
