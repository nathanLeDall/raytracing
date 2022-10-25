//
// Created by nathan on 6/1/2022.
//

#ifndef UNTITLED2_CAMERA_H
#define UNTITLED2_CAMERA_H
#include "rtconstants.h"
//#include "Ray.h"
class camera{
    point3 origin;
    point3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u,v,w;
    double lensRadius;
public:
    camera(
            point3 lookfrom, point3 lookat, vec3 vup,
            double vfov, double aspectRatio, double aperture, double focusDist
            ) {

        const double theta = degToRad(vfov);

        // camera
        double h = tan(theta/2);
        double viewPortHeight = 2.0*h;
        double viewPortWidth = aspectRatio * viewPortHeight;
        double focalLength = 1.0;

        w = unit_vector(lookfrom-lookat);
        u = unit_vector(cross(vup,w));
        v = cross(w,u);

        origin = lookfrom;
        horizontal = focusDist * viewPortWidth * u;
        vertical = focusDist*viewPortHeight * v;
        lowerLeftCorner = origin-horizontal/2 - vertical/2 - focusDist*w;
        lensRadius = aperture/2;
    }

    ray get_ray(double s, double t) const{
        vec3 rd = lensRadius * randomInUnitDisk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin+offset, lowerLeftCorner + s*horizontal+ t*vertical - origin - offset);
    }
};
#endif //UNTITLED2_CAMERA_H
