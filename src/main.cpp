
#include  "Logger.h"
#include "MainController.h"


void dispose();

MainController main_controller;
bool exitCommandReceived = false;

int main(int argc, char* argv[]) {
    main_controller.attachCompletionFlagData(&exitCommandReceived);
    while (!exitCommandReceived)
    {
        main_controller.update(1);
    }
    dispose();
    return 0;
}

void dispose()
{
    main_controller.complete();
    Logger::debug("App completed");
}