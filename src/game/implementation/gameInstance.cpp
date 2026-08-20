#include "time_tools.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <gameInstance.hpp>
#include <mutex>


GameInstance::GameInstance() : arena(state), display(state), entities(state){
        display.generate_background(arena);
        display.refresh();
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
        window.create(sf::VideoMode({ DISPLAY_WIDTH, DISPLAY_HEIGHT }), std::to_string(id));

        window.setView(view);
    }
        
    Clock clk(UPS);
    
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
            if ( event->is<sf::Event::KeyPressed>()){
                auto ev = event->getIf<sf::Event::KeyPressed>();
            }
		}


        if (sf::Keyboard::isKeyPressed(key::W)){
            x.state.cameraPosition.y += 2.5;
        }
        if (sf::Keyboard::isKeyPressed(key::S)){ 
            x.state.cameraPosition.y -= 2.5;
        }
        if (sf::Keyboard::isKeyPressed(key::D)){
        
            x.state.cameraPosition.x -= 2.5;
        }
        if (sf::Keyboard::isKeyPressed(key::A)){
            x.state.cameraPosition.x += 2.5;
        }
        

		window.clear();

        x.display.refresh();

        sf::Sprite windowSprite = x.display.get_drawable();
        view.setCenter({x.state.cameraPosition.x,x.state.cameraPosition.y});
		window.draw(windowSprite);

		window.display();
        clk.tick();
	}
}
