#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include<string>
#include<SDL.h>
#include<map>
class TextureManager
{
    public:
    static TextureManager* Instance()
    {
    if(s_pInstance == 0)
    {
    s_pInstance = new TextureManager();
    }
    return s_pInstance;
    }

    bool load(std::string fileName,std::string id, SDL_Renderer* pRenderer);
    void draw(std::string id,int x,int y,int width,int height,SDL_Renderer* pRenderer,SDL_RendererFlip flip = SDL_FLIP_NONE,double angle=0);
    void drawFrame(std::string id,int x,int y,int width,int height,int currentRow,int currentFrame,SDL_Renderer* pRenderer,SDL_RendererFlip flip=SDL_FLIP_NONE,double angle=0);
    SDL_Texture* getTexture(std::string id){return m_textureMap[id];}
    private:
    static TextureManager* s_pInstance;
    TextureManager(){};
    ~TextureManager(){};
    std::map<std::string, SDL_Texture*> m_textureMap;
};
typedef TextureManager TheTextureManager;
#endif // TEXTUREMANAGER_H
