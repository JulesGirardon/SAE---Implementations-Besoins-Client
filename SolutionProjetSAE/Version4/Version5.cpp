#include <iostream>
#include <sstream>
#include <array>
#include "function.h"
#include "ui.h"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32


int main(int argc, char* argv[])
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

    Menu(argc, argv);
 
    return 0;
}