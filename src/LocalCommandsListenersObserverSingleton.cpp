//
// Created by gorod on 10.04.2026.
//

#include "LocalCommandsListenersObserverSingleton.h"

LocalCommandsListenersObserverSingleton::LocalCommandsListenersObserverSingleton(){
    
}

void LocalCommandsListenersObserverSingleton::complete() {
    listeners.clear();
}

void LocalCommandsListenersObserverSingleton::subscribe(LocalCommandsListener* listener) {
    listeners.push_back(listener);
}

void LocalCommandsListenersObserverSingleton::unsubscribe(LocalCommandsListener* listener) {
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end()){
        //found
        listeners.erase(it);
    }
    else{
        //not found
    }
}

void LocalCommandsListenersObserverSingleton::broadcast(LocalCommand &global_command) const {
    for (const auto listener : listeners) {
        listener->onCommandReceived(global_command);
    }
}
