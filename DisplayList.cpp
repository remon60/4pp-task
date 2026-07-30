#include "pch.h"
#include "DisplayList.h"

BEGIN_MESSAGE_MAP(CDisplayList, CListCtrl)
END_MESSAGE_MAP()

BOOL CDisplayList::Init(CWnd* pParent, UINT placeholderID)
{
    CRect rect;
    pParent->GetDlgItem(placeholderID)->GetWindowRect(&rect);
    pParent->ScreenToClient(&rect);

    if (!Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, rect, pParent, IDC_LIST_JOBS))
        return FALSE;

    SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    SetupColumns();
    return TRUE;
}

void CDisplayList::SetupColumns()
{
    InsertColumn(0, _T("Scan No"), LVCFMT_LEFT, 85);
    InsertColumn(1, _T("Pt(Xmm,T°)"), LVCFMT_LEFT, 95);
    InsertColumn(2, _T("Current(mA)"), LVCFMT_LEFT, 80);
    InsertColumn(3, _T("Thkness(um)"), LVCFMT_LEFT, 80);
    InsertColumn(4, _T("Temp(°C)"), LVCFMT_LEFT, 70);
    InsertColumn(5, _T("LoadCell(gm)"), LVCFMT_LEFT, 85);
    InsertColumn(6, _T("Resistance(Ohm/sq)"), LVCFMT_LEFT, 125);
    InsertColumn(7, _T("Timestamp"), LVCFMT_LEFT, 130);
}

void CDisplayList::PopulateFrom(const std::vector<Report>& rows)
{
    DeleteAllItems();

    for (size_t i = 0; i < rows.size(); i++)
    {
        const Report& r = rows[i];

        CString label;
        label.Format(_T("%d.%d.%d.%d"), r.slot, r.scan, r.repeat, r.point);
        int idx = InsertItem((int)i, label);

        CString val;
        val.Format(_T("%.3f, %.3f"), r.x, r.y);
        SetItemText(idx, 1, val);

        val.Format(_T("%.3f"), r.msr_curr);
        SetItemText(idx, 2, val);

        val.Format(_T("%.3f"), r.wfthk);
        SetItemText(idx, 3, val);

        val.Format(_T("%.1f"), r.temp);
        SetItemText(idx, 4, val);

        val.Format(_T("%.3f"), r.lc);
        SetItemText(idx, 5, val);

        val.Format(_T("%.3f"), r.res);
        SetItemText(idx, 6, val);

        SetItemText(idx, 7, r.scantimerstamp);
    }
}