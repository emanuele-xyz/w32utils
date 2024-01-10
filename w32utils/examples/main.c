#include "w32u.h"
#include <stdlib.h>

LRESULT window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	w32u_msg_buf* msg_buf = (w32u_msg_buf*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
	w32u_push_msg(msg_buf, (w32u_msg) { hwnd, msg, wparam, lparam });

	LRESULT result = 0;
	if (msg == WM_CLOSE)
	{
		/* NOTE
		*  Passing this message to DefWindowProc would destroy the window.
		*  We usually don't want this.
		*  In a game, for example, the user should exit using a menu.
		*  If the user tries to close the window, the game will pop a message like "do you want to exit the game?".
		*  Hence, we "catch" this message.
		*/
		result = 0;
	}
	else
	{
		result = DefWindowProcA(hwnd, msg, wparam, lparam);
	}
	return result;
}

void w32u_window_example(void)
{
	BOOL is_dpi_aware = w32u_make_dpi_aware();
	if (!is_dpi_aware) w32u_show_error_popup("Failed to set DPI awareness");

	const char* class_name = "my_window_class_name";
	ATOM class_registered = w32u_register_window_class(class_name);
	if (!class_registered) w32u_show_error_popup("Failed to register window class");

	w32u_msg_buf window_msg_buf = { 0 };
	window_msg_buf.capacity = 256;
	window_msg_buf.buf = calloc(window_msg_buf.capacity, sizeof(w32u_msg));
	HWND window = w32u_create_window(class_name, "Window", 1280, 720, WS_OVERLAPPEDWINDOW, &window_msg_buf, window_proc);
	if (!window) w32u_show_error_popup("Failed create window");

	int is_running = 1;
	while (is_running)
	{
		// NOTE: before starting new frame, we clear the previous window messages.
		w32u_clear_msg_buf(&window_msg_buf);

		/* NOTE:
		*  This loop is called a message pump.
		*  It is used to dispatch pending messages to the window procedure.
		*  We use this message pump to fill the window's message buffer using the specified window procedure.
		*/
		{
			MSG msg = { 0 };
			while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		// NOTE: handle messages inside the message buffer
		for (int i = 0; i < window_msg_buf.size; i++)
		{
			w32u_msg msg = window_msg_buf.buf[i];
			if (msg.msg == WM_CLOSE)
			{
				is_running = 0;
			}
		}
	}

	free(window_msg_buf.buf);
	CloseWindow(window);
	UnregisterClassA(class_name, 0);
}

void w32u_input_state_example(void)
{
	w32u_logger logger = { 0 };
	logger.file = INVALID_HANDLE_VALUE;
	logger.console_out = INVALID_HANDLE_VALUE;
	logger.console_err = INVALID_HANDLE_VALUE;
	logger.debug = 1;
	logger.level = W32U_LOG_LVL_TRACE;

	BOOL is_dpi_aware = w32u_make_dpi_aware();
	if (!is_dpi_aware) w32u_show_error_popup("Failed to set DPI awareness");

	const char* class_name = "my_window_class_name";
	ATOM class_registered = w32u_register_window_class(class_name);
	if (!class_registered) w32u_show_error_popup("Failed to register window class");

	w32u_msg_buf window_msg_buf = { 0 };
	window_msg_buf.capacity = 256;
	window_msg_buf.buf = calloc(window_msg_buf.capacity, sizeof(w32u_msg));
	HWND window = w32u_create_window(class_name, "Window", 1280, 720, WS_OVERLAPPEDWINDOW, &window_msg_buf, window_proc);
	if (!window) w32u_show_error_popup("Failed create window");

	int is_running = 1;
	while (is_running)
	{
		w32u_clear_msg_buf(&window_msg_buf);

		{
			MSG msg = { 0 };
			while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		for (int i = 0; i < window_msg_buf.size; i++)
		{
			w32u_msg msg = window_msg_buf.buf[i];
			if (msg.msg == WM_CLOSE)
			{
				is_running = 0;
			}
		}
	}

	free(window_msg_buf.buf);
	CloseWindow(window);
	UnregisterClassA(class_name, 0);
}

int main(void)
{
	w32u_window_example();
	w32u_input_state_example();

	return 0;
}
