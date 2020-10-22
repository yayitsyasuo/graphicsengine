#include "Window.h"

#define DefaultWindowStyle (WS_POPUP | WS_SYSMENU | WS_CAPTION| WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX |WS_TABSTOP| WS_MAXIMIZEBOX)
// shit that is static (GetHinstanace) doesn't have access to non-static member functions!
// solution?
// private: static WindowClass windowClass;
// and this thing here, idk why
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	: // could as well pass in the parameter (HINSTANCE hInstance) from the WinEntryPoint 
	hInst(GetModuleHandle(NULL))
{
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = NULL;
	// it will assign only to a STATIC function
	// STATIC function can't access no-static members - oops, we fkin need the Window Member
	wc.lpfnWndProc = WindowProcSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0,0,0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(ClassName, hInst);
}

HINSTANCE Window::WindowClass::GetHinstance()
{
	return wndClass.hInst;
}

constexpr const char * Window::WindowClass::GetName()
{
	return ClassName;
}

Window::Window(int width, int height, const char * name)
{
	RECT rect;
	rect.left = 0;
	rect.right = width + rect.left;
	rect.top = 0;
	rect.bottom = height + rect.top;

	AdjustWindowRect(&rect, DefaultWindowStyle, FALSE);
	//create the window
	handle = CreateWindowA(WindowClass::GetName(), name, DefaultWindowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
				   width, height, NULL, NULL, WindowClass::GetHinstance(), this);

	//show the goddamn window
	ShowWindow(handle, SW_SHOWDEFAULT);
}	

Window::~Window()
{
	DestroyWindow(handle);
}

LRESULT Window::WindowProcSetup(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	if (msg = WM_NCCREATE) {
		// literally a Setup- gets compiled only ONCE at the beginning
		const CREATESTRUCTA* const pCreateStruct = reinterpret_cast<CREATESTRUCTA*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreateStruct->lpCreateParams);
		SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WindowPassOn));
		// since now on
		// wc.lpfnWndProc = WindowPassOn;
		// this function never to be called again!
	}
	// if some weird shit pooped out before WM_NCREATE
	return DefWindowProc( handle, msg, wParam, lParam );
}

LRESULT Window::WindowPassOn(HWND handle, UINT msg, WPARAM wParam, LPARAM lPAram)
{
	// gotta extract that LONG_PTR Window
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
	return pWnd->WindowProc(handle, msg, wParam, lPAram);
}



LRESULT Window::WindowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg){
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		// for some reason, this line can't be in a static function
	// I mean this nigga can't call it since it can only CALL C++ static functions?
		return DefWindowProc(handle, msg, wParam, lParam);
	}
}
