#ifndef NPC_H
#define NPC_H
#include "Object.h"
#include <string>
#include<iostream>
#include<SDL.h>
class Status
{   public:
    std::vector<std::string> s;
    std::vector<std::string> a;
    std::vector<std::vector<int>> impact;
    Status(std::vector<std::string> _s,std::vector<std::string> _a,std::vector<std::vector<int>> _impact)
    {
        s=_s;
        a=_a;
        impact=_impact;
    }
    virtual ~Status(){}
};
class NPC: public Object
{   private:
    std::string name,log;
    short status_now=0,sentence_now=0;
    std::vector<Status*> status;
    bool talking=false;
    public:
        NPC(double _x,double _y,std::vector<std::string>_id,double _obj_Width,double _obj_Height,std::string _name,std::vector<Status*> _status,double _lim=1,double _obj_object=0);
        virtual ~NPC(){}
        bool istalk(){return talking;}
        void set_talk(){
            if(talking==false) talking=true;
        }
        void out_talk(){
            talking=false;
            sentence_now=0;
        }
        std::string getlog(char k);
        std::string getname(char k){
            if(!talking) return "";
            if(sentence_now<status[status_now]->s.size())
            return name;
            else return "Player";
        }
};
#endif // STATICOBJECT_H
