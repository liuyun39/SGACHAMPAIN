#include "App.h"

App::App()
	:
	wnd(800, 300, L"Real Time 3D Rendering")
{
}

int App::Go()
{
	while (true)
	{
		if (const auto exitCode = wnd.ProcessMessages())
		{
			return *exitCode;
		}
		DoFrame();
	}
};

void App::DoFrame()
{
	// process input, do updates, render
	const float dt = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << dt << "s";
	wnd.SetTitle(oss.str());
}