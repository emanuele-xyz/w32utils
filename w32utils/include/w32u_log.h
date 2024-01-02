#pragma once

#include <w32u_windows.h>

typedef enum w32u_log_lvl
{
	W32U_LOG_LVL_CRASH,
	W32U_LOG_LVL_ERROR,
	W32U_LOG_LVL_WARN,
	W32U_LOG_LVL_INFO,
	W32U_LOG_LVL_DEBUG,
	W32U_LOG_LVL_TRACE,
} w32u_log_lvl;

// TODO: Add documentation
typedef struct w32u_logger
{
	HANDLE file;
	HANDLE console_out;
	HANDLE console_err;
	BOOL debug;
	int level;
} w32u_logger;

// TODO: Add documentation
void w32u_log(w32u_logger logger, w32u_log_lvl level, const char* msg);

#define w32u_crash(logger, msg) w32u_log(logger, W32U_LOG_LVL_CRASH, msg)
#define w32u_error(logger, msg) w32u_log(logger, W32U_LOG_LVL_ERROR, msg)
#define w32u_warn(logger, msg)  w32u_log(logger, W32U_LOG_LVL_WARN,  msg)
#define w32u_info(logger, msg)  w32u_log(logger, W32U_LOG_LVL_INFO,  msg)
#define w32u_debug(logger, msg) w32u_log(logger, W32U_LOG_LVL_DEBUG, msg)
#define w32u_trace(logger, msg) w32u_log(logger, W32U_LOG_LVL_TRACE, msg)
