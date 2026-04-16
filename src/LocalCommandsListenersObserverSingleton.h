//
// Created by gorod on 10.04.2026.
//

#ifndef CMAKESFMLPROJECT_GLOBALCOMMANDSLISTENERSOBSERVERSINGLETON_H
#define CMAKESFMLPROJECT_GLOBALCOMMANDSLISTENERSOBSERVERSINGLETON_H
#include <vector>

#include "LocalCommandsListener.h"
#include <algorithm>


class LocalCommandsListenersObserverSingleton {

public:
    LocalCommandsListenersObserverSingleton(const LocalCommandsListenersObserverSingleton &) = delete;
    void operator=(const LocalCommandsListenersObserverSingleton &) = delete;

    void complete();

    static LocalCommandsListenersObserverSingleton& getInstance() {
        static LocalCommandsListenersObserverSingleton instance;
        return instance;
    }
    void subscribe(LocalCommandsListener* listener);
    void unsubscribe(LocalCommandsListener* listener);
    void broadcast(LocalCommand &global_command) const;

private:
    LocalCommandsListenersObserverSingleton();
    std::vector<LocalCommandsListener*> listeners;
};


#endif //CMAKESFMLPROJECT_GLOBALCOMMANDSLISTENERSOBSERVERSINGLETON_H