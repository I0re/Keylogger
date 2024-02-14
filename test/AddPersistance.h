#pragma once
#define ADDPERSISTANCE_H
#define ADDPERSISTANCE_H

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>

// Function to add persistence
bool AddPersistence(const std::wstring& filePath);

// Function to remove persistence
bool RemovePersistence();

