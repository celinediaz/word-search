
// letterSoupDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "letterSoup.h"
#include "letterSoupDlg.h"
#include "afxdialogex.h"
#include <algorithm>    // std::sort
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CletterSoupDlg dialog



CletterSoupDlg::CletterSoupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LETTERSOUP_DIALOG, pParent)
	, m_Mayus(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CletterSoupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Mayus);
}

BEGIN_MESSAGE_MAP(CletterSoupDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CletterSoupDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CletterSoupDlg message handlers

BOOL CletterSoupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CletterSoupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CletterSoupDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CletterSoupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CletterSoupDlg::CreateBoard(int height, int width) {
	UpdateData(TRUE);
	Invalidate();
	UpdateWindow();

	canvas = (CStatic*)GetDlgItem(IDC_STATIC);

	CDC* hdc = canvas->GetDC();


	char ch;

	board.clear();
	for (int i = 0; i < height; i++)
	{
		std::vector<char> temp;
		for (int j = 0; j < width; j++)
		{
			ch = ' ';
			temp.push_back(ch);
		}
		board.push_back(temp);
	}

	getWords();

	int length;
	for (int i = 0; i < wordList.size(); i++) {
		length = wordList[i].length();
		if (length <= width && length <= height) {
			direction = (rand() % 8) + 1;
			switch (direction) {
			case 1:
				horiz(i);
				break;
			case 2:
				vertic(i);
				break;
			case 3:
				diagL(i);
				break;
			case 4:
				diagR(i);
				break;
			case 5:
				horizOP(i);
				break;
			case 6:
				verticOP(i);
				break;
			case 7:
				diagLOP(i);
				break;
			case 8:
				diagROP(i);
				break;
			}
		}

		else if (wordList[i].length() > width && wordList[i].length() > height) {
			hdc->TextOut(20, 50, CString("The word is too long to fit into the board"));
		}

		else if (wordList[i].length() <= height && width <= wordList[i].length()) {
			direction = (rand() % 2) + 1;
			switch (direction) {
			case 1:
				horiz(i);
				break;
			case 2:
				horizOP(i);
				break;
			}
		}
		else if (wordList[i].length() <= width && height <= wordList[i].length()) {
			direction = (rand() % 2) + 1;
			switch (direction) {
			case 1:
				vertic(i);
				break;
			case 2:
				verticOP(i);
				break;
			}
		}
		else {
			hdc->TextOut(20, 50, CString("Something strange happened..."));
		}
	}

	hdc->SetTextColor(0);

	std::vector < std::vector < char >> board2 = board;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j] == ' ') {
				if (m_Mayus == 0) {
					board[i][j] = 'A' + rand() % 26;
				}
				else {
					board[i][j] = 'a' + rand() % 26;
				}
			}

		}
	}

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			out = board[i][j];

			if (board2[i][j] == board[i][j]) {
				hdc->SetTextColor(RGB(51, 173, 167));
				hdc->TextOut((i * 20) - 70, j * 20 + 120, out);
			}
			else {
				hdc->SetTextColor(RGB(197, 127, 18));
				hdc->TextOut((i * 20) - 70, j * 20 + 120, out);
			}
		}
	}
	UpdateData(FALSE);

}

void CletterSoupDlg::OnBnClickedButton1()
{
	CString c1;
	GetDlgItemText(IDC_WIDTH, c1);
	CString c2;
	GetDlgItemText(IDC_HEIGHT, c2);
	width = _wtof(c1);
	height = _wtof(c2);
	CreateBoard(width, height);
}

void CletterSoupDlg::getWords()
{
	wordList.clear();
	std::ifstream f;
	f.open("entrada.txt");
	std::string str;
	while (std::getline(f, str, ' '))
	{
		wordList.push_back(str);
	}
	f.close();
}
// see the last else statements on each function for the direction of the following functions.
void CletterSoupDlg::horiz(int i) {

	disp = TRUE;
	int randomColumn = 0;
	if (wordList[i].length() != width) {
		randomColumn = (rand() % (width - wordList[i].length() + 1));
	}

	int randomRow = (rand() % height);

	int rc2 = randomColumn;
	int rr2 = randomRow;
	std::string word = wordList[i];

	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j]) {
			rc2++;
		}
		else {
			disp = FALSE;
		}

	}
	if (disp == FALSE) {
		horiz(i);
	}
	else {
		for (int j = 0; j < wordList[i].length(); j++)
		{
			board[randomColumn][randomRow] = word[j];
			randomColumn++;
		}
	}

}
void CletterSoupDlg::vertic(int i) {
	disp = TRUE;
	int randomRow = 0;
	if (wordList[i].length() != height) {
		randomRow = (rand() % (height - wordList[i].length() + 1));
	}
	int randomColumn = (rand() % width);

	int rc2 = randomColumn;
	int rr2 = randomRow;
	std::string word = wordList[i];

	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j]) {
			rr2++;
		}
		else {
			disp = FALSE;
		}
	}

	if (disp == FALSE) {
		vertic(i);
	}

	else {
		for (int j = 0; j < wordList[i].length(); j++)
		{
			board[randomColumn][randomRow] = word[j];
			randomRow++;
		}
	}
}

