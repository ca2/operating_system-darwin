#include "framework.h"
#include "node.h"
//#include "file_memory_map.h"
//#include "pipe.h"
#include "directory_system.h"
#include "file_system.h"
#include "path_system.h"
//#include "mutex.h"
//#include "exception_translator.h"


DECLARE_FACTORY(acme_posix);


IMPLEMENT_FACTORY(acme_darwin)
{
   
   acme_posix_factory(pfactory);

   pfactory->add_factory_item < ::acme_darwin::node                   , ::platform::node > ();
//   pfactory->add_factory_item < ::acme_posix::file_memory_map        , ::file::memory_map >();

   //pfactory->add_factory_item < ::acme_posix::pipe                   , ::operating_system::pipe >();

   pfactory->add_factory_item < ::acme_darwin::directory_system         , ::directory_system >();
   pfactory->add_factory_item < ::acme_darwin::file_system              , ::file_system >();
   pfactory->add_factory_item < ::acme_darwin::path_system              , ::path_system >();

//   pfactory->add_factory_item < ::acme_posix::exception_translator   , ::exception_translator >();
//
//
//   pfactory->add_factory_item < ::acme_posix::mutex                  , ::mutex >();

}



