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


class Entities{
    public:
        Entities(StateInstance& state);
        std::vector<Bullet>& get_bullet_objects_reference();
    private:
        StateInstance& state; 
        std::vector<Bullet> bullets;
};

class Alliance{
    public:
        Alliance(StateInstance& state, int allianceId, sf::Color allianceColour = sf::Color::Blue);
        int allianceId;
        sf::Color allianceColour;
        std::vector<Player>& get_player_objects_reference();
    private:
        StateInstance& state;
        std::vector<Player> players;
};


class DisplayInstance{
    public:
        sf::RenderTexture surface;
        DisplayInstance(StateInstance& state);
        
        // Sets the render surface to the background texture
        void refresh();
        void generate_background(); // Builds f stateinstance
        void render_entities(); // uses stateinstance
        void render_players(); // uses stateinstance
        sf::Sprite get_drawable();

    private:
        void create_player_texture(sf::Color colour);
        StateInstance& state; 
        sf::RenderTexture background;
};


struct StateInstance {
    sf::Vector2f cameraPosition = {ARENA_WIDTH/2,ARENA_WIDTH/2};
    ArenaInstance::arenaGrid* arena;
    std::vector<Alliance>* alliances;
    std::vector<Bullet>* bullets;
};

class GameInstance{
    public:
        StateInstance state;
        GameInstance();
        DisplayInstance display;
        

    private:
        ArenaInstance arena;
        Entities entities;
};

void instance_mainloop(int id);


#endif
