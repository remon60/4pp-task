
// 4pp-taskDlg.h : header file
//

#pragma once

#include "DisplayList.h"

// CMy4pptaskDlg dialog
class CMy4pptaskDlg : public CDialogEx
{
// Construction
public:
	CMy4pptaskDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY4PPTASK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CDisplayList m_ListJobs;
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnDataPush();

	std::vector<Report> m_loadedRows;
	int m_pushIndex = 0;
};
