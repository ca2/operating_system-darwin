#pragma once


namespace draw2d_xlib
{

   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_DRAW2D_XLIB image :
      virtual public image
   {
   public:




      BITMAPINFO              m_info;
      ::draw2d::bitmap_pointer     m_pbitmap;
      ::draw2d::graphics_pointer   m_spgraphics;
      bool                    m_bMapped;
      //HBITMAP               m_hbitmapOriginal;
      HBITMAP                 m_hbitmap;
      class size_i64            m_sizeWnd;
      BITMAPINFO              m_bitmapinfo;
      XImage *                m_pimage;






      image(::particle * pparticle);
      virtual void construct(int cx, int cy);
      virtual ~image();


      void map(bool bApplyAlphaTransform = true);
      void unmap();


      virtual ::draw2d::graphics * get_graphics();
      virtual ::draw2d::bitmap_pointer get_bitmap();
      virtual ::draw2d::bitmap_pointer detach_bitmap();


      virtual color32_t * get_data();

      void stretch_image(::image::image * pimage);

      bool dc_select(bool bSelect = true);




      using object::create;
      bool create(::size_i32 size);
      bool create(int iWidth, int iHeight);
      bool create(::image::image * pimage);
      bool Destroy();


      using image::from;
      bool from(::image::image * pimage);
      bool from(point_i32 ptDest, ::draw2d::graphics * pgraphics, const ::point_i32 & point, ::size_i32 sz);

      using image::to;
      bool to(::draw2d::graphics * pgraphics, const ::point_i32 & point, ::size_i32 size, point_i32 ptSrc);

      virtual bool update_window(::window * puserinteraction, ::message::message * pmessage);
      virtual bool print_window(::window * puserinteraction, ::message::message * pmessage);

      void SetIconMask(::draw2d::icon * picon, int cx, int cy);


      //bool color_blend(color32_t cr, unsigned char bAlpha);
      //bool Blend(imagepimage, ::image::image * pimageA, int A);
      //void BitBlt(::image::image * pimage, int op);
      //color32_t GetAverageColor();
      //int cos(int i, int iAngle);
      //int sin(int i, int iAngle);
      //int cos10(int i, int iAngle);
      //int sin10(int i, int iAngle);

      //bool is_rgb_black();
      //void xor(::image::image * pimage);

      //void ToAlpha(int i);
      //void ToAlphaAndFill(int i, color32_t cr);
      //void GrayToARGB(color32_t cr);

      //void from_alpha();
      //void mult_alpha(::image::image * pimageWork, bool bPreserveAlpha = true);
      //void set_rgb(int R, int G, int B);

      //void rotate(::image::image * pimage, const ::rectangle_i32 & rectangle, double dAngle, double dScale);
      //void rotate(::image::image * pimage, double dAngle, double dScale);
      //void Rotate034(::image::image * pimage, double dAngle, double dScale);
      //void RadialFill(unsigned char a, unsigned char rectangle, unsigned char g, unsigned char b, int x, int y, int iRadius);
      //void RadialFill(
      //   unsigned char a1, unsigned char r1, unsigned char g1, unsigned char b1, // center colors
      //   unsigned char a2, unsigned char r2, unsigned char g2, unsigned char b2, // border colors
      //   int x, int y, int iRadius);

      //u32 GetPixel(int x, int y);
      //void Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask);
      //void ::color::e_channel_mask(unsigned char uchFind, unsigned char uchSet, unsigned char uchUnset, color::color::color::rgba::echannel echannel);
      //void transparent_color(::color::color color);
      //void DivideRGB(int iDivide);
      //void DivideARGB(int iDivide);
      //void DivideA(int iDivide);
      //virtual void fill_channel(int C, color::color::color::rgba::echannel echannel);
      //void Fill (int A, int R, int G, int B );
      //void Fill ( int R, int G, int B );
      //void FillGlass ( int R, int G, int B, int A );
      //void FillStippledGlass ( int R, int G, int B );
      //void Invert();
      //void ::color::e_channel_invert(color::color::color::rgba::echannel echannel);
      //void ::color::e_channel_multiply(color::color::color::rgba::echannel echannel, double dRate);

      //void Map (int ToRgb, int FromRgb );

      /*void copy( imageimage );
      void Paste ( imageimage );

      void Blend ( imageimage, int A );
      void Darken ( imageimage );
      void Difference ( imageimage );
      void Lighten ( imageimage );
      void Multiply ( imageimage );
      void Screen ( imageimage );

      void copy ( imageimage, int x, int y );
      void PasteRect ( imageimage, int x, int y );

      void FillRect ( int x, int y, int w, int h, int R, int G, int B );
      void FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A );
      void FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B );

      void BlendRect ( imageimage, int x, int y, int A );
      void DarkenRect ( imageimage, int x, int y );
      void DifferenceRect ( imageimage, int x, int y );
      void LightenRect ( imageimage, int x, int y );
      void MultiplyRect ( imageimage, int x, int y );
      void ScreenRect ( imageimage, int x, int y );

      void Line ( int x1, int y1, int x2, int y2, int R, int G, int B );
      void LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A );*/

      //void create_frame(::size_i32 size, int iFrameCount);
      //void set_frame2(void * lpdata, int iFrame, int iFrameCount);
      //void set_frame1(void * lpdata, int iFrame, int iFrameCount);
      //void get_frame(void * lpdata, int iFrame, int iFrameCount);
      //void xor_image_frame2(void * lpdata, int iFrame, int iFrameCount);


      //double pi();


      virtual void read(stream & istream);


   };


} // namespace draw2d_xlib



