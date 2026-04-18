
#include  "Logger.h"
#include "MainController.h"
#include "tests/TestStick.h"


void dispose();
void launchTest();
std::string getTime();

MainController main_controller;

bool tests = false;

int main(int argc, char* argv[]) {
    Logger::debug("App launched at: " + getTime());
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
    Logger::debug("App completed at: " + getTime());
    return 0;
}

void launchTest() {
    TestStick testStick;
}

std::string getTime(){
    auto now = std::chrono::system_clock::now();

    // 2. Преобразуем в time_t (формат времени C)
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // 3. Выводим в читаемом виде
    //std::cout << "Текущее время: " << std::ctime(&now_c);
    std::string time = std::ctime(&now_c);
    return time;
}

void dispose()
{
    main_controller.complete();
    Logger::debug("App completed");
}