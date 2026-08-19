#include <gameInstance.hpp>
#include <mutex>


GameInstance::GameInstance() : arena(state), display(state){
        display.generate_background(arena);
        display.refresh();
}
    




using key = sf::Keyboard::Key;
static std::mutex window_init_mutex;

// Main 
void instance_mainloop(int id){
    sf::RenderWindow window;
    {
        std::lock_guard<std::mutex> lock(window_init_mutex);
        window.create(sf::VideoMode({ DISPLAY_WIDTH, DISPLAY_HEIGHT }), std::to_string(id));
    }
        
    GameInstance x;
    
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
		window.draw(x.display.get_drawable());
		window.display();
	}
}
