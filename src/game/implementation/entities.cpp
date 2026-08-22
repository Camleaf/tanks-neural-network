#include "constants.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <cmath>
#include <entities.hpp>
#include <gameInstance.hpp>
#include <iostream>
#include <memory>
#include <random>


Entities::Entities(StateInstance& state): state(state) {
    this->state.bullets = &bullets;
    this->state.players = &players;
};


std::vector<std::unique_ptr<Bullet>>& Entities::get_bullet_objects_reference(){
    return bullets;
}


std::vector<std::unique_ptr<Player>>& Entities::get_player_objects_reference(){
    return players;
}


sf::Vector2i Entities::pick_starting_location(int playerId){
    sf::Vector2i start = {0,0};
    int i = 0, taxicabDist = 0;
    
    std::random_device dev;
    std::mt19937 rng(dev());
    if (state.spawnTiles->size() == 0) return {0,0};
    std::uniform_int_distribution<std::mt19937::result_type> spawnPick(0,state.spawnTiles->size()-1);
    do {
        taxicabDist = 0;
        start = (*state.spawnTiles)[spawnPick(rng)];
       
        for (std::unique_ptr<Player>& pl : (*state.players)){
            if (pl->get_personal_id() == playerId) continue;
            sf::Vector2f otherCenterPos = pl->get_center_coord();
            int tempTaxicabDist = std::abs(otherCenterPos.x-(start.x*TILES_SIDELENGTH)) + std::abs(otherCenterPos.y-(start.y*TILES_SIDELENGTH));    
            
            if (taxicabDist > tempTaxicabDist) continue;
            taxicabDist = tempTaxicabDist;
        }


        i++;
    } while (taxicabDist < COLLISION_DETECT_TAXICAB_RANGE*2 && i < 10); 

    return start;
}


void Entities::add_player(std::unique_ptr<Player> player){
    player->set_grid_position(sf::Vector2i(pick_starting_location(player->get_personal_id())));
    players.push_back(std::move(player)); 
}


void Entities::respawn_enabled(bool enabled){
    respawn = enabled;
}


void Entities::update(){
    if (!respawn){
        players.erase(
            std::remove_if(players.begin(), players.end(), 
                [](std::unique_ptr<Player>& pl) {
                    pl->step();
                    return !pl->is_alive();
                }
            ),
            players.end()
        );
    } else {
        for (std::unique_ptr<Player>& pl : (*state.players)){
            pl->step();
            if (pl->is_alive()) continue;
            pl->reset_health();
            pl->set_grid_position(
                sf::Vector2i(pick_starting_location(pl->get_personal_id()))
            );
        }
    }
    
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(), 
            [](std::unique_ptr<Bullet>& bl) {
                bl->step();
                return !bl->is_alive();
            }
        ),
        bullets.end()
    );
}







Bullet::Bullet(StateInstance& state, int ownerId, int allianceId, sf::Vector2f position, sf::Angle direction): state(state){
    ownerAllianceId = allianceId; 
    this->ownerId = ownerId;
    translationVector = {
        std::cos(direction.asRadians()),
        std::sin(direction.asRadians())
    };
    // Add magnitude
    bounding_box.position = position + (translationVector*BULLET_STARTING_OFFSET);
    translationVector *= BULLET_PPF;
}

sf::Vector2f Bullet::get_center_coord(){
    return bounding_box.getCenter();
}

bool Bullet::move(){
    
    sf::FloatRect tentativeBounds(bounding_box);
    tentativeBounds.position += translationVector;
   
    sf::Vector2f topLeft = tentativeBounds.position;
    sf::Vector2f bottomRight = topLeft+tentativeBounds.size;

    // Check in bounds
    if (
        topLeft.x < 0 || 
        topLeft.y < 0 || 
        bottomRight.x >= ARENA_WIDTH || 
        bottomRight.y >= ARENA_HEIGHT
    ) return false;
    
    //check if in walls.
    // The -PLAYER_PPF factors are to offset the bounding box edge being on the wall counting as inside.
    for (sf::Vector2f pt : {topLeft,{bottomRight.x,topLeft.y},{topLeft.x,bottomRight.y},bottomRight}){
        sf::Vector2i wallPos({(int)pt.x / TILES_SIDELENGTH,(int)pt.y / TILES_SIDELENGTH});
        if ((*state.arena)[(int)wallPos.y][(int)wallPos.x]){
            return false;
        }
    }
    
    sf::Vector2f centerPos = get_center_coord();
    for (std::unique_ptr<Player>& pl : (*state.players)){
        if (pl->get_personal_id() == ownerId) continue;
        if (pl->get_alliance_id() == ownerAllianceId) continue;
        sf::Vector2f otherCenterPos = pl->get_center_coord();
        

        if (std::abs(otherCenterPos.x-centerPos.x) + std::abs(otherCenterPos.y-centerPos.y) >= COLLISION_DETECT_TAXICAB_RANGE) continue;

        sf::FloatRect otherBound = pl->get_bounding_box();
        
        if (otherBound.findIntersection(tentativeBounds).has_value()){
            pl->damage(damage); 
            return false;
        }
            
    }
    bounding_box = tentativeBounds; 
    return true;
}

sf::Vector2f Bullet::get_position(){
    return bounding_box.position;
}

bool Bullet::is_alive(){
    return alive;
}

void Bullet::step(){
    if (!alive) return;
    alive = move();

    if (tick >= (int)BULLET_DROPOFF_FRAMES){
        damage*=BULLET_DROPOFF_FACTOR;
        tick = 0;
    }

    tick++;
}

