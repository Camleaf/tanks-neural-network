#include <entities.hpp>
#include <gameInstance.hpp>


Entities::Entities(StateInstance& state): state(state) {
    this->state.players = &players;
    this->state.bullets = &bullets;
};



std::vector<Player>& Entities::get_player_objects_reference(){
    return players;
}

std::vector<Bullet>& Entities::get_bullet_objects_reference(){
    return bullets;
}





