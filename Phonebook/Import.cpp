#include "stdafx.h"

#include "resource.h"

#include "..\shared\vector.h"
#include "..\shared\vector_sorted.h"
#include "..\shared\vector_ex.h"
#include "..\shared\vector_sorted_ex.h"
#include "..\shared\file.h"
#include "..\shared\mmf.h"
#include "..\shared\text.h"
#include "..\shared\pack_abstract.h"
#include "..\shared\pack_guzis.h"
#include "..\shared\hyperlink_maunder.h"

#include "about.h"
#include "09.h"
#include "09Dlg.h"
#include "Import.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IMPORT_INITIAL                     (131072)
#define IMPORT_DELTA                       (16384)

/* ******************************************************************** **
** @@ class ImportLineEntry
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

class ImportLineEntry
{  
   public:

      int            _iNum;
      CString        _sKey;
      CString        _sValue;
      CString        _sAppendix1;
      CString        _sAppendix2;

   public:

      ImportLineEntry()
      {
         _iNum = 0;

         _sKey       = _T("");
         _sValue     = _T("");
         _sAppendix1 = _T("");
         _sAppendix2 = _T("");
      }
};

/* ******************************************************************** **
** @@ static int CMP_ID()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static int CMP_ID(const void** const pKey1,const void** const pKey2)
{
   ListLineEntry**   p1 = (ListLineEntry**)pKey1;
   ListLineEntry**   p2 = (ListLineEntry**)pKey2;

   return (*p1)->_iNum - (*p2)->_iNum;
}

/* ******************************************************************** **
** @@ CImport::CImport()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : Constructor
** ******************************************************************** */

CImport::CImport(CWnd* pParent /*=NULL*/)
:  CDialog(CImport::IDD, pParent)
{
   //{{AFX_DATA_INIT(CImport)
   _bHide4 = FALSE;
   _bHide5 = FALSE;
   _bLock = FALSE;
   _bPassword = FALSE;
   _sField1 = _T("");
   _sField2 = _T("");
   _sField3 = _T("");
   _sField4 = _T("");
   _sField5 = _T("");
   _sFile = _T("");
   _sPassword = _T("");
   _sTitle = _T("");
   _sAbout = _T("");
   //}}AFX_DATA_INIT

   _pParent = NULL;
}

