//
// Created by camilo on 2022-08-17 22:52 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "node_gtk/desktop_environment.h"


namespace node_gnome
{


   class CLASS_DECL_NODE_GNOME desktop_environment :
   virtual public ::node_gtk::desktop_environment
{
   public:


   //bool        m_bX11;


   desktop_environment();
   ~desktop_environment() override;


//   virtual ::e_status _get_monitor_rectangle(::collection::index iMonitor, ::INT_RECTANGLE * prectangle);
//   virtual ::e_status _get_workspace_rectangle(::collection::index iMonitor, ::INT_RECTANGLE * prectangle);
//
//
//   void get_monitor_rectangle(::collection::index iMonitor, ::INT_RECTANGLE * prectangle) override;
//   void get_workspace_rectangle(::collection::index iMonitor, ::INT_RECTANGLE * prectangle) override;
//
//
//   void windowing_post(const ::procedure & procedure) override;
//
//
//   bool message_loop_step() override;
//
//
//   //virtual xcb_connection_t * _get_connection() override;


};


} // namespace node_gnomes



