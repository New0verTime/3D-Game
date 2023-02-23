#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include "Ray_cast.h"
#include <SDL_ttf.h>
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
Game* Game::m_pGame = 0;
void Read_map(std::string path,std::vector<std::vector<int>> &maps){
    std::ifstream myfile;
    std::string line;
    myfile.open(path,std::ios::in);
    while (getline(myfile,line))
    {
      std::vector<int> tmp;
      int l=line.size();
      for(int i=0;i<l;++i){
        if(line[i]=='1') tmp.push_back(1);
        else if(line[i]=='0') tmp.push_back(0);
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
    TheTextureManager::Instance()->load("assets/Player.png","Player",m_pRenderer);
    std::cout << "init success\n";
    return true;
}
void Game::render()
{
SDL_Rect rect;
SDL_RenderClear(m_pRenderer);
int m=maps.size(),n=maps[0].size();
SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
for(int i=0;i<m;++i){
    for(int j=0;j<n;++j){
        if(maps[i][j]==1) {
            rect.x = j*50;
            rect.y = i*50;
            rect.w = 50;
            rect.h = 50;
            SDL_RenderDrawRect(m_pRenderer, &rect);
        }
    }
}
SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
Player::Instance()->render(m_pRenderer);
TheRay_cast::Instance()->update();
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
}
