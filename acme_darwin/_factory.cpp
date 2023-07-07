#include "framework.h"
#include "node.h"
//#include "file_memory_map.h"
//#include "pipe.h"
#include "acme_directory.h"
#include "acme_file.h"
#include "acme_path.h"
//#include "mutex.h"
//#include "exception_translator.h"


DECLARE_FACTORY(acme_posix);


IMPLEMENT_FACTORY(acme_darwin)
{
   
   acme_posix_factory(pfactory);

   pfactory->add_factory_item < ::acme_darwin::node                   , ::acme::node > ();
//   pfactory->add_factory_item < ::acme_posix::file_memory_map        , ::file::memory_map >();

   //pfactory->add_factory_item < ::acme_posix::pipe                   , ::operating_system::pipe >();

   pfactory->add_factory_item < ::acme_darwin::acme_directory         , ::acme_directory >();
   pfactory->add_factory_item < ::acme_darwin::acme_file              , ::acme_file >();
   pfactory->add_factory_item < ::acme_darwin::acme_path              , ::acme_path >();

//   pfactory->add_factory_item < ::acme_posix::exception_translator   , ::exception_translator >();
//
//
//   pfactory->add_factory_item < ::acme_posix::mutex                  , ::mutex >();

}



