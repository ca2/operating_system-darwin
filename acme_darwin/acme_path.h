/*****<3ThomasBorregaardSørensen!!Created by camilo*/
// From acme_posix/acme_file.h
// on 2021-08-12
// 18:18 BRT


#include "acme_posix/acme_path.h"


namespace acme_darwin
{


   class CLASS_DECL_ACME acme_path :
      virtual public ::acme_posix::acme_path
   {
   public:


      //__creatable_from_library(acme_path, ::acme_path, "acme_posix");


      acme_path();
      ~acme_path() override;


//      ::file::enum_type get_type(const char * path1) override;
//
//      ::file::path _final(const char * path) override;


   };


} // namespace acme_darwin



