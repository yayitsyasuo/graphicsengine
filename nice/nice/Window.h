#pragma once
#include "xWindows.h"
class Window
{
private:
	class WindowClass {
	public:
		static HINSTANCE GetHinstance();
		static constexpr const char* GetName();
	private:
		WindowClass() noexcept; // register the Window Class
		~WindowClass();
		HINSTANCE hInst;		 // that's the bullshit parameter in INT CALLBACK WinMain()
								 // we don't have the entry point here so we use the other function that returns it
		static WindowClass wndClass;
		static constexpr const char* ClassName = "Battlefield 1944"; // since it is const, we can't change it - why not make it private
	};
public:
	Window(int width, int height, const char* name); // creating a window, CREATEWNDEX returns a Handle
	~Window();
private:
	static LRESULT CALLBACK WindowProcSetup(HWND handle, UINT msg, WPARAM wParam, LPARAM lPAram);
	static LRESULT CALLBACK WindowPassOn(HWND handle, UINT msg, WPARAM wParam, LPARAM lPAram);
	LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lPAram);
private:
	HWND handle;  // return from CREATEWNDEX
};

