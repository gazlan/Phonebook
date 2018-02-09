#if !defined(AFX_IMPORT_H__A8D8B409_FE33_4DBE_A1DB_848C03AED83F__INCLUDED_)
#define AFX_IMPORT_H__A8D8B409_FE33_4DBE_A1DB_848C03AED83F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImport : public CDialog
{
   private:

      C09Dlg*              _pParent;

   public:

      SortedVectorEx       _Import;

   // Construction
   public:

      CImport(CWnd* pParent = NULL);   // standard constructor

      void SetParent(const C09Dlg* pParent);

   // Dialog Data
   //{{AFX_DATA(CImport)
      enum { IDD = IDD_IMPORT };
      BOOL	_bHide4;
      BOOL	_bHide5;
      BOOL	_bLock;
      BOOL	_bPassword;
      CString	_sField1;
      CString	_sField2;
      CString	_sField3;
      CString	_sField4;
      CString	_sField5;
      CString	_sFile;
      CString	_sPassword;
      CString	_sTitle;
      CString	_sAbout;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CImport)
   protected:

      virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
   protected:

   // Generated message map functions
   //{{AFX_MSG(CImport)
      virtual BOOL OnInitDialog();
      afx_msg void OnBtnFile();
      afx_msg void OnChkHide4();
      afx_msg void OnChkHide5();
      afx_msg void OnChkPassword();
      virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   private:

	   bool  LoadTabFile();
	   void  ImportTab();
      void  Cleanup();
      void  Jam(CString& rStr);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
