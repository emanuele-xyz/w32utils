#pragma once

#include <w32u_windows.h>
#include <w32u_window.h>

#define w32u_is_handle_valid(h) (h != INVALID_HANDLE_VALUE)

#define w32u_stringify(x) #x
#define w32u_to_string(x) w32u_stringify(x)

#if defined(W32U_DEBUG)
#define w32u_assert(p) do { if (!(p)) { __debugbreak(); } } while (0)
#elif defined(W32U_RELEASE)
#define w32u_assert(p) do { if (!(p)) { w32u_show_error_popup(__FILE__ "(" w32u_to_string(__LINE__) "): Assertion fail: " #p); (*((int*)(0)) = 0); } } while (0) 
#else
#error Either W32U_DEBUG or W32U_RELEASE must be defined
#endif
