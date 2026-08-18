#include "constants.hpp"
#include <gameInstance.hpp>


DisplayInstance::DisplayInstance(){
    surface = sf::RenderTexture({DISPLAY_WIDTH,DISPLAY_HEIGHT});
    background = sf::RenderTexture({ARENA_WIDTH,ARENA_HEIGHT});
    surface.clear();
}

sf::Sprite DisplayInstance::get_drawable(){
    sf::Sprite sprite(surface.getTexture());
    return sprite;
}


void DisplayInstance::generate_background(ArenaInstance arena){
    background.clear();
    sf::Texture texture(""); // load image texture then figure out how to scale
}
