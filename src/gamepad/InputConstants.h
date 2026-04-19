//
// Created by mgdsstudio on 18.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_INPUTCONSTANTS_H
#define RC_VEHICLE_TERMINAL_INPUTCONSTANTS_H


class InputConstants {

public:
    constexpr static float STICK_DEAD_ZONE_ANGLE = 15;
    constexpr static float STICK_DEAD_ZONE_RIGHT_TOP = STICK_DEAD_ZONE_ANGLE/2;
    constexpr static float STICK_DEAD_ZONE_RIGHT_BOTTOM = 360-STICK_DEAD_ZONE_ANGLE/2;
    constexpr static float STICK_DEAD_ZONE_LEFT_TOP = 180-STICK_DEAD_ZONE_ANGLE/2;
    constexpr static float STICK_DEAD_ZONE_LEFT_BOTTOM = 180+STICK_DEAD_ZONE_ANGLE/2;


};


#endif //RC_VEHICLE_TERMINAL_INPUTCONSTANTS_H