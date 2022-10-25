//
// Created by nathan on 5/29/2022.
//

#ifndef UNTITLED2_HITTABLELIST_H
#define UNTITLED2_HITTABLELIST_H
#include "hittable.h"
#include <memory>
#include <vector>

class hittableList: public hittable{
public:



    hittableList()= default;
    explicit hittableList(std::shared_ptr<hittable> object){add(object);}

    void clear() {objects.clear();}
    void add(std::shared_ptr<hittable> object) {objects.push_back(object);}

    virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const override;

    std::vector<std::shared_ptr<hittable>> objects;
};

bool hittableList::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const{

    hitRecord temp_rec;
    bool hitAnything = false;
    auto closesSoFar = tMax;

    for (const auto& object : objects){
        if(object->hit(r,tMin,closesSoFar, temp_rec)){
            hitAnything = true;
            closesSoFar = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hitAnything;
}
#endif //UNTITLED2_HITTABLELIST_H
