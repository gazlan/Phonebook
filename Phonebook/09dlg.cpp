/* ******************************************************************** **
** @@ 09 Tray Help System
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
#include "..\shared\file.h"
#include "..\shared\mmf.h"
#include "..\shared\text.h"
#include "..\shared\pack_abstract.h"
#include "..\shared\pack_guzis.h"
#include "..\shared\hyperlink_maunder.h"

#include "about.h"
#include "09.h"
#include "09Dlg.h"
#include "import.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TRAY_HELP_SYSTEM               "*   09 09 © Tray Help System   *   "
#define MY_COPYRIGHT                   "©  Gazlan,  2009  *  gazlan@yandex.ru"

#if 0
#ifdef _DEBUG
#define CITY_LABEL                     "КЕМЕРОВО [city/fixed]"
#define GUZIS_MAP                      "@`n\x20phbmkejqsr1o2l3ca\x7Fid4567089x"
#endif
#endif

/* ******************************************************************** **
** @@ internal defines
** ******************************************************************** */

#define WM_TRAY_NOTIFY                 (WM_USER + 1)

#define TITLE_09                       "09 Tray Help System"

#define HYPHEN_LINE_SIZE               (80)
#define GUZIS_MAP_SIZE                 (32)

#define MAX_DESCRIPTION_SIZE           (255)

#define DB_INITIAL                     (131072)
#define DB_DELTA                       (16384)

#define PHONE_BOOK_DELIMITER           (0x09)  // <TAB>

#define DB_NAME                        "09.db"

// Setting
#define LOAD_DB_BIN  
                     
#ifdef _DEBUG
// #define LOAD_DB_TEXT
// #define SAVE_DB_BIN
// #define SAVE_DB_TEXT
// #define SAVE_NOT_PACKED  
// #define REPORT_DB_STAT  
// #define REMOVE_REDUNDANT_SPACE
#endif

/* ******************************************************************** **
** @@ internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@ external global variables
** ******************************************************************** */

extern DWORD      dwKeepError = 0;

/* ******************************************************************** **
** @@ static global variables
** ******************************************************************** */
                  
#ifdef SAVE_DB_BIN
const char psz_XLAT_Direct[256] = // Russian Uppercase to LOW ASCII - GUZIS restriction
{
   '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F', 
   '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F', 
   '\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F', 
   '\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F', 
   '\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F', 
   '\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59', '\x5A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F', 
   '\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F', 
   '\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F', 
   '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F', 
   '\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x96', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F', 
   '\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\x3C', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF', 
   '\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\x3A', '\x3B', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF', 
   '\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F', 
   '\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F', 
   '\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF', 
   '\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF' 
};
#endif

const char psz_XLAT_Reverse[256] = // LOW ASCII to Russian Uppercase - GUZIS restriction
{
   '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F', 
   '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F', 
   '\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F', 
   '\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\xB8', '\xB9', '\xA8', '\x3D', '\x3E', '\x3F', 
   '\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F', 
   '\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59', '\x5A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F', 
   '\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF', 
   '\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF', 
   '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F', 
   '\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x96', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F', 
   '\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\xA8', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF', 
   '\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\xB8', '\xB9', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF', 
   '\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF', 
   '\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF', 
   '\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF', 
   '\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF' 
};

/* ******************************************************************** **
** @@ real code
** ******************************************************************** */

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
** @@ static int CMP_Key()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static int CMP_Key(const void** const pKey1,const void** const pKey2)
{
   ListLineEntry*   p1 = *((ListLineEntry**)pKey1);
   ListLineEntry*   p2 = *((ListLineEntry**)pKey2);

   return p1->_sKey.CompareNoCase(p2->_sKey);
}

/* ******************************************************************** **
** @@ static int CMP_Value()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static int CMP_Value(const void** const pKey1,const void** const pKey2)
{
   ListLineEntry*   p1 = *((ListLineEntry**)pKey1);
   ListLineEntry*   p2 = *((ListLineEntry**)pKey2);

   return p1->_sValue.CompareNoCase(p2->_sValue);
}

/* ******************************************************************** **
** @@ C09Dlg::C09Dlg()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : Constructor
** ******************************************************************** */

C09Dlg::C09Dlg(CWnd* pParent /*=NULL*/)
:  CDialog(C09Dlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(C09Dlg)
   //}}AFX_DATA_INIT
   // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
   _hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   _bVisible = false;

   _pImageList = NULL;

   _sFind = _T("");

   _Selected     = FS_NONE;
   _KeepSelected = FS_NONE;

   _iCurrent = 0;
   _iTotal   = 0;

   _bClosed = false;

   memset(_pszCity,0,MAX_PATH);

   _hFile = INVALID_HANDLE_VALUE;

   LOGFONT     LF;
                                       
   memset(&LF,0,sizeof(LOGFONT));      // zero out structure
  
   LF.lfHeight  = 16;                  // request a 16-pixel-height font
   LF.lfWeight  = 700;                 // BOLD   
   LF.lfCharSet = RUSSIAN_CHARSET;
                       
   strcpy(LF.lfFaceName,"Verdana");    // request a face name

   VERIFY(_Font.CreateFontIndirect(&LF)); // create the font
}

