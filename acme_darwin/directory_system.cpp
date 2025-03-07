// From acme/filesystem/file/dir.cpp by camilo 
// on 2021-08-09 03:19 BRT
// <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "directory_system.h"
#include "file_system.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/_operating_system.h"


#if defined(__APPLE__) || defined(ANDROID)

char * get_current_dir_name();

#endif


#if defined(WINDOWS_DESKTOP)
#include <Shlobj.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#elif defined(LINUX)
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <dirent.h>
#elif defined(ANDROID)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(_UWP)
#include "acme/os/universal_windows/file_winrt.h"
#elif defined(FREEBSD)
#define _GNU_SOURCE
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
char * get_current_dir_name();
#endif


namespace acme_darwin
{


   void TranslateLastError()
   {

      if (errno == EEXIST)
      {

         set_last_status(error_already_exists);

      }
      else
      {

         set_last_status(::success);

      }

   }


   directory_system::directory_system()
   {


   }


   directory_system::~directory_system()
   {


   }

//
//   ::e_status directory_system::create(const char * path)
//   {
//
//
//      return _create(path);
//
//      //}
//
//      //return ::file::system_dir::g_pthis->mk(path, ::get_context_system());
//
//   }
//
//
//   ::e_status directory_system::_create(const char * path)
//   {
//
//      return ::create_directory_path(path);
//
//   }
//
//
//   ::e_status directory_system::create_directory(const char * path)
//   {
//
//      return ::create_directory(path);
//
//   }


//   ::file::path directory_system::module()
//   {
//
//      ::file::path pathModule (file_system()->module());
//
//      return pathModule.folder();
//
//   }
//
//
//   bool directory_system::is(const char * path)
//   {
//
//      bool bDir = false;
//
//      if(!_is(bDir, path))
//      {
//
//         return false;
//
//      }
//
//      return bDir;
//
//   }
//
//
////   void directory_system::rls(::file::path_array & stra, const char * psz)
////   {
////
////      ::collection::count start = stra.get_count();
////
////      ls(stra, psz);
////
////      ::collection::count end = stra.get_count();
////
////      for (::collection::index i = start; i < end; i++)
////      {
////
////         if (is(stra[i]))
////         {
////
////            rls(stra, stra[i]);
////
////         }
////
////      }
////
////   }
//
//
////   void directory_system::rls_dir(::file::path_array & stra, const char * psz)
////   {
////
////      ::collection::count start = stra.get_count();
////
////      ls_dir(stra, psz);
////
////      ::collection::count end = stra.get_count();
////
////      for (::collection::index i = start; i < end; i++)
////      {
////
////         ::file::path path = stra[i];
////
////         rls_dir(stra, path);
////
////      }
////
////   }
//
//
//   void defer_add(::file::listing & listing, const dirent * dp)
//   {
//
//
//      if (file_path_is_dots(dp->d_name))
//      {
//
//         return;
//
//      }
//
//
//      ::file::path path;
//
//      string strFilename(dp->d_name);
//
//      path = listing.m_pathFinal / strFilename;
//
//      if(path.begins(listing.m_pathBasePath))
//      {
//
//         path.m_iBasePathLength = listing.m_pathBasePath.get_length() + 1;
//
//      }
//
//      path.m_iDir = dp->d_type & DT_DIR ? 1 : 0;
//
//      //path.m_iSize = make64_from32(finddata.nFileSizeLow, finddata.nFileSizeHigh);
//
//      listing.defer_add(path);
//
//   }
//
//
//
//   bool directory_system::enumerate(::file::listing & listing)
//   {
//
//      if (listing.m_pathFinal.is_empty())
//      {
//
//         listing.m_pathFinal = listing.m_pathUser;
//
//      }
//
//      if(listing.m_pathBasePath.is_empty())
//      {
//
//         listing.m_pathBasePath = listing.m_pathFinal;
//
//      }
//
//      if (!is(listing.m_pathFinal))
//      {
//
//         return false;
//
//      }
//
//      if (!listing.on_start_enumerating(this))
//      {
//
//         return true;
//
//      }
//
//      DIR * dirp = opendir(listing.m_pathFinal);
//
//      if (dirp == nullptr)
//      {
//
//         return true;
//
//      }
//
//      dirent * dp;
//
//      ::file::path path;
//
//      while ((dp = readdir(dirp)) != nullptr)
//      {
//
//         defer_add(listing, dp);
//
//      }
//
//      closedir(dirp);
//
//      return true;
//
//   }
//
//
//   bool directory_system::list(string_array & stra, const char * psz, ::file::e_flag eflag)
//   {
//
//      DIR * dirp = opendir(psz);
//
//      if (dirp == nullptr)
//      {
//
//         return true;
//
//      }
//
//      dirent * dp;
//
//      ::file::path path;
//
//      while ((dp = readdir(dirp)) != nullptr)
//      {
//
//         if(dp->d_type & DT_DIR)
//         {
//
//            if(eflag & ::file::e_flag_folder && !(eflag & ::file::e_flag_file))
//            {
//
//               stra.add(string(dp->d_name) + "/");
//
//            }
//
//         }
//         else
//         {
//
//            if(eflag & ::file::e_flag_file)
//            {
//
//               stra.add(dp->d_name);
//
//            }
//
//         }
//
//      }
//
//      closedir(dirp);
//
//      return true;
//
//   }
//
//
////   void directory_system::ls_dir(::file::path_array & stra, const char * psz)
////   {
////
////      DIR * dirp = opendir(psz);
////
////      if (dirp == nullptr)
////      {
////
////         return;
////
////      }
////
////      dirent * dp;
////
////      while ((dp = readdir(dirp)) != nullptr)
////      {
////
////         if (file_path_is_dots(dp->d_name))
////         {
////
////            continue;
////
////         }
////
////         ::file::path strPath = ::file::path(psz) / dp->d_name;
////
////         if (is(strPath))
////         {
////
////            stra.add(strPath);
////
////         }
////
////      }
////
////      closedir(dirp);
////
////   }
////
////
////   void directory_system::ls_file(::file::path_array & stra, const char * psz)
////   {
////
////      DIR * dirp = opendir(psz);
////
////      if (dirp == nullptr)
////      {
////
////         return;
////
////      }
////
////      dirent * dp;
////
////      while ((dp = readdir(dirp)) != nullptr)
////      {
////
////         if (file_path_is_dots(dp->d_name))
////         {
////
////            continue;
////
////         }
////
////         ::file::path strPath = ::file::path(psz) / dp->d_name;
////
////         if (!is(strPath))
////         {
////
////            stra.add(strPath);
////
////         }
////
////      }
////
////      closedir(dirp);
////
////   }
//
//
//   ::file::path directory_system::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
//   {
//
//      string_array stra;
//
//      stra.add_tokens(pszEnv, ":");
//
//      string strCandidate;
//
//      for (int i = 0; i < stra.get_count(); i++)
//      {
//
//         if (stra[i].is_empty())
//         {
//
//            continue;
//
//         }
//
//         strCandidate = ::file::path(stra[i]) / pszTopic;
//
//         if (file_system()->exists(strCandidate))
//         {
//
//            return strCandidate;
//
//         }
//
//      }
//
//      return "";
//
//   }
//
//
//   ::file::path directory_system::archive()
//   {
//
//
//      return home() / "archive";
//
//   }
//
//
//   string directory_system::get_current()
//   {
//
//      auto pszCurrentDirName = get_current_dir_name();
//
//      if(::is_null(pszCurrentDirName))
//      {
//
//         auto iErrNo = errno;
//
//         auto estatus = failed_errno_status(iErrNo);
//
//         throw ::exception(estatus, "posix::directory_system::get_current");
//
//      }
//
//      string strCurrentDirName = ::string_from_strdup(pszCurrentDirName);
//
//      return strCurrentDirName;
//
//   }
//
//
//   void directory_system::change_current(const char * psz)
//   {
//
//      auto iError = chdir(psz);
//
//      if(iError)
//      {
//
//         auto iErrNo = errno;
//
//         auto estatus = failed_errno_status(iErrNo);
//
//         throw ::exception(estatus, "posix::directory_system::change_current");
//
//      }
//
//   }
//
//
//
//
////::file::path directory_system::program_files_x86()
////{
////
////   ::file::path path("/opt/ca2");
////
////   return path;
////
////}
////
////
////::file::path directory_system::program_files()
////{
////
////   ::file::path path("/opt/ca2");
////
////   return path;
////
////}
//
//
////
////::file::path directory_system::home()
////{
////
////   return getenv("HOME");
////
////}
//
//
//#if defined(_UWP) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
//
////::file::path directory_system::bookmark()
////{
////
////   auto psystem = acmesystem();
////
////   auto pacmedir = psystem->directory_system();
////
////   return pacmedir->localconfig() / "bookmark";
////
////}
//
//
//#endif
//
//
//#ifdef _UWP
//
//
//::file::path directory_system::home()
//{
//
//   return "";
//
//}
//
//
//#endif
//
//


} // namespace acme_posix

//
//#if defined(__APPLE__) || defined(ANDROID)
//
//
//char * get_current_dir_name()
//{
//   
//   auto size = pathconf(".", _PC_PATH_MAX);
//   
//   if(size <= 0)
//   {
//      
//      size = PATH_MAX;
//      
//   }
//   
//   char * buf = (char *) malloc(size + 1);
//   
//   if(buf == nullptr)
//   {
//    
//      return nullptr;
//      
//   }
//   
//   auto ptr = getcwd(buf, (size_t)(size + 1));
//   
//   return ptr;
//
//}
//
//
//#endif
//
//
//
