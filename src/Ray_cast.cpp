#include "Ray_cast.h"
#include "TextureManager.h"
#include<iostream>
Ray_cast* Ray_cast::m_pRay_cast = 0;

void casting(double x0,double y0, double x1, double y1,double a,bool b,int type){
    SDL_Rect Rect,Rect2;
    int length=(type&896)>>7;
    type=type%128;
    double l=std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    double x=720*(length+1)/(l*std::cos((30-a)/57.295779));
    Rect.x=int((1280*a)/60);
    Rect.y=int(360-x);
    Rect.w=3;
    Rect.h=int(x)+int(x/(length+1));
    if(b==0)
    Rect2.x=int((y1-int(y1))*341)*3;
    else Rect2.x=int((x1-int(x1))*341)*3;
    Rect2.y=0;
    Rect2.w=3;
    Rect2.h=1024;
    SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture(std::to_string(type)),&Rect2,&Rect);
}

void drawFloor(double x0,double y0, double x1, double y1,double a){
    double l=std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    double x=720*(l+std::sqrt(3))/(2*l);
    SDL_RenderDrawPoint(TheGame::Instance()->getRenderer(),int(22*a),int(x));
}
void Ray_cast::update(){
        int type,type2;
        ox=Player::Instance()->getPosx()/50;
        oy=Player::Instance()->getPosy()/50;
        angle=Player::Instance()->getAngle();
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),255,255,255,255);
        for(double i=angle-view_angle/2;i<=angle+view_angle/2;i+=0.1){
            double lx=std::cos(i/57.295779)*View_Limitation+ox,ly=std::sin(i/57.295779)*View_Limitation+oy,x1=lx,y1=ly,x2=lx,y2=ly;
            if(lx>ox){
            for(double j=int(lx);j>=std::ceil(ox);--j){
                //drawFloor(ox,oy,j,oy+(j-ox)*std::tan(i/57.295779),i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap((int)j,int(oy+(j-ox)*std::tan(i/57.295779)));
                if( k && !(k&3072) ){
                    type=k;
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                }
                else if(k&&(k&1024)){
                    type=k;
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                }
            }
            }
            else if(lx<ox){
            for(double j=std::ceil(lx);j<=int(ox);++j){
                //drawFloor(ox,oy,j,oy+(j-ox)*std::tan(i/57.295779),i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap((int)(j-1),int(oy+(j-ox)*std::tan(i/57.295779)));
                if( k &&!(k&3072)){
                    type=k;
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                }
                int k2=TheGame::Instance()->getMap((int)(j),int(oy+(j-ox)*std::tan(i/57.295779)));
                if(k2&&(k2&1024)){
                    type=k2;
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                }
            }
            }
            if(ly>oy){
            for(double j=int(ly);j>=std::ceil(oy);--j){
                //drawFloor(ox,oy,ox+(j-oy)/std::tan(i/57.295779),j,i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap(int(ox+(j-oy)/std::tan(i/57.295779)),(int)j);
                if( k &&!(k&3072) ){
                    type2=k;
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                }
                else if(k&& (k&2048)){
                    type2=k;
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                }
            }
            }
            else if(ly<oy){
            for(double j=std::ceil(ly);j<=int(oy);++j){
                //drawFloor(ox,oy,ox+(j-oy)/std::tan(i/57.295779),j,i-(angle-view_angle/2));
                int k=TheGame::Instance()->getMap(int(ox+(j-oy)/std::tan(i/57.295779)),(int)(j-1));
                if( k&&!(k&3072) ){
                    type2=k;
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                }
                int k2=TheGame::Instance()->getMap(int(ox+(j-oy)/std::tan(i/57.295779)),(int)(j));
                if(k2&&(k2&2048)){
                    type2=k2;
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                }
            }
            }
            if(x1==lx&&x2==lx){
                    ray_infox[int(10*(i-angle+view_angle/2))]=lx;
                    ray_infoy[int(10*(i-angle+view_angle/2))]=ly;
                    continue;
            }
            else if((x1-x2)*(x1-ox)<0){
                    casting(ox,oy,x1,y1,i-(angle-view_angle/2),0,type);
                    ray_infox[int(10*(i-angle+view_angle/2))]=x1;
                    ray_infoy[int(10*(i-angle+view_angle/2))]=y1;
            }
            else {casting(ox,oy,x2,y2,i-(angle-view_angle/2),1,type2);
                    ray_infox[int(10*(i-angle+view_angle/2))]=x2;
                    ray_infoy[int(10*(i-angle+view_angle/2))]=y2;
            }
        }
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),0,0,0,255);
}
