/*****<3ThomasBorregaardSørensen!!Created by camilo*/
// From acme_posix/file_system.h
// on 2021-08-12
// 18:20 BRT
#include "framework.h"
#include "path_system.h"
#include "acme/filesystem/filesystem/path.h"
#include <sys/stat.h>


namespace acme_darwin
{


   path_system::path_system()
   {


   }

   path_system::~path_system()
   {


   }


//   ::file::enum_type path_system::get_type(const char * path1)
//   {
//
//      struct stat st;
//
//      if (stat(path1, &st))
//      {
//
//         return ::file::e_type_doesnt_exist;
//
//      }
//
//      if ((st.st_mode & S_IFDIR))
//      {
//
//         return ::file::e_type_folder;
//
//      }
//      else
//      {
//
//         return ::file::e_type_file;
//
//      }
//
//   }
//
//
//   ::file::path path_system::_final(const char * path)
//   {
//
//      if (::is_null(path))
//      {
//
//         return "";
//
//      }
//
//      if(*path == '\0')
//      {
//
//         return "";
//
//      }
//
//      char * pszRealPath = ::realpath(path, NULL);
//
//      if (::is_null(pszRealPath))
//      {
//
//         return "";
//
//      }
//
//      ::file::path filepath(pszRealPath);
//
//      ::free(pszRealPath);
//
//      return filepath;
//
//   }


} // namespace acme_darwin



