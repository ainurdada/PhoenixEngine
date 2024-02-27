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
	inline float GetDeltaTime() const { return delta_time; };
	/// <summary>
	/// Get the fixed delta time in seconds
	/// </summary>
	inline float GetFixedDeltaTime() const { return ms_per_update; };
	/// <summary>
	/// Get the time since the game was started in seconds
	/// </summary>
	/// <returns></returns>
	inline float GetTime() const;
private:
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point current_time;
	std::chrono::steady_clock::time_point previous_time;
	float delta_time;
	float ms_per_update = 0.01f;
};

