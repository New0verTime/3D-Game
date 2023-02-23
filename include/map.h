#ifndef MAP_H
#define MAP_H
#include<iostream>
#include<vector>
#include<string>
class map
{
    public:
        map(){};
        ~map(){};
        void Read_map(std::string path, std::vector<std::vector<int>> &maps);
    private:
};

#endif // MAP_H
