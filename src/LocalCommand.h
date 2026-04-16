//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_GLOBALCOMMAND_H
#define CMAKESFMLPROJECT_GLOBALCOMMAND_H

#include "LocalCommandPrefix.h"

class LocalCommand {

public:
    LocalCommand();

    LocalCommand(LocalCommandPrefix globalCommandPrefix, float param);

    LocalCommand(LocalCommandPrefix globalCommandPrefix, bool enabled);

    LocalCommandPrefix getPrefix() const;

    [[nodiscard]] float getFloatValue() const {
        return floatValue;
    }

    void setPrefix(LocalCommandPrefix globalCommandPrefix);

    void setFloatValue(float value);

    void setBoolValue(bool value) {
        this->boolValue = value;
    }

    void setIntValue(int value);

    int getId() const;

    bool getBool() const;

private:
    LocalCommandPrefix prefix = LocalCommandPrefix::NO_DATA;
    float floatValue;
    int intValue = 0;
    bool boolValue = true;
    int id;

    static int counter;

    void setId();
};


#endif //CMAKESFMLPROJECT_GLOBALCOMMAND_H
