//
// Created by Alexander on 09.04.2026.
//

#ifndef CMAKESFMLPROJECT_IUPDATEABLE_H
#define CMAKESFMLPROJECT_IUPDATEABLE_H


class IUpdateable {
public:

    virtual ~IUpdateable() = default;

    virtual void update(float tpf) = 0;
    virtual void complete() = 0;
};


#endif //CMAKESFMLPROJECT_IUPDATEABLE_H
