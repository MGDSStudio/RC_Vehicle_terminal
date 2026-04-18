//
// Created by gorod on 14.04.2026.
//

#ifndef CMAKESFMLPROJECT_TOUCHPLACE_H
#define CMAKESFMLPROJECT_TOUCHPLACE_H


#include "../libs/GeometrieLibrary.h"
#include "../Logger.h"

enum class WhatChanged{
    X, Y, BOTH, NOT_INIT
};

class TouchPlace
{

public:

    TouchPlace(const float max, const float deadZoneAngleInDegrees)
    {
        this->max = max;
        this->min = -max;
        this->rightZoneUp = deadZoneAngleInDegrees/2;
        this->rightZoneDown = 360-deadZoneAngleInDegrees/2;
        this->leftZoneUp = 180-deadZoneAngleInDegrees/2;
        this->leftZoneDown = 180+deadZoneAngleInDegrees/2;
    }

    void setX(float x)
    {
        prevX = this->actualX;
        this->actualX = x;
        if (actualX != prevX) xWasUpdated = true;
    }

    void setY(float y)
    {
        prevY = this->actualY;
        this->actualY = y;
        if (actualY != prevY) yWasUpdated = true;
    }

    float getX()
    {
        return actualX;
    }

    float getY()
    {
        return actualY;
    }

    bool wasPlaceUpdated()
    {
        if (xWasUpdated || yWasUpdated){
            WhatChanged whatChanged = WhatChanged::NOT_INIT;
            if (xWasUpdated && yWasUpdated) {
                whatChanged = WhatChanged::BOTH;
                xWasUpdated = false;
                yWasUpdated = false;
            }
            else if (xWasUpdated){
                whatChanged = WhatChanged::X;
                xWasUpdated = false;
            }
            else if (yWasUpdated){
                whatChanged = WhatChanged::Y;
                yWasUpdated = false;
            }
            validateAndCorrect(whatChanged);
            return true;
        }
        else return false;
    }

    float getAngle() const {
        return GeometrieLibrary::getAngleDegrees(actualX, actualY);
    }

    float getRadius() const {
        return GeometrieLibrary::dist(0,0,actualX, actualY);
    }

private:
    inline static bool X_CHANGED = true;
    inline static bool Y_CHANGED = !X_CHANGED;
    inline static bool UPDATED = true;
    inline static bool NOT_UPDATED = !UPDATED;

    inline static bool debug = true;
    float max;
    float min;
    float rightZoneUp;
    float rightZoneDown;
    float leftZoneUp;
    float leftZoneDown;
    float actualX = 0;
    float actualY = 0;
    float prevX = 0;
    float prevY = 0;
    float angle;
    bool actualPlaceInDeadZone = false;
    bool xWasUpdated = false;
    bool yWasUpdated = false;
    bool firstInit = true;

    static void log(std::string msg)
    {
        if (debug)
        {
            Logger::custom("TouchPlace", msg);
        }
    }

    void updateCoordinates()
    {
        if (actualX>max) actualX = max;
        if (actualX<min) actualX = min;
        if (actualY>max) actualY = max;
        if (actualY<min) actualY = min;
    }

    void resetValues(WhatChanged whatChanged)
    {
        if (whatChanged == WhatChanged::X) this->actualX = prevX;
        else if (whatChanged == WhatChanged::Y) this->actualY = prevY;
        else if (whatChanged == WhatChanged::BOTH){
            this->actualX = prevX;
            this->actualY = prevY;
        }
        if (debug) {
            std::string message = "Touch place was reset back to the prev values. Was changed: ";
            if (whatChanged == WhatChanged::X) message+="X ";
            else if (whatChanged == WhatChanged::Y) message+="Y ";
            else message+="BOTH";
            Logger::debug(message + "; x now: " + std::to_string(actualX) + "; y now: " + std::to_string(actualY));
        }
    }

    bool updateAngle(WhatChanged whatChanged)
    {
        actualPlaceInDeadZone = false;
        this->angle = GeometrieLibrary::getAngleToObjectInDegrees(0,0, actualX, actualY);
        if (angle < rightZoneUp)    //15
        {
            this->actualPlaceInDeadZone = true;
        }
        else if (angle > rightZoneDown)     //345
        {
            this->actualPlaceInDeadZone = true;
        }
        else if (angle > leftZoneUp && angle < 180)
        {
            this->actualPlaceInDeadZone = true;
        }
        else if (angle < leftZoneDown && angle > 180)
        {
            this->actualPlaceInDeadZone = true;
        }
        if (actualPlaceInDeadZone)
        {
            resetValues(whatChanged);
            return NOT_UPDATED;
        }
        else {
            if (debug){
                log("New value was validated successfully");

            }
            return UPDATED;
        }
    }

    void validateAndCorrect(WhatChanged whatChanged)
    {
        updateCoordinates();
        if (!firstInit) {
            updateAngle(whatChanged);
        }
        firstInit = false;
    }
};


#endif //CMAKESFMLPROJECT_TOUCHPLACE_H

/*
void updateAngle(bool whatChanged)
    {
        actualPlaceInDeadZone = false;
        this->angle = GeometrieLibrary::getAngleToObjectInDegrees(0,0, actualX, actualY);
        float deltaAngle = 0;
        if (angle < rightZoneUp)    //15
        {
            deltaAngle = rightZoneUp - angle;
            this->actualPlaceInDeadZone = true;
        }
        else if (angle > rightZoneDown)     //345
        {
            deltaAngle = rightZoneDown - angle;
            this->actualPlaceInDeadZone = true;
        }
        else if (angle > leftZoneUp && angle < 180)
        {
            deltaAngle = leftZoneUp - angle;
            this->actualPlaceInDeadZone = true;
        }
        else if (angle < leftZoneDown && angle > 180)
        {
            deltaAngle = leftZoneDown - angle;
            this->actualPlaceInDeadZone = true;
        }
        if (actualPlaceInDeadZone)
        {
            resetValues(whatChanged);
        }
    }
*/