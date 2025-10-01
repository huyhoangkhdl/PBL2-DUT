#include "Mylib.h"
using namespace std;

void Board::clearAttackMap() { // Reset attack map
        memset(attackedByRed, 0, sizeof(attackedByRed));
        memset(attackedByBlack, 0, sizeof(attackedByBlack));
    }

        void Board::markAttacks(Piece* p) {
        if (!p) return;
        auto& attacked = (p->getColor() == PlayerColor::RED) ? attackedByRed : attackedByBlack;
        int x = p->getX();
        int y = p->getY();

        // Xe (Rock)
        if (dynamic_cast<Rock*>(p)) {
            for (int i = x + 1; i < 10; i++) { attacked[i][y] = true; if (grid[i][y]) break; }
            for (int i = x - 1; i >= 0; i--) { attacked[i][y] = true; if (grid[i][y]) break; }
            for (int j = y + 1; j < 9; j++)  { attacked[x][j] = true; if (grid[x][j]) break; }
            for (int j = y - 1; j >= 0; j--) { attacked[x][j] = true; if (grid[x][j]) break; }
        }

        // Mã (Knight)
        if (dynamic_cast<Knight*>(p)) {
            int dx[8] = { 2,  2, -2, -2,  1,  1, -1, -1 };
            int dy[8] = { 1, -1,  1, -1,  2, -2,  2, -2 };
            int blockX[8] = { 1,  1, -1, -1,  0,  0,  0,  0 };
            int blockY[8] = { 0,  0,  0,  0,  1, -1,  1, -1 };

            for (int i = 0; i < 8; i++) {
                int bx = x + blockX[i];
                int by = y + blockY[i];
                if (bx < 0 || bx > 9 || by < 0 || by > 8) continue;
                if (grid[bx][by] != nullptr) continue;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < 10 && ny >= 0 && ny < 9) attacked[nx][ny] = true;
            }
        }

        // Tượng (Elephant)
        if (dynamic_cast<Elephant*>(p)) {
            int dx[4] = {-2,-2,2,2};
            int dy[4] = {-2,2,2,-2};
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx > 9 || ny < 0 || ny > 8) continue;
                if (p->isValidMove(nx, ny, grid)) attacked[nx][ny] = true;
            }
        }

        // Sĩ (Advisor)
        if (dynamic_cast<Advisor*>(p)) {
            int dx[4] = {-1,-1,1,1};
            int dy[4] = {-1,1,1,-1};
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx > 9 || ny < 0 || ny > 8) continue;
                if (p->isValidMove(nx, ny, grid) &&
                    (grid[nx][ny] == nullptr || grid[nx][ny]->getColor() != p->getColor())) {
                    attacked[nx][ny] = true;
                }
            }
        }

        // Tốt (Pawn)
        if (dynamic_cast<Pawn*>(p)) {
            int dx[4] = {-1, 0, 1, 0};
            int dy[4] = {0, 1, 0, -1};
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx > 9 || ny < 0 || ny > 8) continue;
                if (p->isValidMove(nx, ny, grid) &&
                    (grid[nx][ny] == nullptr || grid[nx][ny]->getColor() != p->getColor())) {
                    attacked[nx][ny] = true;
                }
            }
        }

        // Tướng (General)
        if (dynamic_cast<General*>(p)) {
            int dx[4] = {-1, 0, 1, 0};
            int dy[4] = {0, 1, 0, -1};
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx > 9 || ny < 0 || ny > 8) continue;
                if (p->isValidMove(nx, ny, grid) &&
                    (grid[nx][ny] == nullptr || grid[nx][ny]->getColor() != p->getColor())) {
                    attacked[nx][ny] = true;
                }
            }
        }

        // Pháo (Cannon)
        if (dynamic_cast<Cannon*>(p)) {
            int dirX[4] = {1, -1, 0, 0};
            int dirY[4] = {0, 0, 1, -1};

            for (int d = 0; d < 4; d++) {
                int i = x + dirX[d];
                int j = y + dirY[d];
                bool foundBlock = false;

                while (i >= 0 && i < 10 && j >= 0 && j < 9) {
                    if (!foundBlock) {
                // Trước khi gặp quân cản: chỉ đánh dấu ô trống
                        if (grid[i][j] == nullptr) {
                            attacked[i][j] = true; // có thể đi
                        } else {
                            foundBlock = true; // gặp quân cản
                        }
                    } else {
                // Sau khi gặp quân cản: chỉ xét ô đầu tiên có quân
                        if (grid[i][j] != nullptr) {
                            if (grid[i][j]->getColor() != p->getColor())
                                attacked[i][j] = true; // có thể ăn
                            break; // dừng tại đây
                        }
                    }
                    i += dirX[d];
                    j += dirY[d];
                }
            }
        }
    }

    bool Board::generalsFacing() const {
        if (!redGeneral || !blackGeneral) return false;
        if (redGeneral->getY() != blackGeneral->getY()) return false;
        int col = redGeneral->getY();
        int top = min(redGeneral->getX(), blackGeneral->getX());
        int bottom = max(redGeneral->getX(), blackGeneral->getX());
        for (int i = top + 1; i < bottom; i++) {
            if (grid[i][col] != nullptr) return false;
        }
        return true;
    }

    bool Board::isInCheck(PlayerColor side) {
        General* king = (side == PlayerColor::RED) ? redGeneral : blackGeneral;
        if (!king) return false;
        int kx = king->getX(), ky = king->getY();
        return (side == PlayerColor::RED) ? attackedByBlack[kx][ky] : attackedByRed[kx][ky];
    }



    Board::Board() :  currentPlayer(PlayerColor::RED), redGeneral(nullptr), blackGeneral(nullptr){
        memset(grid, 0, sizeof(grid));
        clearAttackMap();
        currentPlayer = PlayerColor::RED;
        redGeneral = blackGeneral = nullptr;
        is_Red_over = false;
        is_Black_over = false;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 9; j++)
                grid[i][j] = nullptr;

        initializePieces();
        rebuildAttackMap();
    }

    Board::~Board() {
        // Xóa tất cả Piece đã new (đảm bảo xóa đúng 1 lần)
        for (int i = 0; i < allPieces.size(); i++) {
            delete allPieces[i];
        }
        allPieces.clear();
    }


    // ====== Khởi tạo quân ======
    void Board::initializePieces() {
        // General
        grid[0][4] = new General(PlayerColor::BLACK, 0, 4);
        allPieces.push_back(grid[0][4]);
        blackGeneral = dynamic_cast<General*>(grid[0][4]);

        grid[9][4] = new General(PlayerColor::RED, 9, 4);
        allPieces.push_back(grid[9][4]);
        redGeneral = dynamic_cast<General*>(grid[9][4]);

        // Advisors
        grid[0][3] = new Advisor(PlayerColor::BLACK, 0, 3); allPieces.push_back(grid[0][3]);
        grid[0][5] = new Advisor(PlayerColor::BLACK, 0, 5); allPieces.push_back(grid[0][5]);
        grid[9][3] = new Advisor(PlayerColor::RED, 9, 3);   allPieces.push_back(grid[9][3]);
        grid[9][5] = new Advisor(PlayerColor::RED, 9, 5);   allPieces.push_back(grid[9][5]);

        // Elephants
        grid[0][2] = new Elephant(PlayerColor::BLACK, 0, 2); allPieces.push_back(grid[0][2]);
        grid[0][6] = new Elephant(PlayerColor::BLACK, 0, 6); allPieces.push_back(grid[0][6]);
        grid[9][2] = new Elephant(PlayerColor::RED, 9, 2);   allPieces.push_back(grid[9][2]);
        grid[9][6] = new Elephant(PlayerColor::RED, 9, 6);   allPieces.push_back(grid[9][6]);

        // Knights
        grid[0][1] = new Knight(PlayerColor::BLACK, 0, 1); allPieces.push_back(grid[0][1]);
        grid[0][7] = new Knight(PlayerColor::BLACK, 0, 7); allPieces.push_back(grid[0][7]);
        grid[9][1] = new Knight(PlayerColor::RED, 9, 1);   allPieces.push_back(grid[9][1]);
        grid[9][7] = new Knight(PlayerColor::RED, 9, 7);   allPieces.push_back(grid[9][7]);

        // Rooks
        grid[0][0] = new Rock(PlayerColor::BLACK, 0, 0); allPieces.push_back(grid[0][0]);
        grid[0][8] = new Rock(PlayerColor::BLACK, 0, 8); allPieces.push_back(grid[0][8]);
        grid[9][0] = new Rock(PlayerColor::RED, 9, 0);   allPieces.push_back(grid[9][0]);
        grid[9][8] = new Rock(PlayerColor::RED, 9, 8);   allPieces.push_back(grid[9][8]);

        // Cannons
        grid[2][1] = new Cannon(PlayerColor::BLACK, 2, 1); allPieces.push_back(grid[2][1]);
        grid[2][7] = new Cannon(PlayerColor::BLACK, 2, 7); allPieces.push_back(grid[2][7]);
        grid[7][1] = new Cannon(PlayerColor::RED, 7, 1);   allPieces.push_back(grid[7][1]);
        grid[7][7] = new Cannon(PlayerColor::RED, 7, 7);   allPieces.push_back(grid[7][7]);

        // Pawns
        for (int j = 0; j < 9; j += 2) {
            grid[3][j] = new Pawn(PlayerColor::BLACK, 3, j); allPieces.push_back(grid[3][j]);
            grid[6][j] = new Pawn(PlayerColor::RED, 6, j);   allPieces.push_back(grid[6][j]);
        }

        // lưu ý: redGeneral/blackGeneral đã set ở trên
    }


    // ====== In bàn cờ ======
    void Board::printBoard() const {
        cout << "\n   ";
        for (int j = 0; j < 9; ++j) cout << j << "  ";
        cout << "\n";
        for (int i = 0; i < 10; i++) {
            cout << i << "  ";
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] != nullptr)
                    cout << grid[i][j]->getSymbol() << " ";
                else
                    cout << ".. ";
            }
            cout << "\n";
        }
        cout << "Lượt: " << (currentPlayer == PlayerColor::RED ? "ĐỎ" : "ĐEN") << "\n";
        cout << "(Nhập -1 -1 -1 -1 để thoát)\n";
    }
    //==== forward ===
    // ====== Di chuyển ======
    bool Board::movePiece(int fromX, int fromY, int toX, int toY) {
        // 1. Kiểm tra biên
        if (toX < 0 || toX > 9 || toY < 0 || toY > 8 ||
            fromX < 0 || fromX > 9 || fromY < 0 || fromY > 8) return false;

        // 2. Không được đứng yên
        if (fromX == toX && fromY == toY) return false;

        // 3. Ô xuất phát phải có quân và thuộc lượt hiện tại
        Piece* piece = grid[fromX][fromY];
        if (!piece || piece->getColor() != currentPlayer) return false;

        // 4. Không đi vào quân cùng màu
        Piece* target = grid[toX][toY];
        if (target && target->getColor() == currentPlayer) return false;

        // 5. Kiểm tra theo luật quân
        if (!piece->isValidMove(toX, toY, grid)) return false;

        // 6. Giả lập di chuyển để kiểm tra tự chiếu
        Piece* savedTo = target;
        int oldX = piece->getX(), oldY = piece->getY();
        grid[fromX][fromY] = nullptr;
        grid[toX][toY] = piece;
        piece->setPosition(toX, toY);

        // rebuild attack map 1 lần cho trạng thái giả lập
        rebuildAttackMap();
        bool illegal = isInCheck(currentPlayer) || generalsFacing();

        // Hoàn tác nếu không hợp lệ
        if (illegal) {
            grid[fromX][fromY] = piece;
            grid[toX][toY] = savedTo;
            piece->setPosition(oldX, oldY);
            rebuildAttackMap();
            return false;
        }

        // Lưu vào history (lưu pointer của quân bị ăn nếu có)
        Move m;
        m.fromX = fromX; m.fromY = fromY;
        m.toX = toX; m.toY = toY;
        m.movedPiece = piece;
        m.capturedPiece = savedTo;
        history.push(m);

        // clear redoStack
        redoStack.clear();

        // Nếu tới đây => nước đi hợp lệ
        // ✳️ KHÔNG delete savedTo ở đây — giữ pointer để undo/redo có thể khôi phục
        // trạng thái. Việc xóa bộ nhớ quản lý ở destructor thông qua allPieces.

        // rebuild attack map cho trạng thái chính thức
        rebuildAttackMap();

        // 7. Báo chiếu tướng (nếu có)
        PlayerColor opponent = (currentPlayer == PlayerColor::RED) ? PlayerColor::BLACK : PlayerColor::RED;
        if (isInCheck(opponent)) {
            cout << "\nChiếu tướng!\n";
        }

        // 8. Đổi lượt
        currentPlayer = (currentPlayer == PlayerColor::RED ? PlayerColor::BLACK : PlayerColor::RED);
        return true;
    }



    bool Board::canMove(int fromX, int fromY, int toX, int toY) {
        // 1. Kiểm tra biên
        if (toX < 0 || toX > 9 || toY < 0 || toY > 8 ||
            fromX < 0 || fromX > 9 || fromY < 0 || fromY > 8) return false;

        // 2. Không được đứng yên
        if (fromX == toX && fromY == toY) return false;

        // 3. Lấy quân xuất phát
        Piece* piece = grid[fromX][fromY];
        if (!piece || piece->getColor() != currentPlayer) return false;

        // 4. Không được đi vào quân cùng màu
        Piece* target = grid[toX][toY];
        if (target && target->getColor() == currentPlayer) return false;

        // 5. Kiểm tra hợp lệ theo luật quân
        if (!piece->isValidMove(toX, toY, grid)) return false;

        // 6. Giả lập di chuyển
        Piece* savedTo = target;
        int oldX = piece->getX(), oldY = piece->getY();
        grid[fromX][fromY] = nullptr;
        grid[toX][toY] = piece;
        piece->setPosition(toX, toY);
        rebuildAttackMap();
        bool legal = !(isInCheck(currentPlayer) || generalsFacing());

        // 7. Khôi phục trạng thái
        grid[fromX][fromY] = piece;
        grid[toX][toY] = savedTo;
        piece->setPosition(oldX, oldY);
        rebuildAttackMap();
        return legal;
    }

    // hàm canmove cho AI

    bool Board::canMoveForAI(int fromX, int fromY, int toX, int toY, PlayerColor side) {
    // 1. Kiểm tra biên
    if (toX < 0 || toX > 9 || toY < 0 || toY > 8 ||
        fromX < 0 || fromX > 9 || fromY < 0 || fromY > 8) return false;

    // 2. Không được đứng yên
    if (fromX == toX && fromY == toY) return false;

    // 3. Lấy quân xuất phát
    Piece* piece = grid[fromX][fromY];
    if (!piece || piece->getColor() != side) return false;

    // 4. Không được đi vào quân cùng màu
    Piece* target = grid[toX][toY];
    if (target && target->getColor() == side) return false;

    // 5. Kiểm tra hợp lệ theo luật quân
    if (!piece->isValidMove(toX, toY, grid)) return false;

    // 6. Giả lập di chuyển
    Piece* savedTo = target;
    int oldX = piece->getX(), oldY = piece->getY();
    grid[fromX][fromY] = nullptr;
    grid[toX][toY] = piece;
    piece->setPosition(toX, toY);
    rebuildAttackMap();

    bool legal = !(isInCheck(side) || generalsFacing());

    // 7. Khôi phục trạng thái
    grid[fromX][fromY] = piece;
    grid[toX][toY] = savedTo;
    piece->setPosition(oldX, oldY);
    rebuildAttackMap();

    return legal;
}

