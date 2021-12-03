#include <Windows.h>
#include "headerDefinitions.h"
#include "header.h"
#include <iostream>

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSW NewWindowClass(HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);
static HWND hEdit;
static HWND responce;
static HWND alphabetEdit;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASSW SoftwareMainClass = NewWindowClass(CreatePatternBrush(
		(HBITMAP)LoadImage(NULL, TEXT("book.jpg"), 0, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)),
		LoadCursor(NULL, IDC_HAND), hInst,
		(HICON)LoadImage(NULL, L"book.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED),
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
	static HBRUSH Brush;

	switch (msg) {
	case WM_CREATE:
		LOGBRUSH lb;
		lb.lbStyle = BS_SOLID;
		lb.lbColor = RGB(0, 102, 102); 
		lb.lbHatch = HS_BDIAGONAL;
		Brush = CreateBrushIndirect(&lb);
		MainWNDAddMenus(hWnd);
		MainWNDAddWidgets(hWnd);
		break;
	case WM_ERASEBKGND: {
		RECT rect;
		HDC hDC = (HDC)wp;
		GetClientRect(hWnd, &rect);
		FillRect(hDC, &rect, Brush);
		break;
	}
	case WM_DESTROY:
		if (NULL != Brush)
		{
			DeleteObject(Brush);
			Brush = NULL;
		}
		PostQuitMessage(0);
		break;
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
		case AboutWorkAppAction:
			MessageBoxA(hWnd, "Для того , чтобы использовать приложение , введите в поле ключевое слово для поиска и ответ будет сгенерирован мгновенно", "Помощь", MB_OK);
			break;
		case ButtonToSend:
			SetWindowTextA(responce, getResult(hEdit).c_str());
			break;
		case AlphabetWindow:
			alphabetEdit = CreateWindow(L"EDIT",
				L"",
				WS_BORDER | WS_VISIBLE,
				10, 10, 300, 20,
				hWnd, NULL, NULL, NULL);
			break;
		}
		break;
	case WM_KEYDOWN: 
		switch (wp) {
		case VK_RETURN :
			SetWindowTextA(responce, getResult(hEdit).c_str());
			break;
		case VK_END :
			PostQuitMessage(0);
			break;
		}
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
	AppendMenu(InfoMenu, MF_STRING, AboutWorkAppAction, L"Помощь");

	AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)InfoMenu, L"Информация");
	//AppendMenu(SubMenu, MF_STRING, AlphabetWindow, L"Посимвольный поиск");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Выход");

	SetMenu(hWnd, rootMenu);
}

 
void MainWNDAddWidgets(HWND hWnd) {
	CreateWindowA("static", "Введите ключевое слово запроса", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 545, 20, hWnd,
		NULL, NULL, NULL, NULL);
	hEdit = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER, 163, 30, 200, 20, hWnd,
		NULL, NULL, NULL, NULL);
	responce = CreateWindow(L"EDIT", L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
		5, 80,
		480, 300,
		hWnd, (HMENU)10, NULL, NULL);
	CreateWindowA("button", "Поиск", WS_VISIBLE | WS_CHILD, 163, 55, 60, 20, hWnd,
		(HMENU)ButtonToSend, NULL, NULL, NULL);
}

