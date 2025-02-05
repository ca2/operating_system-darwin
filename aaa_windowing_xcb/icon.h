// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


#include "aura/windowing/icon.h"


namespace windowing_xcb
{


   class CLASS_DECL_WINDOWING_XCB icon :
      virtual public ::windowing::icon
   {
   public:


      string m_strTrayIconName;

      array<concrete<::int_size> > m_sizea;


      icon();

      ~icon() override;


      string get_tray_icon_name() const;


      void set_tray_icon_name(const string & strTrayIconName) override;


      void get_sizes(array<concrete<::int_size> > & a);


      void * get_os_data(const ::int_size & size) const;


      void load_matter(string strPath);

      void load_app_tray_icon(string strPath);

      void load_file(string strPath);


      image_pointer get_image(const concrete<::int_size> & size);


   };



} // namespace windowing



