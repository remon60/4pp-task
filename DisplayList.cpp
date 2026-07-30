#include "pch.h"
#include "DisplayList.h"
#include "ColumnOptionsDlg.h"

BEGIN_MESSAGE_MAP(CDisplayList, CListCtrl)
    ON_WM_CONTEXTMENU()
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

CDisplayList::CDisplayList()
{
    m_columns.push_back({ _T("Scan No"), 85, [](const Report& r) {
        CString s; s.Format(_T("%d.%d.%d.%d"), r.slot, r.scan, r.repeat, r.point); return s;
    } });
    m_columns.push_back({ _T("Pt(Xmm,T°)"), 95, [](const Report& r) {
        CString s; s.Format(_T("%.3f, %.3f"), r.x, r.y); return s;
    } });
    m_columns.push_back({ _T("Current(mA)"), 80, [](const Report& r) {
        CString s; s.Format(_T("%.3f"), r.msr_curr); return s;
    } });
    m_columns.push_back({ _T("Thkness(um)"), 80, [](const Report& r) {
        CString s; s.Format(_T("%.3f"), r.wfthk); return s;
    } });
    m_columns.push_back({ _T("Temp(°C)"), 70, [](const Report& r) {
        CString s; s.Format(_T("%.1f"), r.temp); return s;
    } });
    m_columns.push_back({ _T("LoadCell(gm)"), 85, [](const Report& r) {
        CString s; s.Format(_T("%.3f"), r.lc); return s;
    } });
    m_columns.push_back({ _T("Resistance(Ohm/sq)"), 125, [](const Report& r) {
        CString s; s.Format(_T("%.3f"), r.res); return s;
    } });
    m_columns.push_back({ _T("Timestamp"), 130, [](const Report& r) {
        return r.scantimerstamp;
    } });
}

void CDisplayList::SetupColumns()
{
    CHeaderCtrl* pHeader = GetHeaderCtrl();
    int existing = pHeader ? pHeader->GetItemCount() : 0;
    for (int i = existing - 1; i >= 0; i--)
        DeleteColumn(i);

    int listCol = 0;
    for (size_t i = 0; i < m_columns.size(); i++)
    {
        if (!m_columns[i].visible)
            continue;

        InsertColumn(listCol, m_columns[i].header, LVCFMT_LEFT, m_columns[i].width);
        listCol++;
    }
}

void CDisplayList::PopulateFrom(const std::vector<Report>& rows)
{
    m_rows = rows;

    DeleteAllItems();

    for (size_t r = 0; r < rows.size(); r++)
    {
        const Report& row = rows[r];

        int listCol = 0;
        int idx = -1;
        for (size_t c = 0; c < m_columns.size(); c++)
        {
            if (!m_columns[c].visible)
                continue;

            CString val = m_columns[c].getValue(row);
            if (idx == -1)
                idx = InsertItem((int)r, val);
            else
                SetItemText(idx, listCol, val);
            listCol++;
        }
    }
}

void CDisplayList::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CColumnOptionsDlg dlg;
    dlg.m_bShowScanNo = m_columns[0].visible;
    dlg.m_bShowPt = m_columns[1].visible;
    dlg.m_bShowCurrent = m_columns[2].visible;
    dlg.m_bShowThkness = m_columns[3].visible;
    dlg.m_bShowTemp = m_columns[4].visible;
    dlg.m_bShowLoadCell = m_columns[5].visible;
    dlg.m_bShowResistance = m_columns[6].visible;
    dlg.m_bShowTimestamp = m_columns[7].visible;

    if (dlg.DoModal() != IDOK)
        return;

    m_columns[0].visible = dlg.m_bShowScanNo;
    m_columns[1].visible = dlg.m_bShowPt;
    m_columns[2].visible = dlg.m_bShowCurrent;
    m_columns[3].visible = dlg.m_bShowThkness;
    m_columns[4].visible = dlg.m_bShowTemp;
    m_columns[5].visible = dlg.m_bShowLoadCell;
    m_columns[6].visible = dlg.m_bShowResistance;
    m_columns[7].visible = dlg.m_bShowTimestamp;

    SetupColumns();
    PopulateFrom(m_rows);
}