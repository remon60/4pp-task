#include "pch.h"
#include "DisplayList.h"
#include "ColumnOptionsDlg.h"

CDisplayList::CDisplayList()
{
    m_columns.push_back({ _T("Scan No"), 85, [](const Report& r) {
        CString s; s.Format(_T("%d.%d.%d.%d"), r.slot, r.scan, r.repeat, r.point); return s;
    }, true, true });
    m_columns.push_back({ _T("Pt(Xmm,T°)"), 95, [](const Report& r) {
        CString s; s.Format(_T("%.3f, %.3f"), r.x, r.y); return s;
    }, true, true });
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

void CDisplayList::InsertRow(int itemIndex, const Report& row)
{
    int listCol = 0;
    int idx = -1;
    for (size_t c = 0; c < m_columns.size(); c++)
    {
        if (!m_columns[c].visible)
            continue;

        CString val = m_columns[c].getValue(row);
        if (idx == -1)
            idx = InsertItem(itemIndex, val);
        else
            SetItemText(idx, listCol, val);
        listCol++;
    }
}

void CDisplayList::PopulateFrom(const std::vector<Report>& rows)
{
    m_rows = rows;

    DeleteAllItems();

    for (size_t r = 0; r < m_rows.size(); r++)
    {
        InsertRow((int)r, m_rows[r]);
    }
}

void CDisplayList::AppendOne(const Report& row)
{
    m_rows.push_back(row);
    InsertRow(GetItemCount(), row);
}

void CDisplayList::Clear()
{
    DeleteAllItems();
    m_rows.clear();
}

void CDisplayList::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CColumnOptionsDlg dlg;
    for (size_t i = 0; i < m_columns.size(); i++)
    {
        dlg.m_show[i] = m_columns[i].visible;
        dlg.m_locked[i] = m_columns[i].locked;
    }

    if (dlg.DoModal() != IDOK)
        return;

    for (size_t i = 0; i < m_columns.size(); i++)
    {
        if (!m_columns[i].locked)
            m_columns[i].visible = dlg.m_show[i];
    }

    SetupColumns();
    PopulateFrom(m_rows);
}