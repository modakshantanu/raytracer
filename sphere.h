#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vector.h"

class sphere : public hittable {
    public:
        sphere() {}
        sphere(Vec cen, int r, Vec c) : center(cen), radius(r), color(c) {};

        virtual bool hit(
            const ray& r, int t_min, int t_max, hit_record& rec) const override;

    public:
        Vec center;
        int radius;
        Vec color;
};

bool sphere::hit(const ray& r, int t_min, int t_max, hit_record& rec) const {
    Vec oc = r.orig - center;
    int a = r.dir.lsq();
    int halfb = dot(oc, r.dir);
    int c = oc.lsq() - FPMUL(radius, radius);
    int disc = FPMUL(halfb, halfb) - FPMUL(a,c);

    if (disc < 0) {
        return false;
        
    } 
    int sqrd = FPSQRT(disc);

    int root = FPDIV(-halfb -sqrd , a);
    // if (t_max < root) {
    //     cerr<<t_max<<' '<<root<<endl;
    // }
    if (root < t_min || t_max < root) {
        root = FPDIV(-halfb + sqrd, a);
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    // if (root < 10 && root >= 0) {
        
    //     cerr<<root<<endl;
    //     cerr<<r<<endl;
    //     cerr<<r.at(root)<<endl;
    // }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec outward_nomral = (rec.p - center)/ radius; 
    rec.set_face_normal(r, outward_nomral);
    rec.color = color;

    return true;
}

#endif