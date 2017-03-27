// TransparentStatic.cpp : implementation file
//

#include "stdafx.h"
#include "TransparentStaticWhite.h"


// CTransparentStatic

IMPLEMENT_DYNAMIC(CTransparentStaticWhite, CStatic)
CTransparentStaticWhite::CTransparentStaticWhite()
{
}

CTransparentStaticWhite::~CTransparentStaticWhite()
{
}


BEGIN_MESSAGE_MAP(CTransparentStaticWhite, CStatic)
   ON_MESSAGE(WM_SETTEXT,OnSetText)
   ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CTransparentStatic message handlers

LRESULT CTransparentStaticWhite::OnSetText(WPARAM wParam,LPARAM lParam)
{
   LRESULT Result = Default();
   CRect Rect;
   GetWindowRect(&Rect);
   GetParent()->ScreenToClient(&Rect);
   GetParent()->InvalidateRect(&Rect);
   GetParent()->UpdateWindow();
   return Result;
}


HBRUSH CTransparentStaticWhite::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
   pDC->SetTextColor(RGB(255, 255, 255));
   pDC->SetBkMode(TRANSPARENT);
   return (HBRUSH)GetStockObject(NULL_BRUSH);
}


