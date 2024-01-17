#pragma once

#include <w32u_windows.h>
#include <w32u_window.h>

/*
    If you want to know more, read the following links:
    - For mouse input:
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousewheel
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondown
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttonup
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttondown
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttonup
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttondown
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttonup
    - For keyboard input:
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-keydown
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-keyup
        > https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
*/

/*
    Mouse Input
    - wheel: Wheel rotation in multiples or divisions of WHEEL_DELTA.
             Positive when rotating forward, away from the user.
             Negative when rotating backward, toward the user.
    - x|y: Cursor x|y coordinate, relative to the upper left corner of the client area.
    - (l|m|r)button: Mouse left|middle|right button. 1 if pressed, 0 otherwise.

    Keyboard Input
    - key: Keyboard keys. Indexed by virtual key codes. 1 if pressed, 0 otherwise.
           VK_OEM_CLEAR is the highest key code.
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
