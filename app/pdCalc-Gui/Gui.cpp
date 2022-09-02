
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Gui.h"
#include "Button.h"
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
    if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf"))
        return;

    std::vector<sf::Button> Buttons;
    sf::Button undo((sf::RectangleShape()), sf::Text());
    undo.setPosition({100, 300});
    undo.setSize({150, 100});
    undo.setShapeColor(sf::Color::Cyan);
    undo.setTextColor(sf::Color::Blue);
    undo.setFont(font);
    undo.setString("undo");
    Buttons.emplace_back(std::move(undo));

    sf::Button redo((sf::RectangleShape()), sf::Text());
    redo.setPosition({300, 300});
    redo.setSize({150, 100});
    redo.setShapeColor(sf::Color::Cyan);
    redo.setTextColor(sf::Color::Blue);
    redo.setFont(font);
    redo.setString("redo");
    Buttons.emplace_back(std::move(redo));

    sf::Button shiftButton((sf::RectangleShape()), sf::Text());
    shiftButton.setPosition({500, 300});
    shiftButton.setSize({150, 100});
    shiftButton.setShapeColor(sf::Color::Cyan);
    shiftButton.setTextColor(sf::Color::Blue);
    shiftButton.setFont(font);
    shiftButton.setString("shift");
    Buttons.emplace_back(std::move(shiftButton));



    sf::RectangleShape input({700, 100});
    input.setPosition({50, 450});

    sf::Text tx_input("numbers", font, 100);
    tx_input.setPosition({50, 450});
    tx_input.setFillColor(sf::Color::Magenta);

    sf::RectangleShape screen({700, 200});
    screen.setPosition({50, 50});
    screen.setFillColor(sf::Color::White);
    screen.setOutlineColor(sf::Color::Green);

    sf::Text tx_screen("numbers", font, 30);
    tx_screen.setPosition({50, 50});
    tx_screen.setFillColor(sf::Color::Magenta);

    // run the program as long as the window is open
    std::string tx_num{};
    bool shift = false;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                std::string msg{};
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                for(auto & Button : Buttons) {
                    auto lt = Button.getPosition();
                    auto size = Button.getSize();
                    if(x >= lt.x && x <= lt.x + size.x && y >= lt.y && y <= lt.y + size.y) {
                        msg = Button.getString();
                        break;
                    }
                }
		        if(!msg.empty()) {
                    if(msg == "shift") {
                        shift = !shift;
                        Buttons[2].setShapeColor(shift ? sf::Color::Red : sf::Color::Cyan);
                    }
                    else raise(UserInterface::CommandEntered, std::make_shared<CommandData>(msg));
		        }
            }
            else if (event.type == sf::Event::KeyPressed) {
                auto num = event.key.code;
                std::cout << num << std::endl;

                if(num == sf::Keyboard::Key::Enter) {
                    if(!tx_num.empty()) {
                        raise(UserInterface::CommandEntered, std::make_shared<CommandData>(tx_num));
                        tx_num.clear();
                    }

                }
                else if(num == sf::Keyboard::Key::BackSpace) {
                    if(!tx_num.empty()) tx_num.pop_back();
                }
                else if(num == sf::Keyboard::Key::LShift || num == sf::Keyboard::Key::RShift) {
                    shift = !shift;
                    Buttons[2].setShapeColor(shift ? sf::Color::Red : sf::Color::Cyan);
                }
                else if(num == sf::Keyboard::Key::Hyphen) raise(UserInterface::CommandEntered, std::make_shared<CommandData>("-"));
                else if(num == sf::Keyboard::Key::Equal && shift) {
                    raise(UserInterface::CommandEntered, std::make_shared<CommandData>("+"));
                    shift = !shift;
                    Buttons[2].setShapeColor(shift ? sf::Color::Red : sf::Color::Cyan);
                }
                else if(num == sf::Keyboard::Key::Num8 && shift) {
                    raise(UserInterface::CommandEntered, std::make_shared<CommandData>("*"));
                    shift = !shift;
                    Buttons[2].setShapeColor(shift ? sf::Color::Red : sf::Color::Cyan);
                }
                else if(num == sf::Keyboard::Key::Slash) {
                    raise(UserInterface::CommandEntered, std::make_shared<CommandData>("/"));
                }
                else if (num >= 26 && num <= 35) tx_num.push_back(num -26 + '0');
                else if(num >= 0 && num <= 25) tx_num.push_back('a' + num);
                //std::cout << tx_num << std::endl;
            }
        }


        window.clear({113, 115, 117});
        for(auto& shape:Buttons) window.draw(shape);


        window.draw(screen);
        window.draw(input);
        tx_input.setString(tx_num);
        window.draw(tx_input);
        tx_screen.setString(screen_display);
        window.draw(tx_screen);


        window.display();

    }


}
    
}
