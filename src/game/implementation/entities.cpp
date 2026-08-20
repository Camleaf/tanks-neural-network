#include <entities.hpp>
#include <gameInstance.hpp>


Entities::Entities(StateInstance& state): state(state) {
    this->state.bullets = &bullets;
};


std::vector<Bullet>& Entities::get_bullet_objects_reference(){
    return bullets;
}



Alliance::Alliance(StateInstance& state, int allianceId, sf::Color allianceColour) : state(state){
    this->allianceId = allianceId;
    this->allianceColour = allianceColour;
}

std::vector<Player>& Alliance::get_player_objects_reference(){
    return players;
}

