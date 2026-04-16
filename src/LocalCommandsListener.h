//
// Created by gorod on 10.04.2026.
//

#ifndef CMAKESFMLPROJECT_GLOBALCOMMANDSLISTENER_H
#define CMAKESFMLPROJECT_GLOBALCOMMANDSLISTENER_H
#include "LocalCommand.h"


class LocalCommandsListener {
public:
    virtual void onCommandReceived(LocalCommand& global_command);
};


#endif //CMAKESFMLPROJECT_GLOBALCOMMANDSLISTENER_H