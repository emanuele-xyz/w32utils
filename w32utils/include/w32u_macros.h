#pragma once

#include <w32u_windows.h>

#define w32u_is_handle_valid(h) (h != INVALID_HANDLE_VALUE)

#if defined(W32U_DEBUG)
#define w32u_assert(p) do { if (!(p)) { __debugbreak(); } } while (0)
#elif defined(W32U_RELEASE)
#define w32u_assert(p) do { if (!(p)) { (*((int*)(0)) = 0); } } while (0) 
#else
#error Either W32U_DEBUG or W32U_RELEASE must be defined
#endif
