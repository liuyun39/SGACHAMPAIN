#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int 		nCmdShow
)
{
		Window wnd(800, 300, L"Real Time 3D Rendering");
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