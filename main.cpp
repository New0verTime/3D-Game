#include<SDL.h>
#include"TextureManager.h"
#include"Game.h"
#include<iostream>
int main(int argc, char* argv[])
{
    TheGame::Instance()->init("Chapter 1", 50, 50, 1280, 750, 0);
while(TheGame::Instance()->running())
{
    TheGame::Instance()->handleEvents();
    TheGame::Instance()->update();
    TheGame::Instance()->render();
}
TheGame::Instance()->clean();
return 0;
}
