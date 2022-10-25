//
// Created by nathan on 5/28/2022.
//

#ifndef UNTITLED2_HITTABLE_H
#define UNTITLED2_HITTABLE_H
#include "Ray.h"
class material;
struct hitRecord{
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    bool frontFace;

    inline void setFaceNormal(const ray& r, const vec3& outwardNormal){
        frontFace = dot(r.getDirection(), outwardNormal)<0;
        normal = frontFace? outwardNormal: -outwardNormal;
    }
};
class hittable{
public:
    virtual bool hit(const ray& r, double tMin,double tMax, hitRecord& rec) const =0;
};

#endif //UNTITLED2_HITTABLE_H
