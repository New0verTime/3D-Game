#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include "StaticObject.h"
#include "Ray_cast.h"
#include <SDL_ttf.h>
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
Game* Game::m_pGame = 0;
void Read_map(std::string path,std::vector<std::vector<int>> &maps){
    maps.clear();
    std::ifstream myfile;
    std::string line;
    myfile.open(path,std::ios::in);
    while (getline(myfile,line))
    {
      std::vector<int> tmp;
      int l=line.size();
      for(int i=0;i<l;++i){
        if(line[i]!=' ') tmp.push_back(line[i]-'0');
      }
      maps.push_back(tmp);
    }
    myfile.close();
}
SDL_Texture* Game::str_to_texture(std::string str){
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, str.c_str(), {0,0,0} );
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_pRenderer,textSurface);
    SDL_FreeSurface(textSurface);
    return textTexture;
}
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
    std::cout << "SDL init success\n";
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow != 0) // window init success
    {
    std::cout << "window creation success\n";
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    if(m_pRenderer != 0) // renderer init success
    {
    std::cout << "renderer creation success\n";
    SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);}
    else
    {
    std::cout << "renderer init fail\n";
    return false; // renderer init fail
    }
    }
    else
    {
    std::cout << "window init fail\n";
    return false; // window init fail
    }
    }
    else
    {
    std::cout << "SDL init fail\n";
    return false; // SDL init fail
        }
    m_bRunning = true;
    TTF_Init();
    gFont = TTF_OpenFont( "Raleway-Medium.ttf", 28 );
    Read_map("assets/map.txt",maps);
    TheTextureManager::Instance()->load("assets/1.png","1",m_pRenderer);
    TheTextureManager::Instance()->load("assets/2.png","2",m_pRenderer);
    TheTextureManager::Instance()->load("assets/3.png","3",m_pRenderer);
    TheTextureManager::Instance()->load("assets/4.png","4",m_pRenderer);
    TheTextureManager::Instance()->load("assets/5.png","5",m_pRenderer);
    TheTextureManager::Instance()->load("assets/6.png","6",m_pRenderer);
    TheTextureManager::Instance()->load("assets/mrb.png","mrb",m_pRenderer);
    TheTextureManager::Instance()->load("assets/sky.png","sky",m_pRenderer);
// cau hoi tai sao khi lam nhu the nay lai loi? StaticObject Test_Object(2,2,"1"); m_pObj.push_back(&Test_Object) lai sai?
    StaticObject* Test_Object =new StaticObject(2.0,2.0,"5",720,1.5);
    movingObject* Test_Object2 =new movingObject(2.0,2.0,"mrb",720,1.5,0.01);
    m_pObj.push_back(Test_Object);
    m_pObj2.push_back(Test_Object2);
    std::cout << "init success\n";
    return true;
}
void Game::render()
{
SDL_RenderClear(m_pRenderer);
//TheTextureManager::Instance()->draw("sky",0,0,1280,360,m_pRenderer);
Player::Instance()->render(m_pRenderer);
TheRay_cast::Instance()->render();
int l=m_pObj.size();
for(int i=0;i<l;++i){
    m_pObj[i]->getInfo();
    m_pObj[i]->RenderObject();
}
l=m_pObj2.size();
for(int i=0;i<l;++i){
    m_pObj2[i]->getInfo();
    m_pObj2[i]->RenderObject();

}
SDL_RenderPresent(m_pRenderer);
}
void Game::handleEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
        {
    switch (event.type)
        {
        case SDL_QUIT:
        m_bRunning = false;
        break;
        default:
        break;
            }
        }
}
void Game::clean()
{
    std::cout << "cleaning game\n";
    TTF_CloseFont( gFont );
    gFont = NULL;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
void Game::update()
{
Player::Instance()->update();
int l=m_pObj2.size();
for(int i=0;i<l;++i)
    m_pObj2[i]->go();
}
