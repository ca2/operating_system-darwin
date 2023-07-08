#include "framework.h"
#include "file_context.h"
#include "os_context.h"
#include "node.h"
#include "app_launcher.h"
//#include "posix_spawn/process.h"
//#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_5)
//#include "system_5/interprocess_caller.h"
//#include "system_5/interprocess_target.h"
//#endif
//
//#ifdef FILE_SYSTEM_INOTIFY
//
//#include "inotify/watch.h"
//#include "inotify/watcher.h"
//
//#endif


__FACTORY_EXPORT void apex_posix_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void acme_darwin_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_darwin_factory(::factory::factory * pfactory)
{

   apex_posix_factory(pfactory);
   
   acme_darwin_factory(pfactory);
   
   pfactory->add_factory_item < ::apex_darwin::app_launcher, ::apex::app_launcher >();

}



