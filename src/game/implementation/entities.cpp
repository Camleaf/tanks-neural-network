#include <entities.hpp>
#include <gameInstance.hpp>


Entities::Entities(StateInstance& state): state(state) {
    this->state.bullets = &bullets;
    this->state.players = &players;
};


std::vector<Bullet>& Entities::get_bullet_objects_reference(){
    return bullets;
}


std::vector<Player*>& Entities::get_player_objects_reference(){
    return players;
}

void Entities::add_player(Player* player){
    players.push_back(player); 
}
