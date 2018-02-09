/* ******************************************************************** **
** @@ Vector Ex
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Dscr   :
** ******************************************************************** */

#ifndef _VECTOR_EX_HPP_
#define _VECTOR_EX_HPP_

#if _MSC_VER > 1000
#pragma once
#endif 

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   Classes
** ******************************************************************** */

/* ******************************************************************** **
** @@ class VectorEx
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

class VectorEx : public Vector
{
   protected:

      HANDLE         _hFile;
      CMemFile*      _pMemFile;

   public:

               VectorEx();
               VectorEx(DWORD dwSize,WORD wDelta,bool bGrow = true,bool bShrink = false);
      virtual ~VectorEx();

      void     SetFileHandle(HANDLE hFile);
      void     SetMemFilePtr(const CMemFile* const pMemFile);

      virtual bool   Load();
      virtual bool   Save();

      virtual void   MemLoad();
      virtual void   MemSave();

   protected:

      bool LoadItem(void* pBuf,int iItemSize);
      bool SaveItem(const void* const pBuf,int iItemSize);

      bool LoadBString(char* pStr);
      bool SaveBString(const char* const pStr);

      void MemLoadItem(void* pBuf,int iItemSize);
      void MemSaveItem(const void* const pBuf,int iItemSize);
};

/* ******************************************************************** **
** @@                   Prototypes
** ******************************************************************** */

#endif

/* ******************************************************************** **
**                End of File
** ******************************************************************** */
