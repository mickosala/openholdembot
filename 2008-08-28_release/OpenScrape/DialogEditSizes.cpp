// DialogEditSizes.cpp : implementation file
//

#include "stdafx.h"
#include "DialogEditSizes.h"
#include "debug.h"


// CDlgEditSizes dialog

IMPLEMENT_DYNAMIC(CDlgEditSizes, CDialog)

CDlgEditSizes::CDlgEditSizes(CWnd* pParent /*=NULL*/) : CDialog(CDlgEditSizes::IDD, pParent)
{
    __SEH_SET_EXCEPTION_HANDLER
}

CDlgEditSizes::~CDlgEditSizes()
{
}

void CDlgEditSizes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_WIDTH, m_Width);
	DDX_Control(pDX, IDC_HEIGHT, m_Height);
}


BEGIN_MESSAGE_MAP(CDlgEditSizes, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgEditSizes::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgEditSizes message handlers

BOOL CDlgEditSizes::OnInitDialog()
{
	__SEH_HEADER

	int			i;
	CString		text;

	CDialog::OnInitDialog();

	SetWindowText(titletext.GetString());

	for (i=0; i<strings.GetSize(); i++)  m_Name.AddString(strings[i].GetString());
	m_Name.SelectString(-1, name.GetString());
	m_Name.SetWindowPos(NULL, 0, 0, 145, 300, SWP_NOMOVE | SWP_NOZORDER);

	text.Format("%d", width);
	m_Width.SetWindowText(text.GetString());
	text.Format("%d", height);
	m_Height.SetWindowText(text.GetString());

	m_Name.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

	__SEH_LOGFATAL("CDlgEditSizes::OnInitDialog : \n");
}

void CDlgEditSizes::OnBnClickedOk()
{
	__SEH_HEADER

	CString		text;

	if (m_Name.GetCurSel() != LB_ERR)
		m_Name.GetLBText(m_Name.GetCurSel(), name);
	else
		name = "";

	m_Width.GetWindowText(text);
	width = atoi(text.GetString());
	m_Height.GetWindowText(text);
	height = atoi(text.GetString());

	OnOK();

	__SEH_LOGFATAL("CDlgEditSizes::OnBnClickedOk : \n");
}
