#pragma once
#define OnMenuAction1		1
#define OnExitSoftware		2
#define OnMenuAction3		3
#define AboutAppAction		4
#define AboutAuthorAction	5
#define ButtonToSend		6

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSW NewWindowClass(HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

void MainWNDAddMenus(HWND hWnd);
void MainWNDAddWidgets(HWND hWnd);
