#include "w32u.h"
#include "stdio.h" // TODO: to be removed

void w32u_log_example(void)
{
	// NOTE: when opening a file or getting std handles, you should check for errors
	w32u_logger logger = { 0 };
	logger.file = CreateFileA("log.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);;
	logger.console_out = GetStdHandle(STD_OUTPUT_HANDLE);
	logger.console_err = GetStdHandle(STD_ERROR_HANDLE);
	logger.debug = 1;
	logger.level = W32U_LOG_LVL_TRACE;

	w32u_crash(logger, "Hello!");
	w32u_error(logger, "Hello!");
	w32u_warn(logger, "Hello!");
	w32u_info(logger, "Hello!");
	w32u_debug(logger, "Hello!");
	w32u_trace(logger, "Hello!");
}

void w32u_window_example(void)
{
	BOOL is_dpi_aware = w32u_make_dpi_aware();
	if (!is_dpi_aware) w32u_show_error_popup("Failed to set DPI awareness");

	const char* class_name = "my_window_class_name";
	ATOM class_registered = w32u_register_window_class(class_name);
	if (!class_registered) w32u_show_error_popup("Failed to register window class");
	HWND window = w32u_create_window(class_name, "Window", 1280, 720, WS_OVERLAPPEDWINDOW);
	if (!window) w32u_show_error_popup("Failed create window");

	int is_running = 1;
	while (is_running)
	{
		MSG msg = { 0 };
		while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
}

int main(void)
{
	w32u_log_example();
	w32u_window_example();

	return 0;
}
