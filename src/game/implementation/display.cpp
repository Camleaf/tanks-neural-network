#include "constants.hpp"
#include <gameInstance.hpp>
#include <iostream>
#include <constants.hpp>

sf::Texture resizeTexture(sf::Texture &origTexture, sf::Vector2u size)
{
    sf::Sprite sprite(origTexture);

    sf::Vector2u originalSize = origTexture.getSize();
    float scaleX = ((float)size.x) / originalSize.x;
    float scaleY = ((float)size.y) / originalSize.y;

    sprite.setScale({scaleX, scaleY});

    sf::RenderTexture renderTexture({size.x,size.y});

    renderTexture.clear(sf::Color::Transparent);
    renderTexture.draw(sprite);
    renderTexture.display();

    return renderTexture.getTexture();
}

DisplayInstance::DisplayInstance(StateInstance& state): state(state) {
    surface = sf::RenderTexture({ARENA_WIDTH,ARENA_HEIGHT});
    background = sf::RenderTexture({ARENA_WIDTH,ARENA_HEIGHT});
    surface.clear();
    surface.display();
}

sf::Sprite DisplayInstance::get_drawable(){
    sf::Sprite sprite(surface.getTexture());
    return sprite;
}


void DisplayInstance::generate_background(ArenaInstance &arenaInstance){
    background.clear();
    sf::Texture floorTexture("assets/tileable.jpg");
    sf::Texture wallTexture("assets/walltile.jpg");
    
    floorTexture = resizeTexture(floorTexture,{TILES_SIDELENGTH,TILES_SIDELENGTH});
    wallTexture = resizeTexture(wallTexture,{TILES_SIDELENGTH,TILES_SIDELENGTH});
    
    sf::Sprite renderSprite(floorTexture);

    auto arena = arenaInstance.get_arena();
    for (int row = 0; row<std::size(arena); row++){
        for (int col = 0; col<std::size(arena[0]); col++){
            if (arena[row][col]){
                renderSprite.setTexture(wallTexture,true);
            } else {
                renderSprite.setTexture(floorTexture,true);
            }

            renderSprite.setPosition({
                (float)(col*TILES_SIDELENGTH),
                (float)(row*TILES_SIDELENGTH)}
            );
            
            background.draw(renderSprite);
        }
    }
    background.display();
}

void DisplayInstance::render_entities(Entities& entities){

}



void DisplayInstance::refresh(){
    surface.clear();
    sf::Sprite bgSprite(background.getTexture());
    surface.draw(bgSprite);
    surface.display(); 
}


