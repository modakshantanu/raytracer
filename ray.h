#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include <iostream>


class ray {
    public:
        Vec orig, dir;
    ray() {}
    ray(const Vec& origin, const Vec& direction) :
        orig(origin), dir(direction) {}
    
    Vec at(int t) const {
        return orig + t * dir;
    }

};

inline std::ostream& operator<<(std::ostream &out, const ray &v) {
    return out << v.orig <<" | "<<v.dir; 
}

#endif