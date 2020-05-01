#pragma once
#include <time.h>

class Timer
{
public:
	Timer();
	~Timer();

	void start(); //start the timer in constructor?
	void reset();
	float getElapsedTime(); //returns elapsed time in seconds since last start.

private:
	clock_t start_t;
};

