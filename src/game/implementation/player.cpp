#include "constants.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <gameInstance.hpp>
#include <entities.hpp>
#include <iostream>
#include <memory>


Player::Player(StateInstance& state, int personalId, sf::Vector2f position, int allianceId, int shootDelay) : state(state), shootInterval(shootDelay){
    shootInterval.reset_time();
    this->bounding_box = sf::FloatRect(position,{PLAYER_BOUNDING_BOX_SIDELENGTH,PLAYER_BOUNDING_BOX_SIDELENGTH});
    this->allianceId = allianceId;
    this->personalId = personalId;
    turretAngle=sf::degrees(0);
}

int Player::get_alliance_id(){
    return allianceId;
}

int Player::get_personal_id(){
    return personalId;
}

sf::FloatRect Player::get_bounding_box(){
    return bounding_box;
}

sf::Vector2f Player::get_center_coord(){
    return bounding_box.getCenter();
}

sf::Vector2f Player::get_position(){
    return bounding_box.position;
}

sf::Angle Player::get_turret_angle(){
    return turretAngle;
}

void Player::set_turret_angle(sf::Angle turretAngle){
    this->turretAngle = turretAngle;
}

void Player::shoot(){
    if (shootInterval.interval_passed()){
        (*state.bullets).push_back(
                std::move(
                    std::make_unique<Bullet>(state,allianceId,get_position(),turretAngle)
                )
        );
    }
}




// To avoid x blockage affecting y movement, can simply
bool Player::move(sf::Vector2f vector, float magnitude){
    sf::Vector2f scaledVector = vector * (float)magnitude;
    
    sf::FloatRect tentativeBounds(bounding_box);
    tentativeBounds.position += scaledVector;
   
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
    for (sf::Vector2f pt : {topLeft,{bottomRight.x-PLAYER_PPF,topLeft.y},{topLeft.x,bottomRight.y-PLAYER_PPF},bottomRight-sf::Vector2f{PLAYER_PPF,PLAYER_PPF}}){
        sf::Vector2i wallPos({(int)pt.x / TILES_SIDELENGTH,(int)pt.y / TILES_SIDELENGTH});
        if ((*state.arena)[(int)wallPos.y][(int)wallPos.x]){
            return false;
        }
    }
    
    sf::Vector2f centerPos = get_center_coord();
    for (std::unique_ptr<Player>& pl : (*state.players)){
        if (personalId == pl->personalId) continue;
        sf::Vector2f otherCenterPos = pl->get_center_coord();
        

        if (otherCenterPos.x + otherCenterPos.y-centerPos.x-centerPos.y >= COLLISION_DETECT_TAXICAB_RANGE) continue;

        sf::FloatRect otherBound = pl->get_bounding_box();
        
        if (otherBound.findIntersection(tentativeBounds).has_value()){
            return false;
        }
            
    }
    bounding_box = tentativeBounds; 
    return true;
}



HumanPlayer::HumanPlayer(StateInstance& state, int personalId, sf::Vector2f position, int allianceId) : Player(state, personalId, position, allianceId) {}

using key = sf::Keyboard::Key;
void HumanPlayer::step(){

    sf::Vector2f moveVector{0,0};

    if (sf::Keyboard::isKeyPressed(key::Up)){
        moveVector.y -= PLAYER_PPF;
    }
    if (sf::Keyboard::isKeyPressed(key::Down)){ 
        moveVector.y += PLAYER_PPF;
    }
    if (moveVector.y != 0){
        move({0,moveVector.y});
    }
    if (sf::Keyboard::isKeyPressed(key::Left)){
        moveVector.x -= PLAYER_PPF;
    }
    if (sf::Keyboard::isKeyPressed(key::Right)){
        moveVector.x += PLAYER_PPF;
    }
    if (moveVector.x != 0){
        move({moveVector.x,0});
    }


    state.cameraPosition = get_position();

    // Calculate vector between mouse and player then atan2 to get angle
    sf::Vector2f mousePosition{sf::Mouse::getPosition()};
    sf::Vector2f diffVec = get_center_coord() - mousePosition;
    set_turret_angle(sf::radians(std::atan2(diffVec.y,diffVec.x)));


    if (sf::Keyboard::isKeyPressed(key::Space)){
        shoot();
    }

}

BotPlayer::BotPlayer(StateInstance& state, int personalId, sf::Vector2f position, int allianceId) : Player(state, personalId, position, allianceId) {}

void BotPlayer::step(){
        
}
