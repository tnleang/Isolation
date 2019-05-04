//
// Created by Titichot Nuntapramote on 4/24/19.
//

#include "Isolation.h"

Isolation::Isolation() {
    initialize();
}

Isolation::Isolation(const char& whoFirst, int timeLimit) { // need time limit
    initialize();
    if ( whoFirst == 'C') {
        computer = playing = 'X';
        opponent = waiting = 'O';
    }
    else {
        computer = playing = 'O';
        opponent = waiting = 'X';
    }
    this->timeLimit = timeLimit;

}

void Isolation::initialize() {
    // initial position

    for (int i=0; i < BOARD_SIZE; ++i) {
        for (int j=0; j < BOARD_SIZE; ++j) {
            board[i][j] = '-';
            tempBoard[i][j] = '-';
        }
    }
    board[0][0] = 'X';
    board[BOARD_SIZE - 1][BOARD_SIZE - 1] = 'O';
    tempBoard[0][0] = 'X';
    tempBoard[BOARD_SIZE - 1][BOARD_SIZE - 1] = 'O';
    currentX = pair<int,int>(0,0);
    currentO = pair<int,int>(BOARD_SIZE-1, BOARD_SIZE-1);
}

void Isolation::computerMove() {
    pair<int,int> move = getMove(computer);
    makeMove(computer, move.first, move.second);
    playerC.emplace_back(getcurrent(move));
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

//    pair<int,int> move = getMove();
//    makeMove(opponent, move.first, move.second);
//    playerO.emplace_back(getcurrent(move));
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

string Isolation::getcurrent(pair<int,int> move) const {
    string position = "";
    position.append(1,char(move.first + 65));
    position.append(1,char(move.second + 49));
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
    if (!isValidMove(player, pair<int,int>(row ,col))) {
        cout << "Not valid move" << "\n";
        return false;
    }
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
    if (outOfBound(movePosition)) {
        return false;
    }
    int row = player == 'X' ? currentX.first : currentO.first;
    int col = player == 'X' ? currentX.second : currentO.second;
    pair<int, int> current_player_pos = player == 'X' ? currentX : currentO;

    if (DEBUG)
        cout << "I am " << player << " at "<<row<< "," << col<< endl;

    int rowDis = abs(row - movePosition.first);
    int colDis = abs(col - movePosition.second);

    if (DEBUG)
        cout << "I am moving to " <<movePosition.first<< " , " << movePosition.second<< endl;
    if ( rowDis == 0 && colDis == 0) { // same spot
        if (DEBUG)
            cout << "INVALID MOVE (moving to the same spot)" << endl;
        return false;
    }
    else if (row > movePosition.first && col == movePosition.second)  { // TOP
        return checkValidPathVertHoriz(current_player_pos, movePosition, true, false);
    }
    else if (row == movePosition.first && col < movePosition.second)  { // RIGHT
        return checkValidPathVertHoriz(current_player_pos, movePosition, false, true);
    }
    else if (row < movePosition.first && col == movePosition.second)  { // DOWN
        return checkValidPathVertHoriz(current_player_pos, movePosition, false, false);
    }
    else if (row == movePosition.first && col > movePosition.second)  { // LEFT
        return checkValidPathVertHoriz(current_player_pos, movePosition, true, true);
    }
    else if (rowDis == colDis) { // proper diagonal
        if (row > movePosition.first && col < movePosition.second) { // TOP RIGHT
            return checkValidPathDiagonal(current_player_pos, rowDis, true, false);
        }
        else if (row < movePosition.first && col < movePosition.second) { // DOWN RIGHT
            return checkValidPathDiagonal(current_player_pos, rowDis, false, false);
        }
        else if (row < movePosition.first && col > movePosition.second) { // DOWN LEFT
            return checkValidPathDiagonal(current_player_pos, rowDis, false, true);
        }
        else if (row > movePosition.first && col > movePosition.second) { // TOP LEFT
            return checkValidPathDiagonal(current_player_pos, rowDis, true, true);
        }
    }
    else {
        if (DEBUG)
            cout << "NOT A VALID MOVE (DIAGONAL ROW & COL are not the same)" << endl;
        return false;
    }
}

bool Isolation::checkValidPathVertHoriz(pair<int, int> current_position, pair<int, int> next_position, bool dirUpOrLeft, bool horizontal) const{
    pair<int, int> currentMove = current_position;
    int *current_pos = &(horizontal ? currentMove.second : currentMove.first);
    int current_selected_pos = (horizontal ? current_position.second : current_position.first);
    int goal_pos = (horizontal ? next_position.second : next_position.first);

    for (int i = 1; (dirUpOrLeft ? current_selected_pos - i >= goal_pos : current_selected_pos + i <= goal_pos); ++i) {
        *current_pos = current_selected_pos + (dirUpOrLeft ? -i : i);
        if(isUsed(currentMove)){
            return false;
        }
    }
    return true;
}

bool Isolation::checkValidPathDiagonal(pair<int, int> current_position, int distance, bool up, bool left) const{
    for (int i = 1; i < distance; ++i) {
        if(isUsed(pair<int, int>(current_position.first + (up ? -i : i), current_position.second + (left ? -i : i)))){
            return false;
        }
    }
    return true;
}


inline bool Isolation::outOfBound(pair<int, int> position) const {
    /*
     *  check if the position is not within the board
     *  return true if one is out
     */
    return  position.first < 0 || position.first >= BOARD_SIZE ||
            position.second < 0 || position.second >= BOARD_SIZE;
}

inline bool Isolation::isUsed(pair<int, int> position, const char board[BOARD_SIZE][BOARD_SIZE]) const {
    /*
     * check if the spot is avialible to move
     */
    return board[position.first][position.second] != '-';
}

inline bool Isolation::isUsed(pair<int, int> position) const {
    /*
     * check if the spot is available to move
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

void Isolation::getAllLegalMovesVertHoriz(vector<pair<int, int>> &list, const char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool dirUpOrLeft, bool horizontal) {
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

void Isolation::getAllLegalMovesDiagonally(vector<pair<int, int>> &list, const char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool dirRight){
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

vector<pair<int,int>> Isolation::getAllPossibleMoves(const char board[BOARD_SIZE][BOARD_SIZE], const pair<int, int> &player_pos) {
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
            cout << "                  ";
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

/*
 * Starts the alphaBetaSearch with current board and the computer's current position
 * It is an iterative deepening search, so it starts at depth 1 and check if the score is INF or -INF
 * if true then return the node else continue to search with depth + 1
 */
currentMovedNode Isolation::iterativeDeepSearch( char play){
    int depth = 1;
    int alpha = -INF;
    int beta = INF;
    copyBoard(board, tempBoard);
    currentMovedNode node;
    node.score = -INF;
    Board newBoard;
    newBoard.maxPos = (play == 'X' ? currentX : currentO);
    newBoard.minPos = (play == 'X' ? currentO : currentX);
    startTime = chrono::high_resolution_clock::now();
    while(true){
        currentMovedNode newNode = alphaBetaSearch(newBoard, depth, alpha, beta);
        if(newNode.score == -INF || newNode.score == INF){
            node = newNode;
            break;
        }
        if(newNode.score > node.score){
            node = newNode;
        }
        alpha = -INF;
        beta = INF;
        ++depth;
        if(isTimeOver()){
            break;
        }
    }
    return node;
}

currentMovedNode Isolation::alphaBetaSearch(const Board &board, const int &depth, int &alpha, int &beta, bool max_player) {
    currentMovedNode node = max_player ? maxValue(board, depth, alpha, beta) : minValue(board, depth, alpha, beta);
    return node;
}

currentMovedNode Isolation::maxValue(const Board &board, const int &depth, int &alpha, int &beta){
//    cout << "maxValue depth: " << depth << "\n";
    vector<pair<int, int>> legalMoves = getAllPossibleMoves(tempBoard, board.maxPos);
    // No legal moves means terminal state
    if(legalMoves.empty()){
//        cout << "No moves left for max" << "\n";
        currentMovedNode node;
        node.score = -INF;
        node.movedPosition = pair<int, int>(-1, -1);
        return node;
    }

    int current_highest_score = -INF;
    pair<int, int> current_best_move = legalMoves.at(0);
    currentMovedNode node;
    Board nextBoard;
    for(pair<int, int> move : legalMoves){
        nextBoard = board;
        applyMove(move, nextBoard, true);
        nextBoard.maxPos = move;

        if(depth == 1){
            node.score = heuristic2(nextBoard);
            node.movedPosition = move;
        }else{
            node = alphaBetaSearch(nextBoard, depth-1, alpha, beta, false);
        }

        undoMove(move, board, true);

        if(node.score >= beta){
            node.movedPosition = move;
            return node;
        }

        if(node.score > current_highest_score){
            current_highest_score = node.score;
            current_best_move = move;
        }

        alpha = max(alpha, current_highest_score);

        if(isTimeOver()){
            break;
        }
    }
    node.score = current_highest_score;
    node.movedPosition = current_best_move;
    return node;
}

currentMovedNode Isolation::minValue(const Board &board, const int &depth, int &alpha, int &beta){
    vector<pair<int, int>> legalMoves = getAllPossibleMoves(tempBoard, board.minPos);

    // No legal moves means terminal state
    if(legalMoves.empty()){
        currentMovedNode node;
        node.score = INF;
        node.movedPosition = pair<int, int>(-1, -1);
        return node;
    }

    int current_lowest_score = INF;
    pair<int, int> current_best_move = legalMoves.at(0);
    currentMovedNode node;
    Board nextBoard;
    for(pair<int, int> move : legalMoves){
        nextBoard = board;
        applyMove(move, nextBoard, false);
        nextBoard.minPos = move;

        if(depth == 1){
            node.score = heuristic2(nextBoard);
            node.movedPosition = move;
        }else{
            node = alphaBetaSearch(nextBoard, depth-1, alpha, beta, true);
        }

        undoMove(move, board, false);

        if(node.score <= alpha){
            node.movedPosition = move;
            return node;
        }

        if(node.score < current_lowest_score){
            current_lowest_score = node.score;
            current_best_move = move;
        }

        beta = min(beta, current_lowest_score);

        if(isTimeOver()){
            break;
        }
    }
    node.score = current_lowest_score;
    node.movedPosition = current_best_move;
    return node;
}

pair<int, int> Isolation::getMove( char play) {
    currentMovedNode node = iterativeDeepSearch(play);
    return node.movedPosition;
}

void Isolation::applyMove(pair<int, int> move, const Board &board, bool max_player){
    pair<int, int> player_pos = max_player ? board.maxPos : board.minPos;
    tempBoard[player_pos.first][player_pos.second] = '#';
    tempBoard[move.first][move.second] = max_player ? computer : opponent;
}

void Isolation::undoMove(pair<int, int> move, const Board &board, bool max_player){
    pair<int, int> player_pos = max_player ? board.maxPos : board.minPos;
    tempBoard[player_pos.first][player_pos.second] = max_player ? computer : opponent;
    tempBoard[move.first][move.second] = '-';
}

void Isolation::copyBoard(const char board[BOARD_SIZE][BOARD_SIZE], char newBoard[BOARD_SIZE][BOARD_SIZE]){
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            newBoard[i][j] = board[i][j];
        }
    }
}

