#ifndef GAMEINSTANCE
#define GAMEINSTANCE

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <constants.hpp>
#include <entities.hpp>
#include <vector>

struct StateInstance;

class ArenaInstance{
    public:
        ArenaInstance(StateInstance& state);
        typedef std::array<std::array<bool,ARENA_TILES_HORIZONTAL>,ARENA_TILES_VERTICAL> arenaGrid; 
        arenaGrid& get_arena();
        void generate_walls();
    private: 
        StateInstance& state; 
        arenaGrid arena;      
        void bisect_walls(sf::IntRect container, int detail);
        
};


class EntitiesInstance{
    public:
        EntitiesInstance(StateInstance& state);
        Player& get_player_object_reference();
        std::vector<Enemy>& get_enemy_objects_reference();
        std::vector<Bullet>& get_bullet_objects_reference();
    private:
        StateInstance& state; 
        Player player;
        std::vector<Enemy> enemies;
        std::vector<Bullet> bullets;
};


class DisplayInstance{
    public:
        sf::RenderTexture surface;
        DisplayInstance(StateInstance& state);
        
        // Sets the render surface to the background texture
        void refresh();
        void generate_background(ArenaInstance &arena);
        void render_entities(EntitiesInstance &entities);
        
        sf::Sprite get_drawable();

    private:
        StateInstance& state; 
        sf::RenderTexture background;
};


struct StateInstance {
    sf::Vector2f cameraPosition = {ARENA_WIDTH/2,ARENA_WIDTH/2};
    ArenaInstance::arenaGrid* arena;
    Player* player;
    std::vector<Enemy>* enemies;
    std::vector<Bullet>* bullets;
};

class GameInstance{
    public:
        StateInstance state;
        GameInstance();
        DisplayInstance display;
        

    private:
        ArenaInstance arena;
        //EntitiesInstance entities;        
};

void instance_mainloop(int id);


#endif
