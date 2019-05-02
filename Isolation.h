//
// Created by Titichot Nuntapramote on 4/24/19.
//

#ifndef ISOLATION_ISOLATION_H
#define ISOLATION_ISOLATION_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <limits>       // std::numeric_limits
#include <chrono>

using namespace std;

const int BOARD_SIZE = 8;

const int TIME_LIMIT = 20;

struct Board {
    pair<int,int> maxPos;
    pair<int,int> minPos;
    char board[BOARD_SIZE][BOARD_SIZE];
};

const int INF = INT_MAX;

struct currentMovedNode {
    currentMovedNode& operator=(const currentMovedNode &other){
        if(&other == this){
            return *this;
        }
        this->score = other.score;
        this->movedPosition = other.movedPosition;
    }

    int score;
    pair<int, int> movedPosition;
};

class Isolation {
public:
    Isolation();
    Isolation(const char& whoFirst);

    void initialize();
    void display() const;
    bool makeMove(const char& player, int row, int col);
    friend ostream& operator<<(ostream &out, const Isolation &x);
    string getcurrentX() const;
    string getcurrentO() const;
    void computerMove();
    bool computeMove(string movingPosition); // testing function
    bool opponentMove(string movingPosition);
    bool isWin(const char& player);
    inline bool isComputerPlay() const {return playing == computer;}
    char whoIsPlaying() const {return playing;}
    pair<int, int> getMove();


private:
    bool isValidMove(const char& player, pair<int,int> movePosition) const;
    bool checkLosingCondition(const char& player) const;
    inline bool outOfBound(pair<int,int> position) const;
    inline bool isUsed(pair<int,int> position) const;
    inline bool isUsed(pair<int, int> position, const char board[BOARD_SIZE][BOARD_SIZE]) const;
    int utility(const char& player);
    void getAllLegalMovesVertHoriz(vector<pair<int, int>> &list, const char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool upOrLeft, bool horizontal);
    void getAllLegalMovesDiagonally(vector<pair<int, int>> &list, const char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool dirRight);
    vector<pair<int,int>> getAllPossibleMoves(const char board[BOARD_SIZE][BOARD_SIZE], const pair<int, int> &player_pos);


    currentMovedNode iterativeDeepSearch();
    currentMovedNode alphaBetaSearch(const Board &board, const int &depth, int &alpha, int &beta, bool max_player = true);
    currentMovedNode maxValue(const Board &board, const int &depth, int &alpha, int &beta);
    currentMovedNode minValue(const Board &board, const int &depth, int &alpha, int &beta);

    void copyBoard(const char board[BOARD_SIZE][BOARD_SIZE], char newBoard[BOARD_SIZE][BOARD_SIZE]);
    void applyMove(pair<int, int> move, Board &board, bool max_player);
    void printBoard(const char board[BOARD_SIZE][BOARD_SIZE]);
//    pair<int,int> alphaBetaSreach(char board[BOARD_SIZE][BOARD_SIZE]);
//    int maxValue(char board[BOARD_SIZE][BOARD_SIZE], int& alpha, int& beta);
//    int minValue(char board[BOARD_SIZE][BOARD_SIZE], int& alpha, int& beta);

    int heuristic1 (Board b);
    int heuristic2 (Board b);

    char board[BOARD_SIZE][BOARD_SIZE];
    vector<string> playerC;
    vector<string> playerO;
    pair<int,int> currentX;
    pair<int,int> currentO;
    char playing;
    char waiting;
    char computer;
    char opponent;


};



#endif //ISOLATION_ISOLATION_H
