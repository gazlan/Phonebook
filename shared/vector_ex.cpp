/* ******************************************************************** **
** @@ Vector Ex
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

#include "search.h"
#include "file.h"
#include "vector.h"
#include "vector_ex.h"

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */

static const int  MIN_INDEX_OF = 64;      // Search Optimization

/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ VectorEx::VectorEx()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : Constructor
** ******************************************************************** */

VectorEx::VectorEx()
:  Vector()
{
   _hFile    = INVALID_HANDLE_VALUE;
   _pMemFile = NULL;
}

/* ******************************************************************** **
** @@ VectorEx::VectorEx()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : Constructor
** ******************************************************************** */

VectorEx::VectorEx
(
   DWORD       dwSize,
   WORD        wDelta,
   bool        bGrow,
   bool        bShrink
)
:  Vector(dwSize,wDelta,bGrow,bShrink)
{
   _hFile    = INVALID_HANDLE_VALUE;
   _pMemFile = NULL;
}

/* ******************************************************************** **
** @@ VectorEx::~VectorEx()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : Destructor
** ******************************************************************** */

VectorEx::~VectorEx()
{
   _hFile    = INVALID_HANDLE_VALUE;
   _pMemFile = NULL;
}

/* ******************************************************************** **
** @@ VectorEx::Load()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

bool VectorEx::Load()
{
   DWORD    dwSize = 0;

   if (!LoadItem(&_dwCount,sizeof(DWORD)))
   {
      return false;
   }

   if (!LoadItem(&dwSize,sizeof(DWORD)))
   {
      return false;
   }

   if (dwSize)
   {
      Resize(dwSize);

      _dwSize = dwSize;
   }

   if (!LoadItem(&_wDelta,sizeof(WORD)))
   {
      return false;
   }

   if (!LoadItem(&_bGrow,sizeof(bool)))
   {
      return false;
   }

   if (!LoadItem(&_bShrink,sizeof(bool)))
   {
      return false;
   }
   
   return true;
}

/* ******************************************************************** **
** @@ VectorEx::Save()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

bool VectorEx::Save()
{
   if (!SaveItem(&_dwCount,sizeof(DWORD)))
   {
      return false;
   }

   if (!SaveItem(&_dwSize,sizeof(DWORD)))
   {
      return false;
   }

   if (!SaveItem(&_wDelta,sizeof(WORD)))
   {
      return false;
   }

   if (!SaveItem(&_bGrow,sizeof(bool)))
   {
      return false;
   }

   if (!SaveItem(&_bShrink,sizeof(bool)))
   {
      return false;
   }
   
   return true;
}

/* ******************************************************************** **
** @@ VectorEx::MemLoad()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

void VectorEx::MemLoad()
{
}

/* ******************************************************************** **
** @@ VectorEx::MemSave()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

void VectorEx::MemSave()
{
   MemSaveItem(&_dwSize,sizeof(int));
   MemSaveItem(&_wDelta,sizeof(int));
   MemSaveItem(&_bGrow, sizeof(bool));
   MemSaveItem(&_bShrink,sizeof(bool));
}

/* ******************************************************************** **
** @@ VectorEx::LoadItem()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

bool VectorEx::LoadItem
(
   void*          pBuf,
   int            iItemSize
)
{
   if (_hFile == INVALID_HANDLE_VALUE)
   {
      return false;
   }

   return ReadBuffer(_hFile,pBuf,iItemSize);
}

/* ******************************************************************** **
** @@ VectorEx::SaveItem()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

bool VectorEx::SaveItem
(
   const void* const       pBuf,
   int                     iItemSize
)
{
   if (_hFile == INVALID_HANDLE_VALUE)
   {
      return false;
   }

   return WriteBuffer(_hFile,pBuf,iItemSize);
}

/* ******************************************************************** **
** @@ VectorEx::MemLoadItem()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : 
** ******************************************************************** */

void VectorEx::MemLoadItem(void* pBuf,int iItemSize)
{
}

/* ******************************************************************** **
** @@ VectorEx::MemSaveItem()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : 
** ******************************************************************** */

void VectorEx::MemSaveItem(const void* const pBuf,int iItemSize)
{
   _pMemFile->Write(pBuf,iItemSize);
}

/* ******************************************************************** **
** @@ VectorEx::LoadBString()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : 
** ******************************************************************** */

bool VectorEx::LoadBString
(
   char*       pszStr
)
{
   BYTE     bySize = 0;

   if (!LoadItem(&bySize,sizeof(BYTE)))
   {
      return false;
   }
   
   if (!LoadItem(pszStr,sizeof(char) * bySize))
   {
      return false;
   }

   pszStr[bySize] = 0;     // ASCIIZ

   return true;
}

/* ******************************************************************** **
** @@ VectorEx::SaveBString()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : 
** ******************************************************************** */

bool VectorEx::SaveBString
(
   const char* const       pStr
)
{
   BYTE     bySize = (BYTE)strlen(pStr);         

   if (!SaveItem(&bySize,sizeof(BYTE)))
   {
      return false;
   }
   
   return SaveItem(pStr,sizeof(char) * bySize);
}

/* ******************************************************************** **
** @@ VectorEx::SetFileHandle()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

void VectorEx::SetFileHandle(HANDLE hFile)
{
   ASSERT(hFile);

   _hFile = hFile;
}

/* ******************************************************************** **
** @@ VectorEx::SetMemFilePtr()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

void VectorEx::SetMemFilePtr(const CMemFile* const pMemFile)
{
   ASSERT(pMemFile);

   _pMemFile = (CMemFile*)pMemFile;
}

/* ******************************************************************** **
**                End of File
** ******************************************************************** */
