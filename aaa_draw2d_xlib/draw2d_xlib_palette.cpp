#include "framework.h"


namespace draw2d_xlib
{


   palette::palette(::particle * pparticle) :
      ::object(pparticle)
   {

   }


   palette::~palette()
   {

   }


   /*   // palette
      palette::operator HPALETTE() const
      {

         //return (HPALETTE)(this == nullptr ? nullptr : get_os_data());

         return nullptr;

      }

   */
   /*

      palette* PASCAL palette::from_handle(::particle * pparticle, HPALETTE hPalette)
      {

         //return dynamic_cast < palette * > (::win::object::from_handle(papp, hPalette));

         return nullptr;

      }

   */


   /*

      int_bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
      {

      //   return Attach(::CreatePalette(lpLogPalette));

         return false;

      }

   */



   /*

      int_bool palette::CreateHalftonePalette(::image * pimage)
      {

         //ASSERT(pgraphics != nullptr && (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() != nullptr);
         //return Attach(::CreateHalftonePalette((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1()));

         return false;

      }

   */


   /*   unsigned int palette::GetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY lpPaletteColors) const
      {

         //ASSERT(get_os_data() != nullptr);
         //return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

         return 0;

      }


      unsigned int palette::SetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY lpPaletteColors)
      {

         //ASSERT(get_os_data() != nullptr);
         //return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

         return 0;

      }


      void palette::AnimatePalette(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY lpPaletteColors)
      {

         //ASSERT(get_os_data() != nullptr);

         //::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

      }


      unsigned int palette::GetNearestPaletteIndex(color32_t crColor) const
      {

         //ASSERT(get_os_data() != nullptr);

         //return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor);

         return 0;

      }*/


   /*

      int_bool palette::ResizePalette(unsigned int nNumEntries)
      {

         //ASSERT(get_os_data() != nullptr);

         //return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries);

         return false;

      }

   */

   /*
      int palette::GetEntryCount()
      {

         //ASSERT(get_os_data() != nullptr);

         //unsigned short nEntries;

         //::GetObject(get_os_data(), sizeof(unsigned short), &nEntries); return (int)nEntries;

         return 0;

      }
   */

} // namespace mac







