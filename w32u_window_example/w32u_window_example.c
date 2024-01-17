#include <w32u.h>

LRESULT window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int* is_running = (int*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);

    LRESULT result = 0;
    if (msg == WM_CLOSE)
    {
        *is_running = 0;

        /* NOTE:
            Passing this message to DefWindowProc would destroy the window.
            We usually don't want this.
            In a game, for example, the user should exit using a menu.
            If the user tries to close the window, the game will pop a message like "do you want to exit the game?".
            Hence, we "catch" this message.
        */
        result = 0;
    }
    else
    {
        result = DefWindowProcA(hwnd, msg, wparam, lparam);
    }
    return result;
}

int main(void)
{
    BOOL is_dpi_aware = w32u_make_dpi_aware();
    if (!is_dpi_aware) w32u_show_error_popup("Failed to set DPI awareness");

    const char* class_name = "my_window_class_name";
    ATOM class_registered = w32u_register_window_class(class_name);
    if (!class_registered) w32u_show_error_popup("Failed to register window class");

    int is_running = 1;
    HWND window = w32u_create_window(class_name, "Window", 1280, 720, WS_OVERLAPPEDWINDOW, window_proc, &is_running);
    if (!window) w32u_show_error_popup("Failed create window");

    while (is_running)
    {
        /* NOTE:
        *  This loop is called a message pump.
        *  It is used to dispatch pending messages to the window procedure.
        *  We use this message pump to fill the window's message buffer using the specified window procedure.
        */
        {
            MSG msg = { 0 };
            while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }
    }

    DestroyWindow(window);
    UnregisterClassA(class_name, 0);

    return 0;
}
