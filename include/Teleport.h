#ifndef TELEPORT_H
#define TELEPORT_H
#include "Object.h"
#include <string>
#include<iostream>
#include"Game.h"
#include<SDL.h>
#include<vector>
class Teleport: public Object
{   private:
    std::string mapid;
    double d_x,d_y;
    public:
        Teleport(double _x,double _y,std::vector<std::string> _id,double _obj_Width,double _obj_Height,double _lim,double _obj_object,std::string map_id,double des_x,double des_y);
        virtual ~Teleport(){}
        void getInfo();
};
#endif // MOVINGOBJECT_H
