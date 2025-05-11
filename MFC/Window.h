
// Window.h : header file
//

#pragma once
#include <vector>
#include "helper.h"
#include <iostream>

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

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CRect GetDrawableArea() const;
	bool IsPointDrawable(CPoint) const;
	void ClearScreen();
	
	CButton CButtonSimplePolygon;
	CButton CButtonSegmentsIntersect;
	CButton CButtonGiftWrapping;
	CButton CButtonGraham;
	CButton CButtonIncremental;
	afx_msg void OnBnClickedSimplePolygon();
	afx_msg void OnBnClickedSegmentsIntersect();
	afx_msg void OnBnClickedGiftWrapping();
	afx_msg void OnBnClickedGraham();
	afx_msg void OnBnClickedIncremental();

	CEdit CEditNumPoints;
	CButton CButtonGeneratePoints;
	afx_msg void OnBnClickedGeneratePoints();

	CButton CButtonDrawTangents;
	CButton CButtonPointInCH;
	CButton CButtonAddSegment;
	CButton CButtonAddPoint;
	CButton CButtonAddPolygon;

	vector<MyPoint> points;
	vector<MySegment> segments;
	vector<MyPoint> CH;

	vector<pair<int, int>> diagonals;
	void DrawDiagonal(CDC&, const pair<int, int>&);
	vector<MyPoint> intersectionPoints;

	bool second_click = false;
	bool polygonVisible = false;
	bool hullVisible = false;

	CButton CButtonClear;
	afx_msg void OnBnClickedClear();

	CButton CButtonGenerateHVSegments;
	CButton CButtonIntersectHVSegments;
	afx_msg void OnBnClickedGenerateHvSegments();
	afx_msg void OnBnClickedIntersectHvSegments();

	CButton CButtonTriangulate;
	afx_msg void OnBnClickedTriangulate();
};
