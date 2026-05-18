#include "Window.h"
#include "utils.h"
#include "App.h"
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int 		nCmdShow
)
{
	try
	{
		return App{}.Go();
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
	return 1;  // default quit code is 0, but we're returning 1 to indicate an error in case we get here by some unexpected path
}