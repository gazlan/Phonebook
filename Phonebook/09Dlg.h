/* ******************************************************************** **
** @@ 09
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

#ifndef _09DLG_H_
#define _09DLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* ******************************************************************** **
** @@ internal defines
** ******************************************************************** */

/* ******************************************************************** **
** @@ enum FIND_SELECTOR
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

enum FIND_SELECTOR
{
   FS_NONE,
   FS_PHONE,
   FS_NAME,
   FS_ADDR
};

/* ******************************************************************** **
** @@ class ListLineEntry
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

class ListLineEntry
{  
   public:

      int            _iNum;
      CString        _sKey;
      CString        _sValue;
      CString        _sAppendix1;
      CString        _sAppendix2;

   public:

      ListLineEntry()
      {
         _iNum = 0;

         _sKey       = _T("");
         _sValue     = _T("");
         _sAppendix1 = _T("");
         _sAppendix2 = _T("");
      }
};

/* ******************************************************************** **
** @@ class C09Dlg : public CDialog
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

class C09Dlg : public CDialog
{
   private:

      HANDLE                     _hFile;
      CString                    _sFind;
      FIND_SELECTOR              _Selected;
      FIND_SELECTOR              _KeepSelected;
      bool                       _bClosed;
      int                        _iCurrent;
      char                       _pszCity[MAX_PATH + 1];
      CFont                      _Font;
      bool                       _bVisible;
      HICON                      _hIcon;

   private:

      bool  KeepItem(const void* const pBuf,int iItemSize);
      bool  RestoreItem(void* const pBuf,int iItemSize);
      bool  KeepBString(const char* const pStr);
      bool  RestoreBString(char* const pStr);
      void  Switcher();

      bool  LoadBinDB();
      bool  SaveBinDB();

      bool  LoadTextDB();
      bool  SaveTextDB();

      void  ClearSelection();
      void  ModifyHeaderItems(int iArrowPos);
      void  SearchName();
      void  SearchPhone();
      void  SearchAddr();
      void  Cleanup();
      void  Go();
      bool  OnMenuCopy();
      bool  OnMenuRCopy(int iField);
      bool  CopyData(const BYTE* const pBuf,DWORD dwSize);

   public:

      int                        _iTotal;
      SortedVectorEx             _DB;

   // Construction
   public:
      
      C09Dlg(CWnd* pParent = NULL);   // standard constructor
      
// Dialog Data
   //{{AFX_DATA(C09Dlg)
   enum { IDD = IDD_09 };

   CStatic     m_City;
   CEdit       m_Find;
   CButton     m_Phone;
   CButton     m_Name;
   CButton     m_Addr;
   CListCtrl   m_List;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(C09Dlg)
   public:

   protected:

   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
   protected:

      CImageList*       _pImageList;

   // Generated message map functions
   //{{AFX_MSG(C09Dlg)
      afx_msg void OnDestroy();
      afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
      afx_msg LRESULT OnTrayNotify(WPARAM wParam,LPARAM lParam);
      afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnRbPhone();
   afx_msg void OnRbName();
   afx_msg void OnRbAddr();
   afx_msg void OnChangeEdtText();
   afx_msg void OnBtnFirst();
   afx_msg void OnBtnUp();
   afx_msg void OnBtnPrev();
   afx_msg void OnBtnNext();
   afx_msg void OnBtnDn();
   afx_msg void OnBtnLast();
   afx_msg void OnClose();
   afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnItemclickList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnUnhide();
   afx_msg void OnAppExit();
	afx_msg void OnCloseupCmbDatabase();
	//}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   private:

      BOOL     SetTrayIcon(HWND hwnd,UINT uID,HICON hicon,LPSTR lpszTip);
      BOOL     ResetTrayIcon(HWND hwnd, UINT uID);
      void     TrayEvent(WPARAM wParam,LPARAM lParam);
      void     Restore();
      void     OnImport();
      void     OnExport();
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
