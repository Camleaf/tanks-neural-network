#ifndef ENTITIES 
#define ENTITIES

#include "time_tools.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <constants.hpp>

struct StateInstance;



class Player{
    public:
        Player(StateInstance& state, int personalId, sf::Vector2f position, int allianceId, int shootDelay=400);
        int get_alliance_id();
        int get_personal_id();
        sf::Color get_alliance_colour();
        sf::FloatRect get_bounding_box();
        sf::Vector2f get_center_coord();
        sf::Vector2f get_position();
        void set_turret_angle(sf::Angle turretAngle);
        sf::Angle get_turret_angle();

        bool move(sf::Vector2f vector, float magnitude=2);
        void shoot();
        
        virtual void step() = 0;

    protected:
        int personalId;
        StateInstance& state;
        Interval shootInterval;
        sf::FloatRect bounding_box;
        sf::Angle turretAngle;
        int allianceId;

};


class BotPlayer : public Player {
    public:
        
        BotPlayer(StateInstance& state, int personalId, sf::Vector2f position, int allianceId);
        void step() override;
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(StateInstance& state, int personalId, sf::Vector2f position, int allianceId);
        void step() override;
};


class NeuralNetPlayer: public Player {
    public:
        NeuralNetPlayer(StateInstance& state, int personalId, sf::Vector2f position, int allianceId);
        void step() override;
};





class Bullet{
    public:
        Bullet(StateInstance& state, int allianceId, sf::Vector2f position, sf::Angle direction);
        sf::Vector2f get_center_coord();
        void step();
        bool is_alive();
        sf::Vector2f get_position();
    private:
        bool move();
        StateInstance& state;
        sf::FloatRect bounding_box = {{0.f,0.f},{BULLET_BOUNDING_BOX_SIDELENGTH,BULLET_BOUNDING_BOX_SIDELENGTH}};
        sf::Vector2f translationVector;
        float distanceTravelled;
        int ownerAllianceId;
        bool alive = true;
};


#endif
