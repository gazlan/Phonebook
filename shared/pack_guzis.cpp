#include "stdafx.h"

#include "pack_abstract.h"
#include "pack_guzis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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

#define DUPE_THRESHOLD        (4) // Smallest duplicated byte count

// Our 5-bit alphabet.
static BYTE    pAlphabet[33] = "abcdefghijklmnopqrstuvwxyz ,.;-\"";

/* ******************************************************************** **
** @@ Guzis::Guzis()
** @  Copyrt : 
** @  Author : Chuck Guzis, 1993
** @  Modify :
** @  Update :
** @  Notes  : Dr. Dobb's Journal. #207 November 1993. pp. 117, 118, 144, 145.
** @  Notes  : Constructor
** ******************************************************************** */

Guzis::Guzis()
{
   _Init();
}

/* ******************************************************************** **
** @@ Guzis::~Guzis()
** @  Copyrt : 
** @  Author : Chuck Guzis, 1993
** @  Modify :
** @  Update :
** @  Notes  : Dr. Dobb's Journal. #207 November 1993. pp. 117, 118, 144, 145.
** @  Notes  : Destructor
** ******************************************************************** */

Guzis::~Guzis()
{
}

/* ******************************************************************** **
** @@ Guzis::SetMap()
** @  Copyrt : 
** @  Author :
** @  Modify : 
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void Guzis::SetMap(const BYTE* const pszMap)
{
   if (IsBadReadPtr(pszMap,32))
   {
      return;
   }

   memcpy(pAlphabet,pszMap,32); 
   
   _Init();
}      

/* ******************************************************************** **
** @@ Guzis::_DupeCheck()
** @  Copyrt : 
** @  Author : Chuck Guzis, 1993
** @  Modify :
** @  Update :
** @  Notes  : Dr. Dobb's Journal. #207 November 1993. pp. 117, 118, 144, 145.
** @  Notes  : DupeCheck - Return the number of duplicated characters.
** @  Notes  : Always returns at least 1.
** ******************************************************************** */

int Guzis::_DupeCheck(BYTE* byWhat)
{
   BYTE     byRefChar = *byWhat++;  // Reference character

   for (int kk = 1; *byWhat; ++kk)
   {
      if (byRefChar != *byWhat++)
      {
         break;
      }
   }

   return kk;
}

/* ******************************************************************** **
** @@ Guzis::_Init()
** @  Copyrt : 
** @  Author : Chuck Guzis, 1993
** @  Modify :
** @  Update :
** @  Notes  : Dr. Dobb's Journal. #207 November 1993. pp. 117, 118, 144, 145.
** @  Notes  : Construct the AlphaMap array. This is done purely for speed, as
** @  Notes  : the memchr() function could be used to search the string.
** ******************************************************************** */

void Guzis::_Init()
{
   memset(_pAlphaMap,0,sizeof(_pAlphaMap)); // Clear it to 0

   BYTE*    pChr = pAlphabet;

   for (int ii = 1; *pChr; ++ii)
   {
      _pAlphaMap[*pChr] = (BYTE)ii;
      ++pChr;
   }

   _dwPackedSize   = 0;
   _dwUnpackedSize = 0;
}

/* ******************************************************************** **
** @@ Guzis::Pack()
** @  Copyrt : 
** @  Author : Chuck Guzis, 1993
** @  Modify :
** @  Update :
** @  Notes  : Dr. Dobb's Journal. #207 November 1993. pp. 117, 118, 144, 145.
** @  Notes  : Compress a line and do repeated byte encoding.
** @  Notes  : This is a two-pass operation. Internally, we store a flag 
** @  Notes  : in lbi of 0x8000 + count. The next byte in lbi[] may contain 
** @  Notes  : the repeated byte.
** ******************************************************************** */

