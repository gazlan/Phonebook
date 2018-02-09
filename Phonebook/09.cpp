/* ******************************************************************** **
** @@ 09
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Modify :
** @  Notes  :
** ******************************************************************** */

/* ******************************************************************** **
** uses precompiled headers
** ******************************************************************** */

#include "stdafx.h"

#include "resource.h"

#include "..\shared\vector.h"
#include "..\shared\vector_sorted.h"
#include "..\shared\vector_ex.h"
#include "..\shared\vector_sorted_ex.h"

#include "09.h"
#include "09Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef NDEBUG
#pragma optimize("gsy",on)
#pragma comment(linker,"/FILEALIGN:512 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
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
                  
C09App      theApp;

/* ******************************************************************** **
** @@ real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ C09App::MESSAGE_MAP()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

BEGIN_MESSAGE_MAP(C09App, CWinApp)
   //{{AFX_MSG_MAP(C09App)
      // NOTE - the ClassWizard will add and remove mapping macros here.
      //    DO NOT EDIT what you see in these blocks of generated code!
   //}}AFX_MSG
   ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/* ******************************************************************** **
** @@ C09App::C09App()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : Constructor
** ******************************************************************** */

C09App::C09App()
{
   // TODO: add construction code here,
   // Place all significant initialization in InitInstance
}

/* ******************************************************************** **
** @@ C09App::InitInstance()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

BOOL C09App::InitInstance()
{
   // Only One Instance of this App is available !
   _hMutext = CreateMutex(NULL,TRUE,"09_mutext");

   if (!_hMutext)
   {
      return FALSE;
   }

   if (GetLastError() == ERROR_ALREADY_EXISTS)
   {
      return FALSE;
   }

   AfxInitRichEdit();
   AfxEnableControlContainer();

   // Standard initialization
   // If you are not using these features and wish to reduce the size
   // of your final executable, you should remove from the following
   // the specific initialization routines you do not need.

   #ifdef _AFXDLL
   Enable3dControls();        // Call this when using MFC in a shared DLL
   #else
   Enable3dControlsStatic();  // Call this when linking to MFC statically
   #endif

   C09Dlg  dlg;

   m_pMainWnd = &dlg;

   int nResponse = dlg.DoModal();

   if (nResponse == IDOK)
   {
      // TODO: Place code here to handle when the dialog is
      // dismissed with OK
   }
   else if (nResponse == IDCANCEL)
   {
      // TODO: Place code here to handle when the dialog is
      // dismissed with Cancel
   }

   // Since the dialog has been closed, return FALSE so that we exit the
   // application, rather than start the application's message pump.
   return FALSE;
}

/* ******************************************************************** **
** @@ C09App::ExitInstance
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

int C09App::ExitInstance()
{
   CloseHandle(_hMutext);
   _hMutext = INVALID_HANDLE_VALUE;

   return CWinApp::ExitInstance();
}

/* ******************************************************************** **
** @@                   End of File
** ******************************************************************** */
