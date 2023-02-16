// From apex/platform/app_launcher.h by camilo on 2023-02-15 19:26 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/app_launcher.h"


namespace apex_darwin
{


   class CLASS_DECL_APEX app_launcher : 
virtual public ::apex::app_launcher
   {
   public:


      app_launcher();

      virtual void initialize_app_launcher(::particle * pparticle, string strPlatform, string strApp);


      virtual string get_executable_extension();

      virtual string get_params();

      virtual void run();


   };




} // namespace apex_darwin



