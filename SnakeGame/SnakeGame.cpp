#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    //char board[20][50];

    ////   0 1 2 3
    //// 0 x x x x x x 
    //// 1 x         x
    //// 2 x         x
    //// 3 x x x x x x


    //for(int i = 0; i < 20; i++)
    //{
    //    for (int j = 0; j < 50; j++)
    //    {
    //        if (i == 0 || i == 19 || j == 0 || j == 49)
    //        {
    //            board[i][j] = '#';
    //        }
    //        else board[i][j] = ' ';
    //    }

    //    cout << "\n";
    //}

    // destroy board

    Game game;

    game.start_game();

    return 0;
}
