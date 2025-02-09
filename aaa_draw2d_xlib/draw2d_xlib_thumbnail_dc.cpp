#include "framework.h"


/*
/////////////////////////////////////////////////////////////////////////////
// Helper functions

__STATIC long CLASS_DECL_DRAW2D_XLIB _AfxMultMultDivDiv(
   int factor, int num1, int num2,
   int den1, int den2)
{
#ifdef _AFX_PORTABLE
   // make sure that (num1 * num2) does not overflow 31-bits.
   long temp = num1 < 0 ? -num1 : num1;
   for (int nBitsResult = 0; temp != 0; nBitsResult++)
      temp >>= 1;
   temp = num2 < 0 ? -num2 : num2;
   for (; temp != 0; nBitsResult++)
      temp >>= 1;
   if (nBitsResult > 31)
   {
      num1 >>= nBitsResult - 31;
      num2 >>= nBitsResult - 31;
   }

   // make sure that (den1 * den2) does not overflow 31-bits
   temp = den1 < 0 ? -den1 : den1;
   for (nBitsResult = 0; temp != 0; nBitsResult++)
      temp >>= 1;
   temp = den2 < 0 ? -den2 : den2;
   for (; temp != 0; nBitsResult++)
      temp >>= 1;
   if (nBitsResult > 31)
   {
      den1 >>= nBitsResult - 31;
      den2 >>= nBitsResult - 31;
   }

   long numerator = (long)num1 * (long)num2;   // no overflow
   long denominator = (long)den1 * (long)den2; // no overflow
#else
   long long numerator = (long long)num1 * (long long)num2;   // no overflow
   long long denominator = (long long)den1 * (long long)den2; // no overflow
   long long temp;
#endif

   temp = numerator < 0 ? -numerator : numerator;
   int nBitsInNum;
   for (nBitsInNum = 0; temp != 0; nBitsInNum++)
      temp >>= 1;

   temp = factor < 0 ? -factor : factor;
   int nBitsInFactor;
   for (nBitsInFactor = 0; temp != 0; nBitsInFactor++)
      temp >>= 1;

   nBitsInNum += nBitsInFactor;

   //
   // normalizing the denominator to positive results in an easier
   // determination of whether there is overflow
   //
   if (denominator < 0)
   {
      denominator = -denominator;
      numerator = -numerator;
   }

   // get the product of factor * numerator representable in a long/long long
   // while distributing loss of presision across all three numerator terms
   // Adjust denominator as well
   //
   while (nBitsInNum-- > 31)
   {
      numerator >>= 1;
      denominator >>= 1;
      if (nBitsInNum-- <= 31)
         break;
      numerator >>= 1;
      denominator >>= 1;
      if (nBitsInNum-- <= 31)
         break;
      factor >>= 1;
      denominator >>= 1;
   }
   numerator *= factor;

   if (denominator == 0)
      return numerator < 0 ? LONG_MIN : LONG_MAX;

   return (long) ((numerator + denominator/2) / denominator);
}

/////////////////////////////////////////////////////////////////////////////
// Print Thumbnail DC (thumbnail_dc)

thumbnail_dc::thumbnail_dc()
{
   // Initial scale factor and top-left offset
   m_nScaleNum = m_nScaleDen = 1;
   m_sizeTopLeft.cx() = m_sizeTopLeft.cy() = 8;
   m_hFont = m_hPrinterFont = nullptr;
}

void thumbnail_dc::SetOutputDC(HDC hDC)
{
   ASSERT(hDC != nullptr);
   m_nSaveDCIndex = ::SaveDC(hDC); // restore in ReleaseOutputDC()
   ::draw2d::graphics_pointer::SetOutputDC(hDC);

   if (get_handle2() != nullptr)
   {
      MirrorMappingMode(false);

      if (m_hFont)
         ::SelectObject(get_os_data(), m_hFont);
      else
         MirrorFont();
      MirrorAttributes();
   }
}

void thumbnail_dc::ReleaseOutputDC()
{
   ASSERT(get_os_data() != nullptr);
   ::RestoreDC(get_os_data(), m_nSaveDCIndex); // Saved in SetOutputDC()
   ::draw2d::graphics_pointer::ReleaseOutputDC();
}

void thumbnail_dc::SetAttribDC(HDC hDC)
{
   ASSERT(hDC != nullptr);
   ::draw2d::graphics_pointer::SetAttribDC(hDC);

   MirrorMappingMode(true);
   MirrorFont();
   MirrorAttributes();
}

thumbnail_dc::~thumbnail_dc()
{
   ASSERT(get_os_data() == nullptr);      // Should not have a screen DC at this time
   AfxDeleteObject((HGDIOBJ*)&m_hFont);
}

void thumbnail_dc::SetScaleRatio(int nNumerator, int nDenominator)
{
   m_nScaleNum = nNumerator;
   m_nScaleDen = nDenominator;
   if (get_handle2() != nullptr)
   {
      MirrorMappingMode(true);
      MirrorFont();
   }
}

// Implementation support
#ifdef _DEBUG
void thumbnail_dc::assert_ok() const
{
   ::draw2d::graphics_pointer::assert_ok();
}


void thumbnail_dc::dump(dump_context & dumpcontext) const
{
   ::draw2d::graphics_pointer::dump(dumpcontext);

   dumpcontext << "Scale Factor: " << m_nScaleNum << "/" << m_nScaleDen;
   dumpcontext << "\n";
}
#endif

int thumbnail_dc::SaveDC()
{
   ASSERT(get_handle2() != nullptr);
   int nAttribIndex = ::SaveDC(get_handle2());
   if (get_os_data() != nullptr)
   {
      // erase font from object
      ::SelectObject(get_os_data(), GetStockObject(SYSTEM_FONT));
      m_nSaveDCDelta = ::SaveDC(get_os_data()) - nAttribIndex;
      // Select font back in after save
      ::SelectObject(get_os_data(), m_hFont);
   }
   else
   {
      m_nSaveDCDelta = 0x7fff;        // impossibly high value
   }
   return nAttribIndex;
}

int_bool thumbnail_dc::RestoreDC(int nSavedDC)
{
   ASSERT(get_handle2() != nullptr);
   int_bool bSuccess = ::RestoreDC(get_handle2(), nSavedDC);
   if (bSuccess)
   {
      if (m_nSaveDCDelta != 0x7fff)
      {
         ASSERT(get_os_data() != nullptr);      // erased Output DC after save

         if (nSavedDC != -1)
            nSavedDC += m_nSaveDCDelta;
         bSuccess = ::RestoreDC(get_os_data(), nSavedDC);
         MirrorFont();               // mirror the font
      }
      else
      {
         ASSERT(get_os_data() == nullptr);      // Added the Output DC after save
      }
   }
   return bSuccess;
}

void thumbnail_dc::MirrorAttributes()
{
   ASSERT(get_handle2() != nullptr);

   if (get_os_data() != nullptr)
   {
      // extract and re-set Pen and Brush
      HGDIOBJ hTemp = ::SelectObject(get_handle2(), ::GetStockObject(BLACK_PEN));
      ::SelectObject(get_handle2(), hTemp);
      ::SelectObject(get_os_data(), hTemp);
      hTemp = ::SelectObject(get_handle2(), ::GetStockObject(BLACK_BRUSH));
      ::SelectObject(get_handle2(), hTemp);
      ::SelectObject(get_os_data(), hTemp);

      SetROP2(GetROP2());
      SetBkMode(GetBkMode());
      SetTextAlign(GetTextAlign());
      SetPolyFillMode(GetPolyFillMode());
      set_interpolation_mode(GetStretchBltMode());
      SetTextColor(GetNearestColor(GetTextColor()));
      SetBkColor(GetNearestColor(GetBkColor()));
   }
}

object* thumbnail_dc::SelectStockObject(int nIndex)
{
   ASSERT(get_handle2() != nullptr);

   HGDIOBJ hObj = ::GetStockObject(nIndex);

   switch (nIndex)
   {
   case ANSI_FIXED_FONT:
   case ANSI_VAR_FONT:
   case DEVICE_DEFAULT_FONT:
   case OEM_FIXED_FONT:
   case SYSTEM_FONT:
   case SYSTEM_FIXED_FONT:
   case DEFAULT_GUI_FONT:
      // Handle the stock fonts correctly
      {
         object* pObject = ::draw2d_xlib::object::from_handle(
                     ::SelectObject(get_handle2(), hObj));

         // Don't re-mirror screen font if this is the same font.
         if (m_hPrinterFont == (HFONT) hObj)
            return pObject;

         m_hPrinterFont = (HFONT) hObj;

         ASSERT(m_hPrinterFont != nullptr); // Do not allow infinite recursion

         MirrorFont();
         return pObject;
      }

   default:
      if (get_os_data() != nullptr)
         ::SelectObject(get_os_data(), hObj);
      return ::draw2d_xlib::object::from_handle(::SelectObject(get_handle2(), hObj));
   }
}

void thumbnail_dc::MirrorFont()
{
   if (get_handle2() == nullptr)
      return;         // can't do anything without Attrib DC

   if (m_hPrinterFont == nullptr)
   {
      SelectStockObject(DEVICE_DEFAULT_FONT); // will recurse
      return;
   }

   if (get_os_data() == nullptr)
      return;         // can't mirror font without a screen DC

   LOGFONTW logFont;
   // Fill the logFont structure with the original info
   ::GetObject(m_hPrinterFont, sizeof(LOGFONTW), (LPVOID)&logFont);

   TEXTMETRICW tm;

   GetTextFace(LF_FACESIZE, (char *)&logFont.lfFaceName[0]);
   GetTextMetrics(&tm);

   // Set real values based on the Printer's text metrics.

   if (tm.tmHeight < 0)
      logFont.lfHeight = tm.tmHeight;
   else
      logFont.lfHeight = -(tm.tmHeight - tm.tmInternalLeading);

   logFont.lfWidth = tm.tmAveCharWidth;
   logFont.lfWeight = tm.tmWeight;
   logFont.lfItalic = tm.tmItalic;
   logFont.lfUnderline = tm.tmUnderlined;
   logFont.lfStrikeOut = tm.tmStruckOut;
   logFont.lfCharSet = tm.tmCharSet;
   logFont.lfPitchAndFamily = tm.tmPitchAndFamily;

   HFONT hNewFont = ::CreateFontIndirect(&logFont);
   ::SelectObject(get_os_data(), hNewFont);

   ::GetTextMetrics(get_os_data(), &tm);

   // Is the displayed font too large?

   int cyDesired = -logFont.lfHeight;
   int cyActual;
   if (tm.tmHeight < 0)
      cyActual = -tm.tmHeight;
   else
      cyActual = tm.tmHeight - tm.tmInternalLeading;

   int_size sizeWinExt;
   VERIFY(::GetWindowExtEx(get_os_data(), &sizeWinExt));
   int_size sizeVpExt;
   VERIFY(::Get_wiewportExtEx(get_os_data(), &sizeVpExt));

   // Only interested in Extent Magnitudes, not direction
   if (sizeWinExt.cy() < 0)
      sizeWinExt.cy() = -sizeWinExt.cy();
   if (sizeVpExt.cy() < 0)
      sizeVpExt.cy() = -sizeVpExt.cy();

   // Convert to screen device coordinates to eliminate rounding
   // errors as a source of SmallFont aliasing

   cyDesired = MulDiv(cyDesired, sizeVpExt.cy(), sizeWinExt.cy());
   cyActual = MulDiv(cyActual, sizeVpExt.cy(), sizeWinExt.cy());

   ASSERT(cyDesired >= 0 && cyActual >= 0);

   if (cyDesired < cyActual)
   {
      logFont.lfFaceName[0] = 0;      // let the mapper find a good fit

      if ((logFont.lfPitchAndFamily & 0xf0) == FF_DECORATIVE)
         logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DECORATIVE;
      else
         logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTcaRE;

      HFONT hTempFont = ::CreateFontIndirect(&logFont);
      ::SelectObject(get_os_data(), hTempFont);           // Select it in.
      ::DeleteObject(hNewFont);
      hNewFont = hTempFont;
   }

   AfxDeleteObject((HGDIOBJ*)&m_hFont);  // delete the old logical font
   m_hFont = hNewFont;         // save the memory_new one
}

::write_text::font* thumbnail_dc::SelectObject(::write_text::font* pFont)
{
   if (pFont == nullptr)
      return nullptr;

   ASSERT(get_handle2() != nullptr);
   ASSERT_VALID(pFont);

   ::write_text::font* pOldFont = (::write_text::font*) ::draw2d_xlib::object::from_handle(
            ::SelectObject(get_handle2(), pFont->get_handle()));

   // If same as already selected, don't re-mirror screen font
   if (m_hPrinterFont != pFont->get_handle())
   {
      m_hPrinterFont = (HFONT)pFont->get_handle();
      MirrorFont();
   }

   return pOldFont;
}

/////////////////////////////////////////////////////////////////////////////
// Drawing-Attribute Functions

color32_t thumbnail_dc::SetBkColor(color32_t crColor)
{
   ASSERT(get_handle2() != nullptr);
   if (get_os_data() != nullptr)
      ::SetBkColor(get_os_data(), ::GetNearestColor(get_handle2(), crColor));
   return ::SetBkColor(get_handle2(), crColor);
}

color32_t thumbnail_dc::SetTextColor(color32_t crColor)
{
   ASSERT(get_handle2() != nullptr);
   if (get_os_data() != nullptr)
      ::SetTextColor(get_os_data(), ::GetNearestColor(get_handle2(), crColor));
   return ::SetTextColor(get_handle2(), crColor);
}

int thumbnail_dc::SetMapMode(int nMapMode)
{
   ASSERT(get_handle2() != nullptr);
   int nModeOld = ::SetMapMode(get_handle2(), nMapMode);
   MirrorMappingMode(true);
   return nModeOld;
}

int_point thumbnail_dc::set_origin(int x, int y)
{
   ASSERT(get_handle2() != nullptr);
   int_point ptOrgOld;
   VERIFY(::SetContextOrgEx(get_handle2(), x, y, &ptOrgOld));
   MirrorContextOrg();
   return ptOrgOld;
}

int_point thumbnail_dc::offset_origin(int nWidth, int nHeight)
{
   ASSERT(get_handle2() != nullptr);
   int_point ptOrgOld;
   VERIFY(::OffsetContextOrgEx(get_handle2(), nWidth, nHeight, &ptOrgOld));
   MirrorContextOrg();
   return ptOrgOld;
}

int_size thumbnail_dc::set_context_extents(int x, int y)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::Set_wiewportExtEx(get_handle2(), x, y, &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

int_size thumbnail_dc::scale_context_extents(int xNum, int xDenom, int yNum, int yDenom)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::scale_context_extentsEx(get_handle2(), xNum, xDenom,
      yNum, yDenom, &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

int_size thumbnail_dc::set_window_ext(int x, int y)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::SetWindowExtEx(get_handle2(), x, y, &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

int_size thumbnail_dc::scale_window_ext(int xNum, int xDenom, int yNum, int yDenom)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom,
      &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

/////////////////////////////////////////////////////////////////////////////
// Text Functions

// private helpers for text_out functions

__STATIC int CLASS_DECL_DRAW2D_XLIB _AfxComputeNextTab(int x, unsigned int nTabStops, LPINT lpnTabStops, int nTabOrigin, int nTabWidth)
{
   ENSURE(nTabWidth!=0);
   x -= nTabOrigin;        // normalize position to tab origin
   for (unsigned int i = 0; i < nTabStops; i++, lpnTabStops++)
   {
      if (*lpnTabStops > x)
        {
         return *lpnTabStops + nTabOrigin;
        }
   }
   return (x / nTabWidth + 1) * nTabWidth + nTabOrigin;
}

// Compute a character delta table for correctly positioning the screen
// font characters where the printer characters will appear on the page
int_size thumbnail_dc::ComputeDeltas(int& x, const char * lpszString, unsigned int &nCount,
   int_bool bTabbed, unsigned int nTabStops, LPINT lpnTabStops, int nTabOrigin,
   __out_z char * lpszOutputString, int* pnDxWidths, int& nRightFixup)
{
   ASSERT_VALID(this);

   TEXTMETRICW tmAttrib;
   TEXTMETRICW tmScreen;
   ::GetTextMetrics(get_handle2(), &tmAttrib);
   ::GetTextMetrics(get_os_data(), &tmScreen);

   int_size sizeExtent;
   ::GetTextExtentPoint32A(get_handle2(), "A", 1, &sizeExtent);

   int_point ptCurrent;
   unsigned int nAlignment = ::GetTextAlign(get_handle2());
   int_bool bUpdateCP = (nAlignment & TA_UPDATECP) != 0;
   if (bUpdateCP)
   {
      ::GetCurrentPositionEx(get_os_data(), &ptCurrent);
      x = ptCurrent.x;
   }

   const char * lpszCurChar = lpszString;
   const char * lpszStartRun = lpszString;
   int* pnCurDelta = pnDxWidths;
   int nStartRunPos = x;
   int nCurrentPos = x;
   int nStartOffset = 0;

   int nTabWidth = 0;
   if (bTabbed)
   {
      if (nTabStops == 1)
      {
         nTabWidth = lpnTabStops[0];
      }
      else
      {
         // get default int_size of a tab
         nTabWidth = LOWORD(::GetTabbedTextExtentA(get_handle2(),
            "\t", 1, 0, nullptr));
      }
   }

   for (unsigned int i = 0; i < nCount; i++)
   {
      int_bool bSpace = ((_TUCHAR)*lpszCurChar == (_TUCHAR)tmAttrib.tmBreakChar);
      if (bSpace || (bTabbed && *lpszCurChar == '\t'))
      {
         // bSpace will be either true (==1) or false (==0).  For spaces
         // we want the space included in the get_text_extent, for tabs we
         // do not want the tab included
         int nRunLength = (int)(lpszCurChar - lpszStartRun) + bSpace;

         int_size sizeExtent;
         ::GetTextExtentPoint32(get_handle2(), lpszStartRun, nRunLength,
            &sizeExtent);
         int nNewPos = nStartRunPos + sizeExtent.cx()
            - tmAttrib.tmOverhang;

         // now, if this is a Tab (!bSpace), compute the next tab stop
         if (!bSpace)
         {
            nNewPos = _AfxComputeNextTab(nNewPos, nTabStops, lpnTabStops,
                        nTabOrigin, nTabWidth);
         }

         // add this width to previous width
         if (pnCurDelta == pnDxWidths)
            nStartOffset += nNewPos - nCurrentPos;
         else
            *(pnCurDelta-1) += nNewPos - nCurrentPos;

         nCurrentPos = nNewPos;

         nStartRunPos = nCurrentPos;     // set start of run
         // *lpszCurChar must be SBC: tmBreakChar or '\t'
         lpszStartRun = lpszCurChar + 1;
      }
      else
      {
         // For the non-tabbed or non-tab-character case
         int cxScreen;
         if (_istlead(*lpszCurChar))
         {
            cxScreen = tmScreen.tmAveCharWidth;
            *pnCurDelta = tmAttrib.tmAveCharWidth;
         }
         else
         {
            ::GetCharWidth(get_os_data(), (_TUCHAR)*lpszCurChar,
               (_TUCHAR)*lpszCurChar, &cxScreen);
            if (!::GetCharWidth(get_handle2(), (_TUCHAR)*lpszCurChar,
               (_TUCHAR)*lpszCurChar, pnCurDelta))
            {
               // If printer driver fails the above call, use the average width
               *pnCurDelta = tmAttrib.tmAveCharWidth;
            }
         }
         *pnCurDelta -= tmAttrib.tmOverhang;
         cxScreen -= tmScreen.tmOverhang;
         nCurrentPos += *pnCurDelta;     // update current position

         // Center character in allotted space
         if (pnCurDelta != pnDxWidths)
         {
            int diff = (*pnCurDelta - cxScreen) / 2;
            *pnCurDelta -= diff;
            *(pnCurDelta - 1) += diff;
         }
         *lpszOutputString++ = *lpszCurChar;
         if (_istlead(*lpszCurChar))
         {
            *lpszOutputString++ = *(lpszCurChar+1); // copy trailing unsigned char
            *(pnCurDelta + 1) = *pnCurDelta;        // double wide
            nCurrentPos += *pnCurDelta;
            pnCurDelta++;
            i++;
         }
         pnCurDelta++;
      }
      lpszCurChar = _tcsinc(lpszCurChar);
   }

   nAlignment &= TA_CENTER|TA_RIGHT;
   sizeExtent.cx() = nCurrentPos - x;
   nRightFixup = 0;

   if (nAlignment == TA_LEFT)
      x += nStartOffset;      // Full left side adjustment
   else if (nAlignment == TA_CENTER)
      x += nStartOffset/2;    // Adjust Center by 1/2 left side adjustment
   else if (nAlignment == TA_RIGHT)
      nRightFixup = nStartOffset; // Right adjust needed later if TA_UPDATECP

   if (bUpdateCP)
      ::MoveToEx(get_os_data(), x, ptCurrent.y, nullptr);

   nCount = (unsigned int)(pnCurDelta - pnDxWidths);   // number of characters output
   return sizeExtent;
}

int_bool thumbnail_dc::text_out(int x, int y, const char * lpszString, int nCount)
{
   return ExtTextOut(x, y, 0, nullptr, lpszString, nCount, nullptr);
}

int_bool thumbnail_dc::ExtTextOut(int x, int y, unsigned int nOptions, const ::int_rectangle & rectangle,
   const char * lpszString, unsigned int nCount, LPINT lpDxWidths)
{
   ASSERT(get_os_data() != nullptr);
   ASSERT(get_handle2() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(lpDxWidths == nullptr ||
         fx_is_valid_address(lpDxWidths, sizeof(int) * nCount, false));
   ASSERT(fx_is_valid_address(lpszString, nCount, false));

   int* pDeltas = nullptr;
   char * pOutputString = nullptr;
   int nRightFixup = 0;

   if (lpDxWidths == nullptr)
   {
      if (nCount == 0)    // Do nothing
         return true;

      try
      {
         pDeltas = memory_new int[nCount];
         pOutputString = memory_new char[nCount];
      }
      catch(const ::exception & e)
      {
         delete[] pDeltas;  // in case it was allocated
         // Note: DELETE_EXCEPTION(e) not required
         return false;   // Could not allocate buffer, cannot display
      }


      ComputeDeltas(x, (char *)lpszString, nCount, false, 0, nullptr, 0,
                              pOutputString, pDeltas, nRightFixup);

      lpDxWidths = pDeltas;
      lpszString = pOutputString;
   }

   int_bool bSuccess = ::ExtTextOut(get_os_data(), x, y, nOptions, rectangle, lpszString,
                                          nCount, lpDxWidths);
   if (nRightFixup != 0 && bSuccess && (GetTextAlign() & TA_UPDATECP))
   {
      ::int_point point;
      ::GetCurrentPositionEx(get_os_data(), &point);
      MoveTo(point.x - nRightFixup, point.y);
   }
   delete[] pDeltas;
   delete[] pOutputString;

   return bSuccess;
}

int_size thumbnail_dc::TabbedTextOut(int x, int y, const char * lpszString, int nCount,
   int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(fx_is_valid_address(lpszString, nCount, false));
   ASSERT(lpnTabStopPositions == nullptr ||
         fx_is_valid_address(lpnTabStopPositions, sizeof(int) * nTabPositions,
            false));

   if (nCount <= 0)
      return (unsigned int) 0;         // nCount is zero, there is nothing to print

   int* pDeltas = nullptr;
   char * pOutputString = nullptr;
   int nRightFixup;

   try
   {
      pDeltas = memory_new int[nCount];
      pOutputString = memory_new char[nCount];
   }
   catch(const ::exception & e)
   {
      delete[] pDeltas;
      // Note: DELETE_EXCEPTION(e) not required
      return (unsigned int) 0;           // signify error
   }


   unsigned int uCount = nCount;
   int_size sizeFinalExtent = ComputeDeltas(x, lpszString, uCount, true,
                     nTabPositions, lpnTabStopPositions, nTabOrigin,
                     pOutputString, pDeltas, nRightFixup);

   int_bool bSuccess = ExtTextOut(x, y, 0, nullptr, pOutputString, uCount, pDeltas);

   delete[] pDeltas;
   delete[] pOutputString;

   if (bSuccess && (GetTextAlign() & TA_UPDATECP))
   {
      ::int_point point;
      ::GetCurrentPositionEx(get_os_data(), &point);
      MoveTo(point.x - nRightFixup, point.y);
   }

   return sizeFinalExtent;
}

// This one is too complicated to do character-by-character output positioning
// All we really need to do here is mirror the current position
int thumbnail_dc::DrawText(const char * lpszString, int nCount, INT_RECTANGLE * prectangle,
   unsigned int nFormat)
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(rectangle != nullptr);
   ASSERT(fx_is_valid_address(rectangle, sizeof(INT_RECTANGLE)));
   ASSERT(nCount == -1 ?
      AfxIsValidString(lpszString) :
      fx_is_valid_address(lpszString, nCount, false));

   int retVal = ::DrawText(get_os_data(), lpszString, nCount, rectangle, nFormat);

   int_point pos;
   ::GetCurrentPositionEx(get_os_data(), &pos);
   ::MoveToEx(get_handle2(), pos.x, pos.y, nullptr);
   return retVal;
}

int thumbnail_dc::DrawTextEx(__in_ecount(nCount) char * lpszString, int nCount, INT_RECTANGLE * prectangle,
   unsigned int nFormat, LPDRAWTEXTPARAMS lpDTParams)
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(rectangle != nullptr);
   ASSERT(fx_is_valid_address(rectangle, sizeof(INT_RECTANGLE)));
   ASSERT(nCount == -1 ?
      AfxIsValidString(lpszString) :
      fx_is_valid_address(lpszString, nCount, false));

   int retVal = ::DrawTextEx(get_os_data(), lpszString, nCount, rectangle, nFormat, lpDTParams);

   int_point pos;
   ::GetCurrentPositionEx(get_os_data(), &pos);
   ::MoveToEx(get_handle2(), pos.x, pos.y, nullptr);
   return retVal;
}

int_bool thumbnail_dc::GrayString(::draw2d::brush*,
            int_bool (CALLBACK *)(HDC, LPARAM, int),
               LPARAM lpData, int nCount, int x, int y, int, int)
{
   information(::aura::trace::category_AppMsg, 0, "text_out() substituted for GrayString() in Print Thumbnail.\n");
   return text_out(x, y, (const char *)lpData, nCount);
}

int thumbnail_dc::Escape(int nEscape, int nCount, const char * lpszInData, void * lpOutData)
{
   // The tact here is to NOT allow any of the document control escapes
   // to be passed through.  Elimination of StartDoc and EndDoc should
   // eliminate anything actually going to the printer.  Also anything
   // that actually draws something will be filtered.

   ASSERT(get_handle2() != nullptr);

   switch (nEscape)
   {
   case NEXTBAND:
   case SETCOLORTABLE:
   case GETCOLORTABLE:
   case FLUSHOUTPUT:
   case DRAFTMODE:
   case QUERYESCSUPPORT:
   case GETPHYSPAGESIZE:
   case GETPRINTINGOFFSET:
   case GETScaLINGFACTOR:
   case GETPENWIDTH:
   case SETCOPYCOUNT:
   case SELECTPAPERSOURCE:
   case GETTECHNOLOGY:
   case SETLINEcaP:
   case SETLINEJOIN:
   case SETMITERLIMIT:
   case BANDINFO:
   case GETVECTORPENSIZE:
   case GETVECTORBRUSHSIZE:
   case ENABLEDUPLEX:
   case GETSETPAPERBINS:
   case GETSETPRINTORIENT:
   case ENUMPAPERBINS:
   case SETDIBScaLING:
   case ENUMPAPERMETRICS:
   case GETSETPAPERMETRICS:
   case GETEXTENDEDTEXTMETRICWS:
   case GETEXTENTTABLE:
   case GETPAIRKERNTABLE:
   case GETTRACKKERNTABLE:
   case ENABLERELATIVEWIDTHS:
   case ENABLEPAIRKERNING:
   case SETKERNTRACK:
   case SETALLJUSTVALUES:
   case SETCHARSET:
   case SET_BACKGROUND_COLOR:
   case SET_SCREEN_ANGLE:
   case SET_SPREAD:
      return ::Escape(get_handle2(), nEscape, nCount, lpszInData, lpOutData);

   default:
      return 0;
   }
}

void thumbnail_dc::MirrorMappingMode(int_bool bCompute)
{
   ASSERT(get_handle2() != nullptr);
   if (bCompute)
   {
      //
      // The following formula is used to compute the screen's viewport extent
      // From the printer and screen information and the Printer's Context
      // Extents.  (Note:  This formula is used twice, once for horizontal
      // and once for vertical)
      //
      // It is assumed that the Window Extents are maintained as equal.
      //
      //                  m * LogPixPerInch(Screen) * VpExt(Printer)
      // VpExt(Screen) = -------------------------------------------------
      //                          n * LogPixPerInch(Printer)
      //
      // Where m/n is the scaling factor.  (m/n > 1 is expansion)
      //

      VERIFY(::Get_wiewportExtEx(get_handle2(), &m_sizeVpExt));
      VERIFY(::GetWindowExtEx(get_handle2(), &m_sizeWinExt));

      while (m_sizeWinExt.cx() > -0x4000 && m_sizeWinExt.cx() < 0x4000 &&
            m_sizeVpExt.cx()  > -0x4000 && m_sizeVpExt.cx()  < 0x4000)
      {
         m_sizeWinExt.cx() <<= 1;
         m_sizeVpExt.cx()  <<= 1;
      }

      while (m_sizeWinExt.cy() > -0x4000 && m_sizeWinExt.cy() < 0x4000 &&
            m_sizeVpExt.cy()  > -0x4000 && m_sizeVpExt.cy()  < 0x4000)
      {
         m_sizeWinExt.cy() <<= 1;
         m_sizeVpExt.cy()  <<= 1;
      }

      long lTempExt = _AfxMultMultDivDiv(m_sizeVpExt.cx(),
         m_nScaleNum, afxData.cxPixelsPerInch,
         m_nScaleDen, ::GetDevicecaps(get_handle2(), LOGPIXELSX));

      ASSERT(m_sizeWinExt.cx() != 0);
      m_sizeVpExt.cx() = (int)lTempExt;

      lTempExt = _AfxMultMultDivDiv(m_sizeVpExt.cy(),
         m_nScaleNum, afxData.cyPixelsPerInch,
         m_nScaleDen, ::GetDevicecaps(get_handle2(), LOGPIXELSY));

      ASSERT(m_sizeWinExt.cy() != 0);
      m_sizeVpExt.cy() = (int)lTempExt;
   }

   if (get_os_data() != nullptr)
   {
      ::SetMapMode(get_os_data(), MM_ANISOTROPIC);
      ::SetWindowExtEx(get_os_data(), m_sizeWinExt.cx(), m_sizeWinExt.cy(), nullptr);
      ::Set_wiewportExtEx(get_os_data(), m_sizeVpExt.cx(), m_sizeVpExt.cy(), nullptr);

      // Now that the Logical Units are synchronized, we can set the Context Org
      MirrorContextOrg();
   }
}

void thumbnail_dc::MirrorContextOrg()
{
   if (get_handle2() == nullptr || get_os_data() == nullptr)
      return;

   int_point ptVpOrg;
   VERIFY(::GetContextOrgEx(get_handle2(), &ptVpOrg));
   PrinterDPtoScreenDP(&ptVpOrg);
   ptVpOrg += m_sizeTopLeft;
   ::SetContextOrgEx(get_os_data(), ptVpOrg.x, ptVpOrg.y, nullptr);

   int_point ptWinOrg;
   VERIFY(::GetWindowOrgEx(get_handle2(), &ptWinOrg));
   ::SetWindowOrgEx(get_os_data(), ptWinOrg.x, ptWinOrg.y, nullptr);
}

void thumbnail_dc::SetTopLeftOffset(const ::int_size & sizeTopLeft)
{
   ASSERT(get_handle2() != nullptr);
   m_sizeTopLeft = sizeTopLeft;
   MirrorContextOrg();
}

void thumbnail_dc::ClipToPage()
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   // create a int_rectangle in Screen Device coordinates that is one pixel larger
   // on all sides than the actual page.  This is to hide the fact that
   // the printer to screen mapping mode is approximate and may result
   // in rounding error.

   ::int_point point(::GetDevicecaps(get_handle2(), HORZRES),
            ::GetDevicecaps(get_handle2(), VERTRES));
   PrinterDPtoScreenDP(&point);

   // Set the screen dumpcontext <<to MM_TEXT and no WindowOrg for the interesection

   ::SetMapMode(get_os_data(), MM_TEXT);
   ::SetWindowOrgEx(get_os_data(), 0, 0, nullptr);
   ::SetContextOrgEx(get_os_data(), m_sizeTopLeft.cx(), m_sizeTopLeft.cy(), nullptr);
   ::IntersectClipRect(get_os_data(), -1, -1, point.x + 2, point.y + 2);

   // Resynchronize the mapping mode
   MirrorMappingMode(false);
}

// these conversion functions can be used without an attached screen DC

void thumbnail_dc::PrinterDPtoScreenDP(INT_POINT * lpPoint) const
{
   ASSERT(get_handle2() != nullptr);

   int_size sizePrinterVpExt;
   VERIFY(::Get_wiewportExtEx(get_handle2(), &sizePrinterVpExt));
   int_size sizePrinterWinExt;
   VERIFY(::GetWindowExtEx(get_handle2(), &sizePrinterWinExt));

   long xScreen = _AfxMultMultDivDiv(lpPoint->x,
      sizePrinterWinExt.cx(), m_sizeVpExt.cx(),
      sizePrinterVpExt.cx(), m_sizeWinExt.cx());

   lpPoint->x = (int)xScreen;

   long yScreen = _AfxMultMultDivDiv(lpPoint->y,
      sizePrinterWinExt.cy(), m_sizeVpExt.cy(),
      sizePrinterVpExt.cy(), m_sizeWinExt.cy());

   lpPoint->y = (int)yScreen;
}

////////////////////////////////////////////////////////////////////////////
// AfxCreateDC

HDC CLASS_DECL_DRAW2D_XLIB AfxCreateDC(HGLOBAL hDevNames, HGLOBAL hDevMode)
{
   if (hDevNames == nullptr)
      return nullptr;

   LPDEVNAMES lpDevNames = (LPDEVNAMES)::GlobalLock(hDevNames);
   LPDEVMODE  lpDevMode = (hDevMode != nullptr) ?
                  (LPDEVMODE)::GlobalLock(hDevMode) : nullptr;

   if (lpDevNames == nullptr)
      return nullptr;

   HDC hDC = ::CreateDC((const char *)lpDevNames + lpDevNames->wDriverOffset,
                 (const char *)lpDevNames + lpDevNames->wDeviceOffset,
                 (const char *)lpDevNames + lpDevNames->wOutputOffset,
                 lpDevMode);

   ::GlobalUnlock(hDevNames);
   if (hDevMode != nullptr)
      ::GlobalUnlock(hDevMode);
   return hDC;
}


// IMPLEMENT_DYNAMIC(thumbnail_dc, ::draw2d::graphics_pointer)

/////////////////////////////////////////////////////////////////////////////
*/
