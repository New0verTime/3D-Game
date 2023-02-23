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
        if(line[i]=='1') tmp.push_back(1);
        else if(line[i]=='0') tmp.push_back(0);
      }
      maps.push_back(tmp);
    }
    myfile.close();
}
