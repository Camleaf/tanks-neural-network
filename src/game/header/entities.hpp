#ifndef ENTITIES 
#define ENTITIES

#include "time_tools.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <constants.hpp>

struct StateInstance;



const int COLLISION_DETECT_TAXICAB_RANGE = 5;

class Player{
    public:
        Player(StateInstance& state, sf::Vector2f position, int allianceId, sf::Color colour, int shootDelay=400);
        int get_alliance_id();
        sf::Color get_alliance_colour();
        sf::FloatRect get_bounding_box();
        sf::Vector2f get_center_coord();

        void set_turret_angle(sf::Angle turretAngle);
        sf::Angle get_turret_angle();

        bool move(sf::Vector2f vector, float magnitude=2);
        void shoot();

        virtual void step();

    protected:
        StateInstance& state;
        Interval shootInterval;
        sf::FloatRect bounding_box;
        sf::Color colour;
        sf::Angle turretAngle;
        int allianceId;

};


class BotPlayer : public Player {
    public:
        
        BotPlayer(StateInstance& state, sf::Vector2f position, int allianceId, sf::Color colour);
        void step();
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(StateInstance& state, sf::Vector2f position, int allianceId, sf::Color colour);
        void step();
};


class NeuralNetPlayer: public Player {
    public:
        NeuralNetPlayer(StateInstance& state, sf::Vector2f position, int allianceId, sf::Color colour);
        void step();
};






class Bullet{
    
};


#endif



