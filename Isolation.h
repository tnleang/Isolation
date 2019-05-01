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

TIME_LIMIT

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



private:
    bool isValidMove(const char& player, pair<int,int> movePosition) const;
    bool checkLosingCondition(const char& player) const;
    inline bool outOfBound(pair<int,int> position) const;
    inline bool isUsed(pair<int,int> position) const;
    inline bool isUsed(pair<int, int> positio, char board[BOARD_SIZE][BOARD_SIZE]) const;
    int utility(const char& player);
    void getAllLegalMovesVertHoriz(vector<pair<int, int>> &list, char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool upOrLeft, bool horizontal);
    void getAllLegalMovesDiagonally(vector<pair<int, int>> &list, char board[BOARD_SIZE][BOARD_SIZE], int player_y, int player_x, bool dirRight);
    vector<pair<int,int>> getAllPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], const pair<int, int> &player_pos);
    pair<int, int> getMove();

    currentMovedNode iterativeDeepSearch();
    currentMovedNode alphaBetaSearch(char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &depth, int &alpha, int &beta, bool max_player = true);
    currentMovedNode maxBaseDepthValue(vector<pair<int, int>> &legalMoves, char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &alpha, const int &beta, const int &highest_score, const pair<int, int> &best_move);
    currentMovedNode minBaseDepthValue(vector<pair<int, int>> &legalMoves, char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &alpha, const int &beta, const int &lowest_score, const pair<int, int> &best_move);
    currentMovedNode maxValue(vector<pair<int, int>> &legalMoves, char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &depth, int &alpha, int &beta, const int &highest_score, const pair<int, int> &best_move);
    currentMovedNode minValue(vector<pair<int, int>> &legalMoves, char board[BOARD_SIZE][BOARD_SIZE], pair<int, int> player_pos, const int &depth, int &alpha, int &beta, const int &lowest_score, const pair<int, int> &best_move);
    int getHeuristicScore(char board[BOARD_SIZE][BOARD_SIZE]);

    void copyBoard(char board[BOARD_SIZE][BOARD_SIZE], char newBoard[BOARD_SIZE][BOARD_SIZE]);
    void applyMove(pair<int, int> move, pair<int, int> player_pos, char board[BOARD_SIZE][BOARD_SIZE]);
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