/* ******************************************************************** **
** @@ C09Dlg::DoDataExchange()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(C09Dlg)
   DDX_Control(pDX, IDC_STT_CITY, m_City);
   DDX_Control(pDX, IDC_EDT_TEXT, m_Find);
   DDX_Control(pDX, IDC_RB_PHONE, m_Phone);
   DDX_Control(pDX, IDC_RB_NAME, m_Name);
   DDX_Control(pDX, IDC_RB_ADDR, m_Addr);
   DDX_Control(pDX, IDC_LIST, m_List);
   //}}AFX_DATA_MAP
}

/* ******************************************************************** **
** @@ C09Dlg::MESSAGE_MAP()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

BEGIN_MESSAGE_MAP(C09Dlg, CDialog)
   //{{AFX_MSG_MAP(C09Dlg)
   ON_WM_DESTROY()
   ON_WM_SYSCOMMAND()
   ON_MESSAGE(WM_TRAY_NOTIFY, OnTrayNotify)
   ON_WM_WINDOWPOSCHANGING()
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
   ON_BN_CLICKED(IDC_RB_PHONE, OnRbPhone)
   ON_BN_CLICKED(IDC_RB_NAME, OnRbName)
   ON_BN_CLICKED(IDC_RB_ADDR, OnRbAddr)
   ON_EN_CHANGE(IDC_EDT_TEXT, OnChangeEdtText)
   ON_BN_CLICKED(IDC_BTN_FIRST, OnBtnFirst)
   ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
   ON_BN_CLICKED(IDC_BTN_PREV, OnBtnPrev)
   ON_BN_CLICKED(IDC_BTN_NEXT, OnBtnNext)
   ON_BN_CLICKED(IDC_BTN_DN, OnBtnDn)
   ON_BN_CLICKED(IDC_BTN_LAST, OnBtnLast)
   ON_WM_CLOSE()
   ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
   ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
   ON_NOTIFY(HDN_ITEMCLICK, 0, OnItemclickList)
   ON_WM_CTLCOLOR()
   ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
   ON_COMMAND(ID_APP_EXIT, OnAppExit)
   ON_COMMAND(IDM_UNHIDE, Restore)
   ON_CBN_CLOSEUP(IDC_CMB_DATABASE, OnCloseupCmbDatabase)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/* ******************************************************************** **
** @@ C09Dlg::OnInitDialog()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

BOOL C09Dlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // Add "About..." menu item to system menu.
   // IDM_ABOUTBOX must be in the system command range.
   ASSERT((IDM_ABOUT & 0xFFF0) == IDM_ABOUT);
   ASSERT(IDM_ABOUT < 0xF000);

   CMenu*      pSysMenu = GetSystemMenu(FALSE);

   if (pSysMenu)
   {  
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT,"&About...");
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING | MF_GRAYED, IDM_IMPORT, "&Import...");
      pSysMenu->AppendMenu(MF_STRING | MF_GRAYED, IDM_EXPORT, "&Export...");
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_EXIT, "E&xit");
   }

   // Set the icon for this dialog.  The framework does this automatically
   //  when the application's main window is not a dialog
   SetIcon(_hIcon,TRUE);       // Set big icon
   SetIcon(_hIcon,FALSE);      // Set small icon
   
   // TODO: Add extra initialization here
   CenterWindow();
   
   m_List.InsertColumn(0,"Num",  LVCFMT_LEFT,100,0);
   m_List.InsertColumn(1,"Key",  LVCFMT_LEFT,200,1);
   m_List.InsertColumn(2,"Value",LVCFMT_LEFT,250,2);
   m_List.InsertColumn(3,"Apx1", LVCFMT_LEFT,100,3);
   m_List.InsertColumn(4,"Apx2", LVCFMT_LEFT,100,4);

   DWORD    dwStyle = m_List.GetExtendedStyle();

   dwStyle |= LVS_OWNERDATA | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_FLATSB | LVS_EX_GRIDLINES;
   
   m_List.SetExtendedStyle(dwStyle);

   _bClosed = false;

   _DB.Resize(DB_INITIAL);
   _DB.Delta (DB_DELTA);

   _DB.SetSorter(CMP_ID);  // Unique field !
   _DB.QSort(); 
      
   #ifdef LOAD_DB_BIN
   LoadBinDB();
   #endif

   #ifdef LOAD_DB_TEXT
   LoadTextDB();
   #endif

   #ifdef SAVE_DB_BIN
   SaveBinDB();
   #endif

   #ifdef SAVE_DB_TEXT
   SaveTextDB();
   #endif

   _iTotal = _DB.Count();

   m_List.SetItemCountEx(_iTotal,LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);

   char     pszTemp[MAX_PATH];

   wsprintf(pszTemp,"%d",_iTotal);

   m_City.SetFont(&_Font,FALSE);

   SetDlgItemText(IDC_STT_COUNT,pszTemp);
   SetDlgItemText(IDC_STT_CITY,_pszCity);

   m_Name.SetCheck(BST_CHECKED);

   UpdateData(TRUE);

   OnRbName();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

/* ******************************************************************** **
** @@ C09Dlg::OnSysCommand()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
   switch (nID & 0xFFF0)
   {
      case SC_CLOSE:
      {
         _bVisible = false;
         ShowWindow(SW_HIDE);
         SetTrayIcon(this->m_hWnd,IDR_MAINFRAME,_hIcon,TITLE_09);
         break;
      }
      case IDM_EXIT:
      {
         _bVisible = false;
         PostMessage(WM_CLOSE);
         break;
      }
      case IDM_ABOUT:
      {
         CAboutDlg      dlg;
         dlg.DoModal();
         break;
      }
      case IDM_IMPORT:
      {
         OnImport();
         break;
      }
      case IDM_EXPORT:
      {
         OnExport();
         break;
      }
      default:
      {
         CDialog::OnSysCommand(nID,lParam);
      }
   }
}

/* ******************************************************************** **
** @@ C09Dlg::OnPaint()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void C09Dlg::OnPaint() 
{
   if (IsIconic())
   {
      CPaintDC dc(this); // device context for painting

      SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

      // Center icon in client rectangle
      int cxIcon = GetSystemMetrics(SM_CXICON);
      int cyIcon = GetSystemMetrics(SM_CYICON);

      CRect rect;
      
      GetClientRect(&rect);
      
      int x = (rect.Width()  - cxIcon + 1) / 2;
      int y = (rect.Height() - cyIcon + 1) / 2;

      // Draw the icon
      dc.DrawIcon(x,y,_hIcon);
   }
   else
   {
      CDialog::OnPaint();
   }
}

/* ******************************************************************** **
** @@ C09Dlg::OnQueryDragIcon()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

// The system calls this to obtain the cursor to display while the user drags
// the minimized window.

HCURSOR C09Dlg::OnQueryDragIcon()
{
   return (HCURSOR)_hIcon;
}

/* ******************************************************************** **
** @@ C09Dlg::OnClickList()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   *pResult = 0;

   if (!_DB.Count())
   {
      return;
   }

   NM_LISTVIEW*   pNMListView = (NM_LISTVIEW*)pNMHDR;
   
   _iCurrent = pNMListView->iItem;
}
      

/* ******************************************************************** **
** @@ C09Dlg::OnDblclkList()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   *pResult = 0;

   if (!_DB.Count())
   {
      return;
   }

   if (OnMenuCopy())
   {
      MessageBox("Запись скопирована в буфер обмена.","Копирование",MB_OK | MB_ICONINFORMATION);
   }
}

/* ******************************************************************** **
** @@ C09Dlg::OnRclickList()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   *pResult = 0;

   if (!_DB.Count())
   {
      return;
   }

   NM_LISTVIEW*   pNMListView = (NM_LISTVIEW*)pNMHDR;
   
   _iCurrent = pNMListView->iItem;

   if (OnMenuRCopy(pNMListView->iSubItem))
   {
      MessageBox("Поле скопировано в буфер обмена.","Копирование",MB_OK | MB_ICONINFORMATION);
   }
}

/* ******************************************************************** **
** @@ C09Dlg::Switcher()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::Switcher()
{
   if (_Selected == _KeepSelected)
   {
      return;
   }

   if (!_DB.Count())
   {
      return;
   }

   _KeepSelected = _Selected;

   CWaitCursor    Waiter;

   switch (_Selected)
   {
      case FS_PHONE:
      {
         m_Phone.SetCheck(1);
         m_Name.SetCheck (0);
         m_Addr.SetCheck (0);
         ModifyHeaderItems(0);
         _DB.SetSorter(CMP_ID); 
         break;
      }
      case FS_NAME:
      {
         m_Phone.SetCheck(0);
         m_Name.SetCheck (1);
         m_Addr.SetCheck (0);
         ModifyHeaderItems(1);
         _DB.SetSorter(CMP_Key);   // Not Unique
         break;
      }
      case FS_ADDR:
      {
         m_Phone.SetCheck(0);
         m_Name.SetCheck (0);
         m_Addr.SetCheck (1);
         ModifyHeaderItems(2);
         _DB.SetSorter(CMP_Value);   // Not Unique
         break;
      }
      default:
      {
         return;
      }
   }

   _DB.QSort(); 

   _iCurrent = 0;    // Reset !

   SetDlgItemText(IDC_EDT_TEXT,"");    // Reset !

   m_List.RedrawWindow();

   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);

   Waiter.Restore();
}

/* ******************************************************************** **
** @@ C09Dlg::OnRbPhone()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnRbPhone() 
{
   _Selected = FS_PHONE;

   Switcher();
}

/* ******************************************************************** **
** @@ C09Dlg::OnRbName()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnRbName() 
{
   _Selected = FS_NAME;

   Switcher();
}

/* ******************************************************************** **
** @@ C09Dlg::OnRbAddr()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnRbAddr() 
{
   _Selected = FS_ADDR;

   Switcher();
}

/* ******************************************************************** **
** @@ C09Dlg::OnChangeEdtText()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnChangeEdtText() 
{
   if (!_DB.Count())
   {
      return;
   }
   
   GetDlgItemText(IDC_EDT_TEXT,_sFind);

   if (_sFind.IsEmpty())
   {
      m_List.SetItemState (0,LVIS_SELECTED,LVIS_SELECTED);
      m_List.EnsureVisible(0,FALSE);
      return;
   }
   
   switch (_Selected)
   {
      case FS_NAME:
      {
         SearchName();
         break;
      }
      case FS_PHONE:
      {
         SearchPhone();
         break;
      }
      case FS_ADDR:
      {
         SearchAddr();
         break;
      }
   }
}

/* ******************************************************************** **
** @@ C09Dlg::OnBtnFirst()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnBtnFirst() 
{
   _iCurrent = 0;

   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);
}

/* ******************************************************************** **
** @@ C09Dlg::OnBtnUp()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnBtnUp() 
{
   int   Cnt = m_List.GetCountPerPage();

   _iCurrent -= Cnt;
   
   if (_iCurrent < 0)    
   {
      _iCurrent += _iTotal;
   }

   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);
}

/* ******************************************************************** **
** @@ C09Dlg::OnBtnPrev()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnBtnPrev() 
{
   --_iCurrent;
   
   if (_iCurrent < 0)    
   {
      _iCurrent += _iTotal;
   }

   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);
}

/* ******************************************************************** **
** @@ C09Dlg::OnBtnNext()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnBtnNext() 
{
   ++_iCurrent;

   _iCurrent %= _iTotal;

   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);
}

/* ******************************************************************** **
** @@ C09Dlg::OnBtnDn()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnBtnDn() 
{
   int   Cnt = m_List.GetCountPerPage();

   _iCurrent += Cnt;

   _iCurrent %= _iTotal;

   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);
}

/* ******************************************************************** **
** @@ C09Dlg::OnBtnLast()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnBtnLast() 
{
   _iCurrent = _iTotal - 1;

   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);
}

/* ******************************************************************** **
** @@ C09Dlg::OnInitDialog()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::ModifyHeaderItems(int iArrowPos)
{
   if (_bClosed)
   {
      // Don't create imaje list !
      return;
   }

   // create image list for header items
   if (!_pImageList)
   {
      _pImageList = new CImageList();

      ASSERT(_pImageList != NULL); 

      if (!_pImageList)
      {
         return;
      }

      C09App*    pApp = (C09App*)AfxGetApp();

      _pImageList->Create(16,16,ILC_COLOR24 ,2,0);
      _pImageList->Add(pApp->LoadIcon(IDI_ARROW));
      _pImageList->Add(pApp->LoadIcon(IDI_EMPTY));

      // Retrieve embedded header control
      CHeaderCtrl*      pHdrCtrl = m_List.GetHeaderCtrl();

      pHdrCtrl->SetImageList(_pImageList);
   }

   CHeaderCtrl*      pHdrCtrl = m_List.GetHeaderCtrl();

   // Set Icon to each header item
   int      iCnt = pHdrCtrl->GetItemCount();

   HD_ITEM     Item;

   TCHAR    pszText[MAX_PATH + 1];

   Item.mask       = HDI_TEXT |  HDI_IMAGE | HDI_FORMAT;
   Item.pszText    = pszText;
   Item.cchTextMax = MAX_PATH;

   for (int ii = 0; ii < iCnt; ++ii)
   {
      pHdrCtrl->GetItem(ii,&Item);

      Item.iImage = ii == iArrowPos  ?  0  :  1;
      Item.fmt    = HDF_LEFT | HDF_BITMAP_ON_RIGHT | HDF_BITMAP | HDF_IMAGE | HDF_STRING;
      
      pHdrCtrl->SetItem(ii,&Item);
   }
}

/* ******************************************************************** **
** @@ C09Dlg::OnDestroy()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::OnDestroy() 
{
   CDialog::OnDestroy();
   
   ResetTrayIcon(this->m_hWnd,IDR_MAINFRAME);

   _bClosed = true;
   
   Cleanup();
}

/* ******************************************************************** **
** @@ C09Dlg::OnClose()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::OnClose() 
{
   _bClosed = true;

   Cleanup();

   CDialog::OnClose();
}

/* ******************************************************************** **
** @@ C09Dlg::Cleanup()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::Cleanup()
{
   _Font.DeleteObject();

   if (_hFile != INVALID_HANDLE_VALUE)
   {
      CloseHandle(_hFile);
      _hFile = INVALID_HANDLE_VALUE;
   }

   CWaitCursor    Waiter;
     
   if (_pImageList)
   {
      delete _pImageList;
      _pImageList = NULL;
   }

   DWORD    dwCnt = _DB.Count();

   // Should be Int !!
   for (int ii = dwCnt - 1; ii >= 0; --ii)
   {
      ListLineEntry*    pItem = (ListLineEntry*)_DB.At(ii);

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
         _DB.RemoveAt(ii);
         delete pItem;
         pItem = NULL;
      }
   }
}

/* ******************************************************************** **
** @@ C09Dlg::KeepItem()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool C09Dlg::KeepItem
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
** @@ C09Dlg::RestoreItem()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool C09Dlg::RestoreItem
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
** @@ C09Dlg::KeepBString()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

bool C09Dlg::KeepBString
(
   const char* const       pStr
)
{
   BYTE     bySize = (BYTE)strlen(pStr);         

   if (!KeepItem(&bySize,sizeof(BYTE)))
   {
      return false;
   }
   
   return KeepItem(pStr,sizeof(char) * bySize);
}

/* ******************************************************************** **
** @@ C09Dlg::RestoreBString()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

bool C09Dlg::RestoreBString
(
   char*       pszStr
)
{
   BYTE     bySize = 0;

   if (!RestoreItem(&bySize,sizeof(BYTE)))
   {
      return false;
   }
   
   if (!RestoreItem(pszStr,sizeof(char) * bySize))
   {
      return false;
   }

   pszStr[bySize] = 0;     // ASCIIZ

   return true;
}

/* ******************************************************************** **
** @@ C09Dlg::SaveBinDB()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

#ifdef _DEBUG
#ifdef SAVE_DB_BIN
bool C09Dlg::SaveBinDB()
{
   CWaitCursor    Waiter;

   _hFile = CreateFile(DB_NAME);

   CloseHandle(_hFile);
   _hFile = INVALID_HANDLE_VALUE;

   _hFile = OpenFileReadWrite(DB_NAME);

   _DB.SetFileHandle(_hFile);

   DWORD    dwHash = 0;

   KeepItem(&dwHash,sizeof(DWORD));

   // Save the Vectors
   if (!_DB.Save()) 
   {
      return false;
   }
                  
   DWORD    dwSigLo = 0x09DB0100;
   DWORD    dwSigHi = 0x47F35E9F;
   
   KeepItem(&dwSigLo,sizeof(DWORD));
   KeepItem(&dwSigHi,sizeof(DWORD));

   KeepBString(CITY_LABEL);
   KeepItem(GUZIS_MAP,GUZIS_MAP_SIZE);

   #ifdef REPORT_DB_STAT
   FILE*    pOut = fopen("jumbo.txt","wt");
   #endif

   Guzis    Packer;

   Packer.SetMap((BYTE*)GUZIS_MAP);

   DWORD    dwCnt = _DB.Count();

   KeepItem(&dwCnt,sizeof(DWORD));

   for (DWORD ii = 0; ii < dwCnt; ++ii)
   {
      LIST_LINE_ENTRY*      pItem = (LIST_LINE_ENTRY*)_DB.At(ii);

      if (pItem)
      {
         KeepItem(&pItem->_iNum,sizeof(int));

         // Create Jumbo Text Record
         char     pszSrc[MAX_PATH];
         char     pszDst[MAX_PATH];

         memset(pszSrc,0,MAX_PATH);
         memset(pszDst,0,MAX_PATH);

         void*    pDest = pszDst;

         DWORD    dwDstSize = 0;

         wsprintf(pszSrc,"%s@%s@%s@%s",pItem->_pszName,pItem->_sValue,pItem->_sAppendix1,pItem->_sAppendix2);
         
         #ifdef SAVE_NOT_PACKED
         KeepBString(pszSrc);
         #else
         int   iSrcLen = strlen(pszSrc);

         for (int ii = 0; ii < iSrcLen; ++ii)
         {
            pszSrc[ii] = psz_XLAT_Direct[(BYTE)pszSrc[ii]];
         }
         
         #ifdef REPORT_DB_STAT
         fprintf(pOut,"%s\n",pszSrc);
         #endif

         Packer.Pack(pszSrc,pDest,iSrcLen,dwDstSize);

         KeepItem(&dwDstSize,sizeof(BYTE));
         KeepItem(pDest,dwDstSize);
         #endif
      }
   }

   #ifdef REPORT_DB_STAT
   fclose(pOut);
   pOut = NULL;
   #endif
       
   CloseHandle(_hFile);
   _hFile = INVALID_HANDLE_VALUE;

   MMF      MF;

   if (!MF.OpenReadWrite(DB_NAME))
   {
      // Error !
      return false;
   }

   BYTE*    pBuf   = MF.Buffer();
   DWORD    dwSize = MF.Size();

   *(DWORD*)pBuf = SuperFastHash(pBuf + sizeof(DWORD),dwSize - sizeof(DWORD));

   MF.Close();

   return true;
}
#endif
#endif

/* ******************************************************************** **
** @@ C09Dlg::LoadBinDB()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

#ifdef LOAD_DB_BIN
bool C09Dlg::LoadBinDB()
{
   char     pszMap[GUZIS_MAP_SIZE + 1];

   memset(pszMap,0,sizeof(pszMap));

   CWaitCursor    Waiter;

   _hFile = OpenFileReadOnly(DB_NAME);

   _DB.SetFileHandle(_hFile);

   DWORD    dwHash = 0;

   RestoreItem(&dwHash,sizeof(DWORD));

   // Load the Vectors
   if (!_DB.Load()) 
   {
      return false;
   }

   _DB.Reset(); // Reset Counter !

   DWORD    dwSigLo = 0;
   DWORD    dwSigHi = 0;
   
   RestoreItem(&dwSigLo,sizeof(DWORD));
   RestoreItem(&dwSigHi,sizeof(DWORD));

   RestoreBString(_pszCity);
   RestoreItem(pszMap,GUZIS_MAP_SIZE);

   Guzis    Packer;

   Packer.SetMap((BYTE*)pszMap);

   DWORD    dwCnt = 0;

   RestoreItem(&dwCnt,sizeof(int));

   for (DWORD ii = 0; ii < dwCnt; ++ii)
   {
      ListLineEntry*    pItem = new ListLineEntry;

      if (!pItem)
      {
         // Error 
         CloseHandle(_hFile);
         _hFile = INVALID_HANDLE_VALUE;
         return false;
      }

      RestoreItem(&pItem->_iNum,sizeof(int));

      // Create Jumbo Text Record
      char     pszSrc[MAX_PATH];
      char     pszDst[MAX_PATH];

      void*    pDest = pszDst;

      int      iSrcLen   = 0;
      DWORD    dwDstSize = 0;

      RestoreItem(&iSrcLen,sizeof(BYTE));
      RestoreItem(pszSrc,iSrcLen);

      Packer.Unpack(pszSrc,pDest,iSrcLen,dwDstSize);

      pszDst[dwDstSize] = 0;   // ASCIIZ

      for (int ii = 0; ii < (int)dwDstSize; ++ii)
      {
         pszDst[ii] = psz_XLAT_Reverse[(BYTE)pszDst[ii]];
      }

      bool  bFirst = false;
      bool  bNext  = false;
      bool  bLast  = false;

      char*    pszFirst = strchr(pszDst,      '@');
      char*    pszNext  = strchr(pszFirst + 1,'@');
      char*    pszLast  = strchr(pszNext  + 1,'@');

      // Breaks
      if (pszFirst)
      {
         bFirst    = true;
         *pszFirst = 0;
      }

      if (pszNext)
      {
         bNext    = true;
         *pszNext = 0;
      }

      if (pszLast)
      {
         bLast    = true;
         *pszLast = 0;
      }

      pItem->_sKey = pszDst;

      if (bFirst)
      {
         pItem->_sValue = pszFirst + 1;
      }

      if (bNext)
      {
         pItem->_sAppendix1 = pszNext + 1;
      }

      if (bLast)
      {
         pItem->_sAppendix2 = pszLast + 1;
      }

      if (_DB.Insert(pItem) == -1)
      {
         delete pItem;
         pItem = NULL;
      }
   }

   CloseHandle(_hFile);
   _hFile = INVALID_HANDLE_VALUE;

   return true;
}
#endif

/* ******************************************************************** **
** @@ C09Dlg::LoadTextDB()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

#ifdef _DEBUG
#ifdef LOAD_DB_TEXT
bool C09Dlg::LoadTextDB()
{
   CWaitCursor    Waiter;

   FILE*    pIn  = fopen("db.tab","rt");

   #ifdef _DEBUG 
   FILE*    pErr = fopen("db_error.txt", "wt");
   FILE*    pOut = fopen("db_insert.txt","wt");
   #endif

   if (!pIn)
   {
      return false;
   }

   char     pszLine[MAX_PATH + 1];

   int   iCnt = 0;

   // Read a String from the file to Buf
   while (fgets((char*)pszLine,sizeof(pszLine),pIn))
   {
      pszLine[MAX_PATH] = 0;  // Ensure ASCIIZ !

      DWORD    dwEOL = strcspn(pszLine,"\r\n");

      pszLine[dwEOL] = 0;  // Remove EOL chars

      char     pszPhone[MAX_DESCRIPTION_SIZE + 1];
      char     pszName [MAX_DESCRIPTION_SIZE + 1];
      char     pszAdr1 [MAX_DESCRIPTION_SIZE + 1];
      char     pszAdr2 [MAX_DESCRIPTION_SIZE + 1];
      char     pszAdr3 [MAX_DESCRIPTION_SIZE + 1];

      char*    pText = pszLine;     // Prepare
         
      // Phone
      pText = (char*)AcquireToken(pText,PHONE_BOOK_DELIMITER,pszPhone,MAX_DESCRIPTION_SIZE);
      // Name
      pText = (char*)AcquireToken(pText,PHONE_BOOK_DELIMITER,pszName,MAX_DESCRIPTION_SIZE);
      // Adr1
      pText = (char*)AcquireToken(pText,PHONE_BOOK_DELIMITER,pszAdr1,MAX_DESCRIPTION_SIZE);
      // Adr2
      pText = (char*)AcquireToken(pText,PHONE_BOOK_DELIMITER,pszAdr2,MAX_DESCRIPTION_SIZE);
      // Adr3
      pText = (char*)AcquireToken(pText,PHONE_BOOK_DELIMITER,pszAdr3,MAX_DESCRIPTION_SIZE);

      int   iPhone = atoi(pszPhone);

      if (iPhone)
      {
         LIST_LINE_ENTRY*     pItem = new LIST_LINE_ENTRY;

         if (!pItem)
         {
            return false;
         }

         memset(pItem,0,sizeof(LIST_LINE_ENTRY));

         pItem->_iNum = iPhone;

         strncpy(pItem->_pszName,pszName,MAX_NAME_SIZE);
         pItem->_pszName[MAX_NAME_SIZE] = 0; // ASCIIZ

         #ifdef REMOVE_REDUNDANT_SPACE 
         int iLen = strlen(pItem->_pszName);

         if ((pItem->_pszName[iLen - 2] == 0x20) && (pItem->_pszName[iLen - 4] == 0x20))
         {
            if ((pItem->_pszName[iLen - 1] >= 'А') && (pItem->_pszName[iLen - 1] <= 'Я'))
            {
               if ((pItem->_pszName[iLen - 3] >= 'А') && (pItem->_pszName[iLen - 3] <= 'Я'))
               {
                  pItem->_pszName[iLen - 2] = pItem->_pszName[iLen - 1];
                  pItem->_pszName[iLen - 1] = 0; // ASCIIZ
               }
            }
         }
         #endif

         strncpy(pItem->_sValue,pszAdr1,MAX_ADR1_SIZE);
         pItem->_sValue[MAX_ADR1_SIZE] = 0; // ASCIIZ

         strncpy(pItem->_sAppendix1,pszAdr2,MAX_ADR2_SIZE);
         pItem->_sAppendix1[MAX_ADR2_SIZE] = 0; // ASCIIZ

         strncpy(pItem->_sAppendix2,pszAdr3,MAX_ADR3_SIZE);
         pItem->_sAppendix2[MAX_ADR3_SIZE] = 0; // ASCIIZ

         if (_DB.Insert(pItem) != -1)
         {
            #ifdef _DEBUG 
            fprintf(pOut,"%6d@%s@%s@%s@%s\n",pItem->_iNum,pItem->_pszName,pItem->_sValue,pItem->_sAppendix1,pItem->_sAppendix2); 
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
#endif
#endif

/* ******************************************************************** **
** @@ C09Dlg::SaveTextDB()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

#ifdef _DEBUG
#ifdef SAVE_DB_TEXT
bool C09Dlg::SaveTextDB()
{
   CWaitCursor    Waiter;

   FILE*    pOut  = fopen("db.tab","wt");

   if (!pOut)
   {
      return false;
   }

   char     pszLine[MAX_PATH];

   DWORD    dwCnt = _DB.Count();

   for (DWORD ii = 0; ii < dwCnt; ++ii)
   {
      LIST_LINE_ENTRY*      pItem = (LIST_LINE_ENTRY*)_DB.At(ii);

      if (pItem)
      {
         fprintf(pOut,"%6d@%s@%s@%s@%s\n",pItem->_iNum,pItem->_pszName,pItem->_sValue,pItem->_sAppendix1,pItem->_sAppendix2); 
      }
   }

   fclose(pOut);
   pOut = NULL;

   return true;
}
#endif
#endif

/* ******************************************************************** **
** @@ C09Dlg::OnGetdispinfoList()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   *pResult = 0;

   LV_DISPINFO*      pDispInfo = (LV_DISPINFO*)pNMHDR;

   LV_ITEM*          pItem = &(pDispInfo)->item;

   int      iIndex = pItem->iItem;

   if (pItem->mask & LVIF_TEXT)
   {
      ListLineEntry*    pEntry = (ListLineEntry*)_DB.At(iIndex);

      if (pEntry)
      {
         switch (pItem->iSubItem)
         {
            case 0: 
            {
               wsprintf(pItem->pszText,"%d",pEntry->_iNum);
               break;
            }
            case 1: 
            {
               strcpy(pItem->pszText,(LPCTSTR)pEntry->_sKey);
               break;
            }
            case 2: 
            {
               strcpy(pItem->pszText,(LPCTSTR)pEntry->_sValue);
               break;
            }
            case 3: 
            {
               strcpy(pItem->pszText,(LPCTSTR)pEntry->_sAppendix1);
               break;
            }
            case 4: 
            {
               if (pEntry->_sAppendix2)
               {
               strcpy(pItem->pszText,(LPCTSTR)pEntry->_sAppendix2);
               }
               break;
            }
         }
      }
   }
}

/* ******************************************************************** **
** @@ C09Dlg::SearchName()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::SearchName()
{
   DWORD    dwCnt = _DB.Count();

   int   iLen = _sFind.GetLength();

   for (DWORD ii = 0; ii < dwCnt; ++ii)
   {
      ListLineEntry*      pItem = (ListLineEntry*)_DB.At(ii);

      if (pItem)
      {
         CString     sFragment = pItem->_sKey;

         if (sFragment.GetLength() > iLen)
         {
            sFragment.SetAt(iLen,0);   // Truncate
         }

         // Case insensitive !!
         if (!sFragment.CompareNoCase(_sFind)) 
         {
            _iCurrent = ii;
            Go();
            return;
         }
      }
   }

   MessageBeep(MB_ICONHAND);
   _sFind.SetAt(_sFind.GetLength() - 1,0);

   // Dirty trick to set Cursor beyond of the text !
   m_Find.SetSel(0,-1,FALSE);
   m_Find.ReplaceSel((LPCTSTR)_sFind,TRUE);
}

/* ******************************************************************** **
** @@ C09Dlg::SearchPhone()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::SearchPhone()
{           
   char     pszPattern[MAX_PATH + 1];

   strncpy(pszPattern,(LPCTSTR)_sFind,MAX_PATH);

   DWORD    dwCnt = _DB.Count();

   int   iLen = strlen(pszPattern);

   for (DWORD ii = 0; ii < dwCnt; ++ii)
   {
      ListLineEntry*    pItem = (ListLineEntry*)_DB.At(ii);

      if (pItem)
      {
         char     pszPhone[MAX_PATH + 1];

         wsprintf(pszPhone,"%d",pItem->_iNum);

         // Case insensitive !!
         if (!_strnicmp(pszPhone,pszPattern,iLen))
         {
            _iCurrent = ii;
            Go();
            return;
         }
      }
   }

   MessageBeep(MB_ICONHAND);
   _sFind.SetAt(_sFind.GetLength() - 1,0);

   // Dirty trick to set Cursor beyond of the text !
   m_Find.SetSel(0,-1,FALSE);
   m_Find.ReplaceSel((LPCTSTR)_sFind,TRUE);
}

/* ******************************************************************** **
** @@ C09Dlg::SearchAddr()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::SearchAddr()
{
   DWORD    dwCnt = _DB.Count();

   int   iLen = strlen((LPCTSTR)_sFind);

   for (DWORD ii = 0; ii < dwCnt; ++ii)
   {
      ListLineEntry*    pItem = (ListLineEntry*)_DB.At(ii);

      if (pItem)
      {
         CString     sFragment = pItem->_sValue;

         if (sFragment.GetLength() > iLen)
         {
            sFragment.SetAt(iLen,0);   // Truncate
         }

         // Case insensitive !!
         if (!sFragment.CompareNoCase(_sFind)) 
         {
            _iCurrent = ii;
            Go();
            return;
         }
      }
   }

   MessageBeep(MB_ICONHAND);
   _sFind.SetAt(_sFind.GetLength() - 1,0);

   // Dirty trick to set Cursor beyond of the text !
   m_Find.SetSel(0,-1,FALSE);
   m_Find.ReplaceSel((LPCTSTR)_sFind,TRUE);
}

/* ******************************************************************** **
** @@ C09Dlg::ClearSelection()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::ClearSelection()
{
   int      iCount = m_List.GetSelectedCount();
   int      iIndex = -1;

   // Update all of the selected items.
   if (iCount > 0)
   {
      for (int ii = 0; ii < iCount; ++ii)
      {
         iIndex = m_List.GetNextItem(iIndex,LVNI_SELECTED);
         ASSERT(iIndex != -1);
         m_List.SetItemState(iIndex,0,LVIS_SELECTED);
      }
   }
}

/* ******************************************************************** **
** @@ C09Dlg::Go()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : 
** ******************************************************************** */

