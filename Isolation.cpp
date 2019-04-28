//
// Created by Titichot Nuntapramote on 4/24/19.
//

#include "Isolation.h"

Isolation::Isolation() {
    initialize();
}

Isolation::Isolation(const char& whoFirst) { // need time limit
    initialize();
    if ( whoFirst == 'C') {
        computer = playing = 'X';
        opponent = waiting = 'O';
    }
    else {
        computer = playing = 'O';
        opponent = waiting = 'X';
    }

}

void Isolation::initialize() {
    // initial position

    for (int i=0; i < BOARD_SIZE; ++i) {
        for (int j=0; j < BOARD_SIZE; ++j) {
            board[i][j] = '-';
        }
    }
    board[0][0] = 'X';
    board[BOARD_SIZE - 1][BOARD_SIZE - 1] = 'O';
    currentX = pair<int,int>(0,0);
    currentO = pair<int,int>(BOARD_SIZE-1, BOARD_SIZE-1);
}

void Isolation::computerMove() {

//    pair<int,int> move = alphaBetaSreach(board);
//    makeMove(computer,move.first,move.second);

}

bool Isolation::computeMove(string movingPosition) {
    pair<int,int> move = pair<int,int>(movingPosition[0] - 65, movingPosition[1] - 49);
    cout << move.first <<" , " << move.second << endl;
    if ( isValidMove(computer, move) ) {
        makeMove(computer, move.first, move.second);
        playerC.emplace_back(movingPosition);
        return true;
    }
    return false;
}

bool Isolation::opponentMove(string movingPosition) {
    // need to handle the user input
    // tokenize the moving position format
    pair<int,int> move = pair<int,int>(movingPosition[0] - 65, movingPosition[1] - 49);
    cout << move.first <<" , " << move.second << endl;
    if ( isValidMove(opponent, move) ) {
        makeMove(opponent, move.first, move.second);
        playerO.emplace_back(movingPosition);
        return true;
    }
    return false;
}

//pair<int,int> Isolation::alphaBetaSreach(char board[BOARD_SIZE][BOARD_SIZE]){
//    /*
//     * input: state -- current board in the game
//     * value <- maxValue(board, -inf, inf)
//     * return the action in Successors(state) with value
//     */
//    int alpha = numeric_limits<int>::min();
//    int beta = numeric_limits<int>::max();
//}
//
//int Isolation::maxValue (char board[BOARD_SIZE][BOARD_SIZE], int& alpha, int& beta) {
//    /*
//     * input: state, current state in game
//     *          alpha, the value of the best alternative for MAX along the path to state
//     *          beta, the value of the best alternative for MIN along the path to state
//     *  if Terminal-test(state) then return Utility(state)
//     *  value <- -inf
//     *  for s in succerssors(state) do
//     *      value <- MAX(value, min-value(s,alpha, beta))
//     *      if value >= beta then return value
//     *      alpha <- MAX(alpha, value)
//     *  return value
//     */
//
//}
//
//int Isolation::minValue(char board[BOARD_SIZE][BOARD_SIZE], int &alpha, int &beta) {
//    /*
//     * input: state, current state in game
//     *          alpha, the value of the best alternative for MAX along the path to state
//     *          beta, the value of the best alternative for MIN along the path to state
//     *  if Terminal-test(state) then return Utility(state)
//     *  value <- -inf
//     *  for s in succerssors(state) do
//     *      value <- MIN(value, max-value(s,alpha, beta))
//     *      if value <= alpha then return value
//     *      alpha <- MIN(beta, value)
//     *  return value
//     */
//}

string Isolation::getcurrentX() const {
    string position = "";
    position.append(1,char(currentX.first + 65));
    position.append(1,char(currentX.second + 49));
    return position;
}

string Isolation::getcurrentO() const {
    string position = "";
    position.append(1,char(currentO.first + 65));
    position.append(1,char(currentO.second + 49));
    return position;
}

