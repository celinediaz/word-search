
// letterSoupDlg.h : header file
//

#pragma once
#include <vector>       // std::vector
#include <string>


// CletterSoupDlg dialog
class CletterSoupDlg : public CDialogEx
{
// Construction
public:
	CletterSoupDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LETTERSOUP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	CStatic* canvas;



// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	void CreateBoard(int height, int width);
	void getWords();
	std::vector<std::string> wordList;
	std::vector < std::vector < char >> board;
	std::vector<std::string> boardStr;
	int direction;
	int width, height;
	CString out;
	void horiz(int i);
	void vertic(int i);
	void diagL(int i);
	void diagR(int i);
	void horizOP(int i);
	void verticOP(int i);
	void diagLOP(int i);
	void diagROP(int i);
	bool disp = TRUE;
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int m_Mayus;
};
