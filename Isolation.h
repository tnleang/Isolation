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

using namespace std;

const int BOARD_SIZE = 8;

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
    bool opponentMove(string movingPosition);


private:
    bool isValidMove(const char& player, pair<int,int> movePosition) const;
    inline bool outOfBound(pair<int,int> position) const;
    inline bool isUsed(pair<int,int> position) const;
    bool isWin(const char& player);
    int utility(const char& player);
    vector<pair<int,int>> getAllPossitbleMoves(const char& player);

    pair<int,int> alphaBetaSreach(char board[BOARD_SIZE][BOARD_SIZE]);
    int maxValue(char board[BOARD_SIZE][BOARD_SIZE], int& alpha, int& beta);
    int minValue(char board[BOARD_SIZE][BOARD_SIZE], int& alpha, int& beta);

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