// hàm mô phỏng AI
bool Board::simulateMove(const Move& m) {
    Piece* piece = grid[m.fromX][m.fromY];
    if (!piece) return false;

    Piece* target = grid[m.toX][m.toY];

    Move move = m;
    move.movedPiece = piece;
    move.capturedPiece = target;
    history.push(move);

    grid[m.fromX][m.fromY] = nullptr;
    grid[m.toX][m.toY] = piece;
    piece->setPosition(m.toX, m.toY);

    rebuildAttackMap();

    // ✅ tự động đổi lượt (giống movePiece)
    currentPlayer = (currentPlayer == PlayerColor::RED ? PlayerColor::BLACK : PlayerColor::RED);

    return true;
}


    // Chỉ gọi hàm này khi bị chiếu
        bool Board::is_game_over(){ 
            if (isInCheck(currentPlayer)) {
                for(int i = 0; i < 10; i++){
                    for(int j = 0; j < 9; j++){
                        if(grid[i][j] != nullptr && grid[i][j]->getColor() == currentPlayer){
                            for(int h = 0; h < 10; h++){
                                for(int k = 0; k < 9; k++){
                                    if (canMove(i, j, h, k)) {
                                    return false; // còn ít nhất 1 nước cứu
                                    }
                                }
                            }
                        }
                    }
                }
        // nếu không còn nước nào cứu được
                if(currentPlayer == PlayerColor::RED) is_Red_over = true;
                else is_Black_over = true;
                return true;
            }
            return false; // không bị chiếu thì chắc chắn chưa thua
        }
    bool Board::get_is_over_game(){
            if(is_Red_over || is_Black_over){
                return true;
            }
            return false;
        }
    // Hàm check tết cả vị trí đi được của 1 quân và lưu nó lại
    void Board::check_piece(int fromX, int fromY){
        Piece* p = grid[fromX][fromY];
        if(p == nullptr) return;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                is_valid_move_piece[i][j] = false;
            }
        }
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                if(canMove(fromX,fromY,i,j)) is_valid_move_piece[i][j] = true;
            }
        }
    }

    void Board::undoMove(){; // (tùy chọn)
        if (history.isEmpty()) return;
        Move last = history.pop();

        // Hoàn tác: trả quân về vị trí cũ
        grid[last.fromX][last.fromY] = last.movedPiece;
        grid[last.toX][last.toY] = last.capturedPiece; // khôi phục quân ăn
        last.movedPiece->setPosition(last.fromX, last.fromY);

        // Đổi lượt về người vừa đi
        currentPlayer = (currentPlayer == PlayerColor::RED) ? PlayerColor::BLACK : PlayerColor::RED;

    // Lưu vào redoStack để có thể làm lại
        redoStack.push(last);

        rebuildAttackMap();
    }
    void Board::redoMove(){ // (tùy chọn)
        if (redoStack.isEmpty()) return;
        Move mv = redoStack.pop();

        grid[mv.fromX][mv.fromY] = nullptr;
        grid[mv.toX][mv.toY] = mv.movedPiece;
        mv.movedPiece->setPosition(mv.toX, mv.toY);

        // ✳️ KHÔNG delete mv.capturedPiece ở đây — pointer đã quản lý trong allPieces

        // Đổi lượt về người tiếp theo
        currentPlayer = (currentPlayer == PlayerColor::RED) ? PlayerColor::BLACK : PlayerColor::RED;

        history.push(mv);
        rebuildAttackMap();
    }


    // ====== Attack map ======
    void Board::rebuildAttackMap() {  // Xây lại toàn bộ bảng tấn công
        clearAttackMap();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] != nullptr) {
                    markAttacks(grid[i][j]);
                }
            }
        }
    }

    //Hàm sinh nước đi

