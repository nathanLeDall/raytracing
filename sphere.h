//
// Created by nathan on 5/28/2022.
//

#ifndef UNTITLED2_SPHERE_H
#define UNTITLED2_SPHERE_H
#include "hittable.h"
#include "vec3.h"
class sphere : public hittable{
public:
    point3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;

    sphere() {}
    sphere(point3 cen, double r, std::shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(m)
    {};

    virtual bool hit(const ray& r, double tMin,double tMax, hitRecord& rec)const;
};
bool sphere::hit(const ray& r, double tMin,double tMax, hitRecord& rec) const{

    vec3 oc = r.getOrign() - center;
    auto a = r.getDirection().length_squared();
    auto half_b = dot(oc, r.getDirection());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant<0) return false;
    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd)/a;
    if (root<tMin || tMax < root){
        root = (-half_b - sqrtd)/a;
        if (root < tMin || tMax < root){
            return false;
        }
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r,outwardNormal);
    rec.mat_ptr = mat_ptr;
    return true;
}
#endif //UNTITLED2_SPHERE_H
