#pragma once
#include "afxdialogex.h"


// CColumnOptionsDlg dialog

class CColumnOptionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColumnOptionsDlg)

public:
	CColumnOptionsDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CColumnOptionsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLUMN_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bShowScanNo;
	BOOL m_bShowPt;
	BOOL m_bShowCurrent;
	BOOL m_bShowThkness;
	BOOL m_bShowTemp;
	BOOL m_bShowLoadCell;
	BOOL m_bShowResistance;
	BOOL m_bShowTimestamp;
};
