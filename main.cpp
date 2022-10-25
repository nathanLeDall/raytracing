#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include "Colour.h"
#include "rtconstants.h"
#include "Camera.h"


vec3 randomInHemisphere(const vec3& normal)
{
    vec3 inUnitsphere = randomInUnitSphere();
    if(dot(inUnitsphere,normal)>0.0){
        return inUnitsphere;
    }
    return -inUnitsphere;
}
color rayColor(const ray& r, const hittable& world, int depth){
    hitRecord rec;
    if (depth<=0){
        return {0,0,0};
    }

    if (world.hit(r,0.001,infinity,rec)){
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r,rec,attenuation, scattered)){
            return attenuation * rayColor(scattered,world,depth-1);
        }
        return {0,0,0};
    }

    vec3 unitDirection = unit_vector(r.getDirection());
    auto t = 0.5*(unitDirection.y() + 1.0);
    return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

void trace(std::vector<color *>* vect, const int tmp, const camera& cam, const hittableList& world, const int image_width,const int tmp2, const int maxDepth, const int samplesPerPixel, const int image_height){
    for (int j = tmp; j > tmp2; --j) {
        //std::cerr << "\rscans remaining: "<< j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixelColour(0,0,0);
            for (int k = 0; k<samplesPerPixel; k++)
            {
                double u = double(i+randomDouble())/ (image_width-1);
                double v = double(j+randomDouble())/ (image_height-1);
                ray r = cam.get_ray(u,v);
                pixelColour += rayColor(r,world,maxDepth);
            }
            vect->push_back(writeColour(pixelColour, samplesPerPixel));
            
        }
    }
}

int main() {

    // Image
    const auto aspectRatio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspectRatio);
    const int samplesPerPixel = 50;
    const int maxDepth = 30;
    // World


    hittableList world = randomScene(); // <- a huge scene with a lot of objects takes 
    //hittableList world = scene1(); //<- a smaller scene with only 4 objects takes about 5.5 secs to process on my machine



    // camera
    point3 lookfrom(5,1,8);
    point3 lookat(0,0,0);
    vec3 vup(0,0.1,0);
    auto distToFocus = 8.0;
    auto aperture = 0.1;
    camera cam(lookfrom, lookat, vup,12.0, aspectRatio,aperture,distToFocus);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    /*for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rscans remaining: "<< j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixelColour(0,0,0);
            for (int k = 0; k<samplesPerPixel; k++)
            {
                double u = double(i+randomDouble())/ (image_width-1);
                double v = double(j+randomDouble())/ (image_height-1);
                ray r = cam.get_ray(u,v);
                pixelColour += rayColor(r,world,maxDepth);
            }
            writeColour(std::cout, pixelColour, samplesPerPixel);
        }
    }*/

    auto* f1 = new std::vector<color*>{};
    auto* f2 = new std::vector<color*>{};
    auto* f3 = new std::vector<color*>{};
    auto* f4 = new std::vector<color*>{};
    auto* f5 = new std::vector<color*>{};
    auto* f6 = new std::vector<color*>{};
    auto* f7 = new std::vector<color*>{};
    auto* f8 = new std::vector<color*>{};
    auto* f9 = new std::vector<color*>{};
    auto* f10 = new std::vector<color*>{};

    std::thread t1(trace,f1, 225, cam, world, image_width, 205, maxDepth, samplesPerPixel,image_height);
    std::thread t2(trace,f2, 205, cam, world, image_width, 195, maxDepth, samplesPerPixel,image_height);
    std::thread t3(trace,f3, 195, cam, world, image_width, 160, maxDepth, samplesPerPixel,image_height);
    std::thread t4(trace,f4, 160, cam, world, image_width, 145, maxDepth, samplesPerPixel,image_height);
    std::thread t5(trace,f5, 145, cam, world, image_width, 125, maxDepth, samplesPerPixel,image_height);
    std::thread t6(trace,f6, 125, cam, world, image_width, 105, maxDepth, samplesPerPixel,image_height);
    std::thread t7(trace,f7, 105, cam, world, image_width, 85, maxDepth, samplesPerPixel,image_height);
    std::thread t8(trace,f8, 85, cam, world, image_width, 65, maxDepth, samplesPerPixel,image_height);
    std::thread t9(trace,f9, 65, cam, world, image_width, 45, maxDepth, samplesPerPixel,image_height);
    std::thread t10(trace,f10, 45, cam, world, image_width, 0, maxDepth, samplesPerPixel,image_height);

    if(t1.joinable())
    {
        t1.join();
    }
    if(t2.joinable())
    {
        t2.join();
    }
    if(t3.joinable())
    {
        t3.join();
    }
    if(t4.joinable())
    {
        t4.join();
    }
    if(t5.joinable())
    {
        t5.join();
    }
    if(t6.joinable())
    {
        t6.join();
    }
    if(t7.joinable())
    {
        t7.join();
    }
    if(t8.joinable())
    {
        t8.join();
    }
    if(t9.joinable())
    {
        t9.join();
    }
    if(t10.joinable())
    {
        t10.join();
    }

    for (auto i: *f1)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f2)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f3)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f4)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f5)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f6)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f7)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f8)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f9)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    for (auto i: *f10)
    {
        std::cout << static_cast<int>(i->x()) << ' ' << static_cast<int>(i->y()) << ' ' << static_cast<int>(i->z()) << '\n';
    }
    auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::cerr << end-start;
}