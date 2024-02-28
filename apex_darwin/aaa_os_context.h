#pragma once


#include "apex_posix/os_context.h"


namespace apex_darwin
{


   class CLASS_DECL_APEX os_context :
      virtual public ::apex_posix::os_context
   {
   public:


      os_context();
      ~os_context() override;


      bool is_alias(const ::file::path & path) override;
      
      
      virtual ::process_identifier current_process_identifier() override;


   };


} // namespace apex_darwin



