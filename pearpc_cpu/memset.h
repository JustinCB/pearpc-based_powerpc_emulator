#include "config.h"
#include <limits.h>
#ifndef HAVE_MEMSET_H
#define HAVE_MEMSET_H
#if HAVE_MEMSET_S
#define memset_f(b, c, len) memset_s(b, (rsize_t)(RSIZE_MAX - 1), c, (rsize_t)len)
#else
static inline void * memset_f(void * b, int c, size_t len)
{
	long i;
	char * ptr = (char *)b;
	for (i = 0; i < (long)len; i++) {
		ptr[i] = (unsigned char)c;
	}
	return b;
}
#endif
#endif