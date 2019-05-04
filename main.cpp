#include <iostream>
#include <cstdlib>

#include "Isolation.h"

using namespace std;

int main() {
    char who;
    char cur;
    bool play = true;
    string movee;
    int time;

    cout << "Welcome!! Please enter who will play first [C]omputer or [O]pponent: " ;
    cin >> who;
    cout << "how many second is time limit: " ;
    cin >> time;
    Isolation game = Isolation(who, time);
    cout << game;

    /**
     * So far the alphabeta works, it takes a while to get an answer because it uses iterative deepening
     * and has to iterate through the tree again for every new depth, e.x. depth: 1 => 1,2 => 1,2,3 => and so forth
     * until it finds a terminal state, but at the beginning of the game the iterative deepening would not hit terminal states
     * before 20 seconds. So, instead it returns the move with the highest score.
     *
     * TODO:
     *  Create menu to handle opponent's input and computer's getMove and apply that move.
     */

    game.twoAIPlay();
//    while(play) {
//        if (game.isComputerPlay()) {
//            game.computerMove();
//        } else {
//            cout << " Make a move for Opponent: ";
//            cin >> movee;
//            game.opponentMove(movee);
//        }
//        cur = game.whoIsPlaying() == 'X'? 'O' : 'X';
//        cout << game << endl;
//        if (game.isWin(cur)){
//            cout << cur << " is the winner!" << endl;
//            play = false;
//        }
//    }

    return 0;
}