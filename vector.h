#ifndef VEC
#define VEC

#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

#define FPMUL(a,b) ((a * b) >> 8)
#define FPDIV(a,b) ((a << 8) / b)
#define FPSQRT(a) ((int) (sqrt(a << 8)))

inline int unitrandom() {
    
    return (rand() & 0x7f) - 127;
}



class Vec {
    public:
    int e[3];
    Vec() : e{0,0,0} {}
    Vec(int a, int b, int c) : e{a,b,c} {}

    Vec operator-() const {return Vec(-e[0],-e[1],-e[2]);}
    
    Vec& operator+=(const Vec &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec& operator*=(const int t) {
        e[0] = FPMUL(e[0], t);
        e[1] = FPMUL(e[1], t);
        e[2] = FPMUL(e[2], t);
        return *this;
    }

    Vec& operator/=(const int t) {
        e[0] = FPDIV(e[0], t);
        e[1] = FPDIV(e[1], t);
        e[2] = FPDIV(e[2], t);
        return *this;
    }

    int lsq() const {
        return FPMUL(e[0],e[0]) + FPMUL(e[1],e[1]) + FPMUL(e[2], e[2]);
    }

    // TODO : OPTIMISE THIS?
    int len() const {
        return FPSQRT(lsq());
    }

    inline static Vec random() {
        return Vec(unitrandom(), unitrandom(), unitrandom());
    }


};



inline std::ostream& operator<<(std::ostream &out, const Vec &v) {
    return out << v.e[0]/256.0 << ' ' << v.e[1]/256.0 << ' ' << v.e[2]/256.0;
    
}

inline Vec operator+(const Vec &u, const Vec &v) {
    return Vec(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec operator-(const Vec &u, const Vec &v) {
    return Vec(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec operator*(const Vec &u, const Vec &v) {
    return Vec(FPMUL(u.e[0],v.e[0]), FPMUL(u.e[1], v.e[1]), FPMUL(u.e[2] , v.e[2]));
}

inline Vec operator*(int t, const Vec &v) {
    return Vec(FPMUL(t,v.e[0]), FPMUL(t,v.e[1]), FPMUL(t,v.e[2]));
}

inline Vec operator*(const Vec &v, int t) {
    return t * v;
}

inline Vec operator/(Vec v, int t) {
    return FPDIV(256,t) * v;
}

inline int dot(const Vec &u, const Vec &v) {
    return FPMUL(u.e[0] , v.e[0]) 
         + FPMUL(u.e[1] , v.e[1])
         + FPMUL(u.e[2] , v.e[2]);
}

inline Vec cross(const Vec &u, const Vec &v) {
    return Vec(FPMUL(u.e[1] , v.e[2]) - FPMUL(u.e[2] , v.e[1]),
                FPMUL(u.e[2] , v.e[0]) - FPMUL(u.e[0] , v.e[2]),
                FPMUL(u.e[0] , v.e[1]) - FPMUL(u.e[1] , v.e[0]));
}

inline Vec unit_vector(Vec v) {

    // cerr<<v<<' '<<v.len()<<endl;
    // cerr<<v / v.len() << endl;
    return v / v.len();
}

Vec random_in_unit_sphere() {
    while (true) {
        auto p = Vec::random();
        if (p.lsq() >= 250) continue;
        return p;
    }
}

#endif