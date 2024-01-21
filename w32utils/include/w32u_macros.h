#pragma once

#include <w32u_windows.h>
#include <w32u_window.h>

#define w32u_is_handle_valid(h) (h != INVALID_HANDLE_VALUE)

#define w32u_internal_stringify(x) #x
#define w32u_stringify(x) w32u_internal_stringify(x)

#define w32u_at __FILE__ "(" w32u_stringify(__LINE__) ")"

#if defined(W32U_DEBUG)
#define w32u_break(msg) __debugbreak()
#elif defined(W32U_RELEASE)
#define w32u_break(msg) do { w32u_show_error_popup(w32u_at ": " msg); (*((int*)(0)) = 0); } while (0)
#else
#error Either W32U_DEBUG or W32U_RELEASE must be defined
#endif

#define w32u_assert(p) do { if (!(p)) { w32u_break("Assertion failed " #p); } } while (0)
#define w32u_assert_hr(hr) w32u_assert(SUCCEEDED(hr))

#define w32u_check(call) do { int res = (call); if (!res) { w32u_break(#call " failed"); } } while (0)
#define w32u_check_hr(call) do { HRESULT hr = (call); if (!SUCCEEDED(hr)) { w32u_break(#call " failed"); } } while (0)
