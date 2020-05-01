#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::start()
{
	start_t = clock();
}

void Timer::reset()
{
	start_t = clock();
}

float Timer::getElapsedTime()
{
	return (float(clock()-start_t)) / CLOCKS_PER_SEC;
}
