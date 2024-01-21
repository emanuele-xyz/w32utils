#include <w32u.h>

typedef struct window_data
{
    int* is_running;
    w32u_input_state* input_state;
} window_data;

LRESULT window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    window_data* data = (window_data*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    int* is_running = data->is_running;
    w32u_input_state* input_state = data->input_state;

    LRESULT result = 0;
    switch (msg)
    {
    case WM_CLOSE:
    {
        *is_running = 0;
        result = 0;
    } break;
    case WM_MOUSEWHEEL:
    {
        input_state->mouse.wheel = GET_WHEEL_DELTA_WPARAM(wparam);
    } break;
    case WM_MOUSEMOVE:
    {
        input_state->mouse.x = GET_X_LPARAM(lparam); input_state->mouse.y = GET_Y_LPARAM(lparam);
    } break;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    {
        input_state->mouse.lbutton = (msg == WM_LBUTTONDOWN);
    } break;
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    {
        input_state->mouse.mbutton = (msg == WM_MBUTTONDOWN);
    } break;
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    {
        input_state->mouse.rbutton = (msg == WM_RBUTTONDOWN);
    } break;
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        input_state->keyboard.key[wparam] = (msg == WM_KEYDOWN);
    } break;
    default:
    {
        result = DefWindowProcA(hwnd, msg, wparam, lparam);
    } break;
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

    /*
        NOTE:
        We keep track of the previous and the current input states.
        I tend to use this approach, instead of relying directly on the OS, because:
        - It lets me keep track of multiple input states at once.
        - It lets me generate custom input events.
    */
    w32u_input_state input_buf[2] = { 0 };
    int input_idx = 0;
    
    w32u_check(w32u_make_dpi_aware());

    const char* class_name = "my_window_class_name";
    w32u_check(w32u_register_window_class(class_name));

    int is_running = 1;
    window_data window_data = { 0 };
    window_data.is_running = &is_running;
    window_data.input_state = &input_buf[curr_input(input_idx)];

    HWND window = 0;
    w32u_check(w32u_create_window(class_name, "Window", 1280, 720, WS_OVERLAPPEDWINDOW, window_proc, &window_data, &window));

    while (is_running)
    {
        /*
            NOTE:
            Make next input state current and copy the previous state to the current state.
            We clear the mouse wheel, since mouse wheel input is not permanent between frames.
            At the end, remember to update the window data struct.
        */
        input_idx = next_input(input_idx);
        input_buf[curr_input(input_idx)] = input_buf[prev_input(input_idx)];
        input_buf[curr_input(input_idx)].mouse.wheel = 0;
        window_data.input_state = &input_buf[curr_input(input_idx)];

        {
            MSG msg = { 0 };
            while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }

        {
            int was_pressed = input_buf[prev_input(input_idx)].keyboard.key['T'];
            int is_pressed = input_buf[curr_input(input_idx)].keyboard.key['T'];
            if (!was_pressed && is_pressed)
            {
                w32u_trace(logger, "Just pressed T ...");
            }
        }
    }

    DestroyWindow(window);
    UnregisterClassA(class_name, 0);

    return 0;
}
