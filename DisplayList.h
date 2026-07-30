#pragma once
#include <afxcmn.h>
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

class CDisplayList : public CListCtrl
{
public:
    DECLARE_MESSAGE_MAP()

public:
    BOOL Init(CWnd* pParent, UINT placeholderID);
    void SetupColumns();
    void PopulateFrom(const std::vector<Report>& rows);
};