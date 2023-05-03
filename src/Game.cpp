#include "Game.h"
#include "Ray_cast.h"
#include "Player.h"
#include "TextureManager.h"
#include "StaticObject.h"
#include "Collectable.h"
#include "NPC.h"
#include "Teleport.h"
#include "Object.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
Mix_Music *gMusic = NULL;
Mix_Music *menuMusic=NULL;
Mix_Chunk *footstep=NULL;
int tam=0;
Game* Game::m_pGame = 0;
bool sorter(Object* lhs, Object* rhs) {
    return lhs->get_dist() > rhs->get_dist();
}
void Read_map(std::string path,std::vector<std::vector<int>> &maps,SDL_Renderer* gRenderer){
    maps.clear();
    std::ifstream myfile;
    std::string line;
    myfile.open(path,std::ios::in);
    while (getline(myfile,line))
    {
      std::vector<int> tmp;
      int l=line.size();
      int k=0;
      for(int i=0;i<l;++i){
        if(line[i]==' ') {
            TheTextureManager::Instance()->load("assets/"+std::to_string(k%128)+".png",std::to_string(k%128),gRenderer);
            tmp.push_back(k);
            k=0;
        }
        else{
            k=k*10+(line[i]-'0');
        }
      }
      maps.push_back(tmp);
    }
    myfile.close();
}
void Read_object(std::string path,std::vector<Object*> &obj_map,SDL_Renderer* gRenderer){
    for(int i=0;i<obj_map.size();++i){
        delete obj_map[i];
    }
    obj_map.clear();
    std::ifstream myfile;
    std::string line;
    myfile.open(path,std::ios::in);
    while (getline(myfile,line))
    {
      std::vector<int> tmp;
        if(line[0]=='0'){
            int l=line.size();
            int k=0;
            for(int i=2;i<l;++i){
                if(line[i]==' ') {
                    tmp.push_back(k);
                    k=0;
                }
                else{
                    k=k*10+(line[i]-'0');
                }
            }
            std::vector<std::string> t;
            tmp.push_back(k);
            for(int i=6;i<tmp.size();++i){
                t.push_back(std::to_string(tmp[i]));
                TheTextureManager::Instance()->load("assets/"+std::to_string(tmp[i])+".png",std::to_string(tmp[i]),gRenderer);
                }
            StaticObject* objj =new StaticObject(tmp[0],tmp[1],t,tmp[2]/2.0,tmp[3]/2.0,tmp[5]/2.0,tmp[4]);
            obj_map.push_back(objj);
        }
        else if(line[0]=='1'){
            int l=line.size();
            int k=0;
            for(int i=2;i<l;++i){
                if(line[i]==' ') {
                    tmp.push_back(k);
                    k=0;
                }
                else{
                    k=k*10+(line[i]-'0');
                }
            }
            std::vector<std::string> t;
            tmp.push_back(k);
            //6 7 8 la id
            for(int i=9;i<tmp.size();++i){
                t.push_back(std::to_string(tmp[i]));
                TheTextureManager::Instance()->load("assets/"+std::to_string(tmp[i])+".png",std::to_string(tmp[i]),gRenderer);
                }
            Teleport* objj =new Teleport(tmp[0],tmp[1],t,tmp[2]/2.0,tmp[3]/2.0,tmp[5]/2.0,tmp[4],std::to_string(tmp[6]),tmp[7],tmp[8]);
            obj_map.push_back(objj);
        }
        else if(line[0]=='2') {
            int l=line.size();
            int k=0;
            for(int i=2;i<l;++i){
                if(line[i]==' ') {
                    tmp.push_back(k);
                    k=0;
                }
                else{
                    k=k*10+(line[i]-'0');
                }
            }
            std::vector<std::string> t;
            tmp.push_back(k);
            for(int i=6;i<tmp.size();++i){
                t.push_back(std::to_string(tmp[i]));
                TheTextureManager::Instance()->load("assets/"+std::to_string(tmp[i])+".png",std::to_string(tmp[i]),gRenderer);
                }
            std::string name;
            getline(myfile,name);
            getline(myfile,line);
            l=line.size();
            k=0;
            int s_num;
            for(int i=0;i<l;++i){
                    k=k*10+line[i]-'0';
            }
            s_num=k;
            k=0;
        // moi status
        std::vector<Status*> stt;
        for(int i=0;i<s_num;++i){
            getline(myfile,line);
            l=line.size();
            int sn,an;
            for(int i=0;i<l;++i){
                if(line[i]!=' '){
                    k=k*10+line[i]-'0';
                }
                if(line[i]==' '){
                    sn=k;
                    k=0;
                }
            }
            an=k;
            std::vector<std::string> sentences;
            for(int i=0;i<sn;++i){
            getline(myfile,line);
            sentences.push_back(line);
            }
            std::vector<std::string> answer;
            std::vector<std::vector<int>> impact;
            for(int i=0;i<an;++i){
                k=0;
                getline(myfile,line);
                answer.push_back(line);
                getline(myfile,line);
                std::vector<int> tmp;
                l=line.size();
                for(int i=0;i<l;++i){
                    if(line[i]==' ') {
                        tmp.push_back(k);
                        k=0;
                    }
                    else{
                        k=k*10+(line[i]-'0');
                    }
                }
                impact.push_back(tmp);
            }
            Status* statut = new Status(sentences,answer,impact);
            stt.push_back(statut);
        }
        NPC* objj=new NPC(tmp[0],tmp[1],t,tmp[2]/2.0,tmp[3]/2.0,name,stt,tmp[5]/2.0,tmp[4]/2.0);
        obj_map.push_back(objj);
            }
        else if(line[0]=='3'){
            tam=1;
            int l=line.size();
            int k=0;
            for(int i=2;i<l;++i){
                if(line[i]==' ') {
                    tmp.push_back(k);
                    k=0;
                }
                else{
                    k=k*10+(line[i]-'0');
                }
            }
            std::vector<std::string> t;
            tmp.push_back(k);
            for(int i=6;i<tmp.size();++i){
                t.push_back(std::to_string(tmp[i]));
                TheTextureManager::Instance()->load("assets/"+std::to_string(tmp[i])+".png",std::to_string(tmp[i]),gRenderer);
                }
            Collectable* objj =new Collectable(tmp[0],tmp[1],t,tmp[2]/2.0,tmp[3]/2.0,tmp[5]/2.0,tmp[4]);
            obj_map.push_back(objj);
        }
    }
    myfile.close();
}
void Game::Load_map(std::string map_name,double px,double py,double angle){
    collected=-1;
    tam=0;
    TheTextureManager::Instance()->clearer();
    Read_map("assets/map"+map_name+".txt",maps,m_pRenderer);
    Read_object("assets/objmap"+map_name+".txt",obj_map,m_pRenderer);
    collected+=tam;
    ThePlayer::Instance()->setAngle(angle);
    ThePlayer::Instance()->setPosx(px);
    ThePlayer::Instance()->setPosy(py);
    TheTextureManager::Instance()->load("assets/sky.png","sky",m_pRenderer);
    bg=TheTextureManager::Instance()->getTexture("sky");
    ThePlayer::Instance()->setTime();
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    std::string tmpp = "assets/music"+map_name+".mp3";
    const char* k= tmpp.c_str();
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    gMusic = Mix_LoadMUS(k);
    delete k;
    if(map_name=="1") rain=true;
    else rain=false;
    if(map_name=="5") {R7.w=0,R7.h=0; jikangakakatta=(SDL_GetTicks()-gamestart)/1000;
    if(jikangakakatta<oldHighscore){
            std::fstream HighScoreToFile;
            HighScoreToFile.open("assets/HighScore.txt",std::ios::out);
            HighScoreToFile << jikangakakatta;
            oldHighscore=jikangakakatta;
            HighScoreToFile.close();
    }
            R8.y=0;
    }
    if(map_name=="6") {clean();}
    //    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}
SDL_Texture* Game::str_to_texture(std::string str){
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, str.c_str(), {255,255,255} );
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
    SDL_SetRenderDrawColor(m_pRenderer,255,255,255,255);}
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
    Load_map("0",56.0,56.0,0);
	std::fstream HighScoreFromFile;
	HighScoreFromFile.open("assets/HighScore.txt",std::ios::in);
	HighScoreFromFile >> oldHighscore;
	HighScoreFromFile.close();
    R1.x=0;
    R1.y=0;
    R1.w=1280;
    R1.h=360;
    R2.x=0;
    R2.y=0;
    R2.w=740;
    R2.h=720;
    R3.x=1000;
    R3.y=0;
    R3.h=70;
    R3.w=280;
    R4.x=0;
    R4.y=450;
    R4.h=100;
    R5.y=550;
    R5.w=1280;
    R5.h=170;
    R5.x=0;
    Rect1.w=300;
    Rect1.h=70;
    Rect1.y=640;
    Rect1.x=470;
    Rect2.w=400;
    Rect2.h=70;
    Rect2.y=640;
    Rect2.x=450;
    std::cout << "init success\n";
    TheTextureManager::Instance()->load("assets/arrow.png","arrow",m_pRenderer);
    TheTextureManager::Instance()->load("assets/play.png","play",m_pRenderer);
    TheTextureManager::Instance()->load("assets/quit.png","quit",m_pRenderer);
    TheTextureManager::Instance()->load("assets/3d.png","3d",m_pRenderer);
    TheTextureManager::Instance()->load("assets/guide.png","guide",m_pRenderer);
    TheTextureManager::Instance()->load("assets/guide1.png","guide1",m_pRenderer);
    TheTextureManager::Instance()->load("assets/rain.png","rain",m_pRenderer);
    menuMusic = Mix_LoadMUS("assets/music.mp3");
    return true;
}
void Game::render()
{
if(!menu){
if( Mix_PlayingMusic() == 0)
Mix_PlayMusic( gMusic, -1 );
SDL_RenderClear(m_pRenderer);
SDL_SetRenderDrawColor(m_pRenderer,150,150,150,255);
R1.y=360;
SDL_RenderFillRect(m_pRenderer,&R1);
R1.y=0;
R2.x=ThePlayer::Instance()->getAngle()*5+900;
SDL_RenderCopy(m_pRenderer,bg,&R2,&R1);
TheRay_cast::Instance()->update();
name="";
log="";
for(int i=0;i<obj_map.size();++i){
    obj_map[i]->RenderObject();
    if(obj_map[i]->istalk()) {
        name=obj_map[i]->getname(k);
        log=obj_map[i]->getlog(k);
    }
}if (collected>=0) {
    SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
    R3.x=1000;
    R3.y=0;
    SDL_RenderFillRect(m_pRenderer,&R3);
    SDL_SetRenderDrawColor(m_pRenderer,255,255,255,255);
    SDL_RenderDrawRect(m_pRenderer,&R3);
    SDL_Texture* tmp=str_to_texture("Collected:"+std::to_string(collected));
    SDL_RenderCopy(m_pRenderer,tmp,NULL,&R3);
    SDL_DestroyTexture(tmp); // loi con tro o day
    }
if(name!=""&&log!=""){
    talking=true;
    R4.w=25*name.size();
    SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
    SDL_RenderFillRect(m_pRenderer,&R4);
    SDL_RenderFillRect(m_pRenderer,&R5);
    SDL_SetRenderDrawColor(m_pRenderer,255,255,255,255);
    SDL_RenderDrawRect(m_pRenderer,&R4);
    SDL_RenderDrawRect(m_pRenderer,&R5);
    SDL_Texture* tmp=str_to_texture(name);
    SDL_RenderCopy(m_pRenderer,tmp,NULL,&R4);
    SDL_DestroyTexture(tmp);
    R3.x=0;
    R3.y=550;
    R3.w=14*log.size();
    SDL_Texture* tmp2=str_to_texture(log);
    SDL_RenderCopy(m_pRenderer,tmp2,NULL,&R3);
    SDL_DestroyTexture(tmp2); // loi con tro o day
    if(name!="Player"){
    R3.x=470;
    R3.y=640;
    R3.w=300;
    SDL_Texture* tmp3=str_to_texture("Press J to continue");
    SDL_RenderCopy(m_pRenderer,tmp3,NULL,&R3);
    SDL_DestroyTexture(tmp3); // loi con tro o day
    }
    else{
    R3.x=450;
    R3.y=640;
    R3.w=400;
    SDL_Texture* tmp3=str_to_texture("Press number key to answer");
    SDL_RenderCopy(m_pRenderer,tmp3,NULL,&R3);
    SDL_DestroyTexture(tmp3); // loi con tro o day
    }
}
else talking=false;
k=0;
if(rain){
    R6.y=720-2*int(SDL_GetTicks())%360;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("rain"),&R6,NULL);
}
SDL_Texture* tmp3=str_to_texture("Time: "+std::to_string( int(SDL_GetTicks()-gamestart)/1000 ));
SDL_RenderCopy(m_pRenderer,tmp3,NULL,&R7);
SDL_DestroyTexture(tmp3); // loi con tro o day
SDL_Texture* tmp5=str_to_texture("HighScore: "+std::to_string(oldHighscore));
SDL_RenderCopy(m_pRenderer,tmp5,NULL,&R8);
SDL_DestroyTexture(tmp5); // loi con tro o day
SDL_RenderPresent(m_pRenderer);
}
else{
if( Mix_PlayingMusic() == 0)
Mix_PlayMusic( menuMusic, -1 );
    if(menu_list==3){
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("guide1"),NULL,NULL);
        SDL_RenderPresent(m_pRenderer);
    }
    else{
    SDL_RenderClear(m_pRenderer);
    Rect.x=150;
    Rect.y=100;
    Rect.h=300;
    Rect.w=980;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("3d"),NULL,&Rect);
    Rect.x=500;
    Rect.y=400;
    Rect.h=70;
    Rect.w=280;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("play"),NULL,&Rect);
    Rect.x=500;
    Rect.y=475;
    Rect.h=100;
    Rect.w=280;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("guide"),NULL,&Rect);
    Rect.x=500;
    Rect.y=550;
    Rect.h=100;
    Rect.w=280;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("quit"),NULL,&Rect);
    Rect.x=300;
    Rect.y=400+menu_list*75;
    Rect.h=70;
    Rect.w=200;
    SDL_RenderCopy(m_pRenderer,TheTextureManager::Instance()->getTexture("arrow"),NULL,&Rect);
    SDL_RenderPresent(m_pRenderer);
    }
}
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
        case SDL_KEYDOWN:
            if(event.key.keysym.sym==SDLK_p){
                if(TheRay_cast::Instance()->get_rayinfoy(300)==(int)TheRay_cast::Instance()->get_rayinfoy(300)){
                if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]&4096){
                    if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]&1024)
                    maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]+=1024;
                    else maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]-=1024;
                }
                else if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]&4096){
                    if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]&1024)
                    maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]+=1024;
                    else maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]-=1024;
                }
                else if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][(int)TheRay_cast::Instance()->get_rayinfox(300)]&4096){
                    if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][(int)TheRay_cast::Instance()->get_rayinfox(300)]&1024)
                    maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][(int)TheRay_cast::Instance()->get_rayinfox(300)]+=1024;
                    else maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][(int)TheRay_cast::Instance()->get_rayinfox(300)]-=1024;
                }
                else if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]&4096){
                    if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]&1024)
                    maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]+=1024;
                    else maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)-1][std::ceil(TheRay_cast::Instance()->get_rayinfox(300))]-=1024;
                }
                }
                else {
                if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]&4096){
                    if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]&1024)
                    maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]+=1024;
                    else maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)]-=1024;
                }
                else if(maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][int(TheRay_cast::Instance()->get_rayinfox(300))]&4096){
                    if(maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][(int)TheRay_cast::Instance()->get_rayinfox(300)]&1024)
                    maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][(int)TheRay_cast::Instance()->get_rayinfox(300)]+=1024;
                    else maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][(int)TheRay_cast::Instance()->get_rayinfox(300)]-=1024;
                }
                else if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)-1]&4096){
                    if(maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)-1]&1024)
                    maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)-1]+=1024;
                    else maps[(int)TheRay_cast::Instance()->get_rayinfoy(300)][(int)TheRay_cast::Instance()->get_rayinfox(300)-1]-=1024;
                }
                else if(maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][int(TheRay_cast::Instance()->get_rayinfox(300))-1]&4096){
                    if(maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][(int)TheRay_cast::Instance()->get_rayinfox(300)-1]&1024)
                    maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][(int)TheRay_cast::Instance()->get_rayinfox(300)-1]+=1024;
                    else maps[std::ceil( TheRay_cast::Instance()->get_rayinfoy(300) )][(int)TheRay_cast::Instance()->get_rayinfox(300)-1]-=1024;
                }

                }
            }
            else if(event.key.keysym.sym==SDLK_UP){
                if(menu){
                --menu_list;
                if(menu_list<0) menu_list+=3;
                else if (menu_list==2) menu_list=1;}
            }
            else if(event.key.keysym.sym==SDLK_DOWN){
                if(menu){
                ++menu_list;
                if(menu_list>2) menu_list-=3;}
            }
            else if(event.key.keysym.sym==SDLK_RETURN){
                if(menu){
                if(menu_list==0) {menu=false;    Mix_FreeMusic( menuMusic ); menuMusic = NULL; gamestart=SDL_GetTicks();}
                else if(menu_list==1) menu_list=3;
                else if(menu_list==2) m_bRunning = false;
                }
            }
            else if(event.key.keysym.sym==SDLK_RETURN2){
                if(menu){
                if(menu_list==3){
                    menu_list==1;
                    SDL_DestroyTexture(TheTextureManager::Instance()->getTexture("3d"));
                    SDL_DestroyTexture(TheTextureManager::Instance()->getTexture("guide"));
                    SDL_DestroyTexture(TheTextureManager::Instance()->getTexture("guide1"));
                    SDL_DestroyTexture(TheTextureManager::Instance()->getTexture("play"));
                    SDL_DestroyTexture(TheTextureManager::Instance()->getTexture("quit"));
                    SDL_DestroyTexture(TheTextureManager::Instance()->getTexture("arrow"));
                }
                }
            }
            else if (event.key.keysym.sym==SDLK_t){
                for(int i=0;i<obj_map.size();++i){
                    if(obj_map[i]->get_dist()<5) obj_map[i]->set_talk();
                    }
            }
            else if(talking){
            if(event.key.keysym.sym==SDLK_0){
                k='0';
            }
            else if(event.key.keysym.sym==SDLK_1){
                k='1';
            }
            else if(event.key.keysym.sym==SDLK_2){
                k='2';
            }
            else if(event.key.keysym.sym==SDLK_3){
                k='3';
            }
            else if(event.key.keysym.sym==SDLK_4){
                k='4';
            }
            else if(event.key.keysym.sym==SDLK_5){
                k='5';
            }
            else if(event.key.keysym.sym==SDLK_6){
                k='6';
            }
            else if(event.key.keysym.sym==SDLK_7){
                k='7';
            }
            else if(event.key.keysym.sym==SDLK_8){
                k='8';
            }
            else if(event.key.keysym.sym==SDLK_9){
                k='9';
            }
            else if(event.key.keysym.sym==SDLK_j){
                k='j';
            }
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
if(!menu){
int k=obj_map.size();
for(int i=0;i<k;++i){
    obj_map[i]->getInfo();
    if(obj_map[i]->get_dist()>5) obj_map[i]->out_talk();
}
std::sort(obj_map.begin(), obj_map.end(), &sorter);
Player::Instance()->update();
}
}
