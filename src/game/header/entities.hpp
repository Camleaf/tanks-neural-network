#ifndef ENTITIES 
#define ENTITIES

#include <SFML/Graphics.hpp>
#include <constants.hpp>


class Player{
    public:
        Player();
    private:
        int BULLET_SPEED_MULTIPLIER = 1;
        int SPEED_MULTIPLIER = 1;
        

        int lives = 1;
        
};


class Enemy{

};


class Bullet{

};


#endif



