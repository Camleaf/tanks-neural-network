#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <cmath>
#include <entities.hpp>
#include <gameInstance.hpp>
#include <iostream>
#include <memory>


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

void Entities::add_player(std::unique_ptr<Player> player){
    players.push_back(std::move(player)); 
}


void Entities::update(){

    players.erase(
        std::remove_if(players.begin(), players.end(), 
            [](std::unique_ptr<Player>& pl) {
                pl->step();
                return !pl->is_alive();
            }
        ),
        players.end()
    );
    
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
        sf::Vector2f otherCenterPos = pl->get_center_coord();
        

        if (otherCenterPos.x + otherCenterPos.y-centerPos.x-centerPos.y >= COLLISION_DETECT_TAXICAB_RANGE) continue;

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

