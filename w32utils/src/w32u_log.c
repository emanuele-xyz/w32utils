#include <w32u.h>
#include <stdio.h>

#define W32U_LOG_BUFFER_SIZE 4096

static char s_buffer[W32U_LOG_BUFFER_SIZE] = { 0 };

void w32u_log(w32u_logger logger, w32u_log_lvl level, const char* msg)
{
    level = level < W32U_LOG_LVL_CRASH ? W32U_LOG_LVL_CRASH : (level > W32U_LOG_LVL_TRACE ? W32U_LOG_LVL_TRACE : level);
    msg = msg ? msg : "";

    if (level <= logger.level)
    {
        const char* header = "";
        switch (level)
        {
        case W32U_LOG_LVL_CRASH: { header = "CRASH"; } break;
        case W32U_LOG_LVL_ERROR: { header = "ERROR"; } break;
        case W32U_LOG_LVL_WARN:  { header = "WARN";  } break;
        case W32U_LOG_LVL_INFO:  { header = "INFO";  } break;
        case W32U_LOG_LVL_DEBUG: { header = "DEBUG"; } break;
        case W32U_LOG_LVL_TRACE: { header = "TRACE"; } break;
        }

        int len = _snprintf_s(s_buffer, W32U_LOG_BUFFER_SIZE, W32U_LOG_BUFFER_SIZE - 1, "[%s]: %s\n", header, msg);
        if (len > 0)
        {
            if (w32u_is_handle_valid(logger.file))
            {
                WriteFile(logger.file, s_buffer, len, 0, 0);
            }

            if (w32u_is_handle_valid(logger.console_out) && w32u_is_handle_valid(logger.console_err))
            {
                HANDLE console = level <= W32U_LOG_LVL_ERROR ? logger.console_err : logger.console_out;

                CONSOLE_SCREEN_BUFFER_INFO console_buffer_info = { 0 };
                BOOL got_attributes = GetConsoleScreenBufferInfo(console, &console_buffer_info);

                WORD console_attribute = 0;
                switch (level)
                {
                case W32U_LOG_LVL_CRASH: { console_attribute = BACKGROUND_RED | BACKGROUND_INTENSITY;                     } break;
                case W32U_LOG_LVL_ERROR: { console_attribute = FOREGROUND_RED | FOREGROUND_INTENSITY;                     } break;
                case W32U_LOG_LVL_WARN:  { console_attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;  } break;
                case W32U_LOG_LVL_INFO:  { console_attribute = FOREGROUND_GREEN | FOREGROUND_INTENSITY;                   } break;
                case W32U_LOG_LVL_DEBUG: { console_attribute = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; } break;
                case W32U_LOG_LVL_TRACE: { console_attribute = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;   } break;
                }

                if (got_attributes)
                {
                    SetConsoleTextAttribute(console, console_attribute);
                }

                WriteConsoleA(console, s_buffer, len, 0, 0);

                if (got_attributes)
                {
                    SetConsoleTextAttribute(console, console_buffer_info.wAttributes);
                }
            }

            if (logger.debug)
            {
                OutputDebugStringA(s_buffer);
            }
        }
    }
}
