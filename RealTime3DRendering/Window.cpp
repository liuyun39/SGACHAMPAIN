#include "Window.h"
#include "WindowsMessageMap.h"
#include <sstream>

// Window Stuff
Window::Window(int width, int height, const WCHAR* name) noexcept
{
		// calculate window size based on desired client region size
		RECT wr;
		wr.left = 100;
		wr.right = wr.left + width;
		wr.top = 100;
		wr.bottom = wr.top + height;
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
		// create the window & get hWnd
		hWnd = CreateWindow(
				WindowClass::GetName(), name,
				WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
				CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
				nullptr, nullptr, WindowClass::GetInstance(), this
		);
		// show window
		ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT WINAPI Window::HandleMsgSetup(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam
) noexcept
{
		if (msg == WM_NCCREATE)
		{
				// extract ptr to window class from creation data
				const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
				Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
				// set WinAPI-managed user data to store ptr to window class
				SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
				// set message proc to normal (non-setup) handler now that setup is finished
				SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
				// forward message to window class handler only msg == WM_NCCREATE callback
				return pWnd->HandleMsg(hwnd, msg, wParam, lParam);
		}
		// if we get a message before the WM_NCCREATE message, handle with default handler
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
		// retrieve ptr to window class
		Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
};

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
		static WindowsMessageMap messageMap;
		OutputDebugString(messageMap(msg, lParam, wParam).c_str());
		switch (msg)
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
		return DefWindowProc(hWnd, msg, wParam, lParam);
};


// Window Class Stuff
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const wchar_t* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}