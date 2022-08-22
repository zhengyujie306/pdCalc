#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Magenta);
    circle.setPosition(100.0, 100.0);
    
    sf::Font font;
    if (!font.loadFromFile("/home/zyj/pdCalc/bin/consola.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        window.clear();
        window.draw(text);
        window.display();
        
    }
    

    return 0;
}