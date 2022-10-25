//
// Created by nathan on 6/10/2022.
//

#ifndef UNTITLED2_RANDOMS_H
#define UNTITLED2_RANDOMS_H



inline double randomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max)
{
    return min + (max-min) * randomDouble();
}

inline static vec3 random(){
    return {randomDouble(), randomDouble(), randomDouble()};
}

inline static vec3 random(double min, double max){
    return {randomDouble(min,max),randomDouble(min,max),randomDouble(min,max)};
}

inline vec3 randomInUnitSphere()
{
    while(true)
    {
        vec3 p = random(-1,1);
        if (p.length_squared() <1)
        {
            return p;
        }
    }
}
vec3 randomUnitVector(){
    return unit_vector(randomInUnitSphere());
}
#endif //UNTITLED2_RANDOMS_H
