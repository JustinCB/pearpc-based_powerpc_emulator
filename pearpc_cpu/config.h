/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
#undef AC_APPLE_UNIVERSAL_BUILD

/* Define to 1 if you have the <asm/types.h> header file. */
#undef HAVE_ASM_TYPES_H

/* Have TUN/TAP headers? */
#undef HAVE_BEOS_TUN

/* Define to 1 if you have the `exp2' function. */
#undef HAVE_EXP2

/* Define to 1 if you have the `gettimeofday' function. */
#undef HAVE_GETTIMEOFDAY

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H
#define HAVE_INTTYPES_H 1
/* Define to 1 if you have the <linux/if_tun.h> header file. */
#undef HAVE_LINUX_IF_TUN_H

/* Define to 1 if you have the <linux/netlink.h> header file. */
#undef HAVE_LINUX_NETLINK_H

/* Have TUN/TAP headers? */
#undef HAVE_LINUX_TUN

/* Define to 1 if you have the `log2' function. */
#undef HAVE_LOG2

/* Define to 1 if you have the <mach/clock.h> header file. */
#undef HAVE_MACH_CLOCK_H
#define HAVE_MACH_CLOCK_H 1
/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H
#define HAVE_MEMORY_H 1
/* Define to 1 if you have the `memset' function. */
#undef HAVE_MEMSET

/* Define to 1 if you have the <pthread.h> header file. */
#undef HAVE_PTHREAD_H
#define HAVE_PTHREAD_H 1
/* Define to 1 if you have the `setenv' function. */
#undef HAVE_SETENV

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H
#define HAVE_STINT_H 1
/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H
#define HAVE_STDLIB_H 1
/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H
#define HAVE_STRINGS_H 1
/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H
#define HAVE_STRING_H 1
/* Define to 1 if you have the <sys/socket.h> header file. */
#undef HAVE_SYS_SOCKET_H
#define HAVE_SYS_SOCKET_H 1
/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H
#define HAVE_SYS_STAT_H 1
/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H
#define HAVE_SYS_TYPES_H 1
/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* big-endian byte-order helper constant */
#undef HOST_ENDIANESS_BE
#define HOST_ENDIANESS_BE 0
/* little-endian byte-order helper constant */
#undef HOST_ENDIANESS_LE
#define HOST_ENDIANESS_LE 8
/* Which host endianess/byte-order? */
#undef HOST_ENDIANESS
#define HOST_ENDIANESS HOST_ENDIANESS_LE
/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Have pthread.h? */
#undef PTHREAD_HDR
#define PTHREAD_HDR 1
/* The size of `char', as computed by sizeof. */
#undef SIZEOF_CHAR
#define SIZEOF_CHAR 1
/* The size of `int', as computed by sizeof. */
#undef SIZEOF_INT
#define SIZEOF_INT sizeof(int)
/* The size of `long int', as computed by sizeof. */
#undef SIZEOF_LONG_INT
#define SIZEOF_LONG_INT sizeof(long int)
/* The size of `long long', as computed by sizeof. */
#undef SIZEOF_LONG_LONG
#define SIZEOF_LONG_LONG sizeof(long long)
/* The size of `short', as computed by sizeof. */
#undef SIZEOF_SHORT
#define SIZEOF_SHORT sizeof(short)
/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS
#define STDC_HEADERS 1
/* Location of system/arch/$ARCH_DIR/sysendian.h */
#undef SYSTEM_ARCH_SPECIFIC_ENDIAN_DIR
#define SYSTEM_ARCH_SPECIFIC_ENDIAN_DIR system/arch/generic/sysendian.h
/* Location of system/arch/$ARCH_DIR/sysfeatures.h */
#undef SYSTEM_ARCH_SPECIFIC_FEATURES_DIR
#define SYSTEM_ARCH_SPECIFIC_FEATURES_DIR system/arch/generic/sysfeatures.h
/* Location of system/osapi/$OSAPI_DIR/types.h */
#undef SYSTEM_OSAPI_SPECIFIC_TYPES_HDR
#define SYSTEM_OSAPI_SPECIFIC_TYPES_HDR system/osapi/posix/types.h
/* Which signal to use for clock timer */
#undef SYSTIMER_SIGNAL
#define SYSTIMER_SIGNAL SIGRTMIN
/* Prefer POSIX realtime clock API */
#undef USE_POSIX_REALTIME_CLOCK
#define USE_POSIX_REALTIME_CLOCK 1
/* Use interval timer clock API */
#undef USE_POSIX_SETITIMER

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif

/* Define to 1 if the X Window System is missing or not being used. */
#undef X_DISPLAY_MISSING
#define X_DISPLAY_MISSING 1
/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#undef YYTEXT_POINTER

/* Define to empty if `const' does not conform to ANSI C. */
#undef const
#define const
/* define to 1 if the OS has memset_s */
#undef HAVE_MEMSET_S
#define HAVE_MEMSET_S 1