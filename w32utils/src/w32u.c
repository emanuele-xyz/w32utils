#include <w32u.h>

void w32u_log(w32u_logger logger, w32u_log_lvl level, const char* msg)
{
	level = level < W32U_LOG_LVL_CRASH ? W32U_LOG_LVL_CRASH : (level > W32U_LOG_LVL_TRACE ? W32U_LOG_LVL_TRACE : level);

	if (level <= logger.level)
	{
		if (w32u_is_handle_valid(logger.file))
		{
			// WriteFile
		}

		if (w32u_is_handle_valid(logger.stdout) && w32u_is_handle_valid(logger.stderr))
		{
			// GetConsoleScreenBufferInfo
			// SetConsoleTextAttribute
			// WriteConsole
			// SetConsoleTextAttribute
		}

		if (logger.debug)
		{
			OutputDebugStringA(msg);
		}
	}
}
