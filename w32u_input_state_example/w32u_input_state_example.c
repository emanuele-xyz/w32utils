#include <w32u.h>

LRESULT window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    w32u_msg_buf* msg_buf = (w32u_msg_buf*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    w32u_push_msg(msg_buf, (w32u_msg) { hwnd, msg, wparam, lparam });

    LRESULT result = 0;
    if (msg == WM_CLOSE)
    {
        result = 0;
    }
    else
    {
        result = DefWindowProcA(hwnd, msg, wparam, lparam);
    }
    return result;
}

#define curr_input(idx) (idx)
#define next_input(idx) (((idx) + 1) % 2)
#define prev_input(idx) next_input(idx)

int main(void)
{
    w32u_logger logger = { 0 };
    logger.file = INVALID_HANDLE_VALUE;
    logger.console_out = INVALID_HANDLE_VALUE;
    logger.console_err = INVALID_HANDLE_VALUE;
    logger.debug = 1;
    logger.level = W32U_LOG_LVL_TRACE;

    BOOL is_dpi_aware = w32u_make_dpi_aware();
    if (!is_dpi_aware) w32u_show_error_popup("Failed to set DPI awareness");

    const char* class_name = "my_window_class_name";
    ATOM class_registered = w32u_register_window_class(class_name);
    if (!class_registered) w32u_show_error_popup("Failed to register window class");

    w32u_msg_buf window_msg_buf = { 0 };
    window_msg_buf.capacity = 256;
    window_msg_buf.buf = VirtualAlloc(0, window_msg_buf.capacity * sizeof(w32u_msg), MEM_COMMIT, PAGE_READWRITE);
    HWND window = w32u_create_window(class_name, "Window", 1280, 720, WS_OVERLAPPEDWINDOW, &window_msg_buf, window_proc);
    if (!window) w32u_show_error_popup("Failed create window");

    /*
        NOTE:
        We keep track of the previous and the current input states.
        I tend to use this approach, instead of relying directly on the OS, because:
        - It lets me keep track of multiple input states at once.
        - It lets me generate custom input events.
    */
    w32u_input_state input_buf[2] = { 0 };
    int input_idx = 0;

    int is_running = 1;
    while (is_running)
    {
        w32u_clear_msg_buf(&window_msg_buf);

        /*
            NOTE:
            Make next input state current and copy the previous state to the current state.
            We clear the mouse wheel, since mouse wheel input is not permanent between frames.
        */
        input_idx = next_input(input_idx);
        input_buf[curr_input(input_idx)] = input_buf[prev_input(input_idx)];
        input_buf[curr_input(input_idx)].mouse.wheel = 0;

        {
            MSG msg = { 0 };
            while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }

        for (int i = 0; i < window_msg_buf.size; i++)
        {
            w32u_msg msg = window_msg_buf.buf[i];
            if (msg.msg == WM_CLOSE)
            {
                is_running = 0;
            }
        }

        w32u_update_input(&input_buf[curr_input(input_idx)], window_msg_buf.buf, window_msg_buf.size);

        {
            int was_t_pressed = input_buf[prev_input(input_idx)].keyboard.key['T'];
            int is_t_pressed = input_buf[curr_input(input_idx)].keyboard.key['T'];
            if (!was_t_pressed && is_t_pressed)
            {
                w32u_trace(logger, "Just pressed T ...");
            }
        }
    }

    CloseWindow(window);
    UnregisterClassA(class_name, 0);
    VirtualFree(window_msg_buf.buf, 0, MEM_RELEASE);

    return 0;
}
