// *** ADDED BY HEADER FIXUP ***
#include <istream>
// *** END ***
#include <iostream>
#include <memory>
#include "include/Cli.h"
#include "include/CommandDispatcher.h"
#include "include/AppObservers.h"
#include "include/Stack.h"
#include "include/CoreCommands.h"

// I usually don't make blanket using namespace statements, but this
// example is meant to be simple.
using namespace pdCalc;

using std::cout;
using std::endl;
using std::make_unique;

int main()
{
    Cli cli{std::cin, std::cout};

    CommandDispatcher ce{cli};

    RegisterCoreCommands(cli);

    cli.attach(UserInterface::CommandEntered, make_unique<CommandIssuedObserver>(ce) );

    Stack::Instance().attach(Stack::StackChanged, make_unique<StackUpdatedObserver>(cli) );

    cli.execute();

    return 0;

}
