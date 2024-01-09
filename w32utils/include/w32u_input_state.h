#pragma once

#include <w32u_windows.h>
#include <w32u_window.h>

/*
	TODO: write doc

	VK_OEM_CLEAR is the highest key code.
	Read here: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
*/
typedef struct w32u_input_state
{
	struct
	{
		int wheel;
		int x;
		int y;
		int lbutton;
		int mbutton;
		int rbutton;
	} mouse;
	struct
	{
		int key[VK_OEM_CLEAR];
	} keyboard;
} w32u_input_state;

void w32u_update_input(w32u_input_state* input, w32u_msg* buf, int buf_size);
