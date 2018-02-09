/* ******************************************************************** **
** @@ AbstractPack
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

#ifndef _ABSTRACT_PACK_HPP_
#define _ABSTRACT_PACK_HPP_

#if _MSC_VER > 1000
#pragma once
#endif

/* ******************************************************************** **
** @@ internal defines
** ******************************************************************** */

/* ******************************************************************** **
** @@ internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@ external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@ static global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@ Prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@ AbstractPack
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : Abstract Compression class
** ******************************************************************** */

class AbstractPack
{
   enum { MAX_TOKEN_SIZE = 16 };

   protected:

      BYTE*       _pSrc;
      BYTE*       _pDst;
      BYTE*       _pTempBuf;
      DWORD       _dwSrcSize;
      DWORD       _dwDstSize;
      DWORD       _dwSrcIdx;
      DWORD       _dwDstIdx;
      BYTE        _byTokenSize;
      bool        _bTempBufAllocated;
      bool        _bResizable;
      bool        _bValid;

   public:

               AbstractPack();
      virtual ~AbstractPack();
                     
      virtual bool   Pack  (const void* const pSrc,void*& rpDst,DWORD dwSrcSize,DWORD& rdwDstSize) = 0;
      virtual bool   Unpack(const void* const pSrc,void*& rpDst,DWORD dwSrcSize,DWORD& rdwDstSize) = 0;
     
      virtual DWORD PackedSize() = 0;
      virtual DWORD UnpackedSize() = 0;

      virtual DWORD  GetMaxPackedSize (DWORD dwOriginalSize) = 0;
      virtual DWORD  GetMaxTempBufSize() = 0;

      bool  SetTempBuf(void* pTempBuf);
      bool  AllocTempBuf(DWORD dwSize);
      bool  KillTempBuf();
      bool  IsResizable();
      bool  Validate();

      virtual void   InitSrcBuf(const void* const pBuf,DWORD dwSize,DWORD dwIdx);
      virtual void   InitDstBuf(const void* const pBuf,DWORD dwSize,DWORD dwIdx);

   protected:

      virtual void   SetSrcBuf (const void* const pBuf);
      virtual void   SetDstBuf (void* pBuf);
      virtual void   SetSrcSize(DWORD dwSize);
      virtual void   SetDstSize(DWORD dwSize);
      virtual void   SetScrIdx (DWORD dwIdx);
      virtual void   SetDstIdx (DWORD dwIdx);

      void  Rewrite();                    // Src Only !
      void  Ungetc (DWORD dwCnt = 1);     // Src Only !

      int   SetTokenSize(BYTE bySize);
      int   IncreaseTokenSize();

      virtual int    Getc();
      virtual int    Putc(int iByte);
      virtual int    IssueToken(int iToken);
      virtual int    FetchToken();
      virtual DWORD  Read(void* pBuf,DWORD dwSize);
      virtual DWORD  Write(const void* const pBuf,DWORD dwSize);
};

#endif

/* ******************************************************************** **
** End of File
** ******************************************************************** */
