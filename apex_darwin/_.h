#pragma once


#include "apex_posix/_.h"
#include "acme_darwin/_.h"


#if defined(_APEX_POSIX_LIBRARY)
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_IMPORT
#endif



