#include "constants.hpp"
#include "entities.hpp"
#include "time_tools.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <gameInstance.hpp>
#include <iostream>
#include <mutex>



GameInstance::GameInstance() : arena(state), display(state), entities(state){
        display.generate_background();
        display.reset();
        display.flip();
        
        display.create_alliance_texture(0,sf::Color::Cyan,sf::Color::Cyan);
        
        entities.add_player(std::make_unique<HumanPlayer>(state,0,sf::Vector2f{20,20},0));
        humanPlayerExists = true;

        entities.add_player(std::make_unique<BotPlayer>(state,1,sf::Vector2f{100,100},0));
}
    




using key = sf::Keyboard::Key;
static std::mutex window_init_mutex;

// Main 
void instance_mainloop(int id){
    sf::RenderWindow window;
    GameInstance x;
    sf::View view(sf::FloatRect({x.state.cameraPosition.x, x.state.cameraPosition.y}, {DISPLAY_WIDTH, DISPLAY_HEIGHT}));
    {
        std::lock_guard<std::mutex> lock(window_init_mutex);
        window.create(sf::VideoMode({ DISPLAY_WIDTH, DISPLAY_HEIGHT }, sf::Style::Titlebar | sf::Style::Close), std::to_string(id));

        window.setView(view);
        window.setSize({DISPLAY_WIDTH, DISPLAY_HEIGHT});
    }
        
    Clock clk(UPS);
    
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

        if (!x.humanPlayerExists){ // Controlled through humanplayer class if that exists
            if (sf::Keyboard::isKeyPressed(key::W)){
                x.state.cameraPosition.y -= CAMERA_PPF;
            }
            if (sf::Keyboard::isKeyPressed(key::S)){ 
                x.state.cameraPosition.y += CAMERA_PPF;
            }
            if (sf::Keyboard::isKeyPressed(key::D)){
            
                x.state.cameraPosition.x += CAMERA_PPF;
            }
            if (sf::Keyboard::isKeyPressed(key::A)){
                x.state.cameraPosition.x -= CAMERA_PPF;
            }
        }
        

        x.entities.update();
        x.display.reset();
        x.display.render_entities();
        x.display.render_players();
        x.display.flip();
		
        view.setCenter({x.state.cameraPosition.x,x.state.cameraPosition.y});
        
        sf::Sprite windowSprite = x.display.get_drawable();
        window.clear();
        window.setView(view);
		window.draw(windowSprite);
		window.display();
        clk.tick();
	}
}
