//
// Created by gorod on 14.04.2026.
//

#ifndef CMAKESFMLPROJECT_TOUCHPLACE_H
#define CMAKESFMLPROJECT_TOUCHPLACE_H


#include "../libs/GeometrieLibrary.h"
#include "../Logger.h"

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
        validateAndCorrect(X_CHANGED);
        placeWasUpdated = true;
    }

    void setY(float y)
    {
        prevY = this->actualY;
        this->actualY = y;
        validateAndCorrect(Y_CHANGED);
        placeWasUpdated = true;
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
        if (placeWasUpdated)
        {
            placeWasUpdated = false;
            return true;
        }
        else return placeWasUpdated;
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
    bool previousPlaceInDeadZone = true;
    bool actualPlaceInDeadZone = false;
    bool placeWasUpdated = false;
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

    void resetValues(bool whatChanged)
    {
        if (whatChanged == X_CHANGED) this->actualX = prevX;
        else this->actualY = prevY;
    }

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

    void validateAndCorrect(bool whatChanged)
    {
        updateCoordinates();
        if (!firstInit) {
            updateAngle(whatChanged);
        }
        firstInit = false;
    }




};


#endif //CMAKESFMLPROJECT_TOUCHPLACE_H