#include "movingObject.h"
#include "Player.h"
#include"Ray_cast.h"
#include <string>
#include <iostream>
#include "Game.h"
#include<math.h>
void movingObject::getInfo(){
    double ox=ThePlayer::Instance()->getPosx()/50,oy=ThePlayer::Instance()->getPosy()/50;
    dist=std::sqrt( (ox-x)*(ox-x) + (oy-y)*(oy-y) );
    double player_angle=ThePlayer::Instance()->getAngle()-30;
    if(player_angle<-180) player_angle+=360;
    double theta=std::atan((oy-y) / (ox-x)) *(180/3.14159265) ; // -90 to 90
    if (ox>x) {
        theta+=180;
    }
    if(theta>180) theta-=360;
    delta_angle=theta-player_angle;
    if(delta_angle<0) delta_angle+=360;
    if(delta_angle<60) inside=true;
    else inside=false;
}
void movingObject::RenderObject(){
    if(inside&&dist>0.25){
        if( (x-TheRay_cast::Instance()->get_rayinfo(int(delta_angle*10)))*(x-ThePlayer::Instance()->getPosx()/50) <0  ){
        SDL_Rect Rect;
        double x=720*obj_Height/(dist*std::sqrt(3)); //*std::cos(delta_angle-30)
        Rect.x=int((1280*delta_angle)/60);
        Rect.w=obj_Width/dist;
        Rect.h=1440*obj_Height/(dist*std::sqrt(3));
        Rect.y=360+400/dist-Rect.h;
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture(id),NULL,&Rect);
        }
    }
}
void movingObject::go(){
    if(TheGame::Instance()->stop()) time=SDL_GetTicks();
    else{
    double speed=velocity*(SDL_GetTicks()-time);
    if(Game::Instance()->getMap( int((x+lx*speed*std::cos(angle/57.2958)/4)) , int(y) )==0)
    x+=lx*speed*std::cos(angle/57.2958)/4;
    else lx=-lx;
    if(Game::Instance()->getMap( int(x) , int((y+ly*speed*std::sin(angle/57.2958)/4)) )==0)
    y+=ly*speed*std::sin(angle/57.2958)/4;
    else ly=-ly;
    time=SDL_GetTicks();
    }
}
void movingObject::handleCollide(){
    if(dist<atk_range&&SDL_GetTicks()>damage_cooldown+cd) {ThePlayer::Instance()->setHealth(damage); damage_cooldown=SDL_GetTicks(); }
}
