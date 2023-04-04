#ifndef PLAYER_H
#define PLAYER_H
#include"TextureManager.h"
#include"Game.h"
#include"Ray_cast.h"
#include<iostream>
#include<string>
#include<math.h>
#include<SDL.h>
class Ray_cast;
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
    void setPosx(double _x) {posx=_x;}
    void setPosy(double _y) {posy=_y;}
    void setAngle(double a) {angle=a;}
    void setTime(){time=SDL_GetTicks();}
    void update()
    {
        int speed=Player_speed*(SDL_GetTicks()-time);
        double c=std::cos(angle/57.295779)*speed,s=std::sin(angle/57.295779)*speed;
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if( currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_W ] ){
					posx+=c;
					if (int ((posx-c)/50.0)!=int(posx/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posx-=c;
                        else if(c>0&&a&1024)
                            posx-=c;
                        else if(c<0&&TheGame::Instance()->getMap(int( (posx-c) /50.0) , int(posy/50.0))&1024)
                            posx-=c;
                    }
					posy+=s;
					if(int((posy-s)/50.0)!=int(posy/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posy-=s;
                        else if(s>0&&a&2048)
                            posy-=s;
                        else if(s<0&&TheGame::Instance()->getMap(int( posx /50.0) , int( (posy-s) /50.0))&2048)
                            posy-=s;
                    }
				}
            else if( currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[ SDL_SCANCODE_S ] ){
					posx-=c;
					if (int ((posx+c)/50.0)!=int(posx/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posx+=c;
                        else if(c<0&&a&1024)
                            posx+=c;
                        else if(c>0&&TheGame::Instance()->getMap(int( (posx+c) /50.0) , int(posy/50.0))&1024)
                            posx+=c;
                    }
					posy-=s;
					if(int((posy+s)/50.0)!=int(posy/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posy+=s;
                        else if(s<0&&a&2048)
                            posy+=s;
                        else if(s>0&&TheGame::Instance()->getMap(int( posx /50.0) , int( (posy+s) /50.0))&2048)
                            posy+=s;
                    }
				}
            if( currentKeyStates[ SDL_SCANCODE_LEFT ] ||currentKeyStates[ SDL_SCANCODE_Q ])
				{
					angle-=3;
					if(angle<-180) angle+=360;
				}
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] || currentKeyStates[ SDL_SCANCODE_E ] )
				{
					if(angle>180) angle-=360;
					angle+=3;
				}
            if(currentKeyStates[ SDL_SCANCODE_A ]){
					posx+=s;
					if(int((posx-s)/50.0)!=int(posx/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posx-=s;
                        else if(s>0&&a&1024)
                            posx-=s;
                        else if(s<0&&TheGame::Instance()->getMap(int( (posx-s) /50.0) , int( (posy) /50.0))&1024)
                            posx-=s;
                    }
					posy-=c;
					if (int ((posy+c)/50.0)!=int(posy/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posy+=c;
                        else if(c<0&&a&2048)
                            posy+=c;
                        else if(c>0&&TheGame::Instance()->getMap(int( (posx) /50.0) , int( (posy+c) /50.0))&2048)
                            posy+=c;
                    }
            }
            else if(currentKeyStates[ SDL_SCANCODE_D ]){
					posx-=s;
					if(int((posx+s)/50.0)!=int(posx/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posx+=s;
                        else if(s<0&&a&1024)
                            posx+=s;
                        else if(s>0&&TheGame::Instance()->getMap(int( (posx+s) /50.0) , int( (posy) /50.0))&1024)
                            posx+=s;
                    }
					posy+=c;
					if (int ((posy-c)/50.0)!=int(posy/50.0)){
                        int a=TheGame::Instance()->getMap(int(posx/50.0) , int(posy/50.0));
                        if(!(a&3072)&&a)
                            posy-=c;
                        else if(c>0&&(a&2048))
                            posy-=c;
                        else if(c<0&&TheGame::Instance()->getMap(int( (posx) /50.0) , int( (posy-c)/50.0))&2048)
                            posy-=c;
                    }
            }
        time=SDL_GetTicks();
    }
    private:
    int pWidth=1,pHeight=1;
    double posx=56,posy=56,angle=std::sqrt(2),Player_speed=0.3,time=SDL_GetTicks(); // angle=srqt2 se giup tranh goc 90 do trong viec tinh tan, cot
    static Player* m_pPlayer;
    Player(){};
    ~Player(){};
};
typedef Player ThePlayer;
#endif // PLAYER_H
