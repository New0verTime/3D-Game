#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include<iostream>
#include<vector>
class Object
{   protected:
        std::vector<std::string> id;
        int id_num,id_max;
        double x,y,x1,y1,dist,delta_angle,epsilon,lim,obj_angle;
        bool inside;
        double obj_Width,obj_Height;
    public:
        Object(double _x,double _y,std::vector<std::string> _id,double _obj_Width,double _obj_Height,double _lim=1,double _obj_angle=0);
        virtual ~Object(){}
        virtual void getInfo();
        void RenderObject();
        virtual bool istalk(){return false;}
        virtual void set_talk(){}
        virtual void out_talk(){}
        virtual std::string getlog(char k){return "";}
        virtual std::string getname(char k){return "";}
        double get_dist(){return dist;}
};
#endif // OBJECT_H
