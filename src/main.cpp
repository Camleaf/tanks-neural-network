#include <SFML/Graphics.hpp>
#include <gameInstance.hpp>
#include <constants.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( { DISPLAY_WIDTH, DISPLAY_HEIGHT} ), "SFML works!" );
    
    DisplayInstance x = DisplayInstance();
    
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		window.draw(x.get_drawable());
		window.display();
	}
}
