#include "Window.h"
#include "utils.h";
#include "Mouse.h";
#include <sstream>


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int 		nCmdShow
)
{
		try
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
						while (!wnd.mouse.IsEmpty())
						{
								const auto e = wnd.mouse.Read();
								switch (e.GetType())
								{
										case Mouse::Event::Type::Leave:
												wnd.SetTitle("Mouse Left Window");
												break;
										case Mouse::Event::Type::Move:
										{
												std::ostringstream oss;
												oss << "Mouse Position: (" << e.GetPosX() << ", " << e.GetPosY() << ")";
												wnd.SetTitle(oss.str());
												break;
										}
								}
						}
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
		catch (const LYException& e)
		{
				MessageBox(nullptr, Utf8ToWide(e.what()).c_str(), Utf8ToWide(e.GetType()).c_str(), MB_OK | MB_ICONERROR);
		}
		catch(const std::exception& e)
		{
				MessageBox(nullptr, Utf8ToWide(e.what()).c_str(), L"Standard Exception", MB_OK | MB_ICONERROR);
		}
		catch (...)
		{
				MessageBox(nullptr, L"NO details available", L"Unknown Exception", MB_OK | MB_ICONERROR);
		}
}