/* ******************************************************************** **
** @@ CImport::DoDataExchange()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CImport)
   DDX_Check(pDX, IDC_CHK_HIDE4, _bHide4);
   DDX_Check(pDX, IDC_CHK_HIDE5, _bHide5);
   DDX_Check(pDX, IDC_CHK_LOCKED, _bLock);
   DDX_Check(pDX, IDC_CHK_PASSWORD, _bPassword);
   DDX_Text(pDX, IDC_EDT_FIELD1, _sField1);
   DDV_MaxChars(pDX, _sField1, 32);
   DDX_Text(pDX, IDC_EDT_FIELD2, _sField2);
   DDV_MaxChars(pDX, _sField2, 32);
   DDX_Text(pDX, IDC_EDT_FIELD3, _sField3);
   DDV_MaxChars(pDX, _sField3, 32);
   DDX_Text(pDX, IDC_EDT_FIELD4, _sField4);
   DDV_MaxChars(pDX, _sField4, 32);
   DDX_Text(pDX, IDC_EDT_FIELD5, _sField5);
   DDV_MaxChars(pDX, _sField5, 32);
   DDX_Text(pDX, IDC_EDT_FILE, _sFile);
   DDV_MaxChars(pDX, _sFile, 255);
   DDX_Text(pDX, IDC_EDT_PASSWORD, _sPassword);
   DDV_MaxChars(pDX, _sPassword, 255);
   DDX_Text(pDX, IDC_EDT_TITLE, _sTitle);
   DDV_MaxChars(pDX, _sTitle, 255);
   DDX_Text(pDX, IDC_REDT_ABOUT, _sAbout);
   DDV_MaxChars(pDX, _sAbout, 65535);
   //}}AFX_DATA_MAP
}

/* ******************************************************************** **
** @@ CImport::MESSAGE_MAP()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

BEGIN_MESSAGE_MAP(CImport, CDialog)
   //{{AFX_MSG_MAP(CImport)
   ON_BN_CLICKED(IDC_BTN_FILE, OnBtnFile)
   ON_BN_CLICKED(IDC_CHK_HIDE4, OnChkHide4)
   ON_BN_CLICKED(IDC_CHK_HIDE5, OnChkHide5)
   ON_BN_CLICKED(IDC_CHK_PASSWORD, OnChkPassword)
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/* ******************************************************************** **
** @@ CImport::OnInitDialog()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

BOOL CImport::OnInitDialog() 
{
   CDialog::OnInitDialog();
   
   _Import.Resize(IMPORT_INITIAL);
   _Import.Delta (IMPORT_DELTA);

   _Import.SetSorter(CMP_ID);  // Unique field !
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

/* ******************************************************************** **
** @@ CImport::OnBtnFile()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::OnBtnFile() 
{
   DWORD    dwFlags =   OFN_ENABLESIZING     |
                        OFN_FILEMUSTEXIST    |
                        OFN_HIDEREADONLY     |
                        OFN_NOREADONLYRETURN |
                        OFN_PATHMUSTEXIST;
                                    
   char     pszFilter[MAX_PATH] = "CSV (*.csv)|*.csv|"
                                  "TAB (*.tab)|*.tab|"
                                  "MAP (*.map)|*.map||";

   CFileDialog    User(TRUE,NULL,NULL,dwFlags,pszFilter);

   if (User.DoModal() == IDOK)
   {
      _sFile = User.GetPathName();

      UpdateData(FALSE);
   }
}

/* ******************************************************************** **
** @@ CImport::OnChkHide4()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::OnChkHide4() 
{
   // TODO: Add your control notification handler code here
}

/* ******************************************************************** **
** @@ CImport::OnChkHide5()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::OnChkHide5() 
{
   // TODO: Add your control notification handler code here
}

/* ******************************************************************** **
** @@ CImport::OnChkPassword()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::OnChkPassword() 
{
   // TODO: Add your control notification handler code here
}

/* ******************************************************************** **
** @@ CImport::OnOK()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::OnOK() 
{
   if (_sFile.IsEmpty())
   {
      return;
   }

   char     pszDrive   [_MAX_DRIVE];
   char     pszDir     [_MAX_DIR];
   char     pszFName   [_MAX_FNAME];
   char     pszExt     [_MAX_EXT];

   _splitpath((LPCTSTR)_sFile,pszDrive,pszDir,pszFName,pszExt);

   if (!stricmp(pszExt,".TAB"))
   {
      ImportTab();
   }
/*
FileTree    FTree;

DWORD    dwID = 0;

dwID = FTree.InsertNode(0,FT_TT_NULL,'q',NULL,3);
dwID = FTree.InsertNode(3,FT_TT_NULL,'W',NULL,3);
dwID = FTree.InsertNode(6,FT_TT_NULL,'e',NULL,3);
*/
   
   CDialog::OnOK();
}

