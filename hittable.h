#ifndef HITTABLE_H
#define HITTABLE_H


#include "ray.h"
#include "vector.h"



struct hit_record {
    Vec p;
    Vec normal;
    int t;
    bool front_face;
    Vec color;

    inline void set_face_normal(const ray& r, const Vec& outward_nomral) {
        front_face = dot(r.dir, outward_nomral) < 0;
        normal = front_face ? outward_nomral : -outward_nomral;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, int t_min, int t_max, hit_record& rec) const = 0;
};

#endif
