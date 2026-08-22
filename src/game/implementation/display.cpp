#include "constants.hpp"
#include "entities.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <gameInstance.hpp>
#include <constants.hpp>
#include <colours.hpp>
#include <memory>

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
    
    sf::RectangleShape x;
    x.setSize({BULLET_BOUNDING_BOX_SIDELENGTH,BULLET_BOUNDING_BOX_SIDELENGTH});
    for (std::unique_ptr<Bullet>& bl : (*state.bullets)){
        x.setPosition(bl->get_position());
        x.setFillColor(sf::Color::Black);
        surface.draw(x);
    }

}

void DisplayInstance::create_alliance_texture(int allianceId, sf::Color allianceColour, sf::Color allianceAccent){
    sf::RenderTexture texture({PLAYER_BOUNDING_BOX_SIDELENGTH,PLAYER_BOUNDING_BOX_SIDELENGTH});
    texture.clear(sf::Color(255, 255, 255, 0));
    
    sf::Vector2u size = texture.getSize();
    sf::RectangleShape x({(float)size.x,(float)size.y});
    x.setFillColor(allianceColour);
    texture.draw(x);

   
    playerTextures.insert_or_assign(allianceId, texture.getTexture());
    


}

// Alliance textures MUST have been created by the time this is called, else error
void DisplayInstance::render_players(){    

    for (std::unique_ptr<Player>& pl : (*state.players)){
        int allianceId = pl->get_alliance_id();
        sf::Sprite x(playerTextures[allianceId]);
        x.setPosition(pl->get_position());
        uint8_t player_health = pl->get_health(); // If changing health MUST change this
        x.setColor({player_health, player_health, player_health, 255});
        surface.draw(x);
    }
}

void DisplayInstance::reset(){
    surface.clear();
    sf::Sprite bgSprite(background.getTexture());
    surface.draw(bgSprite);
}


void DisplayInstance::flip(){
    surface.display();
}

