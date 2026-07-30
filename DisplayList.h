#pragma once
#include <afxcmn.h>
#include <functional>
#include <vector>

#define IDC_LIST_JOBS 2001

struct Report {
    CString scantimerstamp;
    int scan;
    int repeat;
    int point;
    int slot;
    float x;
    float y;
    float msr_curr;
    float wfthk;
    float temp;
    float lc;
    float res;

    void Serialize(CArchive& ar)
    {
        if (ar.IsStoring()) {
            ar << scantimerstamp << scan << repeat << point << slot
                << x << y << msr_curr << wfthk << temp << lc << res;
        }
        else {
            ar >> scantimerstamp >> scan >> repeat >> point >> slot
                >> x >> y >> msr_curr >> wfthk >> temp >> lc >> res;
        }
    }
};

struct ColumnDef {
    CString header;
    int width;
    std::function<CString(const Report&)> getValue;
    bool visible = true;
};

class CDisplayList : public CListCtrl
{
public:
    CDisplayList();

    DECLARE_MESSAGE_MAP()

public:
    BOOL Init(CWnd* pParent, UINT placeholderID);
    void SetupColumns();
    void PopulateFrom(const std::vector<Report>& rows);

protected:
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

private:
    std::vector<ColumnDef> m_columns;
    std::vector<Report> m_rows;
};