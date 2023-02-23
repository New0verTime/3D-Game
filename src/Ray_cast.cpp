#include "Ray_cast.h"
#include<iostream>
Ray_cast* Ray_cast::m_pRay_cast = 0;

void Ray_cast::update(){

        ox=Player::Instance()->getPosx()/50;
        oy=Player::Instance()->getPosy()/50;
        angle=Player::Instance()->getAngle();
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),255,255,255,255);
        for(double i=angle-view_angle/2;i<=angle+view_angle/2;i+=1){
            double lx=std::cos(i/57.295779)*View_Limitation+ox,ly=std::sin(i/57.295779)*View_Limitation+oy,x1=lx,y1=ly,x2=lx,y2=ly;
            if(lx>ox){
            for(double j=std::ceil(ox);j<=int(lx);++j){
                if(TheGame::Instance()->getMap((int)j,int(oy+(j-ox)*std::tan(i/57.295779)))==1){
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    break;
                }
            }
            }
            else if(lx<ox){
            for(double j=int(ox);j>=std::ceil(lx);--j){
                if(TheGame::Instance()->getMap((int)(j-1),int(oy+(j-ox)*std::tan(i/57.295779)))==1){
                    x1=j;
                    y1=oy+(j-ox)*std::tan(i/57.295779);
                    break;
                }
            }
            }
            if(ly>oy){
            for(double j=std::ceil(oy);j<=int(ly);++j){
                if(TheGame::Instance()->getMap(int(ox+(j-oy)/std::tan(i/57.295779)),(int)j)==1){
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    break;
                }
            }
            }
            else if(ly<oy){
            for(double j=int(oy);j>=std::ceil(ly);--j){
                if(TheGame::Instance()->getMap(int(ox+(j-oy)/std::tan(i/57.295779)),(int)(j-1))==1){
                    x2=ox+(j-oy)/std::tan(i/57.295779);
                    y2=j;
                    break;
                }
            }
            }
            if((x1-x2)*(x1-ox)<0){
                SDL_RenderDrawLine(TheGame::Instance()->getRenderer(),int(Player::Instance()->getPosx()),int(Player::Instance()->getPosy()),x1*50,y1*50);
            }
            else {SDL_RenderDrawLine(TheGame::Instance()->getRenderer(),int(Player::Instance()->getPosx()),int(Player::Instance()->getPosy()),x2*50,y2*50);

            }
        }
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),0,0,0,255);

}
