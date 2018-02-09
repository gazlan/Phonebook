/* ******************************************************************** **
** @@ Sorted Vector Ex
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
#include "vector_sorted_ex.h"

/* ******************************************************************** **
** @@                   internal #defines
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
** @@ SortedVectorEx()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : Constructor
** ******************************************************************** */

SortedVectorEx::SortedVectorEx()
:  VectorEx()
{
   _bUnique = true;
}

/* ******************************************************************** **
** @@ SortedVectorEx::SortedVectorEx()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : Constructor
** ******************************************************************** */

SortedVectorEx::SortedVectorEx
(
   DWORD    dwSize,
   WORD     wDelta,
   bool     bGrow,
   bool     bShrink,
   bool     bUnique
)
:  VectorEx(dwSize,wDelta,bGrow,bShrink)
{
   _bUnique = bUnique;
}

/* ******************************************************************** **
** @@ SortedVectorEx::~SortedVectorEx()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  : Destructor
** ******************************************************************** */

SortedVectorEx::~SortedVectorEx()
{
}

/* ******************************************************************** **
** @@ SortedVectorEx::Indexof()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

int SortedVectorEx::Indexof(const void* const pItem)
{
   if (!_pSorter)
   {
      return -1;
   }

   if (_dwCount < MIN_INDEX_OF)
   {
      // Linear Search
      return Vector::Indexof(pItem);      
   }

   // Binary Search
   int   iIdx = 0;

   void*    pFound = Search(pItem,&iIdx);

   if (pFound == pItem)
   {
      return iIdx;
   }

   if (!pFound)
   {
      return -1;
   }

   if (!_bUnique)
   {
      int   Lo = iIdx;
      int   Hi = (int)(_dwCount - 1);

      while (Lo < (Hi - MIN_INDEX_OF))
      {
         int   Mid = (Lo + Hi) >> 1;

         if (_pSorter((const void** const)&_pItems[Mid],(const void** const)&pItem) <= 0)
         {
            Lo = Mid + 1;
         }
         else
         {
            Hi = Mid - 1;
         }
      }

      for (int ii = iIdx + 1; ii <= Hi; ++ii)
      {
         if (pItem == _pItems[ii])
         {
            return ii;
         }
      }
   }

   return -1;
}

/* ******************************************************************** **
** @@ SortedVectorEx::Insert()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

int SortedVectorEx::Insert(const void* const pItem)
{
   if (!_pSorter)
   {
      return -1;
   }

   int   iIdx = 0;

   void*    pFound = Search(pItem,&iIdx);

   if (pFound && _bUnique)
   {
      return -1;
   }

   return InsertAt(iIdx,pItem)  ?  iIdx  :  -1;
}

/* ******************************************************************** **
** @@ SortedVectorEx::Search()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

void* SortedVectorEx::Search
(
   const void* const    pKey,
   int*                 pIndex,
   SEARCHER             pSearch
)
{
   if (!_pSorter)
   {
      return NULL;
   }

   int   Lo = 0;
   int   Hi = (int)(_dwCount - 1);

   bool  bFound = false;

   while (Lo <= Hi)
   {
      int   Mid = (Lo + Hi) >> 1;

      int   iResult = 0;
      
      if (pSearch)
      {
         iResult = pSearch((const void** const)&_pItems[Mid],(const void** const)&pKey);
      }
      else
      {
         iResult = _pSorter((const void** const)&_pItems[Mid],(const void** const)&pKey);
      }

      if (iResult < 0)
      {
         Lo = Mid + 1;
      }
      else
      {
         Hi = Mid - 1;

         if (!iResult)     // Found
         {
            bFound = true;

            if (_bUnique)
            {
               Lo = Mid;
            }
         }
      }
   }

   if (pIndex)
   {
      *pIndex = Lo;
   }

   return bFound  ?  _pItems[Lo]  :  NULL;
}

/* ******************************************************************** **
** @@ SortedVectorEx::Load()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

bool SortedVectorEx::Load()
{
   if (!VectorEx::Load())
   {
      return false;
   }

   return LoadItem(&_bUnique,sizeof(bool));
}

/* ******************************************************************** **
** @@ SortedVectorEx::Save()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

bool SortedVectorEx::Save()
{
   if (!VectorEx::Save())
   {
      return false;
   }

   return SaveItem(&_bUnique,sizeof(bool));
}

/* ******************************************************************** **
**                End of File
** ******************************************************************** */
