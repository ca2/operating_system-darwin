#pragma once


#include "operating_system-posix/aura_posix/_.h"
#include "operating_system-darwin/apex_darwin/_.h"


#if defined(_AURA_POSIX_LIBRARY)
   #define CLASS_DECL_AURA_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AURA_POSIX  CLASS_DECL_IMPORT
#endif


namespace aura_posix
{


   class node;


} // namespace aura_posix



