
//
// Created by gorod on 10.04.2026.
//

#ifndef CMAKESFMLPROJECT_BUZZERCONTROLLER_H
#define CMAKESFMLPROJECT_BUZZERCONTROLLER_H
#include "LocalCommandsListener.h"
#include "IUpdateable.h"
#include "gpio/SinglePinActor.h"
#include "gpio/SoftwarePin.h"
#include "gpio/PinsInitializer.h"
#include "LocalCommandPrefix.h"
#include "LocalCommandsListenersObserverSingleton.h"

class BuzzerController : public IUpdateable, LocalCommandsListener{
    //

public:

    BuzzerController();
    ~BuzzerController();

    void update(float tpf) override;
    void complete() override;
    void onCommandReceived(LocalCommand& global_command) override;
    
private:
    const std::filesystem::path PATH = Constants::PATH_TO_DATA / "gpio.json";
    static constexpr float DEAD_ZONE_VALUE = 0.1f;
    void init();
    SinglePinActor buzzer;
};


#endif //CMAKESFMLPROJECT_BUZZERCONTROLLER_H