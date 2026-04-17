//
// Created by gorod on 17.04.2026.
//

#include "CompletionController.h"
#include "LocalCommandsListenersObserverSingleton.h"

CompletionController::CompletionController()
{
    LocalCommandsListenersObserverSingleton::getInstance().subscribe(this);
}

CompletionController::~CompletionController()
{

}

void CompletionController::update(float tpf)
{

}

void CompletionController::complete()
{
    LocalCommandsListenersObserverSingleton::getInstance().unsubscribe(this);
}

void CompletionController::onCommandReceived(const LocalCommand& local_command)
{
   if (local_command.getPrefix() == LocalCommandPrefix::SWITCH_OFF || local_command.getPrefix() == LocalCommandPrefix::PAUSE){
        *completeFlagInputLevel = true;
   }
}
