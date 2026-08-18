#ifndef GAMEINSTANCE
#define GAMEINSTANCE

#include <SFML/Graphics.hpp>
#include <array>
#include <constants.hpp>
#include <types.hpp>

class ArenaInstance{
    private: 
        std::array<std::array<bool,ARENA_TILES_HORIZONTAL>,ARENA_TILES_VERTICAL> walls;      
        void bisect_walls(sf::IntRect container, int detail);
    public:
        ArenaInstance();
        void generate_walls();
        
};

class CameraInstance{
    public:
        CameraInstance(){}; 
    private:
};

class EntitiesInstance{
    
};


class DisplayInstance{
    public:
        sf::RenderTexture surface;
        DisplayInstance();
        
        // Sets the render surface to the background texture
        void refresh(sf::Vector2f camera_position);
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
