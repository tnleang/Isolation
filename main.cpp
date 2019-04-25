#include <iostream>
#include <cstdlib>

#include "Isolation.h"

using namespace std;

int main() {
    cout << "Welcome!! Please enter who will play first [C]omputer or [O]pponent:" << endl;
    Isolation game = Isolation();
    cout << game;
    cout << game.getcurrentX() << endl;
    game.makeMove('X',1,7);
    cout << game;
    game.makeMove('X',1,2);
    cout << game;
    game.makeMove('X',1,8);
    cout << game;

    return 0;
}