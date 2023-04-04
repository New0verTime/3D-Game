#include<SDL.h>
#include"Game.h"
int main(int argc, char* argv[])
{
TheGame::Instance()->init("3D Game", 50, 50, 1280, 720, 0); // khoi tao
while(TheGame::Instance()->running())
{
    TheGame::Instance()->handleEvents(); // cap nhat thong tin tu ban phim
    TheGame::Instance()->update(); // cap nhat trang thai cac vat the
    TheGame::Instance()->render(); // hien thi hinh anh
}
TheGame::Instance()->clean(); // xoa game
return 0;
}
