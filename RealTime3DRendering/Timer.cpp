#include "Timer.h"

Timer::Timer()
{
	last = std::chrono::steady_clock::now();
}

float Timer::Mark()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

float Timer::Peek() const
{
	const auto now = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = now - last;
	return frameTime.count();
}