MyVector<Move> Board::generateMoves(PlayerColor side) {
    MyVector<Move> list;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            Piece* p = grid[i][j];
            if (p && p->getColor() == side) {
                for (int x = 0; x < 10; x++) {
                    for (int y = 0; y < 9; y++) {
                      if (canMoveForAI(i, j, x, y, side)) {
                        Move m{i, j, x, y, p, grid[x][y]};
                        list.push_back(m);
                        }
                    }
                }
            }
        }
    }
    return list;
}


    // Hàm đánh giá nước đi
    int Board::evaluate(PlayerColor side) {
        int score = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 9; j++) {
                Piece* p = grid[i][j];
                if (!p) continue;
                int val = 0;
                if (dynamic_cast<General*>(p)) val = 10000;
                else if (dynamic_cast<Rock*>(p)) val = 500;
                else if (dynamic_cast<Cannon*>(p)) val = 350;
                else if (dynamic_cast<Knight*>(p)) val = 250;
                else if (dynamic_cast<Elephant*>(p)) val = 100;
                else if (dynamic_cast<Advisor*>(p)) val = 100;
                else if (dynamic_cast<Pawn*>(p)) val = 50;
                if (p->getColor() == side) score += val;
                else score -= val;
            }
        }
        return score;
    }

    // minimax + alpha + beta

