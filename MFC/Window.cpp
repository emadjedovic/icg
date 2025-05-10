
// Window.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ICG_lab_II.h"
#include "Window.h"
#include "afxdialogex.h"
#include <queue>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Window dialog



Window::Window(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ICG_LAB_II_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Window::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLEAR, CButtonClear);
	DDX_Control(pDX, IDC_SIMPLE_POLYGON, CButtonSimplePolygon);
	DDX_Control(pDX, IDC_SEGMENTS_INTERSECT, CButtonSegmentsIntersect);
	DDX_Control(pDX, IDC_GIFT_WRAPPING, CButtonGiftWrapping);
	DDX_Control(pDX, IDC_GRAHAM, CButtonGraham);
	DDX_Control(pDX, IDC_INCREMENTAL, CButtonIncremental);
	DDX_Control(pDX, IDC_GENERATE_POINTS, CButtonGeneratePoints);
	DDX_Control(pDX, IDC_NUM_POINTS, CEditNumPoints);
	DDX_Control(pDX, IDC_DRAW_TANGENTS, CButtonDrawTangents);
	DDX_Control(pDX, IDC_POINT_IN_CH, CButtonPointInCH);
	DDX_Control(pDX, IDC_ADD_SEGMENT, CButtonAddSegment);
	DDX_Control(pDX, IDC_ADD_POINT, CButtonAddPoint);
	DDX_Control(pDX, IDC_ADD_POLYGON, CButtonAddPolygon);
}

BEGIN_MESSAGE_MAP(Window, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CLEAR, &Window::OnBnClickedClear)
	ON_BN_CLICKED(IDC_SIMPLE_POLYGON, &Window::OnBnClickedSimplePolygon)
	ON_BN_CLICKED(IDC_SEGMENTS_INTERSECT, &Window::OnBnClickedSegmentsIntersect)
	ON_BN_CLICKED(IDC_GIFT_WRAPPING, &Window::OnBnClickedGiftWrapping)
	ON_BN_CLICKED(IDC_GRAHAM, &Window::OnBnClickedGraham)
	ON_BN_CLICKED(IDC_INCREMENTAL, &Window::OnBnClickedIncremental)
	ON_BN_CLICKED(IDC_GENERATE_POINTS, &Window::OnBnClickedGeneratePoints)
END_MESSAGE_MAP()


// Window message handlers

BOOL Window::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// Returns the drawable area as a CRect with proper margins
CRect Window::GetDrawableArea() const
{
	CRect rect;
	GetClientRect(&rect);

	int width = rect.Width();
	int height = rect.Height();

	int marginLeft = static_cast<int>(width * 0.05);
	int marginRight = static_cast<int>(width * 0.25);
	int marginTop = static_cast<int>(height * 0.10);
	int marginBottom = static_cast<int>(height * 0.20);

	int left = rect.left + marginLeft;
	int top = rect.top + marginTop;
	int right = rect.right - marginRight;
	int bottom = rect.bottom - marginBottom;

	return CRect(left, top, right, bottom);
}

bool Window::IsPointDrawable(CPoint pt) const
{
	return GetDrawableArea().PtInRect(pt);
}

void Window::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for (const auto& pt : points)
		{
			pt.Draw(dc);
		}

		if (polygonVisible && points.size() >= 3)
			DrawPolygon(dc, points);

		if (hullVisible && CH.size() >= 3)
			DrawPolygon(dc, CH);

		CDialogEx::OnPaint();
	}
}

HCURSOR Window::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Window::AddPoint(int x, int y)
{
	CPoint pt(x, y);
	if (IsPointDrawable(pt))
	{
		points.emplace_back(x, y);
		Invalidate();
	}
}

