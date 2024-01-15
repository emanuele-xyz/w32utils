#pragma once

#include <w32u_windows.h>

// Window message
typedef struct w32u_msg
{
    HWND hwnd;
    UINT msg;
    WPARAM wparam;
    LPARAM lparam;
} w32u_msg;

/*
    Window message buffer.
    buf: buffer of messages.
    size: current number of messages inside the buffers.
    capacity: maximum number of messages that may be inside the buffer.
    Valid messages have index in [0, size).
*/
typedef struct w32u_msg_buf
{
    w32u_msg* buf;
    int size;
    int capacity;
} w32u_msg_buf;

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
    If the function succeeds, the return value is a handle to the new window.
    If the function fails, the return value is 0.
*/
HWND w32u_create_window(const char* class_name, const char* title, int w, int h, DWORD style, w32u_msg_buf* msg_buf, WNDPROC window_proc);

// Push message to message buffer
void w32u_push_msg(w32u_msg_buf* msg_buf, w32u_msg msg);

// Clear message buffer
void w32u_clear_msg_buf(w32u_msg_buf* msg_buf);
