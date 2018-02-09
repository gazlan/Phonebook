/* ******************************************************************** **
** @@ AbstractPack
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */


/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include "stdafx.h"

#include "pack_abstract.h"

/* ******************************************************************** **
** @@                   internal #defines
** ******************************************************************** */

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ AbstractPack::AbstractPack()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

AbstractPack::AbstractPack()
{
   _pSrc     = NULL;
   _pDst     = NULL;
   _pTempBuf = NULL;

   _dwSrcSize   = 0;
   _dwDstSize   = 0;
   _dwSrcIdx    = 0;
   _dwDstIdx    = 0;
   _byTokenSize = 0;

   _bResizable        = false;
   _bTempBufAllocated = false;
   _bValid            = false;
}

/* ******************************************************************** **
** @@ AbstractPack::~AbstractPack()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

AbstractPack::~AbstractPack()
{
   KillTempBuf();
}

/* ******************************************************************** **
** @@ AbstractPack::SetTokenSize()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int AbstractPack::SetTokenSize
(
   BYTE     bySize
)
{
   if (!bySize || (bySize > MAX_TOKEN_SIZE))
      return -1;

   _byTokenSize = bySize;

   return (int)_byTokenSize;
}

/* ******************************************************************** **
** @@ AbstractPack::IncreaseTokenSize()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int AbstractPack::IncreaseTokenSize()
{
   if (_byTokenSize > (MAX_TOKEN_SIZE - 1))
      return -1;

   ++_byTokenSize;

   return (int)_byTokenSize;
}

/* ******************************************************************** **
** @@ AbstractPack::SetTempBuf()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool AbstractPack::SetTempBuf
(
   void*       pTempBuf
)
{
   if (_bTempBufAllocated)
   {
      return false;
   }

   _pTempBuf = (BYTE*)pTempBuf;

   return true;
}

/* ******************************************************************** **
** @@ AbstractPack::InitSrcBuf()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::InitSrcBuf
(
   const void* const    pBuf,
   DWORD                dwSize,
   DWORD                dwIdx
)
{
   SetSrcBuf(pBuf);
   SetSrcSize(dwSize);
   SetScrIdx (dwIdx);
}

/* ******************************************************************** **
** @@ AbstractPack::InitDstBuf()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::InitDstBuf
(
   const void* const    pBuf,
   DWORD                dwSize,
   DWORD                dwIdx
)
{
   SetDstBuf((void*)pBuf);
   SetDstSize(dwSize);
   SetDstIdx (dwIdx);
}

/* ******************************************************************** **
** @@ AbstractPack::SetSrcBuf()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::SetSrcBuf
(
   const void* const    pBuf
)
{
   _pSrc = (BYTE*)pBuf;
}

/* ******************************************************************** **
** @@ AbstractPack::SetDstBuf()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::SetDstBuf
(
   void*       pBuf
)
{
   _pDst = (BYTE*)pBuf;
}

/* ******************************************************************** **
** @@ AbstractPack::SetSrcSize()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::SetSrcSize
(
   DWORD       dwSize
)
{
   _dwSrcSize = dwSize;
}

/* ******************************************************************** **
** @@ AbstractPack::SetDstSize()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::SetDstSize
(
   DWORD       dwSize
)
{
   _dwDstSize = dwSize;
}

/* ******************************************************************** **
** @@ AbstractPack::SetScrIdx()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::SetScrIdx(DWORD dwIdx)
{
   _dwSrcIdx = dwIdx;
}

/* ******************************************************************** **
** @@ AbstractPack::SetDstIdx()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::SetDstIdx(DWORD dwIdx)
{
   _dwDstIdx = dwIdx;
}

/* ******************************************************************** **
** @@ AbstractPack::Getc()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int AbstractPack::Getc()
{
   if (!_pSrc || (_dwSrcIdx > (_dwSrcSize - 1)) || IsBadReadPtr(_pSrc,1))
      return -1;

   return (int)_pSrc[_dwSrcIdx++];
}

/* ******************************************************************** **
** @@ AbstractPack::Putc()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int AbstractPack::Putc(int iByte)
{
   if (!_pDst || (_dwDstIdx > (_dwDstSize - 1)) || IsBadWritePtr(_pDst,1))
   {
      return -1;
   }

   return (int)(_pDst[_dwDstIdx++] = (BYTE)iByte);
}

/* ******************************************************************** **
** @@ AbstractPack::Rewrite()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::Rewrite()
{
   SetScrIdx(0);
}

/* ******************************************************************** **
** @@ AbstractPack::Ungetc()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void AbstractPack::Ungetc(DWORD dwCnt)
{
   _dwSrcIdx = (dwCnt >= _dwSrcIdx)  ?  0  :  _dwSrcIdx - dwCnt;
}

/* ******************************************************************** **
** @@ AbstractPack::IssueToken()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int AbstractPack::IssueToken(int iToken)
{
   if (!_byTokenSize || (_byTokenSize > MAX_TOKEN_SIZE))
   {
      return -1;
   }

   static int        iCnt     = 0;
   static DWORD      dwBuffer = 0;

   dwBuffer |= (DWORD)iToken << (32 - _byTokenSize - iCnt);

   iCnt += _byTokenSize;

   int   iResult = 0;

   while (iCnt >= 8)
   {
      iResult = Putc(dwBuffer >> 24);
      dwBuffer <<= 8;
      iCnt -= 8;
   }

   return iResult;
}

/* ******************************************************************** **
** @@ AbstractPack::FetchToken()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int AbstractPack::FetchToken()
{
   if (!_byTokenSize || (_byTokenSize > MAX_TOKEN_SIZE))
      return -1;

   static int        iCnt     = 0;
   static DWORD      dwBuffer = 0;

   while (iCnt <= 24)
   {
      dwBuffer |= (DWORD)Getc() << (24 - iCnt);
      iCnt += 8;
   }

   int   iResult = dwBuffer >> (32 - _byTokenSize);

   dwBuffer <<= _byTokenSize;
   iCnt -= _byTokenSize;

   return iResult;
}

/* ******************************************************************** **
** @@ AbstractPack::AllocTempBuf()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool AbstractPack::AllocTempBuf
(
   DWORD       dwSize
)
{
   if (_pTempBuf || _bTempBufAllocated)
      return false;

   _pTempBuf = new BYTE[dwSize];

   if (!_pTempBuf)
      return false;

   if (IsBadWritePtr(_pTempBuf,dwSize))
      return false;

   _bTempBufAllocated = true;

   return true;
}

/* ******************************************************************** **
** @@ AbstractPack::KillTempBuf()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool AbstractPack::KillTempBuf()
{
   if (!_bTempBufAllocated)
      return false;

   delete _pTempBuf;
   _pTempBuf = NULL;

   _bTempBufAllocated = false;

   return true;
}

/* ******************************************************************** **
** @@ AbstractPack::Read()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

DWORD AbstractPack::Read
(
   void*       pBuf,
   DWORD       dwSize
)
{
   DWORD    dwRealSize = min(dwSize,_dwSrcSize - _dwSrcIdx);

   if (!dwRealSize)
   {
      return 0;
   }

   if (!_pSrc || ((_dwSrcIdx + dwRealSize) > _dwSrcSize) || IsBadReadPtr(_pSrc + _dwSrcIdx,dwRealSize))
   {
      return 0;
   }

   if (!pBuf || IsBadWritePtr(pBuf,dwRealSize))
   {
      return 0;
   }

   memcpy(pBuf,_pSrc + _dwSrcIdx,dwRealSize);

   _dwSrcIdx += dwRealSize;

   return dwRealSize;
}

/* ******************************************************************** **
** @@ AbstractPack::Write()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

DWORD AbstractPack::Write
(
   const void* const       pBuf,
   DWORD                   dwSize
)
{
   DWORD    dwRealSize = min(dwSize,_dwDstSize - _dwDstIdx);

   if (!dwRealSize)
   {
      return 0;
   }

   if (!_pDst || ((_dwDstIdx + dwRealSize) > _dwDstSize) || IsBadWritePtr(_pDst + _dwDstIdx,dwRealSize))
   {
      return 0;
   }

   if (!pBuf || IsBadReadPtr(pBuf,dwRealSize))
   {
      return 0;
   }

   memcpy(_pDst + _dwDstIdx,pBuf,dwRealSize);

   _dwDstIdx += dwRealSize;

   return dwRealSize;
}

/* ******************************************************************** **
** @@ AbstractPack::IsResizable()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool AbstractPack::IsResizable()
{
   return _bResizable;
}

/* ******************************************************************** **
** @@ AbstractPack::Validate()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool AbstractPack::Validate()
{
   return _bValid;
}

/* ******************************************************************** **
** End of File
** ******************************************************************** */
