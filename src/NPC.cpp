#include "NPC.h"
#include "Ray_cast.h"
NPC::NPC(double _x,double _y,std::vector<std::string> _id,double _obj_Width,double _obj_Height,std::string _name,std::vector<Status*> _status,double _lim,double _obj_angle):
    Object(_x,_y,_id,_obj_Width,_obj_Height,_lim,_obj_angle)
    {
    name=_name;
    status=_status;
}
std::string NPC::getlog(char k){
            if(!talking) return "";
            if(sentence_now<status[status_now]->s.size()){
                log=status[status_now]->s[sentence_now];
                if(k=='j') ++sentence_now;
            }
            else if(sentence_now==status[status_now]->s.size()){
                log="";
                for(int i=0;i<status[status_now]->a.size();++i) {
                    log=log+std::to_string(i+1)+" "+status[status_now]->a[i]+"    ";
                    if(k==i+1+'0'){
                        sentence_now=0;
                        for(int j=0;j<status[status_now]->impact[i].size();++j){
                            if(status[status_now]->impact[i][j]&1){
                            int x1,y1;
                            x1=(status[status_now]->impact[i][j]>>11)%1024;
                            y1=(status[status_now]->impact[i][j]>>1)%1024;
                            status_now=status[status_now]->impact[i][j]>>21;
                            TheGame::Instance()->setMap(x1,y1);
                            }
                            else{
                                status_now=status[status_now]->impact[i][j]>>1;
                                break;
                            }
                        }
                        talking=false;
                    }
                }
            }
            return log;
        }
