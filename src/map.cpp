#include "map.h"
#include<iostream>
#include<fstream>
#include<string>
void map::Read_map(std::string path, std::vector<std::vector<int>> &maps){
    std::ifstream myfile;
    std::string line;
    myfile.open(path,std::ios::in);
    while (getline(myfile,line))
    {
      std::vector<int> tmp;
      int l=line.size();
      for(int i=0;i<l;++i){
        if(line[i]=='0') {tmp.push_back(0); std::cout<<line[i];}
        if(line[i]=='1') {tmp.push_back(1); std::cout<<line[i];}
        if(line[i]=='2') {tmp.push_back(2); std::cout<<line[i];}
        if(line[i]=='3') {tmp.push_back(3); std::cout<<line[i];}
        if(line[i]=='4') {tmp.push_back(4); std::cout<<line[i];}
        if(line[i]=='5') {tmp.push_back(5); std::cout<<line[i];}
      }
      maps.push_back(tmp);
    }
    myfile.close();
}
