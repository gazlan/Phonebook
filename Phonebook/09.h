/* ******************************************************************** **
** @@ 09
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

#ifndef _09_H_
#define _09_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* ******************************************************************** **
** @@ internal defines
** ******************************************************************** */

class C09App : public CWinApp
{
   private:

      HANDLE      _hMutext;

public:
   C09App();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(C09App)
   public:
      virtual BOOL   InitInstance();
      virtual int    ExitInstance();
   //}}AFX_VIRTUAL

// Implementation

   //{{AFX_MSG(C09App)
      // NOTE - the ClassWizard will add and remove member functions here.
      //    DO NOT EDIT what you see in these blocks of generated code !
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

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
** @@ Global Function Prototypes
** ******************************************************************** */

#endif

/* ******************************************************************** **
** End of File
** ******************************************************************** */
