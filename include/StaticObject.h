#ifndef STATICOBJECT_H
#define STATICOBJECT_H
#include "Object.h"
#include <string>
#include<iostream>
#include<SDL.h>
class StaticObject: public Object
{
    public:
        StaticObject(double _x,double _y,std::vector<std::string> k,double _obj_Width,double _obj_Height,double _lim=1,double _obj_angle=0);
        virtual ~StaticObject(){}
};
#endif // STATICOBJECT_H
