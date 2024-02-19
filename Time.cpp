#include "Time.h"

Time::Time()
{
	current_time = std::chrono::steady_clock::now();
	previous_time = std::chrono::steady_clock::now();
	delta_time = 0;
}

void Time::Update()
{
	current_time = std::chrono::steady_clock::now();
	delta_time = std::chrono::duration_cast<std::chrono::microseconds>(current_time - previous_time).count() / 1000000.0f;
	previous_time = current_time;
}

float Time::GetDeltaTime() const
{
	return delta_time;
}
