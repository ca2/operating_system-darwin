#pragma once


#include "operating_system-posix/apex_posix/_.h"
#include "operating_system-darwin/acme_darwin/_.h"


#if defined(_apex_posix_project)
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_IMPORT
#endif



