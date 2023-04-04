#include "Collectable.h"
#include "Ray_cast.h"
Collectable::Collectable(double _x,double _y,std::vector<std::string> _id,double _obj_Width,double _obj_Height,double _lim,double _obj_angle):Object(_x,_y,_id,_obj_Width,_obj_Height,_lim,_obj_angle){}
void Collectable::getInfo(){
    if(!collected){
    double ox=ThePlayer::Instance()->getPosx()/50,oy=ThePlayer::Instance()->getPosy()/50;
    dist=std::sqrt( (ox-x)*(ox-x) + (oy-y)*(oy-y) );
    if(dist<1) {collected=true; TheGame::Instance()->setcollect();}
    double player_angle=ThePlayer::Instance()->getAngle()-30;
    if(player_angle<-180) player_angle+=360;
    double theta=std::atan((oy-y) / (ox-x)) *(180/3.14159265) ; // -90 to 90    std::atan(obj_Width/(3*dist)) *(180/3.14159265)
    if (ox>x) {
        theta+=180;
    }
    if(theta>180) theta-=360;
    delta_angle=theta-player_angle;
    if(delta_angle<0) delta_angle+=360;
    double tmp=ThePlayer::Instance()->getAngle()+delta_angle-30-obj_angle;
    if(tmp>180) tmp-=360;
    if(tmp<-180) tmp+=360;
    double tmp2=360.0/id_max;
    tmp+=360+tmp2/2;
    if(tmp>360) tmp-=360;
    id_num=int(tmp/tmp2);
    epsilon=std::min(std::atan(obj_Width/(dist)) *(180/3.14159265),60.0);
    if(delta_angle-epsilon<60||delta_angle+epsilon>360)  inside=true;
    else inside=false;
    }
}
