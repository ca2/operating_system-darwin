#pragma once


#include "acme_posix/_.h"


#if defined(_ACME_DARWIN_LIBRARY)
   #define CLASS_DECL_ACME_DARWIN  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ACME_DARWIN  CLASS_DECL_IMPORT
#endif


namespace acme_darwin
{


   class node;


} // namespace acme_darwin





