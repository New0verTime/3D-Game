#ifndef STATICOBJECT_H
#define STATICOBJECT_H
#include <string>
#include<iostream>
class StaticObject
{
    std::string id;
    double x,y,dist,delta_angle;
    bool inside;
    double obj_Width,obj_Height;
    public:
        StaticObject(double _x,double _y,std::string _id,double _obj_Width,double _obj_Height){
            x=_x;
            y=_y;
            id=_id;
            obj_Width=_obj_Width;
            obj_Height=_obj_Height;
        }
        ~StaticObject(){}
        void getInfo();
        void RenderObject();
};
#endif // STATICOBJECT_H
