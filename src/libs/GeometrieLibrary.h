//
// Created by mgdsstudio on 11.04.2026.
//

#ifndef CMAKESFMLPROJECT_GEOMETRIE_H
#define CMAKESFMLPROJECT_GEOMETRIE_H
#include <cmath>




class GeometrieLibrary {

public:
    static float map(float value, float istart, float istop, float ostart, float ostop) {
        return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
    }


    static void rotate(float degrees, float* x, float* y) {
        if (x == nullptr || y == nullptr) return; // Защита от пустых указателей
        // Переводим градусы в радианы, так как std::sin/cos работают с радианами
        float radians = degrees * (3.1415926535f / 180.0f);
        float sin_a = std::sin(radians);
        float cos_a = std::cos(radians);

        // Сохраняем текущие значения, чтобы расчет 'y' был верным
        float old_x = *x;
        float old_y = *y;

        *x = old_x * cos_a - old_y * sin_a;
        *y = old_x * sin_a + old_y * cos_a;
    }

    static float getAngleToObjectInDegrees(float x1, float y1, float x2, float y2) {
        return getPositiveDegreesAngleToPointInCCW(x1, y1, x2, y2);
    }

    static float getPositiveDegreesAngleToPointInCCW(float x, float y, float x1, float y1) {
        float dx = x1-x;
        float dy = y1-y;
        return angleDeg(dx, dy);
    }

    static float getAngle(double x, float y) {
        return std::atan2(y, x);
    }

    static float getAngleDegrees(double x, float y) {
        float radians = std::atan2(y, x);
        float degrees = radians * (180.0 / M_PI);
        return (degrees < 0) ? (degrees + 360.0) : degrees;
    }

    static float dist(float startX, float startY, float endX, float endY) {
        float dx = endX - startX;
        float dy = endY - startY;

        // 2. Return the square root of the sum of squares
        return std::sqrt(dx * dx + dy * dy);
    }

private:
        static float angleDeg(float x, float y) {
        // M_PI * 180.0f / M_PI — это примерно 57.2957795f
        const float radiansToDegrees = 180.0f / 3.1415926535f;

        float angle = std::atan2(y, x) * radiansToDegrees;
        if (angle < 0) angle += 360.0f;
        return angle;
    }
};

/*
mutVector1.x = x1-x;
        mutVector1.y = y1-y;
        return mutVector1.angleDeg();
*/

#endif //CMAKESFMLPROJECT_GEOMETRIE_H