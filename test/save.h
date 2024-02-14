#ifndef SAVE_H
#define SAVE_H

#include <string>

// Function to save keystrokes to a queue
void save(std::string text);

// Function to continuously save keystrokes from the queue to a file
void saveLoop();

#endif // SAVE_H