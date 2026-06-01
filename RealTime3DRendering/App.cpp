#include "App.h"
#include "Timer.h"

App::App()
	:
	wnd(800, 600, L"Real Time 3D Rendering")
{
}

int App::Go()
{
	while (true)
	{
		if (const auto exitCode = wnd.ProcessMessages())
		{
			return static_cast<int>(*exitCode);
		}
		DoFrame();
	}
};

void App::DoFrame()
{
	// process input, do updates, render
	//const float dt = timer.Peek();
	//std::ostringstream oss;
	//oss << "Time elapsed: " << std::setprecision(1) << std::fixed << dt << "s";
	//wnd.SetTitle(oss.str());
	float c = sin(timer.Peek())/2 + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);

	wnd.Gfx().DrawTestTriangle(
		-timer.Peek(),
		0,
		0
	);
	wnd.Gfx().DrawTestTriangle(
			timer.Peek(), 
			wnd.mouse.GetPosX() / 400.0f - 1.0f, 
			-(wnd.mouse.GetPosY() / 300.0f - 1.0f)
	);

	wnd.Gfx().EndFrame();
}