int Isolation::heuristic1(Board b){
    /*
     * calculate the possibility of winning by calcualte the possible moves left of both player
     *      then compare them
     */
    vector<pair<int,int>> playerLeftMoves = getAllPossibleMoves(tempBoard, b.maxPos);
    vector<pair<int,int>> opponentLeftMoves = getAllPossibleMoves(tempBoard, b.minPos);
    return playerLeftMoves.size() - opponentLeftMoves.size();
}

int Isolation::heuristic2(Board b){
    /*
     * this heuristic builds on top of heuristic 1
     *      compare the moves left between max and min
     *          return the different
     *          if they are the same, compute the distance to the center
     */
    vector<pair<int,int>> playerLeftMoves = getAllPossibleMoves(tempBoard, b.maxPos);
    vector<pair<int,int>> opponentLeftMoves = getAllPossibleMoves(tempBoard, b.minPos);
    if ( playerLeftMoves.size() != opponentLeftMoves.size())
        return playerLeftMoves.size() - opponentLeftMoves.size();

    // compute the distance away from the center of the board
    int centerRow = BOARD_SIZE / 2;
    int centerCol = BOARD_SIZE / 2;
    int distanceMax = abs( b.maxPos.first - centerRow ) + abs( b.maxPos.second - centerCol );
    int distanceMin = abs( b.minPos.first - centerRow ) + abs( b.minPos.second - centerCol );
    return distanceMax - distanceMin;
}

void Isolation::printBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "  1 2 3 4 5 6 7 8" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << char(i + 65) << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool Isolation::isTimeOver() {
    return chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - startTime).count() > timeLimit;
}

void Isolation::twoAIPlay() {
    char cur = 'X';
    bool play = true;
    int count = 0;

    while(play) {
        if( count++ % 2 == 0) {
            pair<int,int> move = getMove('X');
            makeMove('X', move.first, move.second);
            playerC.emplace_back(getcurrent(move));
        }
        else {
            pair<int,int> move = getMove('O');
            makeMove('O', move.first, move.second);
            playerO.emplace_back(getcurrent(move));
        }
        display();
        cur = whoIsPlaying() == 'X'? 'O' : 'X';
        if (isWin(cur)){
            cout << cur << " is the winner!" << endl;
            play = false;
        }
    }
}
