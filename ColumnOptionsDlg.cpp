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
	, m_bShowScanNo(FALSE)
	, m_bShowPt(FALSE)
	, m_bShowCurrent(FALSE)
	, m_bShowThkness(FALSE)
	, m_bShowTemp(FALSE)
	, m_bShowLoadCell(FALSE)
	, m_bShowResistance(FALSE)
	, m_bShowTimestamp(FALSE)
{

}

CColumnOptionsDlg::~CColumnOptionsDlg()
{
}

void CColumnOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHK_SCANNO, m_bShowScanNo);
	DDX_Check(pDX, IDC_CHK_PT, m_bShowPt);
	DDX_Check(pDX, IDC_CHK_CURRENT, m_bShowCurrent);
	DDX_Check(pDX, IDC_CHK_THKNESS, m_bShowThkness);
	DDX_Check(pDX, IDC_CHK_TEMP, m_bShowTemp);
	DDX_Check(pDX, IDC_CHK_LOADCELL, m_bShowLoadCell);
	DDX_Check(pDX, IDC_CHK_RESISTANCE, m_bShowResistance);
	DDX_Check(pDX, IDC_CHK_TIMESTAMP, m_bShowTimestamp);
}


BEGIN_MESSAGE_MAP(CColumnOptionsDlg, CDialogEx)
END_MESSAGE_MAP()


// CColumnOptionsDlg message handlers
