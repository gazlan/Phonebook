; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImport
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "09.h"
LastPage=0

ClassCount=4
Class1=CAboutDlg
Class2=C09App
Class3=C09Dlg

ResourceCount=4
Resource1=IDD_09
Resource2=IDD_IMPORT
Resource3=IDD_ABOUTBOX (English (U.S.))
Class4=CImport
Resource4=IDR_POPUPMENU (English (U.S.))

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=about.h
ImplementationFile=about.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:C09App]
Type=0
BaseClass=CWinApp
HeaderFile=09.h
ImplementationFile=09.cpp

[CLS:C09Dlg]
Type=0
BaseClass=CDialog
HeaderFile=09Dlg.h
ImplementationFile=09Dlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=C09Dlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_09]
Type=1
Class=C09Dlg
ControlCount=18
Control1=IDC_EDT_TEXT,edit,1350631560
Control2=IDC_CMB_DATABASE,combobox,1478558019
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RB_PHONE,button,1342373897
Control5=IDC_RB_NAME,button,1342242825
Control6=IDC_RB_ADDR,button,1342177289
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STT_COUNT,static,1342308352
Control10=IDC_STT_CITY,static,1342308865
Control11=IDC_LIST,SysListView32,1350635917
Control12=IDC_BTN_FIRST,button,1342242816
Control13=IDC_BTN_UP,button,1342242816
Control14=IDC_BTN_PREV,button,1342242816
Control15=IDC_BTN_NEXT,button,1342242817
Control16=IDC_BTN_DN,button,1342242816
Control17=IDC_BTN_LAST,button,1342242816
Control18=IDC_STATIC,static,1342179843

[MNU:IDR_POPUPMENU (English (U.S.))]
Type=1
Class=C09Dlg
CommandCount=0

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_RICH_ABOUT,RICHEDIT,1352730692
Control2=IDC_STT_TITLE,static,1342308865
Control3=IDC_STT_EMAIL,static,1342308876
Control4=IDC_STT_WEB,static,1342308876
Control5=IDC_STT_LOGO,static,1342179854

[DLG:IDD_IMPORT]
Type=1
Class=CImport
ControlCount=25
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDT_FILE,edit,1350633600
Control3=IDC_BTN_FILE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDT_TITLE,edit,1350631553
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDT_FIELD1,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDT_FIELD2,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDT_FIELD3,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDT_FIELD4,edit,1350631552
Control15=IDC_CHK_HIDE4,button,1342242819
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDT_FIELD5,edit,1350631552
Control18=IDC_CHK_HIDE5,button,1342242819
Control19=IDC_STATIC,button,1342177287
Control20=IDC_REDT_ABOUT,RICHEDIT,1352736836
Control21=IDC_CHK_PASSWORD,button,1476460547
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDT_PASSWORD,edit,1484849280
Control24=IDC_CHK_LOCKED,button,1476460547
Control25=IDOK,button,1342242817

[CLS:CImport]
Type=0
HeaderFile=Import.h
ImplementationFile=Import.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CImport

