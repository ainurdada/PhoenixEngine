#include "Time.h"


Time::Time()
{
	instance = this;
	start_time = std::chrono::steady_clock::now();
	current_time = std::chrono::steady_clock::now();
	previous_time = std::chrono::steady_clock::now();
	delta_time = 0;
}
Time* Time::instance = nullptr;

void Time::Update()
{
	current_time = std::chrono::steady_clock::now();
	delta_time = std::chrono::duration_cast<std::chrono::microseconds>(current_time - previous_time).count() / 1000000.0f;
	previous_time = current_time;
}

float Time::GetTime() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() / 1000.0f;
}
