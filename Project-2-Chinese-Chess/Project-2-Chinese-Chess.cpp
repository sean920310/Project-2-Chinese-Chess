//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <iostream>
#include "GameManager.h"

int main()
{
    GameManager game;
    while (1)
    {
        switch (game.menu())
        {
        case 0:
            return 0;
            break;
        case 1:
            game.inGame(InGameState::start);
            break;
        case 2:
            game.readFile();
            game.inGame(InGameState::inputFile);
            break;
        default:
            break;
        }
    }
    //end of application
    return 0;
}
