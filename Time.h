#pragma once

#include <chrono>

class Time
{
public:
	Time();
public:
	void Update();
	/// <summary>
	/// Get the time since the previous frame in seconds
	/// </summary>
	float GetDeltaTime() const;
private:
	std::chrono::steady_clock::time_point current_time;
	std::chrono::steady_clock::time_point previous_time;
	float delta_time;
};

