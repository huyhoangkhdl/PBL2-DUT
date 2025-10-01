// Utility.cpp
#include "Utility.h"
#include <cstdlib> // để dùng system()

void cls() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear"); // Linux/Mac
#endif
}
