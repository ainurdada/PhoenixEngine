#include <windows.h>
#include <chrono>

#include "Window.h"
#include "Time.h"
#include "Graphics.h"

#include <iostream>
#include <thread>

#define MS_PER_UPDATE 0.16

void processInput();
void update(float deltaTime);
void render(float deltaFrame);

int main() {
	Window window;
	window.Create(L"test", 800, 800);
	Graphics graphics;
	graphics.Init(window.GetHWND(), window.ClientWidth, window.ClientHeight);
	Time time;

	float lag = 0;
	while (true)
	{
		time.Update();
		std::cout <<  time.GetDeltaTime() << "\n";
		lag += time.GetDeltaTime();

		processInput();

		while (lag >= MS_PER_UPDATE)
		{
			update(time.GetDeltaTime());
			lag -= MS_PER_UPDATE;
		}

		render(lag / MS_PER_UPDATE);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}


static MSG msg = {};
void processInput()
{
	// Handle the windows messages.
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void update(float deltaTime)
{
}

void render(float deltaFrame)
{
}
