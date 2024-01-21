#pragma once

#include <w32u_windows.h>

/*
    Show error popup window and wait for it to be closed.
*/
void w32u_show_error_popup(const char* msg);

/*
    Force newly created windows to be DPI aware.
    The return value tells whether ot not the function succeeded.
*/
BOOL w32u_make_dpi_aware(void);

/*
    Register basic window class.
    If the function succeeds, the return value is a class atom that uniquely identifies the class being registered.
    If the function fails, the return value is zero.
*/
ATOM w32u_register_window_class(const char* class_name);

/*
    Create a window.
    If the function succeeds, the return value is 1.
    If the function fails, the return value is 0.
*/
int w32u_create_window(const char* class_name, const char* title, int w, int h, DWORD style, WNDPROC window_proc, void* user_data, HWND* out_hwnd);
