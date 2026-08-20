#include "constants.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <gameInstance.hpp>
#include <random>
#include <algorithm>

ArenaInstance::ArenaInstance(StateInstance& state): state(state) {
    generate_walls();
    this->state.arena = &arena;
};

void ArenaInstance::generate_walls(){
    std::fill(&arena[0][0], &arena[0][0]+(ARENA_TILES_VERTICAL*ARENA_TILES_HORIZONTAL),false);

    bisect_walls({{0,0},{ARENA_TILES_HORIZONTAL,ARENA_TILES_VERTICAL}},WALL_DETAIL_LEVEL);
    

};




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
        
        // add wall
        arena[top+i+1][col_line+left] = true;
    }
   
    for (int i = 0; i<width;i++){
        if (i==col_hole || i==col_hole+1) continue;
        
        //Remove every third wall
        wall_create_counter += 1;
        if (wall_create_counter % 3 == 0) continue;

        arena[row_line+top][left+i+1] = true;
    }
    
    const std::array<sf::IntRect,4> new_containers = {
        sf::IntRect({left,top},{col_line-1,row_line-1}),
        sf::IntRect({left,top+row_line+1},{col_line-1,height-row_line}),
        sf::IntRect({left+col_line+1,top},{width-col_line,row_line-1}),
        sf::IntRect({left+col_line+1,top+row_line+1},{width-col_line,height-row_line})
    };

    for (sf::IntRect cont : new_containers){
        bisect_walls(cont,detail-1);
    }
};

std::array<std::array<bool,ARENA_TILES_HORIZONTAL>,ARENA_TILES_VERTICAL>& ArenaInstance::get_arena(){
    return arena;
}
