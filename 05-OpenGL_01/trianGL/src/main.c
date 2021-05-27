#include <stdio.h>
#include <stdlib.h>

#include "gl_calls.h"

// Very naughty hack to fix a Cygwin linker error when using the MinGW GLFW binaries ... :(
#ifdef __CYGWIN__
	#include <stdarg.h>

	void __ms_vsnprintf(char * s, size_t n, const char * format, va_list arg)
	{
		vsnprintf(s, n, format, arg);
	}
#endif

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s (%d)\n", description, error);
	exit(EXIT_FAILURE);
}

int main(void)
{
	printf("Hello triangle!\n");
	return 0;
}
