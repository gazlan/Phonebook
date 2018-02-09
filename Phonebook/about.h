class CAboutDlg : public CDialog
{
   private:

      CFont                      _Font;

   public:

      CAboutDlg();

   // Dialog Data
   //{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_Title;
	CHyperLink	m_Web;
	CHyperLink	m_EMail;
	CString	m_Rich;
	//}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAboutDlg)
   protected:
   
      virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
   protected:
   //{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()
};
