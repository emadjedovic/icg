
// Window.h : header file
//

#pragma once
#include <vector>
#include "helper.h"

// Window dialog
class Window : public CDialogEx
{
// Construction
public:
	Window(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ICG_LAB_II_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	std::vector<MyPoint> points;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedClear();
	
	CButton CButtonSimplePolygon;
	CButton CButtonSegmentsIntersect;
	CButton CButtonGiftWrapping;
	CButton CButtonGraham;
	CButton CButtonIncremental;

	CEdit CEditNumPoints;
	CButton CButtonGeneratePoints;
	CButton CButtonDrawTangents;
	CButton CButtonPointInCH;
	CButton CButtonAddSegment;
	CButton CButtonAddPoint;

	CButton CButtonClear;
};