/* ******************************************************************** **
** @@ CImport::SetParent()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::SetParent(const C09Dlg* pParent)
{
   _pParent = (C09Dlg*)pParent;
}

/* ******************************************************************** **
** @@ CImport::ImportTab()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void CImport::ImportTab()
{
   LoadTabFile();
}

/* ******************************************************************** **
** @@ CImport::LoadTabFile()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

bool CImport::LoadTabFile()
{
   CWaitCursor    Waiter;

   const DWORD    BUF_SIZE = (0x01 << 20);   // About 1 Mb !

   char*    pBuf = new char[BUF_SIZE];

   if (!pBuf)
   {
      // Error !
      return false;
   }

   char     pszError   [_MAX_PATH];
   char     pszInsert  [_MAX_PATH];
   char     pszDrive   [_MAX_DRIVE];
   char     pszDir     [_MAX_DIR];
   char     pszFName   [_MAX_FNAME];
   char     pszExt     [_MAX_EXT];

   _splitpath((LPCTSTR)_sFile,pszDrive,pszDir,pszFName,pszExt);
   _makepath( pszError,pszDrive,pszDir,pszFName,"error.txt");
   _makepath( pszInsert,pszDrive,pszDir,pszFName,"insert.txt");

   FILE*    pErr = fopen(pszError, "wt");
   FILE*    pOut = fopen(pszInsert,"wt");

   FILE*    pIn = fopen((LPCTSTR)_sFile,"rt");

   if (!pIn)
   {
      // Error !
      delete[] pBuf;
      pBuf = NULL;
      return false;
   }

   int   iCnt = 0;

   // Read a String from the file to Buf
   while (fgets(pBuf,BUF_SIZE,pIn))
   {
      pBuf[BUF_SIZE - 1] = 0;  // Ensure ASCIIZ !

      DWORD    dwEOL = strcspn(pBuf,"\r\n");

      pBuf[dwEOL] = 0;  // Remove EOL chars

      CString  sID    = _T("");
      CString  sKey   = _T("");
      CString  sValue = _T("");
      CString  sApx1  = _T("");
      CString  sApx2  = _T("");

      char*    pText = pBuf;     // Prepare
         
      // ID
      pText = (char*)AcquireToken(pText,'\t',sID);
      Jam(sID);

      // key
      pText = (char*)AcquireToken(pText,'\t',sKey);
      Jam(sKey);

      // Value
      pText = (char*)AcquireToken(pText,'\t',sValue);
      Jam(sValue);

      // Appendix1
      pText = (char*)AcquireToken(pText,'\t',sApx1);
      Jam(sApx1);

      // Appendix2
      pText = (char*)AcquireToken(pText,'\t',sApx2);
      Jam(sApx2);

      int   iID = atoi((LPCTSTR)sID);

      if (iID)
      {
         ImportLineEntry*     pItem = new ImportLineEntry;

         if (!pItem)
         {
            delete[] pBuf;
            pBuf = NULL;
            return false;
         }

         pItem->_iNum = iID;

         pItem->_sKey       = sKey;
         pItem->_sValue     = sValue;
         pItem->_sAppendix1 = sApx1;
         pItem->_sAppendix2 = sApx2;

         if (_Import.Insert(pItem) != -1)
         {
            #ifdef _DEBUG 
            fprintf(pOut,"%12ld|%s|%s|%s|%s\n",pItem->_iNum,pItem->_sKey,pItem->_sValue,pItem->_sAppendix1,pItem->_sAppendix2); 
            #endif

            ++iCnt;
         }
         else
         {
            // Insertion Error
            delete pItem;
            pItem = NULL;
         }
      }
   }

   delete[] pBuf;
   pBuf = NULL;

   fclose(pIn);
   pIn = NULL;

   #ifdef _DEBUG 
   fclose(pErr);
   pErr = NULL;
   fclose(pOut);
   pOut = NULL;
   #endif

   return true;
}

/* ******************************************************************** **
** @@ CImport::OnDestroy()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void CImport::OnDestroy() 
{
   CDialog::OnDestroy();

   Cleanup();
}

/* ******************************************************************** **
** @@ CImport::Cleanup()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void CImport::Cleanup()
{
   CWaitCursor    Waiter;
     
   DWORD    dwCnt = _Import.Count();

   // Should be Int !!
   for (int ii = dwCnt - 1; ii >= 0; --ii)
   {
      ImportLineEntry*     pItem = (ImportLineEntry*)_Import.At(ii);

      /*
      // If this ASSERT fails, a bad pointer has been passed in. It may be
      // totally bogus, or it may have been allocated from another heap.
      // The pointer MUST come from the 'local' heap.
      if (!_CrtIsValidHeapPointer(pItem))
      {
         MessageBeep(MB_OK);
      }
      */
      
      if (pItem)
      {
         _Import.RemoveAt(ii);
         delete pItem;
         pItem = NULL;
      }
   }
}

/* ******************************************************************** **
** @@ CImport::Cleanup()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void CImport::Jam(CString& rStr)
{
   rStr.TrimLeft();
   rStr.TrimRight();

   while (rStr.Replace("\x20\x20","\x20"))
   {
      ;  // Do Nothing !
   }
}

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
