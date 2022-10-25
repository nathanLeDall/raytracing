//
// Created by nathan on 6/8/2022.
//

#ifndef UNTITLED2_MATERIAL_H
#define UNTITLED2_MATERIAL_H
#include "rtconstants.h"
#include "randoms.h"

struct hitRecord;
class material{
public:
    virtual bool scatter(
            const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered
            ) const = 0;
};

class lambertian : public material{

public:
    color albedo;

    explicit lambertian(const color& a): albedo(a){}

    bool scatter(
            const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered
            ) const override {
        auto scatterDirection = rec.normal + randomUnitVector();

        if (scatterDirection.nearZero()){
            scatterDirection = rec.normal;
        }

        scattered = ray(rec.p, scatterDirection);
        attenuation = albedo;
        return true;
    }
};

class metal : public material {
public:
    color albedo;
    double fuzz;

    metal(const color& a,double f) : albedo(a), fuzz(f){}

    bool scatter(
            const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered
    ) const override {
        vec3 reflected = reflect(unit_vector(r_in.getDirection()), rec.normal);
        scattered = ray(rec.p, reflected+ fuzz*randomInUnitSphere());
        attenuation = albedo;
        return (dot(scattered.getDirection(), rec.normal) > 0);
    }
};

class dielectric : public material{

public:
    double ir;

    explicit dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

    bool scatter(
            const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered
    ) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double refractionRatio = rec.frontFace? (1.0/ir) : ir;

        vec3 unitDirection = unit_vector(r_in.getDirection());
        double cosTheta = fmin(dot(-unitDirection, rec.normal),1.0);
        double sinTheta = sqrt(1.0-cosTheta*cosTheta);

        bool cannotRefract = refractionRatio*sinTheta>1.0;
        vec3 direction;
        if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble()){
            direction = reflect(unitDirection, rec.normal);
        } else{
            direction = refract(unitDirection, rec.normal, refractionRatio);
        }

        scattered = ray(rec.p, direction);
        return true;
    }
private:
    static double reflectance(double cosine, double refIdx){
        auto r0 = (1-refIdx) / (1+refIdx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1-cosine),5);
    }
};
#endif //UNTITLED2_MATERIAL_H
