#include "Object.h"
#include "Player.h"
#include"Ray_cast.h"
#include <string>
#include <iostream>
#include "Game.h"
#include<math.h>
Object::Object(double _x,double _y,std::vector<std::string> _id,double _obj_Width,double _obj_Height,double _lim,double _obj_angle){
    x=_x;
    y=_y;
    id=_id;
    obj_Width=_obj_Width;
    obj_Height=_obj_Height;
    lim=_lim;
    id_max=_id.size();
    obj_angle=_obj_angle;
}
void Object::getInfo(){
    double ox=ThePlayer::Instance()->getPosx()/50,oy=ThePlayer::Instance()->getPosy()/50;
    dist=std::sqrt( (ox-x)*(ox-x) + (oy-y)*(oy-y) );
    double player_angle=ThePlayer::Instance()->getAngle()-30;
    if(player_angle<-180) player_angle+=360;
    double theta=std::atan((oy-y) / (ox-x)) *57.295779 ; // -90 to 90    std::atan(obj_Width/(3*dist)) *(180/3.14159265)
    if (ox>x) {
        theta+=180;
    }
    if(theta>180) theta-=360;
    delta_angle=theta-player_angle;
    if(delta_angle<0) delta_angle+=360;
    double tmp=ThePlayer::Instance()->getAngle()+delta_angle-30-obj_angle;
    if(tmp>180) tmp-=360;
    if(tmp<-180) tmp+=360;
    double tmp2=360.0/id_max;
    tmp+=360+tmp2/2;
    if(tmp>360) tmp-=360;
    id_num=int(tmp/tmp2);
    epsilon=std::min(std::atan(obj_Width/(dist)) *57.295779,60.0);
    if(delta_angle-epsilon<60||delta_angle+epsilon>360)  inside=true;
    else inside=false;
}
void Object::RenderObject(){
    if(inside&&delta_angle-epsilon<60&&dist>lim){
        double t=720*obj_Height/(dist);
        SDL_Rect Rect,Rect2;
        Rect.w=3;
        Rect.h=t+t/obj_Height;
        Rect.y=360-t;
        Rect2.y=0;
        Rect2.w=3;
        Rect2.h=1024;
        for(double i=-epsilon;i<=0;i+=0.1){
        double s=std::sin(epsilon),c=std::cos(epsilon);
        if( (int((delta_angle+i)*10)>=0&&int((delta_angle+i)*10)<=600)&&(((x+obj_Width*s-TheRay_cast::Instance()->get_rayinfox(int((delta_angle+i)*10)) )*(x+obj_Width*s-ThePlayer::Instance()->getPosx()/50) <0 )
           || ( (y+obj_Width*c-TheRay_cast::Instance()->get_rayinfoy(int((delta_angle+i)*10)) )*(y+obj_Width*c-ThePlayer::Instance()->getPosy()/50) <0)) ){
        Rect.x=int((1280*(delta_angle+i))/60);
        Rect2.x=int((512*(i+epsilon) )/epsilon);
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture(id[id_num]),&Rect2,&Rect);

        }
        }
        for(double i=0;i<=epsilon;i+=0.1){
        if( (int((delta_angle+i)*10)>=0&&int((delta_angle+i)*10)<=600)&&(((x-TheRay_cast::Instance()->get_rayinfox(int((delta_angle+i)*10)) )*(x-ThePlayer::Instance()->getPosx()/50) <0 )
           || ( (y-TheRay_cast::Instance()->get_rayinfoy(int((delta_angle+i)*10)) )*(y-ThePlayer::Instance()->getPosy()/50) <0)) ){
        Rect.x=int((1280*(delta_angle+i))/60);
        Rect2.x=int((512*(i+epsilon) )/epsilon);
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture(id[id_num]),&Rect2,&Rect);

        }
        }
    }
    else if(inside&&delta_angle+epsilon>360&&dist>lim){
        delta_angle-=360;
        double t=720*obj_Height/(dist);
        SDL_Rect Rect,Rect2;
        Rect.w=3;
        Rect.h=t+t/obj_Height;
        Rect.y=360-t;
        Rect2.y=0;
        Rect2.w=3;
        Rect2.h=1024;
        for(double i=-epsilon;i<=0;i+=0.1){
        double s=std::sin(epsilon),c=std::cos(epsilon);
        if( (int((delta_angle+i)*10)>=0&&int((delta_angle+i)*10)<=600)&&(((x+obj_Width*s-TheRay_cast::Instance()->get_rayinfox(int((delta_angle+i)*10)) )*(x+obj_Width*s-ThePlayer::Instance()->getPosx()/50) <0 )
           || ( (y+obj_Width*c-TheRay_cast::Instance()->get_rayinfoy(int((delta_angle+i)*10)) )*(y+obj_Width*c-ThePlayer::Instance()->getPosy()/50) <0)) ){
        Rect.x=int((1280*(delta_angle+i))/60);
        Rect2.x=int((512*(i+epsilon) )/epsilon);
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture(id[id_num]),&Rect2,&Rect);

        }
        }
        for(double i=0;i<=epsilon;i+=0.1){
        if( (int((delta_angle+i)*10)>=0&&int((delta_angle+i)*10)<=600)&&(((x-TheRay_cast::Instance()->get_rayinfox(int((delta_angle+i)*10)) )*(x-ThePlayer::Instance()->getPosx()/50) <0 )
           || ( (y-TheRay_cast::Instance()->get_rayinfoy(int((delta_angle+i)*10)) )*(y-ThePlayer::Instance()->getPosy()/50) <0)) ){
        Rect.x=int((1280*(delta_angle+i))/60);
        Rect2.x=int((512*(i+epsilon) )/epsilon);
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture(id[id_num]),&Rect2,&Rect);

        }
        }
    }
}