int Board::minimax(int depth, int alpha, int beta, PlayerColor side) {
    if (depth == 0 || get_is_over_game()) {
        return evaluate(side);
    }

    MyVector<Move> moves = generateMoves(side);

    if (side == PlayerColor::RED) {
        int maxEval = -1000000000;
        for (int i = 0; i < moves.size(); i++) {
            Move m = moves[i];
            simulateMove(m);
            int eval = minimax(depth - 1, alpha, beta, PlayerColor::BLACK);
            undoMove();
            if (eval > maxEval) maxEval = eval;
            if (eval > alpha) alpha = eval;
            if (beta <= alpha) break; 
        }
        return maxEval;
    } else {
        int minEval = 1000000000;
        for (int i = 0; i < moves.size(); i++) {
            Move m = moves[i];
            simulateMove(m);
            int eval = minimax(depth - 1, alpha, beta, PlayerColor::RED);
            undoMove();
            if (eval < minEval) minEval = eval;
            if (eval < beta) beta = eval;
            if (beta <= alpha) break;
        }
        return minEval;
    }
}



    // hàm tìm nước đi tốt nhất cho AI

Move Board::findBestMove(PlayerColor side, int depth) {
    MyVector<Move> moves = generateMoves(side);
    if (moves.size() == 0) {
        return Move{-1,-1,-1,-1,nullptr,nullptr};
    }
    Move bestMove = moves[0];
    int bestScore = (side == PlayerColor::RED) ? -1000000000 : 1000000000;

    for (int i = 0; i < moves.size(); i++) {
        Move m = moves[i];

        // Dùng simulateMove (không xóa quân) để thử
        simulateMove(m);
        int score = minimax(depth - 1, -1000000000, 1000000000,
                            (side == PlayerColor::RED ? PlayerColor::BLACK : PlayerColor::RED));
        undoMove();

        if ((side == PlayerColor::RED && score > bestScore) ||
            (side == PlayerColor::BLACK && score < bestScore)) {
            bestScore = score;
            bestMove = m;
        }
    }
    return bestMove;
}



    // ====== Getter ======
    PlayerColor Board::getCurrentPlayer() const { return currentPlayer;}
    Piece* Board::getPiece(int x, int y) const { return grid[x][y];}
    // setter cho currentPlayer
    void Board::setCurrentPlayer(PlayerColor side) {
        currentPlayer = side;
    }