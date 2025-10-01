#include "Game.h"
#include "Utility.h"
#include <iostream>
#include <windows.h>
using namespace std;
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Chọn chế độ chơi:\n";
    cout << "1. Người vs Người\n";
    cout << "2. Người vs AI\n";
    int mode;
    cin >> mode;

    Game game(mode == 2); // nếu chọn 2 thì vsAI = true
    game.start();

    return 0;
}