int Isolation::utility(const char &player) {
    /*
     *  return 1 if player win
     *         -1 if player not win
     *         0 otherwise (inconclusive)
     */
    if (getAllPossibleMoves(this->board, (playing == 'X' ? currentX : currentO)).empty())
        return player == playing ? -1 : 1;
    else
        return 0;
}

bool Isolation::makeMove(const char& player, int row, int col) {   // assume it is valid
    /*
     * update move on the board when player make move
     * return true if the move is made
     *        false otherwise (not a valid move)
     */
    if (!isValidMove(player, pair<int,int>(row ,col)))
        return false;
    else {
        if (player == 'X') {
            board[currentX.first][currentX.second] = '#';
            currentX.first = row;
            currentX.second = col;
            board[currentX.first][currentX.second] = 'X';
        }
        else {
            board[currentO.first][currentO.second] = '#';
            currentO.first = row;
            currentO.second = col;
            board[currentO.first][currentO.second] = 'O';
        }
    }
    swap(playing, waiting);
    return true;
}

bool Isolation::isValidMove(const char &player, pair<int, int> movePosition) const {
    const bool DEBUG = false;
    /*
     *  check for valid move
     *      should return false if there is an '#' along the path
     *      all direction:  8 direction ways
     *                             \  |  /
     *                            --  Q  --
     *                             /  |  \
     */
    if (outOfBound(movePosition))
        return false;
    int row = player == 'X' ? currentX.first : currentO.first;
    int col = player == 'X' ? currentX.second : currentO.second;
    if (DEBUG)
        cout << "I am " << player << " at "<<row<< "," << col<< endl;
    int rowDis = abs(row - movePosition.first);
    int colDis = abs(col - movePosition.second);
    if (DEBUG)
        cout << "I am moving to" <<movePosition.first<< "," << movePosition.second<< endl;
    if ( rowDis == 0 && colDis == 0) { // same spot
        if (DEBUG)
            cout << "INVALID MOVE (moving to the same spot)" << endl;
        return false;
    }
    else if (row > movePosition.first && col == movePosition.second)  { // TOP
        for ( int i=row - 1; i >= movePosition.first; --i) {
            if (isUsed(pair<int,int>(i,col))) {
                if (DEBUG)
                    cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                return false;
            }
        }
    }
    else if (row == movePosition.first && col < movePosition.second)  { // RIGHT
        for ( int i=col + 1; i <= movePosition.second; ++i) {
            if (isUsed(pair<int,int>(row,i))) {
                if (DEBUG)
                    cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                return false;
            }
        }
    }
    else if (row < movePosition.first && col == movePosition.second)  { // DOWN
        for ( int i=row + 1; i <= movePosition.first; ++i) {
            if (isUsed(pair<int,int>(i,col))) {
                if (DEBUG)
                    cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                return false;
            }
        }
    }
    else if (row == movePosition.first && col > movePosition.second)  { // LEFT
        for ( int i=col - 1; i >= movePosition.second; --i) {
            if (isUsed(pair<int,int>(row,i))) {
                if (DEBUG)
                    cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                return false;
            }
        }
    }
    else if (rowDis == colDis) { // proper diagonal
        if (row > movePosition.first && col < movePosition.second) { // TOP RIGHT
            for ( int i= 0; i < rowDis; ++i) {
                if (isUsed(pair<int,int>(row-i,col+i))) {
                    if (DEBUG)
                        cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                    return false;
                }
            }
        }
        else if (row > movePosition.first && col < movePosition.second) { // DOWN RIGHT  //bug
            for ( int i= 0; i < rowDis; ++i) {
                if (isUsed(pair<int,int>(row+i,col+i))) {
                    if (DEBUG)
                        cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                    return false;
                }
            }
        }
        else if (row > movePosition.first && col < movePosition.second) { // DOWN LEFT
            for ( int i= 0; i < rowDis; ++i) {
                if (isUsed(pair<int,int>(row+i,col-i))) {
                    if (DEBUG)
                        cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                    return false;
                }
            }
        }
        else if (row > movePosition.first && col < movePosition.second) { // TOP LEFT
            for ( int i= 0; i < rowDis; ++i) {
                if (isUsed(pair<int,int>(row-i,col-i))) {
                    if (DEBUG)
                        cout << "INVALID MOVE (either moving to used spot or hit used spot before the destination)" << endl;
                    return false;
                }
            }
        }
    }
    else {
        if (DEBUG)
            cout << "NOT A VALID MOVE (DIAGONAL ROW & COL are not the same)" << endl;
        return false;
    }
    return true;  // passing all check!!

}

