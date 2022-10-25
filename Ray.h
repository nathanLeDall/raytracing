//
// Created by nathan on 5/25/2022.
//

#ifndef UNTITLED2_RAY_H
#define UNTITLED2_RAY_H

#include "vec3.h"

class ray{
public:
    point3 orign;
    vec3 dir;
    ray(){}
    ray(const point3& orig, const vec3& direction)
        : orign(orig), dir(direction)
    {
    }

    point3 getOrign() const {return orign;}
    vec3 getDirection() const {return dir;}

    point3 at(double t) const{
        return orign + t*dir;
    }
};
#endif //UNTITLED2_RAY_H
