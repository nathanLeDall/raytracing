//
// Created by nathan on 5/24/2022.
//

#ifndef UNTITLED2_COLOUR_H
#define UNTITLED2_COLOUR_H

#include <ostream>
#include "vec3.h"
#include "rtconstants.h"

void writeColour(std::ostream &out, color pixelCol, int samplesPerPixel){
    double r = pixelCol.x();
    double g = pixelCol.y();
    double b = pixelCol.z();
    //divide each colour by number of samples
    double scale = 1.0/ samplesPerPixel;
    r = sqrt(scale*r);
    g = sqrt(scale*g);
    b = sqrt(scale*b);

    // Write the translated [0,255] value of each color component

    out << static_cast<int >(256 * clamp(r,0.0,0.999)) << ' '
        << static_cast<int >(256 * clamp(g,0.0,0.999)) << ' '
        << static_cast<int >(256 * clamp(b,0.0,0.999)) << '\n';
};

color* writeColour(color pixelCol, int samplesPerPixel){

    double r = pixelCol.x();
    double g = pixelCol.y();
    double b = pixelCol.z();
    //divide each colour by number of samples
    double scale = 1.0/ samplesPerPixel;
    r = sqrt(scale*r);
    g = sqrt(scale*g);
    b = sqrt(scale*b);

    // Write the translated [0,255] value of each color component

    auto tmp = new color{(256 * clamp(r,0.0,0.999)),
                             (256 * clamp(g,0.0,0.999)),
                             (256 * clamp(b,0.0,0.999))};
    return tmp;
};
#endif //UNTITLED2_COLOUR_H
