#pragma once
#pragma once
#include "windows.h" // acceder a la api de windows
#include "iostream"
#include "random"

using namespace std;
using namespace System;

void GoTo(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}