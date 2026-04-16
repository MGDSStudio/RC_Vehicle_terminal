//
// Created by gorod on 16.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_RELEASEPINSOFTWARE_H
#define RC_VEHICLE_TERMINAL_RELEASEPINSOFTWARE_H
#include "ReleasePin.h"


class ReleasePinSoftware : public ReleasePin

{
public:
    ~ReleasePinSoftware() override = default;
     void setValue(float value) override;
     void enable(bool flag) override;
     void complete() override;
};


#endif //RC_VEHICLE_TERMINAL_RELEASEPINSOFTWARE_H