
// Window.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ICG_lab_II.h"
#include "Window.h"
#include "afxdialogex.h"

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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Window::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for (const auto& pt : points)
		{
			dc.Ellipse(static_cast<int>(pt.x) - 3, static_cast<int>(pt.y) - 3,
				static_cast<int>(pt.x) + 3, static_cast<int>(pt.y) + 3);
		}

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Window::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Window::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.y > 50) // Avoid the Clear button
	{
		points.emplace_back(point.x, point.y);
		Invalidate();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void Window::OnBnClickedClear()
{
	points.clear();
	Invalidate();
}

void Window::OnBnClickedSimplePolygon()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedSegmentsIntersect()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedGiftWrapping()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedGraham()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedIncremental()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedGeneratePoints()
{
	// TODO: Add your control notification handler code here
}
