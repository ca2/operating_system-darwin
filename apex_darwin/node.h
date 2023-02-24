//
// Created by camilo on 19/01/2021. <33TBS!!
//
//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme_darwin/node.h"
#include "apex_posix/node.h"


namespace apex_darwin
{


   class CLASS_DECL_ACME node :
      virtual public ::acme_darwin::node,
      virtual public ::apex_posix::node
   {
   public:


      node();
      ~node() override;


      int node_init_check(int * pi, char *** ppz) override;

      void on_start_application(::apex::application *papplication) override;


   };


} // namespace apex_posix



