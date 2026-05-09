#include <Windows.h>
#include "WindowsMessageMap.h"
#include <sstream>

LRESULT CALLBACK WndProc(
	HWND   hWnd,
	UINT   Msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	static WindowsMessageMap messageMap;
	OutputDebugString(messageMap(Msg, lParam, wParam).c_str());
	switch (Msg)
	{
		case WM_CLOSE:
			PostQuitMessage(69);
			break;
		case WM_KEYDOWN:
			if (wParam == 'F')
			{
				SetWindowText(hWnd, L"Respects");
			}
			break;
		case WM_KEYUP:
			if (wParam == 'F')
			{
				SetWindowText(hWnd, L"Real Time 3D Rendering");
			}
			break;
		case WM_CHAR:
		{
			static std::wstring title;
			title.push_back((char)wParam);
			SetWindowText(hWnd, title.c_str());
			break;
		}
		case WM_LBUTTONDOWN:
			POINTS pt = MAKEPOINTS(lParam);
			std::wstringstream ss;
			ss << L"X=" << pt.x << L" Y=" << pt.y;
			SetWindowText(hWnd, ss.str().c_str());
			break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
};
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int 		nCmdShow
)
{
	// register window class
	const wchar_t* pClassName = L"hw3dbutts";
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	// create window instance
	HWND hwnd = CreateWindowEx(
		0,
		pClassName,
		L"Real Time 3D Rendering",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);
	ShowWindow(hwnd, SW_SHOW);
	// win message loop
	MSG msg;
	/*GetMessage Return value
	Type: BOOL
	If the function retrieves a message other than WM_QUIT, the return value is nonzero.
	If the function retrieves the WM_QUIT message, the return value is zero.
	If there is an error, the return value is -1.
	*/
	BOOL pResult;
	while ((pResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	if (pResult == -1)
	{
		return -1;
	}
	else
	{
		/*
		https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-quit
		wParam
		The exit code given in the PostQuitMessage function.
		lParam
		This parameter is not used.
		*/
		return (int)msg.wParam;
	}
}