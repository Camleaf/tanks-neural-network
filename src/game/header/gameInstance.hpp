#ifndef GAMESTATE
#define GAMESTATE

#include <SFML/Graphics.hpp>


class ArenaInstance{
    private:
        void bisect_walls(sf::IntRect container, int detail);

    public:
        void generate_walls();
        
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
        void generate_background(ArenaInstance arena);
        void render_entities(EntitiesInstance entities);
        
        sf::Sprite get_drawable();

    private:
        sf::RenderTexture background;
};



class GameInstance{
    public:
        
    private:
        ArenaInstance arena;
        CameraInstance camera;
        EntitiesInstance entities;
        DisplayInstance display;
        
};



#endif