void CletterSoupDlg::diagL(int i) {
	disp = TRUE;
	int randomColumn = 0;
	if (wordList[i].length() != width) {
		randomColumn = (rand() % (width - wordList[i].length()));
	}
	int randomRow = 0;
	if (wordList[i].length() != height) {
		randomRow = (rand() % (height - wordList[i].length()));
	}
	int rc2 = randomColumn;
	int rr2 = randomRow;
	std::string word = wordList[i];


	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j])
		{
			rc2++;
			rr2++;
		}
		else {
			disp = FALSE;
		}
	}

	if (disp == FALSE) {
		diagL(i);
	}
	else {
		for (int j = 0; j < wordList[i].length(); j++)
		{
			board[randomColumn][randomRow] = word[j];
			randomColumn++;
			randomRow++;
		}
	}
}
void CletterSoupDlg::diagR(int i) {
	disp = TRUE;
	int randomRow = 0;
	if (wordList[i].length() != height) {
		randomRow = (rand() % (height - wordList[i].length()));
	}

	int randomColumn = width;
	if (wordList[i].length() != width) {
		randomColumn = wordList[i].length() + (rand() % (width - wordList[i].length()));
	}

	int rc2 = randomColumn;
	int rr2 = randomRow;


	std::string word = wordList[i];

	rc2--;
	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j])
		{
			rc2--;
			rr2++;
		}
		else {
			disp = FALSE;
		}
	}

	if (disp == FALSE) {
		diagR(i);
	}
	else {
		for (int j = 0; j < wordList[i].length(); j++)
		{
			randomColumn--;
			board[randomColumn][randomRow] = word[j];
			randomRow++;
		}
	}
}
void CletterSoupDlg::horizOP(int i) {
	disp = TRUE;

	int randomColumn = width;
	if (wordList[i].length() != width) {
		randomColumn = wordList[i].length() + (rand() % (width - wordList[i].length() + 1));
	}
	int randomRow = (rand() % height);
	std::string word = wordList[i];
	int rc2 = randomColumn;
	int rr2 = randomRow;

	rc2--;

	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j])
		{
			rc2--;
		}
		else {
			disp = FALSE;
		}
	}
	if (disp == FALSE) {
		horizOP(i);
	}

	else {
		for (int j = 0; j < wordList[i].length(); j++)
		{
			randomColumn--;
			board[randomColumn][randomRow] = word[j];
		}
	}

}
void CletterSoupDlg::verticOP(int i) {
	disp = TRUE;
	int randomRow = height;
	if (wordList[i].length() != height) {
		randomRow = wordList[i].length() + (rand() % (height - wordList[i].length() + 1));
	}

	int	randomColumn = (rand() % width);
	int rc2 = randomColumn;
	int rr2 = randomRow;


	std::string word = wordList[i];

	rr2--;

	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j])
		{
			rr2--;
		}
		else {
			disp = FALSE;
		}
	}
	if (disp == FALSE) {
		verticOP(i);
	}
	else {
		for (int j = 0; j < wordList[i].length(); j++)
		{
			randomRow--;
			board[randomColumn][randomRow] = word[j];
		}
	}
}
void CletterSoupDlg::diagLOP(int i) {
	disp = TRUE;
	int randomColumn = width;
	if (wordList[i].length() != width) {
		randomColumn = wordList[i].length() + (rand() % (width - wordList[i].length() + 1));
	}
	int randomRow = height;
	if (wordList[i].length() != height) {
		randomRow = wordList[i].length() + (rand() % (height - wordList[i].length() + 1));
	}
	int rc2 = randomColumn;
	int rr2 = randomRow;


	std::string word = wordList[i];

	rr2--;
	rc2--;

	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j])
		{
			rr2--;
			rc2--;
		}
		else {
			disp = FALSE;
		}
	}
	if (disp == FALSE) {
		diagLOP(i);
	}
	else {
		for (int j = 0; j < wordList[i].length(); j++)
		{
			randomColumn--;
			randomRow--;
			board[randomColumn][randomRow] = word[j];
		}
	}
}
void CletterSoupDlg::diagROP(int i) {
	disp = TRUE;
	int randomColumn = 0;
	if (wordList[i].length() != width) {
		randomColumn = (rand() % (width - wordList[i].length()));
	}

	int randomRow = height;
	if (wordList[i].length() != height) {
		randomRow = wordList[i].length() + (rand() % (height - wordList[i].length() + 1));
	}
	int rc2 = randomColumn;
	int rr2 = randomRow;


	std::string word = wordList[i];
	rr2--;
	for (int j = 0; j < wordList[i].length(); j++)
	{
		if (board[rc2][rr2] == ' ' || board[rc2][rr2] == word[j])
		{
			rc2++;
			rr2--;
		}
		else {
			disp = FALSE;
		}
	}

	if (disp == FALSE) {
		diagROP(i);
	}
	else {


		for (int j = 0; j < wordList[i].length(); j++)
		{
			randomRow--;
			board[randomColumn][randomRow] = word[j];
			randomColumn++;
		}
	}
}