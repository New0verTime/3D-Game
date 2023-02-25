#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include<SDL.h>
#include <string>
#include<iostream>
#include<math.h>
class movingObject
{
    std::string id;
    double x,y,dist,delta_angle,time=SDL_GetTicks(),damage_cooldown=SDL_GetTicks(),atk_range;
    bool inside;
    double obj_Width,obj_Height,velocity,angle=45,lx=1,ly=1,cd;
    int damage;
    public:
        movingObject(double _x,double _y,std::string _id,double _obj_Width,double _obj_Height,double _velocity,int _damage,double _cd,double _atk_range){
            x=_x;
            y=_y;
            id=_id;
            obj_Width=_obj_Width;
            obj_Height=_obj_Height;
            velocity=_velocity;
            damage=_damage;
            cd=_cd;
            atk_range=_atk_range;
        }
        ~movingObject(){}
        double get_angle(){return delta_angle;}
        void go();
        void getInfo();
        void RenderObject();
        void handleCollide();
};
#endif // MOVINGOBJECT_H
