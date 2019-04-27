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
    cur = 'X';

    while(play) {
        if (game.isComputerPlay()) {
            cout << " Make a move for C: ";
            cin >> movee;
            if (game.computeMove(movee)) {
                //cur = cur == 'X' ? 'O' : 'X';
            }
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


//    game.opponentMove("A7");
//    //game.makeMove('X',1,7);
//    cout << game;
//    game.opponentMove("A2");
//    //game.makeMove('X',1,2);
//    cout << game;
//    game.opponentMove("A8");
//    //game.makeMove('X',1,8);
//    cout << game;

    return 0;
}