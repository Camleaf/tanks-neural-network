#include "constants.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <gameInstance.hpp>
#include <iostream>
#include <constants.hpp>
#include <colours.hpp>

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


void DisplayInstance::generate_background(){
    background.clear();
    sf::Texture floorTexture("assets/tileable.jpg");
    sf::Texture wallTexture("assets/walltile.jpg");
    
    floorTexture = resizeTexture(floorTexture,{TILES_SIDELENGTH,TILES_SIDELENGTH});
    wallTexture = resizeTexture(wallTexture,{TILES_SIDELENGTH,TILES_SIDELENGTH});
    
    sf::Sprite renderSprite(floorTexture);


    for (int row = 0; row<ARENA_TILES_VERTICAL; row++){
        for (int col = 0; col<ARENA_TILES_HORIZONTAL; col++){
            if ((*state.arena)[row][col]){
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

void DisplayInstance::render_entities(){
    
}

void DisplayInstance::create_player_texture(sf::Color colour){
    sf::RenderTexture texture({PLAYER_BOUNDING_BOX_SIDELENGTH,PLAYER_BOUNDING_BOX_SIDELENGTH});
    texture.clear(sf::Color(255, 255, 255, 0));
    
    sf::Vector2u size = texture.getSize();
    sf::RectangleShape x({(float)size.x,(float)size.y-8});
    x.setPosition({0,4});
    x.setFillColor(sf::Color(OFF_BLACK));
    texture.draw(x);


}

void DisplayInstance::render_players(){
    // Make a dict or something where it will create the texture for each player by colour whenever it first pops up, then will simply index said colour during render time. 
    // Eventually will need more complicated stuff such as rotation and turret but for not a bounding box will do.
}

void DisplayInstance::refresh(){
    surface.clear();
    sf::Sprite bgSprite(background.getTexture());
    surface.draw(bgSprite);
    surface.display(); 
}


