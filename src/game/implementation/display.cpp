#include "constants.hpp"
#include <gameInstance.hpp>


DisplayInstance::DisplayInstance(){
    surface = sf::RenderTexture({ARENA_WIDTH,ARENA_HEIGHT});
    sf::RectangleShape x;
    x.setSize({ARENA_WIDTH,ARENA_HEIGHT});
    x.setFillColor(sf::Color::Cyan);
    surface.draw(x);
}

sf::Sprite DisplayInstance::get_drawable(){
    sf::Sprite sprite(surface.getTexture());
    return sprite;
}
