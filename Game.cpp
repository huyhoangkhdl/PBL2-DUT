#include "Mylib.h"
using namespace std;

Game::Game(bool aiMode) : vsAI(aiMode) {}

void Game::start() {
    board.printBoard();

    while (!board.get_is_over_game()) {
        PlayerColor current = board.getCurrentPlayer();

        cout << "Lượt " 
             << (current == PlayerColor::RED ? "ĐỎ" : "ĐEN")
             << "\n";

        if (vsAI && current == PlayerColor::BLACK) {
            // ==== Nước đi của AI ====
            cout << "🤖 AI đang tính toán...\n";
            Move best = board.findBestMove(current, 3); // độ sâu tìm kiếm
            if (best.fromX == -1) {
                cout<< "AI không còn nước đi!\n";
                cout<<"Bạn thắng!";
                Sleep(3000);
                break;
            }

            board.simulateMove(best); // dùng simulateMove (tự đổi lượt)
        } 
        else {
            // ==== Nước đi của người chơi ====
            cout << "Nhập nước đi (fromX fromY toX toY), "
                 << "u=undo, r=redo, q=quit: ";

            string cmd;
            cin >> cmd;

            if (cmd == "u") {
                board.undoMove();
            } 
            else if (cmd == "r") {
                board.redoMove();
            } 
            else if (cmd == "q") {
                cout << "Bạn đã thoát game.\n";
                break;
            } 
            else {
                int fromX = stoi(cmd);
                int fromY, toX, toY;
                cin >> fromY >> toX >> toY;
                if (fromX == -1 && fromY == -1 && toX == -1 && toY == -1) {
                    cout << "Bạn đã thoát game.\n";
                    break;
                }

                bool moved = board.movePiece(fromX, fromY, toX, toY);
                if (!moved) {
                    cout << "❌ Nước đi không hợp lệ. Vui lòng nhập lại!\n";
                    continue;
                }
            }
        }

        board.printBoard();

        if (board.is_game_over()) {
            cout << "🎉 Game over! ";
            cout << (board.getCurrentPlayer() == PlayerColor::RED ? "Đen" : "Đỏ")
                 << " thắng!\n";
                 Sleep(3000);
            break;
        }
    }
}