void Window::OnLButtonDown(UINT nFlags, CPoint point)
{
	MyPoint newPoint(point.x, point.y);
	CClientDC dc(this);

	if (CButtonAddPoint.GetCheck() == BST_CHECKED)
	{
		points.push_back(newPoint);
		newPoint.Draw(dc);
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	else if (CButtonAddSegment.GetCheck() == BST_CHECKED)
	{
		if (second_click)
		{
			MySegment newSegment(points.back(), newPoint);
			newSegment.Draw(dc);
			segments.push_back(newSegment);
		}
		second_click = !second_click;
		points.push_back(newPoint);
		newPoint.Draw(dc);
		CDialogEx::OnLButtonDown(nFlags, point);
		
	}
	else if (CButtonPointInCH.GetCheck() == BST_CHECKED)
	{
		if (CH.size() >= 3)
		{
			if (PointInPolygon(CH, newPoint))
				AfxMessageBox(_T("Inside the Convex Hull!"));
			else
				AfxMessageBox(_T("Outside the Convex Hull!"));
		}
	}
	else if (CButtonDrawTangents.GetCheck() == BST_CHECKED)
	{
		if (CH.size() >= 3)
		{
			pair<int, int> tangents = findTangents(newPoint, CH);
			int left_i = tangents.first;
			int right_i = tangents.second;

			if (left_i != -1)
				MySegment(newPoint, CH[left_i]).Draw(dc);
			if (right_i != -1)
				MySegment(newPoint, CH[right_i]).Draw(dc);
		}
		points.push_back(newPoint);
		newPoint.Draw(dc);

		CDialogEx::OnLButtonDown(nFlags, point);
	}
	else if (CButtonAddPolygon.GetCheck() == BST_CHECKED)
	{
		if (points.size() >= 1)
		{
			if (distance(newPoint, points[0]) > 20) {
				MySegment(points[points.size()-1], newPoint).Draw(dc);
				points.push_back(newPoint);
				newPoint.Draw(dc);
				CDialogEx::OnLButtonDown(nFlags, point);
			}
			else {
				MySegment(points[points.size()-1], points[0]).Draw(dc);
			}
		}
		else {
			points.push_back(newPoint);
			newPoint.Draw(dc);

			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}
	else {
		points.push_back(newPoint);
		newPoint.Draw(dc);

		CDialogEx::OnLButtonDown(nFlags, point);
	}
}


void Window::ClearScreen()
{
	points.clear();
	segments.clear();
	CH.clear();
	polygonVisible = false;
	hullVisible = false;
	Invalidate();
}

void Window::OnBnClickedClear()
{
	ClearScreen();
}

void Window::OnBnClickedGeneratePoints()
{
	ClearScreen();
	CRect drawable = GetDrawableArea();
	int width = drawable.Width();
	int height = drawable.Height();

	CString str;
	CEditNumPoints.GetWindowText(str);
	int n = _ttoi(str);

	for (int i = 0; i < n; i++)
	{
		int x = drawable.left + rand() % width;
		int y = drawable.top + rand() % height;
		AddPoint(x, y);
	}
}

void Window::OnBnClickedSimplePolygon()
{
	if (points.size() < 3) {
		std::cout << "Less than three points.";
		return;
	}

	for (int i = 1; i < points.size(); i++) {
		if (points[i] < points[0]) {
			std::swap(points[i], points[0]);
		}
	}

	MyPoint leftmost(points[0]);
	sort(points.begin() + 1, points.end(), [leftmost](MyPoint A, MyPoint B) {
		return Orientation(leftmost, A, B) < 0;
		});

	polygonVisible = true; // optional: add a flag if needed
	Invalidate(); // triggers OnPaint()
}

void Window::OnBnClickedSegmentsIntersect()
{
	if (segments.size() < 2)
		return;

	int n = segments.size();

	MySegment s1 = segments[n - 1]; // last
	MySegment s2 = segments[n - 2]; // second last

	int o1 = Orientation(s1.A, s1.B, s2.A);
	int o2 = Orientation(s1.A, s1.B, s2.B);
	int o3 = Orientation(s2.A, s2.B, s1.A);
	int o4 = Orientation(s2.A, s2.B, s1.B);

	if (o1 != o2 && o3 != o4) {
		AfxMessageBox(_T("Segments intersect!"));
	}
	else {
		AfxMessageBox(_T("Segments don't intersect!"));
	}
}


void Window::OnBnClickedGiftWrapping()
{
		CH.clear(); // make sure previous hull is cleared

		if (points.size() < 3)
			return;

		// Find the leftmost point
		for (int i = 1; i < points.size(); i++) {
			if (points[i] < points[0])
				std::swap(points[i], points[0]);
		}

		MyPoint pivot(points[0]);
		CH.push_back(pivot);

		while (true) {
			MyPoint P = points[0];
			if (P == pivot)
				P = points[1];

			for (const auto& pt : points)
				if (Orientation(pivot, P, pt) > 0)
					P = pt;

			if (P == CH.front()) // if wrapped around
				break;

			CH.push_back(P);
			pivot = P;
		}

		hullVisible = true; // make sure this flag is declared in your class
		Invalidate();       // triggers OnPaint() where the hull will be drawn
}

void Window::OnBnClickedGraham()
{
	CH.clear();
	if (points.size() < 3)
		return;

	// Find the leftmost point
	for (int i = 1; i < points.size(); i++) {
		if (points[i] < points[0])
			std::swap(points[i], points[0]);
	}

	MyPoint leftmost(points[0]);

	// Sort by angle around the leftmost point
	std::sort(points.begin() + 1, points.end(), [leftmost](MyPoint A, MyPoint B) {
		return Orientation(leftmost, A, B) < 0;
		});

	CH.push_back(leftmost);
	CH.push_back(points[1]);

	int prevIndex = 0;
	int currIndex = 1;

	for (int i = 2; i < points.size(); i++) {
		MyPoint nextPoint = points[i];

		// Maintain right-turns only (i.e., counter-clockwise)
		while (CH.size() >= 2 &&
			Orientation(CH[CH.size() - 2], CH[CH.size() - 1], nextPoint) > 0)
		{
			CH.pop_back();
		}

		CH.push_back(nextPoint);
	}

	hullVisible = true;
	Invalidate(); // redraw with the new convex hull
}

void Window::OnBnClickedIncremental()
{
	if (points.size() < 3)
		return;

	// Ensure initial orientation is counter-clockwise
	if (Orientation(points[0], points[1], points[2]) > 0)
		std::swap(points[1], points[2]);

	CH = { points[0], points[1], points[2] };

	int n = points.size();
	for (int i = 3; i < n; i++) {
		MyPoint T = points[i]; // Next point

		if (PointInPolygon(CH, T))
			continue;

		pair<int, int> tangents = findTangents(T, CH);
		int l = tangents.first;
		int r = tangents.second;

		if (r < l) {
			CH.erase(CH.begin() + r + 1, CH.begin() + l);
			CH.insert(CH.begin() + r + 1, T);
		}
		else {
			CH.erase(CH.begin() + r + 1, CH.end());
			if (l != 0)
				CH.erase(CH.begin(), CH.begin() + l);
			CH.insert(CH.begin(), T);
		}
	}

	hullVisible = true;
	Invalidate(); // Triggers repaint to show the hull
}