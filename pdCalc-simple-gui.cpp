#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "include/Gui.h"
#include "include/CommandDispatcher.h"
#include "include/AppObservers.h"
#include "include/Stack.h"
#include "include/CoreCommands.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    pdCalc::Gui gui(window);
    pdCalc::CommandDispatcher ce{gui};

    pdCalc::RegisterCoreCommands(gui);

    gui.attach(pdCalc::UserInterface::CommandEntered, std::make_unique<pdCalc::CommandIssuedObserver>(ce) );

    pdCalc::Stack::Instance().attach(pdCalc::Stack::StackChanged, std::make_unique<pdCalc::StackUpdatedObserver>(gui) );
    
    gui.execute();

    return 0;
}