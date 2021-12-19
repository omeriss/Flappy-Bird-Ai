#include "Game.h"

int main()
{
    Game* game;
    int inputNum;
    cout << "Enter Game Type:\n1- Normal Game\n2- Ai Game\n";
    cin >> inputNum;
    if (inputNum == 1) {
        game = new UserGame();
    }
    else {
        string base, save; {
            cout << "Enter Save bird file name and base bird file name (0 if you dont want to enter one of the files)\n";
            cin >> save >> base;
            game = new AiGame(base, save);
        }
    }
    game->Start();
    return 0;
}