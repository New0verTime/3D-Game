#include "Ray_cast.h"
#include "TextureManager.h"
#include<iostream>
Ray_cast* Ray_cast::m_pRay_cast = 0;

void drawRect(double x0,double y0, double x1, double y1,double a){
    SDL_Rect Rect,Rect2;
    double l=std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    double x=std::min(720/(std::sqrt(3)*l*std::cos( (30-a)/57.295779 )),360.0);
    Rect.x=int(22*a);
    Rect.y=int(360-x);
    Rect.w=3;
    Rect.h=2*int(x);
    Rect2.x=(int(10*a)%341)*3;
    Rect2.y=0;
    Rect2.w=3;
    Rect2.h=1024;
    SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTextureManager::Instance()->getTexture("wall"),&Rect2,&Rect);
}
void drawFloor(double x0,double y0, double x1, double y1,double a){
    SDL_Rect Rect;
    double l=std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    double x=720*(l+std::sqrt(3))/(2*l);
    Rect.x=int(22*a);
    Rect.y=int(x);
    Rect.w=1;
    Rect.h=1;
    SDL_RenderFillRect(TheGame::Instance()->getRenderer(),&Rect);
}
void Ray_cast::update(){

        ox=Player::Instance()->getPosx()/50;
        oy=Player::Instance()->getPosy()/50;
        angle=Player::Instance()->getAngle();
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),255,255,255,255);
        for(double i=angle-view_angle/2;i<=angle+view_angle/2;i+=0.1){
            double lx=std::cos(i/57.295779)*View_Limitation+ox,ly=std::sin(i/57.295779)*View_Limitation+oy,x1=lx,y1=ly,x2=lx,y2=ly;
            if(lx>ox){
            for(double j=std::ceil(ox);j<=int(lx);++j){
                drawFloor(ox,oy,j,oy+(j-ox)*std::tan(i/57.295779),i-(angle-view_angle/2));
                if(TheGame::Instance()->getMap((int)j,int(oy+(j-ox)*std::tan(i/57.295779)))==1){
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    break;
                }
            }
            }
            else if(lx<ox){
            for(double j=int(ox);j>=std::ceil(lx);--j){
                drawFloor(ox,oy,j,oy+(j-ox)*std::tan(i/57.295779),i-(angle-view_angle/2));
                if(TheGame::Instance()->getMap((int)(j-1),int(oy+(j-ox)*std::tan(i/57.295779)))==1){
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    break;
                }
            }
            }
            if(ly>oy){
            for(double j=std::ceil(oy);j<=int(ly);++j){
                drawFloor(ox,oy,ox+(j-oy)/std::tan(i/57.295779),j,i-(angle-view_angle/2));
                if(TheGame::Instance()->getMap(int(ox+(j-oy)/std::tan(i/57.295779)),(int)j)==1){
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    break;
                }
            }
            }
            else if(ly<oy){
            for(double j=int(oy);j>=std::ceil(ly);--j){
                drawFloor(ox,oy,ox+(j-oy)/std::tan(i/57.295779),j,i-(angle-view_angle/2));
                if(TheGame::Instance()->getMap(int(ox+(j-oy)/std::tan(i/57.295779)),(int)(j-1))==1){
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    break;
                }
            }
            }
            if((x1-x2)*(x1-ox)<0){
                //SDL_RenderDrawLine(TheGame::Instance()->getRenderer(),int(Player::Instance()->getPosx()),int(Player::Instance()->getPosy()),x1*50,y1*50);
                drawRect(ox,oy,x1,y1,i-(angle-view_angle/2));
            }
            else {//SDL_RenderDrawLine(TheGame::Instance()->getRenderer(),int(Player::Instance()->getPosx()),int(Player::Instance()->getPosy()),x2*50,y2*50);
                drawRect(ox,oy,x2,y2,i-(angle-view_angle/2));
            }
        }
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),0,0,0,255);

}
