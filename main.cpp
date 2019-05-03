#include <iostream>
#include <cstdlib>

#include "Isolation.h"

using namespace std;

int main() {
    char who;
    char cur;
    bool play = true;
    string movee;

    cout << "Welcome!! Please enter who will play first [C]omputer or [O]pponent: " ;
    cin >> who;
    Isolation game = Isolation(who);
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
//     game.makeMove('X',7,0);
//    cout << game;
//    game.makeMove('X',3,4);
//    cout << game;
    while(play) {
        if (game.isComputerPlay()) {
            game.computerMove();
        } else {
            cout << " Make a move for O: ";
            cin >> movee;
            if (game.opponentMove(movee)) {
                //cur = cur == 'X' ? 'O' : 'X';
            }
        }
        cur = game.whoIsPlaying() == 'X'? 'O' : 'X';
        cout << game << endl;
        if (game.isWin(cur)){
            cout << cur << " is the winner!" << endl;
            play = false;
        }
    }

//    pair<int, int> comp_move = game.getMove();
//    cout << "best move: " << comp_move.first << " , " << comp_move.second << "\n";
//
////    game.opponentMove("A7");
////    //game.makeMove('X',1,7);
////    cout << game;
////    game.opponentMove("A2");
////    //game.makeMove('X',1,2);
////    cout << game;
////    game.opponentMove("A8");
////    //game.makeMove('X',1,8);
////    cout << game;

    return 0;
}