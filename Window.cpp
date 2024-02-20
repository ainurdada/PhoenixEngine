#include "Window.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		std::cout << "Key: " << static_cast<unsigned int>(wparam) << std::endl;

		if (static_cast<unsigned int>(wparam) == 27) PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	}
}

void Window::Create(LPCWSTR windowName, int screenWidth, int screenHeight)
{
	ClientWidth = screenWidth;
	ClientHeight = screenHeight;

	hInstance = GetModuleHandle(nullptr);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = windowName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	RECT windowRect = { 0, 0, static_cast<LONG>(screenWidth), static_cast<LONG>(screenHeight) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;

	auto posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, windowName, windowName,
		dwStyle,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	ShowCursor(true);
}

const HWND& Window::GetHWND() const
{
	return hWnd;
}

void Window::ShowMessageBox(const LPCWSTR& text, const LPCWSTR& caption)
{
	MessageBox(hWnd, text, caption, MB_OK);
}
