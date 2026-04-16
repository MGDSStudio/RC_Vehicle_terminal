//
// Created by mgdsstudio on 11.04.2026.
//

#ifndef CMAKESFMLPROJECT_GEOMETRIE_H
#define CMAKESFMLPROJECT_GEOMETRIE_H

class GeometrieLibrary {

public:
    static float map(float value, float istart, float istop, float ostart, float ostop) {
        return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
    }
};


#endif //CMAKESFMLPROJECT_GEOMETRIE_H