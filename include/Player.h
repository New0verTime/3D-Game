#ifndef PLAYER_H
#define PLAYER_H
#include"TextureManager.h"
#include"Game.h"
#include<iostream>
#include<string>
#include<math.h>
#include<SDL.h>
class Player
{
    public:
    static Player* Instance()
    {
    if(m_pPlayer == 0)
    {
    m_pPlayer = new Player();
    }
    return m_pPlayer;
    }
    double getPosx() {return posx;}
    double getPosy() {return posy;}
    double getAngle() {return angle;}
    void render(SDL_Renderer* mr){
        TheTextureManager::Instance()->draw("Player",posx,posy,pWidth,pHeight,mr,SDL_FLIP_NONE,angle);
    }
    void update()
    {
        int speed=Player_speed*(SDL_GetTicks()-time);
        //std::sin(x);
        //std::cos(x);
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if( currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_W ] ){
				    if(TheGame::Instance()->getMap( int((posx+speed*std::cos(angle/57.2958)/2)/50.0) , int(posy/50.0) )==0)
					posx+=speed*std::cos(angle/57.2958)/2;
				    if(TheGame::Instance()->getMap( int(posx/50.0) , int((posy+speed*std::sin(angle/57.2958)/2)/50.0) )==0)
					posy+=speed*std::sin(angle/57.2958)/2;
				}
            else if( currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[ SDL_SCANCODE_S ] ){
				    if(TheGame::Instance()->getMap( int((posx-speed*std::cos(angle/57.2958)/2)/50.0) , int(posy/50.0) )==0)
					posx-=speed*std::cos(angle/57.2958)/2;
				    if(TheGame::Instance()->getMap( int(posx/50.0) , int((posy-speed*std::sin(angle/57.2958)/2)/50.0) )==0)
					posy-=speed*std::sin(angle/57.2958)/2;
				}
            if( currentKeyStates[ SDL_SCANCODE_LEFT ] ||currentKeyStates[ SDL_SCANCODE_Q ])
				{
					angle-=3;
					if(angle>180) angle-=360;
				}
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] || currentKeyStates[ SDL_SCANCODE_E ] )
				{
					if(angle<-180) angle+=360;
					angle+=3;
				}
            if(currentKeyStates[ SDL_SCANCODE_A ]){
                    if(TheGame::Instance()->getMap( int((posx-speed*std::cos((angle+90)/57.2958)/2)/50.0) , int(posy/50.0) )==0)
					posx-=speed*std::cos((angle+90)/57.2958)/2;
				    if(TheGame::Instance()->getMap( int(posx/50.0) , int((posy-speed*std::sin((angle+90)/57.2958)/2)/50.0) )==0)
					posy-=speed*std::sin((angle+90)/57.2958)/2;
            }
            else if(currentKeyStates[ SDL_SCANCODE_D ]){
                    if(TheGame::Instance()->getMap( int((posx-speed*std::cos((angle-90)/57.2958)/2)/50.0) , int(posy/50.0) )==0)
					posx-=speed*std::cos((angle-90)/57.2958)/2;
				    if(TheGame::Instance()->getMap( int(posx/50.0) , int((posy-speed*std::sin((angle-90)/57.2958)/2)/50.0) )==0)
					posy-=speed*std::sin((angle-90)/57.2958)/2;
            }
        time=SDL_GetTicks();
    }
    private:
    int pWidth=1,pHeight=1;
    double posx=56,posy=56,angle=std::sqrt(2),Player_speed=1,time=SDL_GetTicks(); // angle=srqt2 se giup tranh goc 90 do trong viec tinh tan, cot
    static Player* m_pPlayer;
    Player(){};
    ~Player(){};
};
typedef Player ThePlayer;
#endif // PLAYER_H