inline bool Isolation::outOfBound(pair<int, int> position) const {
    /*
     *  check if the position is not within the board
     *  return true if one is out
     */
    return  position.first < 0 || position.first >= BOARD_SIZE ||
            position.second < 0 || position.second >= BOARD_SIZE;
}

inline bool Isolation::isUsed(pair<int, int> position, char board[BOARD_SIZE][BOARD_SIZE]) const {
    /*
     * check if the spot is avialible to move
     */
    return board[position.first][position.second] != '-';
}

inline bool Isolation::isUsed(pair<int, int> position) const {
    /*
     * check if the spot is avialible to move
     */
    return board[position.first][position.second] != '-';
}

bool Isolation::isWin(const char& player) {
    /*
     * return true if the player is at winning situation
     */

    return player == waiting && checkLosingCondition(playing);
}

bool Isolation::checkLosingCondition(const char& player) const{
    int x_pos = player == 'X' ? currentX.first : currentO.first;
    int y_pos = player == 'X' ? currentX.second : currentO.second;
    for(int dx = (x_pos > 0 ? -1 : 0); dx <= (x_pos < BOARD_SIZE-1 ? 1 : 0); ++dx){
        for (int dy = (y_pos > 0 ? -1 : 0); dy <= (y_pos < BOARD_SIZE-1 ? 1 : 0) ; ++dy) {
            if ((dx != 0 || dy != 0) && !isUsed(pair<int, int>(x_pos + dx, y_pos + dy))) {
                return false;
            }
        }
    }
    return true;
}

void Isolation::getAllLegalMovesVertHoriz(vector<pair<int, int>> &list, char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool dirUpOrLeft, bool horizontal) {
    pair<int, int> move;
    (horizontal ? move.first : move.second) = (horizontal ? player_y : player_x);
    int current_selected_pos = (horizontal ? player_x : player_y);
    int *selected_pair_var = &(horizontal ? move.second : move.first);
    bool notFinished = true;

    for (int i = 1; (dirUpOrLeft ? current_selected_pos - i >= 0 : current_selected_pos + i < BOARD_SIZE) && notFinished; ++i) {
        *selected_pair_var = current_selected_pos + (dirUpOrLeft ? -i : i);
        if(!isUsed(move, board)){
            list.push_back(move);
        }else{
            notFinished = false;
        }
    }
}

void Isolation::getAllLegalMovesDiagonally(vector<pair<int, int>> &list, char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool dirRight){
    pair<int, int> moveUp;
    pair<int, int> moveDown;
    bool upNotFinished = true;
    bool downNotFinished = true;

    for (int i = 1; (dirRight ? player_x + i < BOARD_SIZE : player_x - i >= 0) && (upNotFinished || downNotFinished); ++i) {
        if(upNotFinished && player_y - i >= 0){
            moveUp = pair<int, int>(player_y - i, player_x + (dirRight ? i : -i));
            if(!isUsed(moveUp, board)){
                list.push_back(moveUp);
            }else{
                upNotFinished = false;
            }
        }
        if(downNotFinished && player_y + i < BOARD_SIZE){
            moveDown = pair<int, int>(player_y + i, player_x + (dirRight ? i : -i));
            if(!isUsed(moveDown, board)){
                list.push_back(moveDown);
            }else{
                downNotFinished = false;
            }
        }
    }
}

