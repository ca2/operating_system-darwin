/*****<3ThomasBorregaardSørensen!!Created by camilo*/
// From acme_posix/acme_file.h
// on 2021-08-12
// 18:18 BRT
#pragma once


#include "acme_posix/path_system.h"


namespace acme_darwin
{


   class CLASS_DECL_ACME path_system :
      virtual public ::acme_posix::path_system
   {
   public:


      //__creatable_from_library(acme_path, ::acme_path, "acme_posix");


      path_system();
      ~path_system() override;


//      ::file::enum_type get_type(const char * path1) override;
//
//      ::file::path _final(const char * path) override;


   };


} // namespace acme_darwin



