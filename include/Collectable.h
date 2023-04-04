#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "Object.h"
#include <string>
#include<iostream>
#include<SDL.h>
class Collectable: public Object
{   private:
        bool collected=false;
    public:
        Collectable(double _x,double _y,std::vector<std::string>,double _obj_Width,double _obj_Height,double _lim=1,double _obj_angle=0);
        virtual ~Collectable(){}
        void getInfo();
        bool is_collected(){return collected;}
};
#endif