vector<pair<int,int>> Isolation::getAllPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], const pair<int, int> &player_pos) {
    /*
     * get all posible moves from a player
     *      all direction:  8 direction ways
     *      each direction should stop when hitting either
     *                      '#', 'another player' or out of the board
     *                             \  |  /
     *                            --  Q  --
     *                             /  |  \
     */
    vector<pair<int,int>> successors;
    int row = player_pos.first;
    int col = player_pos.second;
    getAllLegalMovesVertHoriz(successors, board, row, col, false, false); // moving down
    getAllLegalMovesVertHoriz(successors, board, row, col, false, true); // moving right
    getAllLegalMovesVertHoriz(successors, board, row, col, true, false); // moving up
    getAllLegalMovesVertHoriz(successors, board, row, col, true, true); // moving left
    getAllLegalMovesDiagonally(successors, board, row, col, false); // moving left diagonally
    getAllLegalMovesDiagonally(successors, board, row, col, true); // moving right diagonally
    return successors;
}

void Isolation::display() const {
    int i = 0, j;

    cout << "  1 2 3 4 5 6 7 8      Computer vs. Opponent" << endl;
    while ( i < BOARD_SIZE || i < playerC.size() || i < playerO.size() ) {
        if ( i <  BOARD_SIZE) {
            cout << char(i + 65) << " ";
            for ( j = 0; j < BOARD_SIZE; ++j) {
                cout << board[i][j] << " ";
            }
        }
        else {
            cout << "                       ";
        }

        if (i < playerC.size()) {
            cout << "         " << playerC[i] << "       ";
        }
        else {
            cout << "                     ";
        }

        if (i < playerO.size()) {
            cout << playerO[i];
        }
        cout << endl;
        ++i;
    }
}

ostream& operator<<(ostream &out, const Isolation &x) {
    x.display();
    return out;
}

currentMovedNode Isolation::iterativeDeepSearch(){
    int depth = 1;
    int alpha = -INF;
    int beta = INF;
    currentMovedNode node;
    pair<int, int> player_pos = (computer == 'X' ? currentX : currentO);
    while(true){
        node = alphaBetaSearch(this->board, player_pos, depth, alpha, beta);
        if(node.score == -INF || node.score == INF){
            break;
        }
        ++depth;
    }
    return node;
}

/*
 * TODO:
 *  The 'board' value when calling alphabeta should actually be a copy of the board with the move applied.
 *  The 'playing' value should have the updated position of the player after applying a move on the board.
 */
currentMovedNode Isolation::alphaBetaSearch(char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &depth, int &alpha, int &beta, bool max_player) {
    vector<pair<int, int>> allLegalMoves = getAllPossibleMoves(board, player_pos);

    if(allLegalMoves.empty()){
        currentMovedNode node;
        node.score = max_player ? -INF : INF;
        node.movedPosition = pair<int, int>(-1, -1);
        return node;
    }

    int lowest_score = -INF;
    int highest_score = INF;
    pair<int, int> best_move = pair<int, int>(-1, -1);
    currentMovedNode node;
    if(depth == 1){ // Terminal State aka leaf node
        if(max_player){
            node = maxBaseDepthValue(allLegalMoves, alpha, beta, highest_score, best_move);
        }else{
            node = minBaseDepthValue(allLegalMoves, alpha, beta, lowest_score, best_move);
        }
    }else{
        if(max_player){
            node = maxValue(allLegalMoves, board, player_pos, depth, alpha, beta, highest_score, best_move);
        }else{
            node = minValue(allLegalMoves, board, player_pos, depth, alpha, beta, lowest_score, best_move);
        }
    }
    return node;
}

int Isolation::getHeuristicScore(const pair<int, int> &move) {
    return 0;
}

