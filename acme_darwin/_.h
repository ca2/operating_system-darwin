#pragma once


#include "operating_system-posix/acme_posix/_.h"


#if defined(_acme_darwin_project)
   #define CLASS_DECL_ACME_DARWIN  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ACME_DARWIN  CLASS_DECL_IMPORT
#endif


namespace acme_darwin
{


   class node;


} // namespace acme_darwin





