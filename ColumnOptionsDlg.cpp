// CColumnOptionsDlg.cpp : implementation file
//

#include "pch.h"
#include "4pp-task.h"
#include "afxdialogex.h"
#include "ColumnOptionsDlg.h"


// CColumnOptionsDlg dialog

IMPLEMENT_DYNAMIC(CColumnOptionsDlg, CDialogEx)

CColumnOptionsDlg::CColumnOptionsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLUMN_OPTIONS, pParent)
	, m_show{}
{

}

CColumnOptionsDlg::~CColumnOptionsDlg()
{
}

void CColumnOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHK_SCANNO, m_show[0]);
	DDX_Check(pDX, IDC_CHK_PT, m_show[1]);
	DDX_Check(pDX, IDC_CHK_CURRENT, m_show[2]);
	DDX_Check(pDX, IDC_CHK_THKNESS, m_show[3]);
	DDX_Check(pDX, IDC_CHK_TEMP, m_show[4]);
	DDX_Check(pDX, IDC_CHK_LOADCELL, m_show[5]);
	DDX_Check(pDX, IDC_CHK_RESISTANCE, m_show[6]);
	DDX_Check(pDX, IDC_CHK_TIMESTAMP, m_show[7]);
}


BEGIN_MESSAGE_MAP(CColumnOptionsDlg, CDialogEx)
END_MESSAGE_MAP()


// CColumnOptionsDlg message handlers
