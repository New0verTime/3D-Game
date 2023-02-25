#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_ttf.h"
#include "map.h"
#include"StaticObject.h"
#include"movingObject.h"
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
    void clean();
    bool running() { return m_bRunning; }
    int getMap(int x,int y) {if(y>=0&&y<maps.size()&&x>=0&&x<maps[0].size()) return maps[y][x]; else return 1;}
    SDL_Renderer* getRenderer() {return m_pRenderer;}
private:
    static Game* m_pGame;
    Game(){};
    ~Game(){};
    std::vector<std::vector<int>> maps; //30*20 map
    std::vector<StaticObject*> m_pObj;
    std::vector<movingObject*> m_pObj2;
    int score=0;
    TTF_Font *gFont;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;
};
typedef Game TheGame;
#endif // GAME_H
