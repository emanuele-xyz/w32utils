#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define w32u_is_handle_valid(h) (h != INVALID_HANDLE_VALUE)

typedef enum w32u_log_lvl
{
	W32U_LOG_LVL_CRASH,
	W32U_LOG_LVL_ERROR,
	W32U_LOG_LVL_WARN,
	W32U_LOG_LVL_INFO,
	W32U_LOG_LVL_DEBUG,
	W32U_LOG_LVL_TRACE,
} w32u_log_lvl;

typedef struct w32u_logger
{
	HANDLE file;
	HANDLE stdout;
	HANDLE stderr;
	BOOL debug;
	int level;
} w32u_logger;

void w32u_log(w32u_logger logger, w32u_log_lvl level, const char* msg);
