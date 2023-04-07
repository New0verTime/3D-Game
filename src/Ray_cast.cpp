#include "Ray_cast.h"
#include "TextureManager.h"
#include "SDL.h"
#include<iostream>
#include<algorithm>
#include<math.h>
Ray_cast* Ray_cast::m_pRay_cast = 0;
bool sortt(info lhs, info rhs) {
    return fabs(lhs.getx())>fabs(rhs.getx());
}
void Ray_cast::casting(double x0,double y0, double x1, double y1,double a,bool b,int type){
    int length=(type&896)>>7;
    type=type%128;
    double x=720*(length+1)/(std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0))*std::cos((30-a)/57.295779));
    Rect.x=int((1280*a)/60);
    Rect.y=int(360-x);
    Rect.h=int(x)+int(x/(length+1));
    if(b==0)
    Rect2.x=int((y1-int(y1))*341)*3;
    else Rect2.x=int((x1-int(x1))*341)*3;
    SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture(std::to_string(type)),&Rect2,&Rect);
}

void drawFloor(double x0,double y0, double x1, double y1,double a){
    double l=std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    double x=360*(l+std::sqrt(3))/(l);
    SDL_RenderDrawPoint(TheGame::Instance()->getRenderer(),int(22*a),int(x));
}
void Ray_cast::update(){

        int type,type2;
        ox=Player::Instance()->getPosx()/50;
        oy=Player::Instance()->getPosy()/50;
        angle=Player::Instance()->getAngle();
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),255,255,255,255);
        for(double i=angle-view_angle;i<=angle+view_angle;i+=0.1){
            std::vector <info> tmp;
            double t=std::tan(i/57.295779);
            double lx=std::cos(i/57.295779)*View_Limitation+ox,ly=std::sin(i/57.295779)*View_Limitation+oy,x1=lx,y1=ly,x2=lx,y2=ly;
            if(lx>ox){
            for(double j=int(lx);j>=std::ceil(ox);--j){
                //drawFloor(ox,oy,j,oy+(j-ox)*std::tan(i/57.295779),i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap((int)j,int(oy+(j-ox)*t));
                if( k && !(k&3072) ){
                    type=k;
                    x1=j;
                    y1=(j-ox)*t;
                    //casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                    info noww(x1-ox,y1,type,0);
                    tmp.push_back(noww);
                }
                else if(k&&(k&1024)){
                    type=k;
                    x1=j;
                    y1=(j-ox)*t;
                    //casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                    info noww(x1-ox,y1,type,0);
                    tmp.push_back(noww);
                }
            }
            }
            else if(lx<ox){
            for(double j=std::ceil(lx);j<=int(ox);++j){
                //drawFloor(ox,oy,j,oy+(j-ox)*std::tan(i/57.295779),i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap((int)(j-1),int(oy+(j-ox)*t));
                if( k &&!(k&3072)){
                    type=k;
                    x1=j;
                    y1=(j-ox)*t;
                    //casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                    info noww(x1-ox,y1,type,0);
                    tmp.push_back(noww);
                }
                int k2=TheGame::Instance()->getMap((int)(j),int(oy+(j-ox)*t));
                if(k2&&(k2&1024)){
                    type=k2;
                    x1=j;
                    y1=(j-ox)*t;
                    //casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                    info noww(x1-ox,y1,type,0);
                    tmp.push_back(noww);
                }
            }
            }
            if(ly>oy){
            for(double j=int(ly);j>=std::ceil(oy);--j){
                //drawFloor(ox,oy,ox+(j-oy)/std::tan(i/57.295779),j,i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap(int(ox+(j-oy)/t),(int)j);
                if( k &&!(k&3072) ){
                    type2=k;
                    x2=(j-oy)/t;
                    y2=j;
                    //casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                    info noww(x2,y2-oy,type2,1);
                    tmp.push_back(noww);
                }
                else if(k&& (k&2048)){
                    type2=k;
                    x2=(j-oy)/t;
                    y2=j;
                    //casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                    info noww(x2,y2-oy,type2,1);
                    tmp.push_back(noww);
                }
            }
            }
            else if(ly<oy){
            for(double j=std::ceil(ly);j<=int(oy);++j){
                //drawFloor(ox,oy,ox+(j-oy)/std::tan(i/57.295779),j,i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap(int(ox+(j-oy)/t),(int)(j-1));
                if( k&&!(k&3072) ){
                    type2=k;
                    x2=(j-oy)/t;
                    y2=j;
                    //casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                    info noww(x2,y2-oy,type2,1);
                    tmp.push_back(noww);
                }
                int k2=TheGame::Instance()->getMap(int(ox+(j-oy)/t),(int)(j));
                if(k2&&(k2&2048)){
                    type2=k2;
                    x2=(j-oy)/t;
                    y2=j;
                    //casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                    info noww(x2,y2-oy,type2,1);
                    tmp.push_back(noww);
                }
            }
            }
            std::sort(tmp.begin(),tmp.end(),&sortt);
            for(int j=0;j<tmp.size();++j){
                casting(ox,oy,tmp[j].getx()+ox,tmp[j].gety()+oy,i-(angle-view_angle),tmp[j].getb(),tmp[j].gettype());
            }
            if(x1==lx&&x2+ox==lx){
                    ray_infox[int(10*(i-angle+view_angle))]=lx;
                    ray_infoy[int(10*(i-angle+view_angle))]=ly;
                    continue;
            }
            else if((x1-x2-ox)*(x1-ox)<0){
                    //casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                    ray_infox[int(10*(i-angle+view_angle))]=x1;
                    ray_infoy[int(10*(i-angle+view_angle))]=y1+oy;
            }
            else {//casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                    ray_infox[int(10*(i-angle+view_angle))]=x2+ox;
                    ray_infoy[int(10*(i-angle+view_angle))]=y2;
            }
        }
}
