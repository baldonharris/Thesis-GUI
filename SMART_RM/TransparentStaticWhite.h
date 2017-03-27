#pragma once


// CTransparentStatic

class CTransparentStaticWhite : public CStatic
{
	DECLARE_DYNAMIC(CTransparentStaticWhite)

public:
	CTransparentStaticWhite();
	virtual ~CTransparentStaticWhite();

protected:
   afx_msg LRESULT OnSetText(WPARAM,LPARAM);
   afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
   DECLARE_MESSAGE_MAP()
};