#ifndef GAMEINSTANCE
#define GAMEINSTANCE

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <constants.hpp>
#include <entities.hpp>
#include <map>
#include <memory>
#include <vector>

struct StateInstance;

class ArenaInstance{
    public:
        ArenaInstance(StateInstance& state);
        typedef std::array<std::array<bool,ARENA_TILES_HORIZONTAL>,ARENA_TILES_VERTICAL> arenaGrid; 
        arenaGrid& get_arena();
        void generate_arena_standard();
        void generate_arena_movement_training();
        void generate_arena_shooting();
    private: 
        StateInstance& state; 
        arenaGrid arena;
        std::vector<sf::Vector2i> spawnTiles;
        void bisect_walls(sf::IntRect container, int detail);
        int find_spawnable_region();
        
};

// Bullets are added from within the player classes for ease of architecture.
class Entities{
    public:
        Entities(StateInstance& state);
        std::vector<std::unique_ptr<Bullet>>& get_bullet_objects_reference();
        std::vector<std::unique_ptr<Player>>& get_player_objects_reference();
        void add_player(std::unique_ptr<Player> player);
        sf::Vector2i pick_starting_location(int playerId);
        void update();
        void respawn_enabled(bool enabled);
    private:
        bool respawn = false; 
        StateInstance& state;
        std::vector<std::unique_ptr<Bullet>> bullets;
        std::vector<std::unique_ptr<Player>> players;
};



class DisplayInstance{
    public:
        sf::RenderTexture surface;
        DisplayInstance(StateInstance& state);
        
        // Sets the render surface to the background texture
        void reset();
        void flip();
        void generate_background(); // Builds f stateinstance
        void render_entities(); // uses stateinstance
        void render_players(); // uses stateinstance
        sf::Sprite get_drawable();
        void create_alliance_texture(int allianceId, sf::Color allianceColour, sf::Color allianceAccent);
        

    private:
        std::map<int, sf::Texture> playerTextures;
        StateInstance& state; 
        sf::RenderTexture background;
};


struct StateInstance {
    sf::Vector2f cameraPosition = {ARENA_WIDTH/2.f,ARENA_WIDTH/2.f};
    ArenaInstance::arenaGrid* arena;
    std::vector<sf::Vector2i>* spawnTiles;
    std::vector<std::unique_ptr<Player>>* players;
    std::vector<std::unique_ptr<Bullet>>* bullets;
    sf::Window* window;

};

class GameInstance{
    public:
        StateInstance state;
        GameInstance();
        DisplayInstance display;
        Entities entities;
        bool humanPlayerExists = false;
    private:
        ArenaInstance arena;
};

void instance_mainloop(int id);


#endif
