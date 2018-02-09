#include "stdafx.h"

#include "resource.h"

#include "..\shared\hyperlink_maunder.h"

#include "about.h"

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CAboutDlg)
   DDX_Control(pDX, IDC_STT_TITLE, m_Title);
   DDX_Control(pDX, IDC_STT_WEB, m_Web);
   DDX_Control(pDX, IDC_STT_EMAIL, m_EMail);
   DDX_Text(pDX, IDC_RICH_ABOUT, m_Rich);
   DDV_MaxChars(pDX, m_Rich, 65535);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
   //{{AFX_MSG_MAP(CAboutDlg)
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
   //{{AFX_DATA_INIT(CAboutDlg)
   m_Rich = _T("");
   //}}AFX_DATA_INIT

   LOGFONT     LF;

   memset(&LF,0,sizeof(LOGFONT));

   LF.lfHeight = 36;
   LF.lfItalic = TRUE;
   LF.lfWeight = FW_BOLD;

   strcpy(LF.lfFaceName,"Arial");

   VERIFY(_Font.CreateFontIndirect(&LF));    // create the font
}

BOOL CAboutDlg::OnInitDialog() 
{
   CDialog::OnInitDialog();
   
   CenterWindow();

   m_Title.SetFont(&_Font);

   m_EMail.SetURL("mailto: gazlan@yandex.ru");
   m_Web.  SetURL("http://gazlan.narod.ru/");

   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnDestroy() 
{
   CDialog::OnDestroy();
   
   // Done with the font. Delete the font object.
   _Font.DeleteObject();
}
