
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Gui.h"
#include "Tokenizer.h"
#include "Stack.h"
#include <vector>
#include <sstream>
#include <iostream>


using std::ostringstream;

namespace pdCalc {

void Gui::stackChanged() {
    unsigned int nElements{4};
    auto v = Stack::Instance().getElements(nElements);
    ostringstream oss;
    oss.precision(12);
    size_t size = Stack::Instance().size();
    oss << "\n";
    if(size == 0)
        oss << "Stack currently empty.\n";
    else if(size == 1)
        oss << "Top element of stack (size = " << size << "):\n";
    else if(size > 1 && size <= nElements)
        oss << "Top " << size << " elements of stack (size = " << size << "):\n";
    else
        oss << "Top " << nElements << " elements of stack (size = " << size << "):\n";

    size_t j{ v.size() };
    for(auto i = v.rbegin(); i != v.rend(); ++i)
    {
        oss << j << ":\t" << *i << "\n";
        --j;
    }

    postMessage( oss.str() );
}

void Gui::postMessage(const std::string& m) {
    screen_display = m;
}

void Gui::execute() {
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"))
        return;
    sf::Text text("Hello SFML", font, 50);

    // init keyboard
    std::vector<sf::RectangleShape> button;
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Magenta);
    circle.setPosition(100.0, 100.0);
    //button.push_back(circle);

    sf::RectangleShape undo({50, 50});
    sf::RectangleShape redo({50, 50});
    sf::RectangleShape calc({50, 50});
    undo.setPosition({300, 300});
    redo.setPosition({400, 300});
    calc.setPosition({500, 300});
    button.push_back(undo);
    button.push_back(redo);
    button.push_back(calc);

    sf::Text tx_undo("undo", font, 20);
    tx_undo.setPosition({300, 300});
    sf::Text tx_redo("redo", font, 20);
    tx_redo.setPosition({400, 300});
    sf::Text tx_calc("calc", font, 20);
    tx_calc.setPosition({500, 300});
    tx_undo.setFillColor(sf::Color::Green);
    tx_redo.setFillColor(sf::Color::Green);
    tx_calc.setFillColor(sf::Color::Green);
    std::vector<sf::Text> numButton;
    numButton.push_back(tx_undo);
    numButton.push_back(tx_redo);
    numButton.push_back(tx_calc);

    sf::RectangleShape input({700, 100});
    input.setPosition({50, 450});
    button.push_back(input);
    sf::Text tx_input("numbers", font, 100);
    tx_input.setPosition({50, 450});
    tx_input.setFillColor(sf::Color::Magenta);

    sf::RectangleShape screen({700, 300});
    screen.setPosition({50, 50});
    button.push_back(input);
    sf::Text tx_screen("numbers", font, 100);
    tx_screen.setPosition({50, 50});
    tx_screen.setFillColor(sf::Color::Magenta);

    // run the program as long as the window is open
    std::string tx_num{};
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                std::string msg{};
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                for(int i = 0; i < button.size(); ++i) {
                    auto lt = button[i].getPosition();
                    auto size = button[i].getSize();
                    if(x >= lt.x && x <= lt.x + size.x && y >= lt.y && y <= lt.y + size.y) {
                        msg = numButton[i].getString();
                        break;
                    }
                }
                if(!msg.empty()) {
                    std::cout << msg << std::endl;
                    if(msg == "calc") {
                        tx_num.clear();
                    }
                    raise(UserInterface::CommandEntered, std::make_shared<CommandData>(msg));
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                int num = event.key.code;
                if (num >= 26 && num <= 35) tx_num.push_back(num -26 + '0');
                else if(num >= 0 && num <= 25) tx_num.push_back('a' + num);
                std::cout << tx_num << std::endl;
            }
        }


        window.clear();
        for(auto& shape:button) window.draw(shape);
        for(auto& tx:numButton) window.draw(tx);
        tx_input.setString(tx_num);
        window.draw(tx_input);
        tx_screen.setString(screen_display);
        window.draw(tx_screen);
        window.display();

    }


}
    
}