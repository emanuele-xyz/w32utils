# Win32 Utility Library

w32utils is a collection of Win32 boilerplate code and useful utilities to simplify working with the Win32 API.

## Features

- `w32u_macros.h`: Collection of useful macros.
- `w32u_log.h`: Utility for simple logging to a file and/or to the console and/or to the debug output.
- `w32u_window.h`: Utility for creating windows.
- `w32u_input_state.h`: Utility for storing user input.

## Examples

Alongside the library itself, we provide some example programs that describe how to actually use it.
These programs should be read in the following order:
- *w32u_log_example*
- *w32u_window_example*
- *w32u_input_state_example*

## Integration

To integrate the library in your own project, you just need the files inside these folders:
- `w32utils\include`
- `w32utils\src`

There are no external dependencies.

## Supported Platforms

This library is *Windows* only.

## Future Development

I often find myself using the Win32 API when I work on my hobby game programming projects.
I intend to put in this library the Win32 code that can be factored out from these projects for better reusability.

## TODOs
- [ ] Add support for unicode character set.
