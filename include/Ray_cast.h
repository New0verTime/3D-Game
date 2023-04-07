#ifndef RAY_CAST_H
#define RAY_CAST_H
#include<SDL.h>
#include"Player.h"
#include"Game.h"
#include<iostream>
class info{
public:
    info(double _x1, double _y1, int _type, bool _b){x1=_x1; y1=_y1; type=_type; b=_b;}
    double getx(){return x1;}
    double gety(){return y1;}
    int gettype(){return type;}
    bool getb(){return b;}
    ~info(){}
private:
    double x1,y1;
    int type;
    bool b;
};
class Ray_cast
{
    public:
        static Ray_cast* Instance()
        {
        if(m_pRay_cast==0)
        {
        m_pRay_cast=new Ray_cast();
        }
        return m_pRay_cast;
        }
        void update();
        double get_rayinfox(int k) {return ray_infox[k];}
        void set_rayinfox(int k,double u) {ray_infox[k]=u;}
        void casting(double x0,double y0, double x1, double y1,double a,bool b,int type);
        double get_rayinfoy(int k) {return ray_infoy[k];}
        void set_rayinfoy(int k,double u) {ray_infoy[k]=u;}
    private:
        static Ray_cast* m_pRay_cast;
        Ray_cast(){};
        ~Ray_cast(){};
        const double view_angle=30;
        SDL_Rect Rect{0,0,3,0},Rect2{0,0,3,1024};
        double ox,oy,angle=0,View_Limitation=30;
        double ray_infox[601];
        double ray_infoy[601];
};
typedef Ray_cast TheRay_cast;
#endif // RAY_CAST_H
