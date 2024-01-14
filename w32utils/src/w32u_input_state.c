#include <w32u_input_state.h>

void w32u_update_input(w32u_input_state* input, w32u_msg* buf, int buf_size)
{
	for (int i = 0; i < buf_size; i++)
	{
		switch (buf[i].msg)
		{
		case WM_MOUSEWHEEL: { input->mouse.wheel = GET_WHEEL_DELTA_WPARAM(buf[i].wparam); } break;
		case WM_MOUSEMOVE: { input->mouse.x = GET_X_LPARAM(buf[i].lparam); input->mouse.y = GET_Y_LPARAM(buf[i].lparam); } break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP: { input->mouse.lbutton = (buf[i].msg == WM_LBUTTONDOWN); } break;
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP: { input->mouse.mbutton = (buf[i].msg == WM_MBUTTONDOWN); } break;
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP: { input->mouse.rbutton = (buf[i].msg == WM_RBUTTONDOWN); } break;
		case WM_KEYDOWN:
		case WM_KEYUP: { input->keyboard.key[buf[i].wparam] = (buf[i].msg == WM_KEYDOWN); } break;
		}
	}
}
