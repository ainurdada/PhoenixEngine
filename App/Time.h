#pragma once

#include <chrono>

class Time
{
public:
	Time();

	static Time* instance;
public:
	void Update();
	/// <summary>
	/// Get the time since the previous frame in seconds
	/// </summary>
	float GetDeltaTime() const;
	/// <summary>
	/// Get the time since the game was started in seconds
	/// </summary>
	/// <returns></returns>
	float GetTime() const;
private:
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point current_time;
	std::chrono::steady_clock::time_point previous_time;
	float delta_time;
};

