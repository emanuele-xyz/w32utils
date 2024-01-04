#pragma once

#include <w32u_windows.h>

void w32u_show_error_popup(const char* msg);
BOOL w32u_make_dpi_aware(void);
ATOM w32u_register_window_class(const char* class_name);
HWND w32u_create_window(const char* class_name, const char* title, int w, int h, DWORD style);
