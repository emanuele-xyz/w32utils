#include <w32u.h>

int main(void)
{
	// NOTE: when opening a file or getting std handles, you should check for errors
	w32u_logger logger = { 0 };
	logger.file = CreateFileA("log.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
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

	CloseHandle(logger.file);

	return 0;
}
