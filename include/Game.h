#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_ttf.h"
#include"Object.h"
#include <string>
#include <vector>
class Game
{
public:
    static Game* Instance()
    {
    if(m_pGame == 0)
    {
    m_pGame = new Game();
    }
    return m_pGame;
    }
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void update();
    void handleEvents();
    SDL_Texture* str_to_texture(std::string str);
    void Load_map(std::string map_name,double px,double py,double angle);
    void clean();
    void HandleConversation();
    bool running() { return m_bRunning; }
    int getMap(int x,int y) {if(y>=0&&y<maps.size()&&x>=0&&x<maps[0].size()) return maps[y][x]; else return 0;}
    void setMap(int x,int y) { maps[x][y]=0; }
    void setcollect() { ++collected; }
    SDL_Renderer* getRenderer() { return m_pRenderer; }
private:
    static Game* m_pGame;
    Game(){};
    ~Game(){};
    SDL_Rect R1,R2,R3,R4,R5,Rect,Rect1,Rect2;
    TTF_Font *gFont;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* bg;
    std::vector<std::vector<int>> maps;
    std::vector<Object*> obj_map;
    std::string name,log;
    int collected,menu_list=0;
    char k;
    bool menu=true,talking=false,m_bRunning;
};
typedef Game TheGame;
#endif // GAME_H
