#include "AddPersistance.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

bool AddPersistence(const wstring& filePath) {
    HKEY hkey;
    LONG key = RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hkey);
    if (ERROR_SUCCESS == key) {
        key = RegSetValueExW(hkey, L"Testing", 0, REG_SZ, (BYTE*)filePath.c_str(), sizeof(wchar_t) * (filePath.length() + 1));
        RegCloseKey(hkey);
    }
    return (ERROR_SUCCESS == key);
}

bool RemovePersistence() {
    HKEY hkey;
    LONG key = RegOpenKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
    if (ERROR_SUCCESS == key) {
        key = RegDeleteValueW(hkey, L"Testing");
        RegCloseKey(hkey);
    }
    return (ERROR_SUCCESS == key);
}

