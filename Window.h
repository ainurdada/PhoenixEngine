#pragma once

#include <wrl.h>

class Window
{
public:
	void Create(LPCWSTR windowName, int screenWidth, int screenHeight);
	const HWND& GetHWND() const;
	void ShowMessageBox(const LPCWSTR& text, const LPCWSTR& caption);
public:
	int ClientHeight;
	int ClientWidth;

private:
	HWND hWnd;
	HINSTANCE hInstance;
	WNDCLASSEX wc;
};

