#pragma once

#include <bits/move.h>

#include <cstdlib>

__forceinline

//#define __forceinline __attribute__((always_inline))

//#define __forceinline inline __attribute__((__always_inline__))


// #ifndef __attribute_always_inline__
// #if __has_attribute(always_inline) \
//  || __GNUC_PREREQ(3,1) \
//  || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
//  || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
//  || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5110) /* Sun Studio 12.2 C++ */
// #define __attribute_always_inline__  __attribute__((__always_inline__))
// #elif defined(_MSC_VER)
// /* http://msdn.microsoft.com/en-us/library/z8y1yy88.aspx */
// #define __attribute_always_inline__  __forceinline
// #else
// #define __attribute_always_inline__  C99INLINE
// #endif
//#endif