void C09Dlg::Go()
{
   m_List.SetItemState (_iCurrent,LVIS_SELECTED,LVIS_SELECTED);
   m_List.EnsureVisible(_iCurrent,FALSE);

   m_List.SetSelectionMark(_iCurrent);
}

/* ******************************************************************** **
** @@ C09Dlg::OnMenuRCopy()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool C09Dlg::OnMenuRCopy(int iField)
{
   if (!_DB.Count())
   {
      return false;
   }

   int      iSelected = m_List.GetSelectedCount();

   ASSERT(iSelected != -1);

   if (iSelected <= 0)
   {
      MessageBox("Не выбрана запись!","Операция невозможна",MB_OK | MB_ICONSTOP);
      return false;         
   }

   if (iField < 0)
   {
      MessageBox("Не выбрано поле!","Операция невозможна",MB_OK | MB_ICONSTOP);
      return false;         
   }

   POSITION    Pos = m_List.GetFirstSelectedItemPosition();

   if (!Pos)
   {
      MessageBox("Не выбрана запись!","Операция невозможна",MB_OK | MB_ICONSTOP);
      return false;         
   }
   
   CMemFile    MemFile;

   int      iIndex = m_List.GetNextSelectedItem(Pos);

   ListLineEntry*    pItem = (ListLineEntry*)_DB.At(iIndex);

   char     pszTemp[MAX_PATH + 1];

   wsprintf(pszTemp,TRAY_HELP_SYSTEM"%s",_pszCity);

   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);

   memset(pszTemp,0,  MAX_PATH);
   memset(pszTemp,'-',HYPHEN_LINE_SIZE);
 
   MemFile.Write(pszTemp,HYPHEN_LINE_SIZE);
   MemFile.Write("\r\n",2);
    
   switch (iField)
   {
      case 0:
      {
         wsprintf(pszTemp,"%d",pItem->_iNum);

         MemFile.Write(pszTemp,strlen(pszTemp));
         MemFile.Write("\r\n",2);
         break;
      }
      case 1:
      {
         MemFile.Write((LPCTSTR)pItem->_sKey,pItem->_sKey.GetLength());
         MemFile.Write("\r\n",2);
         break;
      }
      case 2:
      {
         MemFile.Write((LPCTSTR)pItem->_sValue,pItem->_sValue.GetLength());
         MemFile.Write("\r\n",2);
         break;
      }
      case 3:
      {
         MemFile.Write((LPCTSTR)pItem->_sAppendix1,pItem->_sAppendix1.GetLength());
         MemFile.Write("\r\n",2);
         break;
      }
      case 4:
      {
         MemFile.Write((LPCTSTR)pItem->_sAppendix2,pItem->_sAppendix2.GetLength());
         MemFile.Write("\r\n",2);
         break;
      }
      default:
      {
         break;
      }
   }
   
   memset(pszTemp,0,  MAX_PATH);
   memset(pszTemp,'-',HYPHEN_LINE_SIZE);
   
   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);
    
   wsprintf(pszTemp,MY_COPYRIGHT);

   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);

   DWORD    dwSize = MemFile.GetLength();

   BYTE*    pBuf = MemFile.Detach();

   CopyData(pBuf,dwSize);

   free(pBuf);

   MemFile.Close();
      
   return true;
}

/* ******************************************************************** **
** @@ C09Dlg::OnMenuCopy()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool C09Dlg::OnMenuCopy()
{
   if (!_DB.Count())
   {
      return false;
   }

   int      iSelected = m_List.GetSelectedCount();

   ASSERT(iSelected != -1);

   if (iSelected <= 0)
   {
      MessageBox("Не выбрана запись!","Операция невозможна",MB_OK | MB_ICONSTOP);
      return false;         
   }

   POSITION    Pos = m_List.GetFirstSelectedItemPosition();

   if (!Pos)
   {
      MessageBox("Не выбрана запись!","Операция невозможна",MB_OK | MB_ICONSTOP);
      return false;         
   }
   
   CMemFile    MemFile;

   int      iIndex = m_List.GetNextSelectedItem(Pos);

   ListLineEntry*    pItem = (ListLineEntry*)_DB.At(iIndex);

   char     pszTemp[MAX_PATH + 1];

   wsprintf(pszTemp,TRAY_HELP_SYSTEM"%s",_pszCity);

   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);

   memset(pszTemp,0,  MAX_PATH);
   memset(pszTemp,'-',HYPHEN_LINE_SIZE);
   
   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);

   wsprintf(pszTemp,"%d",pItem->_iNum);

   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);

   MemFile.Write((LPCTSTR)pItem->_sKey,pItem->_sKey.GetLength());
   MemFile.Write("\r\n",2);

   MemFile.Write((LPCTSTR)pItem->_sValue,pItem->_sValue.GetLength());
   MemFile.Write("\r\n",2);

   MemFile.Write((LPCTSTR)pItem->_sAppendix1,pItem->_sAppendix1.GetLength());
   MemFile.Write("\r\n",2);

   MemFile.Write((LPCTSTR)pItem->_sAppendix2,pItem->_sAppendix2.GetLength());
   MemFile.Write("\r\n",2);

   memset(pszTemp,0,  MAX_PATH);
   memset(pszTemp,'-',HYPHEN_LINE_SIZE);
   
   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);
    
   wsprintf(pszTemp,MY_COPYRIGHT);

   MemFile.Write(pszTemp,strlen(pszTemp));
   MemFile.Write("\r\n",2);

   DWORD    dwSize = MemFile.GetLength();

   BYTE*    pBuf = MemFile.Detach();

   CopyData(pBuf,dwSize);

   free(pBuf);

   MemFile.Close();
      
   return true;
}

/* ******************************************************************** **
** @@ C09Dlg::CopyData()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

bool C09Dlg::CopyData(const BYTE* const pBuf,DWORD dwSize)
{
   if (!OpenClipboard())
   { 
      return FALSE; 
   }

   EmptyClipboard(); 

   // Allocate a global memory object for the text. 
   HGLOBAL     hMem = GlobalAlloc(GMEM_MOVEABLE,dwSize); 

   if (!hMem) 
   { 
      CloseClipboard(); 
      return false; 
   } 

   // Lock the handle and copy the text to the buffer. 
   LPVOID      pMem = GlobalLock(hMem); 

   memcpy(pMem,pBuf,dwSize); 
   
   GlobalUnlock(hMem); 

   // Place the handle on the clipboard. 
   SetClipboardData(CF_TEXT,hMem); 

   CloseClipboard(); 
   GlobalFree(hMem);

   return true;
}

/* ******************************************************************** **
** @@ C09Dlg::OnItemclickList()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::OnItemclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   *pResult = 0;

   // Q250614  !  HOWTO: Sort Items in a CListCtrl in Report View
   //
   // MFC in Visual C++ 6.0 has a problem with header notifications for the ListView control. Although a handler can be added, in the
   // current version it isn't called.
   //
   // The problem here is that the notification doesn't actually originate from the ListView control; instead, the Header control
   // created by the ListView sends the notification. The message map entry listed above does not work. The fix is simple, however,
   // since the Header control always has an ID of 0, the macro can be edited to work correctly

   NM_LISTVIEW*      pNMListView = (NM_LISTVIEW*)pNMHDR;

   switch(pNMListView->iItem)
   {
      case 0:
      {
         OnRbPhone();
         break;
      }
      case 1:
      {
         OnRbName();
         break;
      }
      case 2:
      {
         OnRbAddr();
         break;
      }
   }
}

/* ******************************************************************** **
** @@ C09Dlg::OnCtlColor()
** @  Copyrt :
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

HBRUSH C09Dlg::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor) 
{
   HBRUSH   hDefault = CDialog::OnCtlColor(pDC,pWnd,nCtlColor);

   switch (nCtlColor)
   {
      case CTLCOLOR_STATIC:
      {
         // HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
         // HBRUSH   hbr = CreateSolidBrush(RGB(161,188,154));

         // Are we painting the IDC_STT_CITY control? We can use
         // CWnd::GetDlgCtrlID() to perform the most efficient test.
         if (pWnd->GetDlgCtrlID() == IDC_STT_CITY)
         {
            GetDlgItem(IDC_STT_CITY)->RedrawWindow();

            // Set the text color to BLUE
            pDC->SetTextColor(RGB(0,0,255));
            pDC->SetBkMode(TRANSPARENT);

            // Return handle to our CBrush object
            return hDefault;
         }

         return hDefault;
      }
      default:
      {
         // Call the base class implementation first! Otherwise, it may
         // undo what we're trying to accomplish here.
         return hDefault;
      }
   }
}

/* ******************************************************************** **
** @@ C09Dlg::PreTranslateMessage()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

BOOL C09Dlg::PreTranslateMessage(MSG* pMsg) 
{  
   if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
   {  
      // Prevent <ESC> exit !
      return TRUE;
   }

   return CDialog::PreTranslateMessage(pMsg);
}

/* ******************************************************************** **
** @@ C09Dlg::OnTrayNotify()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

#pragma warning (disable: 4189)

LRESULT C09Dlg::OnTrayNotify(WPARAM wParam,LPARAM lParam)
{    
   // wParam - first message parameter of the callback message. 
   // lParam - second message parameter of the callback message. 
   switch (lParam) 
   {
      case WM_RBUTTONDOWN:
      {
         CMenu       menu;
         VERIFY(menu.LoadMenu(IDR_POPUPMENU));

         CMenu*   pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);

         POINT   pt;

         GetCursorPos (&pt);

         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,AfxGetMainWnd());
         break;
      }
      case WM_LBUTTONDOWN:
//      case WM_LBUTTONDBLCLK:
      {
         if (!_bVisible)  // Only if we're not already visible
         {
            Restore();
         }
   
         break;
      }
   }

   return 0; 
}

/* ******************************************************************** **
** @@ C09Dlg::Restore()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::Restore()
{  
   _bVisible = true;
   ShowWindow(SW_NORMAL);
   SetForegroundWindow();
   SetFocus();
}  

/* ******************************************************************** **
** @@ C09Dlg::SetTrayIcon()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

BOOL C09Dlg::SetTrayIcon(HWND hwnd,UINT uID,HICON hicon,LPSTR lpszTip)
{  
   // hwnd - handle to the window to receive callback messages. 
   // uID - identifier of the icon. 
   // hicon - handle to the icon to add. 
   // lpszTip - ToolTip text. 
   NOTIFYICONDATA tnid; 
 
   tnid.cbSize = sizeof(NOTIFYICONDATA); 
   tnid.hWnd   = hwnd; 
   tnid.uID    = uID; 
   tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
   tnid.hIcon  = hicon; 

   tnid.uCallbackMessage = WM_TRAY_NOTIFY; 

   if (lpszTip) 
   {
      lstrcpyn(tnid.szTip,lpszTip,sizeof(tnid.szTip)); 
   }
   else 
   {
      *tnid.szTip = 0; 
   } 
   
   BOOL    Res = Shell_NotifyIcon(NIM_ADD,&tnid); 
 
   if (hicon) 
   {
      DestroyIcon(hicon); 
   }

   return Res;
}

/* ******************************************************************** **
** @@ C09Dlg::ResetTrayIcon()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

BOOL C09Dlg::ResetTrayIcon(HWND hwnd,UINT uID)
{
   // hwnd - handle to the window that added the icon. 
   // uID  - identifier of the icon to delete. 
   NOTIFYICONDATA tnid; 

   tnid.cbSize = sizeof(NOTIFYICONDATA); 
   tnid.hWnd   = hwnd; 
   tnid.uID    = uID; 

   return Shell_NotifyIcon(NIM_DELETE,&tnid); 
}

/* ******************************************************************** **
** @@ C09Dlg::OnWindowPosChanging()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

// Now you need to override WM_WINDOWPOSCHANGING. 
// You might have to change your message filtering options 
// to have this message show up in the Class Wizard.
void C09Dlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
   CDialog::OnWindowPosChanging(lpwndpos);
      
   if (!_bVisible)
   {
      lpwndpos->flags &= ~SWP_SHOWWINDOW;
      SetTrayIcon(this->m_hWnd,IDR_MAINFRAME,_hIcon,TITLE_09);
   }
   
   CDialog::OnWindowPosChanging(lpwndpos);
}

/* ******************************************************************** **
** @@ C09Dlg::OnAppExit()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::OnAppExit() 
{  
   _bVisible = false;
   PostMessage(WM_CLOSE);
}

/* ******************************************************************** **
** @@ C09Dlg::OnImport()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::OnImport()
{
   CImport     Dlg;

   Dlg.SetParent(this);

   if (Dlg.DoModal() != IDOK)
   {
      return;
   }
}

/* ******************************************************************** **
** @@ C09Dlg::OnExport()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void C09Dlg::OnExport()
{
   if (!_DB.Count())
   {
      return;
   }

   DWORD    dwFlags =   OFN_EXPLORER      | 
                        OFN_ENABLESIZING  | 
                        OFN_CREATEPROMPT  | 
                        OFN_HIDEREADONLY  | 
                        OFN_NOCHANGEDIR   | 
                        OFN_OVERWRITEPROMPT;

   char     pszFilter[MAX_PATH] = "CSV (*.csv)|*.csv|"
                                  "TAB (*.tab)|*.tab|"
                                  "MAP (*.map)|*.map||";

   CFileDialog       Dlg(FALSE,NULL,NULL,dwFlags,pszFilter);

   if (Dlg.DoModal() == IDOK)
   {
      CString     sFile = Dlg.GetPathName();
   }
}

void C09Dlg::OnCloseupCmbDatabase() 
{
   // TODO: Add your control notification handler code here
}

/* ******************************************************************** **
** End of File
** ******************************************************************** */
