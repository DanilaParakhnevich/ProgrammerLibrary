#include <Windows.h>
#include "headerDefinitions.h"
#include "header.h"
#include <iostream>

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSW NewWindowClass(HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);
static HWND hEdit;
static HWND responce;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASSW SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) {
		return -1;
	}
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Programmer's Library", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	while (GetMessageW(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessageW(&SoftwareMainMessage);
	}
	return 0;
}

WNDCLASSW NewWindowClass(HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure) {
	WNDCLASSW NWC = { 0 };

	NWC.hCursor = cursor;
	NWC.hIcon = icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = procedure;
	return NWC;
}
void ResetScrollbarSize(HWND hWnd)
{
	RECT rc = { 0 };
	GetWindowRect(hWnd, &rc);
	SCROLLINFO si = { 0 };
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = 30 * 99 + 21;
	si.nPage = (rc.bottom - rc.top);
	si.nPos = 0;
	si.nTrackPos = 0;
	SetScrollInfo(hWnd, SB_VERT, &si, true);
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case AboutAppAction:
			MessageBoxA(hWnd, "Это приложение создано для того , кто хочет либо изучить сленг программистов, либо вспомнить его. Чтобы получить достоверный результат, стоит ввести подробный ключ.",
				"Информация о приложении", MB_OK);
			break;
		case OnExitSoftware:
			PostQuitMessage(0);
			break;
		case AboutAuthorAction:
			MessageBoxA(hWnd, "Костя Азаренко\nhttps://vk.com/azar_kostya", "Информация об авторе", MB_OK);
			break;
		case ButtonToSend:
			SetWindowTextA(responce, getResult(hEdit).c_str());
			break;
		}
		break;
	case WM_CREATE :
		MainWNDAddMenus(hWnd);
		MainWNDAddWidgets(hWnd);
		break;
	case WM_DESTROY :
		PostQuitMessage(0);
		break;
	case WM_VSCROLL:
		ResetScrollbarSize(responce);
		break;
	}
	
	return DefWindowProc(hWnd, msg, wp, lp);
}


void MainWNDAddMenus(HWND hWnd) {
	HMENU rootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();
	HMENU InfoMenu = CreateMenu();

	AppendMenu(rootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Файл");
	AppendMenu(InfoMenu, MF_STRING, AboutAppAction, L"О приложении");
	AppendMenu(InfoMenu, MF_STRING, AboutAuthorAction, L"Об авторе");

	AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)InfoMenu, L"Информация");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Выход");

	SetMenu(hWnd, rootMenu);
}

 
void MainWNDAddWidgets(HWND hWnd) {
	CreateWindowA("static", "Введите ключевое слово запроса", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 545, 20, hWnd,
		NULL, NULL, NULL, NULL);
	hEdit = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER, 163, 30, 200, 20, hWnd,
		NULL, NULL, NULL, NULL);
	CreateWindowA("button", "Поиск", WS_VISIBLE | WS_CHILD, 163, 55, 60, 20, hWnd,
		(HMENU)ButtonToSend, NULL, NULL, NULL);
	responce = CreateWindowA("static", "",
		WS_VISIBLE | WS_CHILD | ES_LEFT | WS_BORDER | WS_VSCROLL,
		5, 80,
		480, 300,
		hWnd, NULL, NULL, NULL, NULL);
}

