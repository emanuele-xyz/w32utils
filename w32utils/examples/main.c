#include "w32u.h"
#include <stdlib.h>

#if 0
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
#endif
