#include <w32u_window.h>

void w32u_show_error_popup(const char* msg)
{
	MessageBoxA(0, msg, 0, MB_OK | MB_ICONERROR);
}

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

typedef struct w32u_create_window_create_params
{
	w32u_msg_buf* msg_buf;
	WNDPROC window_proc;
} w32u_create_window_create_params;

static LRESULT w32u_window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result = 0;
	if (msg == WM_CREATE)
	{
		CREATESTRUCT* create = (CREATESTRUCT*)lparam;
		w32u_create_window_create_params* create_params = create->lpCreateParams;
		SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)create_params->msg_buf);
		SetWindowLongPtrA(hwnd, GWLP_WNDPROC, (LONG_PTR)create_params->window_proc);
		/* 
		*  NOTE: From https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlongptra#remarks
		*  Certain window data is cached, so changes you make using SetWindowLongPtr will not take effect until you call the SetWindowPos function.
		*  I'm not sure which data is cached.
		*/
		SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		result = create_params->window_proc(hwnd, msg, wparam, lparam);
	}
	else
	{
		result = DefWindowProcA(hwnd, msg, wparam, lparam);
	}
	return result;
}

ATOM w32u_register_window_class(const char* class_name)
{
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW; // NOTE: redraw the entire client area on change dimension change.
	wc.lpfnWndProc = w32u_window_proc;
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

HWND w32u_create_window(const char* class_name, const char* title, int w, int h, DWORD style, w32u_msg_buf* msg_buf, WNDPROC window_proc)
{
	HWND hwnd = 0;

	RECT rect = { 0, 0, w, h };
	BOOL got_dimensions = AdjustWindowRect(&rect, style, 0);
	if (got_dimensions)
	{
		int window_w = rect.right - rect.left;
		int window_h = rect.bottom - rect.top;
		w32u_create_window_create_params lparam = { 0 };
		lparam.msg_buf = msg_buf;
		lparam.window_proc = window_proc;
		hwnd = CreateWindowA(class_name, title, style | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, window_w, window_h, 0, 0, GetModuleHandleA(0), &lparam);
	}

	return hwnd;
}

void w32u_push_msg(w32u_msg_buf* msg_buf, w32u_msg msg)
{
	if (msg_buf && msg_buf->size < msg_buf->capacity)
	{
		msg_buf->buf[msg_buf->size] = msg;
		msg_buf->size++;
	}
}

void w32u_clear_msg_buf(w32u_msg_buf* msg_buf)
{
	if (msg_buf)
	{
		msg_buf->size = 0;
	}
}
