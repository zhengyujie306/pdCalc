// zhyujie zhengyujie306@gmail.com

#ifndef GUI_H
#define GUI_H

#include "UserInterface.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>


namespace pdCalc {
class Gui : public UserInterface
{
public:
    Gui(sf::RenderWindow& _window):window{_window} {};
    ~Gui() = default;

    void execute();
    void postMessage(const std::string& m) override;
    void stackChanged() override;
private:
    

    
    sf::RenderWindow& window;
    std::string screen_display;
    Gui(const Gui&) = delete;
    Gui(Gui&&) = delete;
    Gui& operator=(const Gui&) = delete;
    Gui& operator=(Gui&&) = delete;
};
}

#endif