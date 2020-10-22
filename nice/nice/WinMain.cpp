#include "xWindows.h"
#include "Window.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow ) {

	Window win (800, 400, "I live in Germany");

	MSG msg;
	BOOL return_msg;

	while (return_msg = GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (return_msg == -1) {
		return -1;
	}
	
	return msg.wParam;	
}