#ifndef _GUZIS_HPP_
#define _GUZIS_HPP_

#if _MSC_VER > 1000
#pragma once
#endif

/////////////////////////
// For 7-bit text ONLY !!
/////////////////////////

// Or more presize, any out-of-map char should be LoASCII !!

// -----------------------------------------------------------------

// A fast, efficient text compressor that can acheive up to about 33
// percent reduction on most text files. - Lowercase characters are
// compressed 3 per word. Since there are 32 values in 5 bits, the
// program can pack the basic 26-character alphabet plus 6 special
// characters: <space>, comma, period, semicolon, hyphen and quote.

// If a value 00 is detected, next caracter is taken as literal
// representation if the next character has a value in excess of 127
// (0x80); overwise, the value represent a repeated character count
// of the next char.

// Copyright (c) 1993 by Chuck Guzis. All rights reserved
// Dr. Dobb's Journal. #207 November 1993. pp. 117, 118, 144, 145.
// ftp://ftp.drdobbs.com/sourcecode/ddj/1993/9311.zip

class Guzis : public AbstractPack
{
   private:

      BYTE     _pAlphaMap[256]; // One byte per ASCII value
      DWORD    _dwPackedSize;
      DWORD    _dwUnpackedSize;

   public:

               Guzis();
      virtual ~Guzis();
                     
      virtual bool   Pack  (const void* const pSrc,void*& rpDst,DWORD dwSrcSize,DWORD& rdwDstSize);
      virtual bool   Unpack(const void* const pSrc,void*& rpDst,DWORD dwSrcSize,DWORD& rdwDstSize);

      virtual DWORD PackedSize();
      virtual DWORD UnpackedSize();

      virtual DWORD  GetMaxPackedSize (DWORD dwOriginalSize);
      virtual DWORD  GetMaxTempBufSize();

      void  SetMap(const BYTE* const pszMap);      

   private:

      void  _Init();
      int   _DupeCheck(BYTE* byWhat);
};

#endif
