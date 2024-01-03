#include <w32u_window.h>

/*
	Force newly created windows to be DPI aware.
	The return value tells whether ot not the function succeeded.
*/
BOOL w32u_make_dpi_aware(void)
{
	/*
		On Windows, if you go on Display Settings, you can change the display's scale.
		From what I understand, this changes the display's DPI.
		This messes up things such as window dimensions and coordinates.
		To solve this we can force the windows we create to be DPI aware.
		Read here for more details: https://learn.microsoft.com/en-us/windows/win32/hidpi/dpi-awareness-context.
	*/
	return SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
}

/*
	Register basic window class.
	If the function succeeds, the return value is a class atom that uniquely identifies the class being registered.
	If the function fails, the return value is zero.
*/
ATOM w32u_register_window_class(const char* class_name)
{
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW; // NOTE: redraw the entire client area on change dimension change.
	wc.lpfnWndProc = DefWindowProcA;
	//wc.cbClsExtra = ;
	//wc.cbWndExtra = ;
	wc.hInstance = GetModuleHandleA(0);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	//wc.hbrBackground = ;
	//wc.lpszMenuName = ;
	wc.lpszClassName = class_name;
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
	return RegisterClassExA(&wc);
}

/*
	Create a window.
	If the function succeeds, the return value is a handle to the new window.
	If the function fails, the return value is 0.
*/
HWND w32u_create_window(const char* class_name, const char* title, int w, int h, DWORD style)
{
	HWND hwnd = 0;

	RECT rect = { 0, 0, w, h };
	BOOL got_dimensions = AdjustWindowRect(&rect, style, 0);
	if (got_dimensions)
	{
		int window_w = rect.right - rect.left;
		int window_h = rect.bottom - rect.top;
		hwnd = CreateWindowA(class_name, title, style | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, window_w, window_h, 0, 0, GetModuleHandleA(0), 0);
	}

	return hwnd;
}
