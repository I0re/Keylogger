#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

//GET CPU, GPU, MOTHERBOARD(MAINBOARD), RAM, OS, MACADRESS, AND IP, HOSTNAME

class GetSYSinfo {
public:
    static void GetHostname();
    static int GetComputerInfo(int argc, char* argv[]);
    static char* GetMAC(int adapterType);
    static char* getMAC(int adapterType);
    static void GetExternalIPAddress();
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};