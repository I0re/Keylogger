# Keylogger
The test folder contains the program for the keylogger.

The program will open a terminal window and immediately grab information about the PC it is being run on. information such as MAC addresses of WiFi and Ethernet, external IP, CPU, motherboard, RAM, GPU, OS info, and hostname. (The terminal window will not be invisible because Line 65 is in main.cpp: ShowWindow(GetConsoleWindow(), SW_HIDE); is currently commented out. This is because then the system information will not be shown. (Currently, system information is being outputted to the terminal, but it can be easily made to output system information to the created "keys.txt" file so that you can hide the terminal window and still get the system information.).

The program will store keystrokes in the "keys.txt" file (which can be changed), and once a signal of program termination is received (CTRL+C), the program will send the data in the text file to pastebin through the pastebin API.

Including and linking both curl and systeminfo are required to be done by the user. (If it is requested, I can configure the project with CMake so as not to have the user manually include and link both the curl and systeminfo libraries.).

The keystroked data is saved and added to a queue for as long as the program is running and the terminal signal has not been received.

The program will also attach itself to the computer's registry to enable persistence and be reactivated at every startup.

# Demo

https://github.com/andresv1/Keylogger/assets/95900417/a372126a-14be-4d35-bee3-57a2421cf2e0

