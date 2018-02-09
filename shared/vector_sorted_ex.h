/* ******************************************************************** **
** @@ Sorted Vector Ex
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Dscr   :
** ******************************************************************** */

#ifndef _SORTED_VECTOR_EX_HPP_
#define _SORTED_VECTOR_EX_HPP_

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
** @@ class SortedVectorEx : public Vector
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

class SortedVectorEx : public VectorEx
{
   protected:

      bool   _bUnique;

   public:

      SortedVectorEx();
      SortedVectorEx(DWORD dwSize,WORD wDelta,bool bGrow = true,bool bShrink = false,bool bUnique = true);

      virtual ~SortedVectorEx();

      virtual bool   Load();
      virtual bool   Save();

      bool IsUnique() { return  _bUnique; }
                                 
      virtual int    __fastcall  Indexof(const void* const pItem);
      virtual int    __fastcall  Insert (const void* const pItem);
      virtual void*  __fastcall  Search (const void* const pKey,int* pIndex = NULL,SEARCHER pSearch = NULL);
};

/* ******************************************************************** **
** @@                   Prototypes
** ******************************************************************** */

#endif

/* ******************************************************************** **
**                End of File
** ******************************************************************** */
