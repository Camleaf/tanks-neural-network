#include <entities.hpp>
#include <gameInstance.hpp>
#include <memory>


Entities::Entities(StateInstance& state): state(state) {
    this->state.bullets = &bullets;
    this->state.players = &players;
};


std::vector<Bullet>& Entities::get_bullet_objects_reference(){
    return bullets;
}


std::vector<std::unique_ptr<Player>>& Entities::get_player_objects_reference(){
    return players;
}

void Entities::add_player(std::unique_ptr<Player> player){
    players.push_back(std::move(player)); 
}


void Entities::update(){
    for (std::unique_ptr<Player>& pl : players){
        pl->step();
    }
}
