//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_RELEASEPIN_H
#define RC_VEHICLE_TERMINAL_RELEASEPIN_H
#include <string>


class ReleasePin
{

public:

    virtual ~ReleasePin() = default;
    virtual void setValue(float value) = 0;
    virtual void enable(bool flag);
    virtual void complete();

protected:
    void log(std::string text);
};


#endif //RC_VEHICLE_TERMINAL_RELEASEPIN_H