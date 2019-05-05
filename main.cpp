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

    while(play) {
        if (game.isComputerPlay()) {
            game.computerMove();
        } else {
            cout << " Make a move for Opponent: ";
            cin >> movee;
            game.opponentMove(movee);
        }
        cur = game.whoIsPlaying() == 'X'? 'O' : 'X';
        cout << game << endl;
        if (game.isWin(cur)){
            cout << cur << " is the winner!" << endl;
            play = false;
        }
    }

    return 0;
}