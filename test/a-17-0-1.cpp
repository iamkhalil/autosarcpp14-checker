// Run: $ clang++ -fsyntax-only -std=c++14 -Wreserved-id-macro -Wmacro-redefined -Wbuiltin-macro-redefined -Werror -ferror-limit=0 

// Compliant

#define ABS(x) (((x) < 0) ? -(x) : (x))
#define DATE "Today"
#define LINE 42
#define STDC_HOSTED 1
#define TIME 24 
#define STDC 1
#define FILE filename
#define ERRNO 98 

#undef ABS
#undef DATE
#undef LINE
#undef STDC_HOSTED
#undef TIME
#undef STDC
#undef FILE
#undef ERRNO
#undef ASSERT


// Non-compliant

#define __STDC_FORMAT_MACROS
#include <stdint.h>
#define __STDC_LIMIT_MACROS
#include <inttypes.h>

#define __cplusplus
#define __DATE__
#define __FILE__
#define __LINE__
#define __STDC_HOSTED__
#define __TIME__
#define __STDC__
#define __STDC_MB_MIGHT_NEQ_WC__
#define __STDC_VERSION__
#define __STDC_ISO_10646__
#define __STDCPP_STRICT_POINTER_SAFETY__
#define __STDCPP_THREADS__
#define _ILLEGAL_NAME_WITH_UNDERSCORE_FIRST

#undef __cplusplus
#undef __DATE__
#undef __FILE__
#undef __LINE__
#undef __STDC_HOSTED__
#undef __TIME__
#undef __STDC__
#undef __STDC_MB_MIGHT_NEQ_WC__
#undef __STDC_VERSION__
#undef __STDC_ISO_10646__
#undef __STDCPP_STRICT_POINTER_SAFETY__
#undef __STDCPP_THREADS__
#undef _ILLEGAL_NAME_WITH_UNDERSCORE_FIRST

// Not detected -_-!

#define errno
#define assert

#undef errno
#undef assert

#undef define
#define define 
