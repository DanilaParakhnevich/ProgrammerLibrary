#include <Windows.h>
#include "headerDefinitions.h"

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSW NewWindowClass(HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASSW SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
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

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case OnMenuAction1:
			MessageBoxA(hWnd, "Menu1 has clicked", "Menu worked!", MB_OK);
			break;
		case OnExitSoftware:
			PostQuitMessage(0);
			break;
		case OnMenuAction3:
			MessageBoxA(hWnd, "Menu3 has clicked", "Menu worked!", MB_OK);
			break;
		case ButtonToSend:
			MessageBoxA(hWnd, "Button has clicked", "Yahoo", MB_OK);
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
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

void MainWNDAddMenus(HWND hWnd) {
	HMENU rootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();
	HMENU InfoMenu = CreateMenu();

	AppendMenu(rootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	AppendMenu(InfoMenu, MF_STRING, AboutAppAction, L"About app");
	AppendMenu(InfoMenu, MF_STRING, AboutAuthorAction, L"About author");

	AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)InfoMenu, L"Info");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");



	
	SetMenu(hWnd, rootMenu);
}

void MainWNDAddWidgets(HWND hWnd) {
	CreateWindowA("static", "Input query keyword", WS_VISIBLE | WS_CHILD | ES_CENTER , 5, 5, 450, 20, hWnd, 
		NULL, NULL, NULL, NULL); 
	CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE, 163, 30, 200, 20, hWnd,
		NULL, NULL, NULL, NULL);
	CreateWindowA("button", "input", WS_VISIBLE | WS_CHILD, 163, 55, 60, 20, hWnd,
		(HMENU)ButtonToSend, NULL, NULL, NULL);
}

