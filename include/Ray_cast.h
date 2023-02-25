#ifndef RAY_CAST_H
#define RAY_CAST_H
#include<SDL.h>
#include"Player.h"
#include"Game.h"
#include<iostream>
const double View_Limitation=50,ray_diff=0.1,view_angle=60;
const int ray_width=std::ceil(1280/(view_angle/ray_diff));
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
        void render();
        double get_h(){ return h;}
        double get_rayinfo(int k) {return ray_info[k];}
    private:
        static Ray_cast* m_pRay_cast;
        Ray_cast(){};
        ~Ray_cast(){};
        double ox,oy,angle;
        double h=3;//chieu cao camera
        double ray_info[601]; // luu thong tin cua 600 ray tu angle-30 den angle+30+
};
typedef Ray_cast TheRay_cast;
#endif // RAY_CAST_H