currentMovedNode Isolation::maxBaseDepthValue(vector<pair<int, int>> &legalMoves, const int &alpha, const int &beta, const int &highest_score, const pair<int, int> &best_move){
    int score;
    int current_highest_score;
    pair<int, int> current_best_move;
    currentMovedNode node;
    for(pair<int, int> move : legalMoves){
        score = getHeuristicScore(move);

        if(score >= beta){
            node.score = score;
            node.movedPosition = pair<int, int>(move.first, move.second);
            return node;
        }
        if(score > highest_score){
            current_highest_score = score;
            current_best_move = pair<int, int>(move.first, move.second);
        }
    }

    node.score = current_highest_score;
    node.movedPosition = pair<int, int>(current_best_move.first, current_best_move.second);
    return node;
}

currentMovedNode Isolation::minBaseDepthValue(vector<pair<int, int>> &legalMoves, const int &alpha, const int &beta, const int &lowest_score, const pair<int, int> &best_move) {
    int score;
    int current_lowest_score;
    pair<int, int> current_best_move;
    currentMovedNode node;
    for (pair<int, int> move : legalMoves) {
        score = getHeuristicScore(move);

        if (score <= beta) {
            node.score = score;
            node.movedPosition = pair<int, int>(move.first, move.second);
            return node;
        }
        if (score < lowest_score) {
            current_lowest_score = score;
            current_best_move = pair<int, int>(move.first, move.second);
        }
    }

    node.score = current_lowest_score;
    node.movedPosition = pair<int, int>(current_best_move.first, current_best_move.second);
    return node;
}

/*
 * TODO:
 *  The 'board' value when calling alphabeta should actually be a copy of the board with the move applied.
 */
currentMovedNode Isolation::maxValue(vector<pair<int, int>> &legalMoves, char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &depth, int &alpha, int &beta, const int &highest_score, const pair<int, int> &best_move){
    int current_highest_score;
    pair<int, int> current_best_move;
    currentMovedNode node;
    char newBoard[BOARD_SIZE][BOARD_SIZE];
    for(pair<int, int> move : legalMoves){
        copyBoard(board, newBoard);
        applyMove(move, player_pos, newBoard);
        node = alphaBetaSearch(newBoard, move, depth-1, alpha, beta, false); // board should actually be the board of the move applied

        if(node.score >= beta){
            return node;
        }

        if(node.score > highest_score){
            current_highest_score = node.score;
            current_best_move = pair<int, int>(node.movedPosition.first, node.movedPosition.second);
        }
        alpha = max(alpha, current_highest_score);
    }
    node.score = current_highest_score;
    node.movedPosition = pair<int, int>(current_best_move.first, current_best_move.second);
    return node;
}

/*
 * TODO:
 *  The 'board' value when calling alphabeta should actually be a copy of the board with the move applied.
 */
currentMovedNode Isolation::minValue(vector<pair<int, int>> &legalMoves, char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &depth, int &alpha, int &beta, const int &lowest_score, const pair<int, int> &best_move){
    int current_lowest_score;
    pair<int, int> current_best_move;
    currentMovedNode node;
    char newBoard[BOARD_SIZE][BOARD_SIZE];
    for(pair<int, int> move : legalMoves){
        copyBoard(board, newBoard);
        applyMove(move, player_pos, newBoard);
        node = alphaBetaSearch(newBoard, move, depth-1, alpha, beta, true); // board should actually be the board of the move applied

        if(node.score <= alpha){
            return node;
        }

        if(node.score < lowest_score){
            current_lowest_score = node.score;
            current_best_move = pair<int, int>(node.movedPosition.first, node.movedPosition.second);
        }
        beta = min(beta, current_lowest_score);
    }
    node.score = current_lowest_score;
    node.movedPosition = pair<int, int>(current_best_move.first, current_best_move.second);
    return node;
}

pair<int, int> Isolation::getMove() {
    currentMovedNode node = iterativeDeepSearch();
    return node.movedPosition;
}

void Isolation::copyBoard(char board[BOARD_SIZE][BOARD_SIZE], char newBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            newBoard[i][j] = board[i][j];
        }
    }
}

void Isolation::applyMove(pair<int, int> move, pair<int, int> player_pos, char board[BOARD_SIZE][BOARD_SIZE]){
    board[player_pos.first][player_pos.second] = '#';
    board[move.first][move.second] = 'X';
}