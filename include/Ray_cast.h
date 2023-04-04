#ifndef RAY_CAST_H
#define RAY_CAST_H
#include<SDL.h>
#include"Player.h"
#include"Game.h"
#include<iostream>
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
        double get_rayinfoy(int k) {return ray_infoy[k];}
        void set_rayinfoy(int k,double u) {ray_infoy[k]=u;}
    private:
        static Ray_cast* m_pRay_cast;
        Ray_cast(){};
        ~Ray_cast(){};
        const double view_angle=60;
        double ox,oy,angle=0,View_Limitation=40;
        double h=3;//chieu cao camera
        double ray_infox[601];
        double ray_infoy[601];
};
typedef Ray_cast TheRay_cast;
#endif // RAY_CAST_H
