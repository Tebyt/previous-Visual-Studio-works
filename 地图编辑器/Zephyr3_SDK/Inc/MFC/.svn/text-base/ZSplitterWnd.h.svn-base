#pragma once

#include <MFC\CZWnd.h>

#include <MFC\BaseDef.h>

class CZSplitterCtl;

// CZSplitterWnd
class ZEPHYR_MFC_API CZSplitterWnd : public CZWnd
{
	friend class CZSplitterCtl;

	DECLARE_DYNAMIC(CZSplitterWnd)
public:
	CZSplitterWnd(ZGraph *pGraph);
	virtual ~CZSplitterWnd();

protected:
	inline void SetSplitterCtl(CZSplitterCtl *pSplitterCtl) {

		ZASSERT(pSplitterCtl != NULL);

		m_pSplitterCtl = pSplitterCtl;
	}

	DECLARE_MESSAGE_MAP()
private:
	CZSplitterCtl*	m_pSplitterCtl;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
