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
{   pause=false;
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
    TheTextureManager::Instance()->load("assets/heart.png","heart",m_pRenderer);
    TheTextureManager::Instance()->load("assets/mrb.png","mrb",m_pRenderer);
    TheTextureManager::Instance()->load("assets/sky.png","sky",m_pRenderer);
    TheTextureManager::Instance()->load("assets/gameover.png","gameover",m_pRenderer);
    TheTextureManager::Instance()->load("assets/win.png","win",m_pRenderer);
    TheTextureManager::Instance()->load("assets/sung.png","sung",m_pRenderer);
    TheTextureManager::Instance()->load("assets/sung ban.png","sung ban",m_pRenderer);
    TheTextureManager::Instance()->load("assets/crosshair.png","crosshair",m_pRenderer);
    TheTextureManager::Instance()->load("assets/guide.png","guide",m_pRenderer);
    StaticObject* Test_Object =new StaticObject(2.0,2.0,"5",720,1.5);
    movingObject* Test_Object2 =new movingObject(2.0,2.0,"mrb",720,1.5,0.01,1,1000,1);
    for(int w=1;w<3;++w){
        movingObject* test= new movingObject(w*w,w*w,"mrb",720,1.5,0.01,1,1000,1);
        m_pObj2.push_back(test);
    }
    m_pObj.push_back(Test_Object);
    m_pObj2.push_back(Test_Object2);
    std::cout << "init success\n";
    return true;
}
void Game::render()
{
SDL_RenderClear(m_pRenderer);
if(pause==false) TheTextureManager::Instance()->draw("sky",0,0,1280,360,m_pRenderer);
TheRay_cast::Instance()->render();
if(pause==false){
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
}
const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_M ] ){
        pause=true;
        int u=maps.size(),v=maps[0].size();
        SDL_SetRenderDrawColor(m_pRenderer,255,255,255,255);
        for(int i=0;i<v;++i){
            for(int j=0;j<u;++j){
                if(maps[j][i]){
                SDL_Rect Rect;
                Rect.x=i*20;
                Rect.y=j*20;
                Rect.h=20;
                Rect.w=20;
                SDL_RenderDrawRect(m_pRenderer,&Rect);}
            }
        }
        SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
    }
    else pause=false;
        SDL_Rect Rect;
        Rect.x=600;
        Rect.y=300;
        Rect.h=450;
        Rect.w=680;
    if( currentKeyStates[ SDL_SCANCODE_J ] ){
        SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("sung ban"),NULL,&Rect);
        int l=m_pObj2.size();
        for(int i=l-1;i>=0;--i)
        if(m_pObj2[i]->get_angle()<=33&&m_pObj2[i]->get_angle()>=25){m_pObj2.erase(m_pObj2.begin()+i);}

    }
    else{
        SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("sung"),NULL,&Rect);
    }
    Rect.x=600;
    Rect.y=325;
    Rect.h=40;
    Rect.w=50;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("crosshair"),NULL,&Rect);
for(int i=0;i<ThePlayer::Instance()->getHealth();++i){
    SDL_Rect Rect;
    Rect.x=40*i;
    Rect.y=700;
    Rect.w=30;
    Rect.h=30;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("heart"),NULL,&Rect);
}
SDL_RenderPresent(m_pRenderer);
}
void Game::handleEvents()
{
    SDL_Event e;
    while(tmp==true){
       SDL_RenderClear(m_pRenderer);
       SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("guide"),NULL,NULL);
       SDL_RenderPresent(m_pRenderer);
    if(SDL_PollEvent(&e))
        {
    switch (e.type)
        {
        case SDL_QUIT:
        m_bRunning = false;
        break;
        case SDL_KEYDOWN:
        {
            if(e.key.keysym.sym==SDLK_p) tmp=false;
        }
        break;
        default:
        break;
            }
        }
    }
// chi co chua moi biet toi dang viet cai j :)))))))))  p/s: den day xong game roi :3
    if(SDL_PollEvent(&e))
        {
    switch (e.type)
        {
        case SDL_QUIT:
        m_bRunning = false;
        break;
        case SDL_KEYDOWN:
        {
            if(e.key.keysym.sym==SDLK_p) tmp=false;
        }
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
if (ThePlayer::Instance()->getHealth()==0){
SDL_RenderClear(m_pRenderer);
SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("gameover"),NULL,NULL);
SDL_RenderPresent(m_pRenderer);
SDL_Delay(5000);
m_bRunning=false;
}
Player::Instance()->update();
int l=m_pObj2.size();
if (l==0){
SDL_RenderClear(m_pRenderer);
SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("win"),NULL,NULL);
SDL_RenderPresent(m_pRenderer);
SDL_Delay(5000);
m_bRunning=false;
}
for(int i=0;i<l;++i){
    m_pObj2[i]->go();
    m_pObj2[i]->handleCollide();
}
}
