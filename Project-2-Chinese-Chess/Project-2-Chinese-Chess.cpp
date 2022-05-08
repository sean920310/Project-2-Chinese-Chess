//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <iostream>
#include "GameManager.h"

int main()
{
    GameManager game;
    game.inGame();
    //end of application
    return 0;
}