#pragma warning(disable: 4100)   // unreferenced formal parameter
bool Guzis::Pack(const void* const pSrc,void*& rpDst,DWORD dwSrcSize,DWORD& rdwDstSize)
{
   BYTE*    pIn  = (BYTE*)pSrc;
   BYTE*    pOut = (BYTE*)rpDst;

   while (*pIn)
   {
      WORD     wAcc = 0;

      // Scan the line
      if ((wAcc = (WORD)_DupeCheck(pIn)) > DUPE_THRESHOLD)
      {
         // Compression is ok
         *pOut++ = 0;
         *pOut++ = (BYTE)wAcc;

         // Store the repeated string
         *pOut++ = *pIn;

         pIn += wAcc;
      }
      else
      {
         // See about characters out of map - quote them
         char*    pFound = strchr((char*)pAlphabet,*pIn);

         // If needs quoting
         if (!pFound)
         {
            // Quoting
            *pOut++ = 0;
            *pOut++ = (char)(0x80 | *pIn++);   // Set the quotation flag !
         }
         else
         {
            // See if there are three consecutive symbols that reside
            // in our 5-bit alphabet. Note that an and-of-line will fail
            // the test automatically, so it doesn't require checking
            if (_pAlphaMap[*pIn] && _pAlphaMap[*(pIn + 1)] && _pAlphaMap[*(pIn + 2)])
            {
               // Bingo - got all three
               wAcc = (WORD)(0x8000 | ((_pAlphaMap[*pIn] - 1) << 10) | ((_pAlphaMap[*(pIn + 1)] - 1) << 5) | (_pAlphaMap[*(pIn + 2)] - 1));

               *pOut++ = (BYTE)(wAcc >> 8); // Store first byte
               *pOut++ = (BYTE)(wAcc & 0xFF); // Store second byte

               pIn += 3; // Advance
            }
            else
            {
               // Just copy
               *pOut++ = *pIn++; // Everything else
            }
         }
      }
   }

   _dwPackedSize = pOut - (BYTE*)rpDst;

   rdwDstSize = _dwPackedSize;

   return true;
}

/* ******************************************************************** **
** @@ Guzis::Unpack()
** @  Copyrt : 
** @  Author : Chuck Guzis, 1993
** @  Modify :
** @  Update :
** @  Notes  : Dr. Dobb's Journal. #207 November 1993. pp. 117, 118, 144, 145.
** ******************************************************************** */

bool Guzis::Unpack(const void* const pSrc,void*& rpDst,DWORD dwSrcSize,DWORD& rdwDstSize)
{
   BYTE     Chr;  // Current character
   UINT     k;    // Scratch word cell

   BYTE*    pIn  = (BYTE*)pSrc;
   BYTE*    pOut = (BYTE*)rpDst;

   while ((pIn - (BYTE*)pSrc) < (int)dwSrcSize)
   {
      // Read and decode
      Chr = *pIn++;

      if (Chr & 0x80)
      {
         // Special flagging, packed 5 bits
         k = (Chr << 8);

         Chr = *pIn++;

         k |= Chr; // Form a word

         *pOut++ = pAlphabet[(k >> 10) & 0x1F];
         *pOut++ = pAlphabet[(k >> 5)  & 0x1F];
         *pOut++ = pAlphabet[ k & 31]; // Unpack all three
      }
      else
      {
         if (!Chr)
         {
            // Escape or repeated byte
            Chr = *pIn++;

            if (Chr < 0x80)
            {
               // Repeated byte
               k = Chr;

               // Get the actual byte
               Chr = *pIn++; 

               while (k--)
               {
                  // Write the repeated byte
                  *pOut++ = Chr; 
               }
            }
            else
            {
               // Not repeated, but just quoted
               *pOut++ = (BYTE)(Chr & ~0x80); 
            }
         }
         else
         {
            // Just an ordinary character
            *pOut++ = Chr; 
         }
      }
   }

   *pOut++ = 0;   // ASCIIZ
   
   _dwUnpackedSize = pOut - (BYTE*)rpDst;
   rdwDstSize = _dwUnpackedSize;

   return true;
}

/* ******************************************************************** **
** @@ Guzis::GetMaxPackedSize()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

DWORD Guzis::GetMaxPackedSize(DWORD dwOriginalSize)
{
   return 0;
}

/* ******************************************************************** **
** @@ Guzis::GetMaxTempBufSize()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

DWORD Guzis::GetMaxTempBufSize()
{
   return 0;
}

/* ******************************************************************** **
** @@ Guzis::PackedSize()
** @  Copyrt : 
** @  Author :
** @  Modify : 
** @  Update :
** @  Notes  : 
** ******************************************************************** */

DWORD Guzis::PackedSize()
{
   return _dwPackedSize; 
}

/* ******************************************************************** **
** @@ Guzis::UnpackedSize()
** @  Copyrt : 
** @  Author :
** @  Modify : 
** @  Update :
** @  Notes  : 
** ******************************************************************** */

DWORD Guzis::UnpackedSize()
{
   return _dwUnpackedSize; 
}

/* ******************************************************************** **
** End of File
** ******************************************************************** */
