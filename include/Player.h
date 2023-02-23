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
        std::cout<<int((posx)/50.0)<<" "<<int((posy)/50.0)<<std::endl;
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if( currentKeyStates[ SDL_SCANCODE_UP ] ){
				    if(TheGame::Instance()->getMap( int((posx+speed*std::cos(angle/57.2958))/50.0) , int(posy/50.0) )==0)
					posx+=speed*std::cos(angle/57.2958);
				    if(TheGame::Instance()->getMap( int(posx/50.0) , int((posy+speed*std::sin(angle/57.2958))/50.0) )==0)
					posy+=speed*std::sin(angle/57.2958);
				}
            else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ){
				    if(TheGame::Instance()->getMap( int((posx-speed*std::cos(angle/57.2958))/50.0) , int(posy/50.0) )==0)
					posx-=speed*std::cos(angle/57.2958);
				    if(TheGame::Instance()->getMap( int(posx/50.0) , int((posy-speed*std::sin(angle/57.2958))/50.0) )==0)
					posy-=speed*std::sin(angle/57.2958);
				}
            if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
				{
					angle-=5;
					if(angle>180) angle-=360;
				}
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
				{
					if(angle<-180) angle+=360;
					angle+=5;
				}
        time=SDL_GetTicks();
    }
    private:
    int pWidth=1,pHeight=1;
    double posx=56,posy=56,angle,Player_speed=1,time=SDL_GetTicks();
    static Player* m_pPlayer;
    Player(){};
    ~Player(){};
};
typedef Player ThePlayer;
#endif // PLAYER_H
