#include "constants.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <gameInstance.hpp>
#include <entities.hpp>


Player::Player(StateInstance& state, sf::Vector2f position, int allianceId, sf::Color colour, int shootDelay) : state(state), shootInterval(shootDelay){
    shootInterval.reset_time();
    this->bounding_box = sf::FloatRect(position,{PLAYER_BOUNDING_BOX_SIDELENGTH,PLAYER_BOUNDING_BOX_SIDELENGTH});
    this->allianceId = allianceId;
    this->colour = colour;
    turretAngle=sf::degrees(0);
}


int Player::get_alliance_id(){
    return allianceId;
}

sf::Color Player::get_alliance_colour(){
    return colour;
}

sf::FloatRect Player::get_bounding_box(){
    return bounding_box;
}

sf::Vector2f Player::get_center_coord(){
    return bounding_box.getCenter();
}

sf::Angle Player::get_turret_angle(){
    return turretAngle;
}

void Player::set_turret_angle(sf::Angle turretAngle){
    this->turretAngle = turretAngle;
}

void Player::shoot(){

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
    for (sf::Vector2f pt : {topLeft,{bottomRight.x,topLeft.y},{topLeft.x,bottomRight.y},bottomRight}){
        if ((*state.arena)[(int)pt.y / ARENA_TILES_VERTICAL][(int)pt.x / ARENA_TILES_VERTICAL]){
            return false;
        }
    }
    
    for (Alliance al : (*state.alliances)){
        for (Player pl : (al.get_player_objects_reference())){
            
            sf::Vector2f otherCenterPos = pl.get_center_coord();
            
            if (otherCenterPos.x + otherCenterPos.y >= COLLISION_DETECT_TAXICAB_RANGE) continue;

            sf::FloatRect otherBound = pl.get_bounding_box();

            if (otherBound.findIntersection(tentativeBounds).has_value()){
                return false;
            }
            
        }
    }
    return true;
}



HumanPlayer::HumanPlayer(StateInstance& state, sf::Vector2f position, int allianceId, sf::Color colour) 
    : Player(state, position, allianceId, colour) {
}


void HumanPlayer::step(){

}
