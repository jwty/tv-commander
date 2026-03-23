#ifndef CONFIG_DEF_H_
#define CONFIG_DEF_H_

// Defines for config defaults, overriden at runtime via config file

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 320
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 240
#endif

#ifndef AUTOSCALE
#define AUTOSCALE 1
#endif

#ifndef PATH_DEFAULT
#define PATH_DEFAULT getenv("PWD")
#endif

#ifndef PATH_DEFAULT_RIGHT
#define PATH_DEFAULT_RIGHT getenv("HOME")
#endif

#ifndef CMDR_KEY_UP
#define CMDR_KEY_UP SDLK_UP
#endif
#ifndef CMDR_KEY_RIGHT
#define CMDR_KEY_RIGHT SDLK_RIGHT
#endif
#ifndef CMDR_KEY_DOWN
#define CMDR_KEY_DOWN SDLK_DOWN
#endif
#ifndef CMDR_KEY_LEFT
#define CMDR_KEY_LEFT SDLK_LEFT
#endif
#ifndef CMDR_KEY_SYSTEM
#define CMDR_KEY_SYSTEM SDLK_ESCAPE
#endif
#ifndef CMDR_KEY_PAGEUP
#define CMDR_KEY_PAGEUP SDLK_PAGEUP
#endif
#ifndef CMDR_KEY_PAGEDOWN
#define CMDR_KEY_PAGEDOWN SDLK_PAGEDOWN
#endif
#ifndef CMDR_KEY_OPEN
#define CMDR_KEY_OPEN SDLK_RETURN
#endif
#ifndef CMDR_KEY_PARENT
#define CMDR_KEY_PARENT SDLK_BACKSPACE
#endif
#ifndef CMDR_KEY_OPERATION
#define CMDR_KEY_OPERATION SDLK_SPACE
#endif
#ifndef CMDR_KEY_SELECT
#define CMDR_KEY_SELECT SDLK_INSERT
#endif
#ifndef CMDR_KEY_TRANSFER
#define CMDR_KEY_TRANSFER SDLK_TAB
#endif

#ifndef CMDR_GAMEPAD_UP
#define CMDR_GAMEPAD_UP ControllerButton::UP
#endif
#ifndef CMDR_GAMEPAD_DOWN
#define CMDR_GAMEPAD_DOWN ControllerButton::DOWN
#endif
#ifndef CMDR_GAMEPAD_LEFT
#define CMDR_GAMEPAD_LEFT ControllerButton::LEFT
#endif
#ifndef CMDR_GAMEPAD_RIGHT
#define CMDR_GAMEPAD_RIGHT ControllerButton::RIGHT
#endif
#ifndef CMDR_GAMEPAD_SYSTEM
#define CMDR_GAMEPAD_SYSTEM ControllerButton::X
#endif
#ifndef CMDR_GAMEPAD_PAGEUP
#define CMDR_GAMEPAD_PAGEUP ControllerButton::LEFTSHOULDER
#endif
#ifndef CMDR_GAMEPAD_PAGEDOWN
#define CMDR_GAMEPAD_PAGEDOWN ControllerButton::RIGHTSHOULDER
#endif
#ifndef CMDR_GAMEPAD_OPEN
#define CMDR_GAMEPAD_OPEN ControllerButton::B
#endif
#ifndef CMDR_GAMEPAD_PARENT
#define CMDR_GAMEPAD_PARENT ControllerButton::A
#endif
#ifndef CMDR_GAMEPAD_OPERATION
#define CMDR_GAMEPAD_OPERATION ControllerButton::Y
#endif
#ifndef CMDR_GAMEPAD_SELECT
#define CMDR_GAMEPAD_SELECT ControllerButton::SELECT
#endif
#ifndef CMDR_GAMEPAD_TRANSFER
#define CMDR_GAMEPAD_TRANSFER ControllerButton::START
#endif

#endif // CONFIG_DEF_H_
