#include "constants.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>
#include <gameInstance.hpp>
#include <iostream>
#include <random>
#include <algorithm>

ArenaInstance::ArenaInstance(StateInstance& state): state(state) {
    generate_arena_standard();
    this->state.arena = &arena;
    this->state.spawnTiles = &spawnTiles;
};

void ArenaInstance::generate_arena_standard(){

    // Create grid
    do {
    std::fill(&arena[0][0], &arena[0][0]+(ARENA_TILES_VERTICAL*ARENA_TILES_HORIZONTAL),false);
    bisect_walls({{0,0},{ARENA_TILES_HORIZONTAL,ARENA_TILES_VERTICAL}},WALL_DETAIL_LEVEL);
    } while(find_spawnable_region() < 250);
    // Open spawns for alliances
    const int corner_side_lengths = 2;  
};


void ArenaInstance::generate_arena_movement_training(){
    std::fill(&arena[0][0], &arena[0][0]+(ARENA_TILES_VERTICAL*ARENA_TILES_HORIZONTAL),true);
}


void ArenaInstance::generate_arena_shooting(){
    std::fill(&arena[0][0], &arena[0][0]+(ARENA_TILES_VERTICAL*ARENA_TILES_HORIZONTAL),true);
}


int ArenaInstance::find_spawnable_region(){ 
    // BFS algorithm to floodfill arena
    spawnTiles.clear();
    std::pmr::deque<sf::Vector2i> q;
    std::unique_ptr<arenaGrid> visited = std::make_unique<arenaGrid>();
    q.push_back({0,0});
    (*visited)[0][0] = true;
    while (q.size() != 0){
        auto curNode = q.front();
        for (sf::Vector2i vec : DIRECTIONS){
            auto temp = curNode + vec;
            if (temp.x < 0 || temp.x >= ARENA_TILES_HORIZONTAL || temp.y < 0 || temp.y >= ARENA_TILES_VERTICAL) continue; 
            if (arena[temp.y][temp.x]) continue; // check wall
            if ((*visited)[temp.y][temp.x]) continue; // check visited


            (*visited)[temp.y][temp.x] = true;
            q.push_back(temp);
            spawnTiles.push_back(temp);
            
        }

        q.pop_front();
    }
    
    return spawnTiles.size();
}


void ArenaInstance::bisect_walls(sf::IntRect container, int detail){
    if (detail == 0) return;
    
    int left = container.position.x;
    int top = container.position.y;
    int width = container.size.x;
    int height = container.size.y;

    if (width <= 2 || height <= 2) return;
    
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> 
        horiz_random(1,width-2),
        vertical_random(1,height-2);
    
    int col_line = horiz_random(rng);
    int row_line = vertical_random(rng);
    int col_hole = vertical_random(rng);
    int row_hole = horiz_random(rng);
    
    int wall_create_counter = 0;

    // create vertical wall
    for (int i = 0; i<height;i++){
        if (i==col_hole || i==col_hole+1) continue;
        
        // Remove every 3rd wall
        wall_create_counter += 1;
        if (wall_create_counter % 3 == 0) continue;
        
        if (top+i+1 >= ARENA_TILES_VERTICAL) continue;
        // add wall
        arena[top+i+1][col_line+left] = true;
    }
   
    for (int i = 0; i<width;i++){
        if (i==col_hole || i==col_hole+1) continue;
        
        //Remove every third wall
        wall_create_counter += 1;
        if (wall_create_counter % 3 == 0) continue;
        
        if (left+i+1 >= ARENA_TILES_HORIZONTAL) continue;
        arena[row_line+top][left+i+1] = true;
    }
    
    const std::array<sf::IntRect,4> new_containers = {
        sf::IntRect({left,top},{col_line-1,row_line-1}),
        sf::IntRect({left,top+row_line+1},{col_line-1,height-row_line-1}),
        sf::IntRect({left+col_line+1,top},{width-col_line-1,row_line-1}),
        sf::IntRect({left+col_line+1,top+row_line+1},{width-col_line-1,height-row_line-1})
    };

    for (sf::IntRect cont : new_containers){
        bisect_walls(cont,detail-1);
    }
};

std::array<std::array<bool,ARENA_TILES_HORIZONTAL>,ARENA_TILES_VERTICAL>& ArenaInstance::get_arena(){
    return arena;
}
