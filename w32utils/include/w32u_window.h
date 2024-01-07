#pragma once

#include <w32u_windows.h>

typedef struct w32u_msg
{
	HWND hwnd;
	UINT msg;
	WPARAM wparam;
	LPARAM lparam;
} w32u_msg;

typedef struct w32u_msg_buf
{
	w32u_msg* buf;
	int size;
	int capacity;
} w32u_msg_buf;

void w32u_show_error_popup(const char* msg);
BOOL w32u_make_dpi_aware(void);
ATOM w32u_register_window_class(const char* class_name);
HWND w32u_create_window(const char* class_name, const char* title, int w, int h, DWORD style, w32u_msg_buf* msg_buf, WNDPROC window_proc);
void w32u_push_msg(w32u_msg_buf* msg_buf, w32u_msg msg);
void w32u_clear_msg_buf(w32u_msg_buf* msg_buf);
