#ifndef GAMESTATE
#define GAMESTATE

#include <SFML/Graphics.hpp>


class BoardInstance{
    private:
        
        

    public:
        
};

class CameraInstance{
    public:
        CameraInstance(){}; 
    private:
        sf::Vertex position{{5,5}};
};

class EntitiesInstance{
    
};


class DisplayInstance{
    public:
        sf::RenderTexture surface;
        DisplayInstance();
        
        // Sets the render surface to the background texture
        void refresh();
        void generate_background(BoardInstance board);
        void render_entities(EntitiesInstance entities);
        
        sf::Sprite get_drawable();

    private:
        sf::RenderTexture background;
};



class GameInstance{
    public:
        
    private:
        BoardInstance board;
        CameraInstance camera;
        EntitiesInstance entities;
        DisplayInstance display;
        
};



#endif
