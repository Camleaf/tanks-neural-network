#include <entities.hpp>
#include <gameInstance.hpp>


EntitiesInstance::EntitiesInstance(StateInstance& state): state(state) {
    player = Player();
    this->state.player = &player;
    this->state.bullets = &bullets;
    this->state.enemies = &enemies;
};


Player& EntitiesInstance::get_player_object_reference(){
    return player;
}

std::vector<Enemy>& EntitiesInstance::get_enemy_objects_reference(){
    return enemies;
}

std::vector<Bullet>& EntitiesInstance::get_bullet_objects_reference(){
    return bullets;
}
