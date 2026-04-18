
#include  "Logger.h"
#include "MainController.h"
#include "tests/TestStick.h"


void dispose();
void launchTest();

MainController main_controller;

bool tests = true;

int main(int argc, char* argv[]) {
    bool exitCommandReceived = false;
    if (tests) {
        launchTest();
    }
    else {
        main_controller.attachCompletionFlagData(&exitCommandReceived);
        while (!exitCommandReceived)
        {
            main_controller.update(1);
        }
        dispose();
    }
    return 0;
}

void launchTest() {
    TestStick testStick;
}

void dispose()
{
    main_controller.complete();
    Logger::debug("App completed");
}