#include <bits/stdc++.h>

#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "rtmath.h"



using namespace std;


int frame[160][128][3];

void print() {
    int image_width = 128;
    int image_height = 160;
   cout << "P3\n" << image_width << ' ' << image_height << "\n257\n";
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
           cout << frame[j][i][0] << ' ' << frame[j][i][1] << ' ' << frame[j][i][2] << '\n';
        }
    }
}



int hit_sphere(const Vec center, int radius, const ray& r) {
    Vec oc = r.orig - center;
    int a = r.dir.lsq();
    int halfb = dot(oc, r.dir);
    int c = oc.lsq() - FPMUL(radius, radius);
    int disc = FPMUL(halfb, halfb) -FPMUL(a,c);
    if (disc < 0) {
        return -256;
        
    } else {
        return FPDIV((-halfb - FPSQRT(disc)) ,  a);
    }
}

int max_depth = 2;

Vec ray_color(const ray& r, const hittable& world, int depth) {

    if (depth == 0) {
        return Vec(0,0,0);
    }
    hit_record rec;

    // cerr<<depth<<endl;
    // cerr<<'|'<<r<<endl;
    // cerr<<depth<<endl;
    if (world.hit(r, 0, INF, rec)) {
        Vec target = rec.p + rec.normal + random_in_unit_sphere();
        // cerr<<rec.normal<<endl;
        // return 128 * (rec.normal + Vec(255,255,255));
        return 160 * rec.color +  70 * ray_color(ray(rec.p, target - rec.p), world, depth - 1); 
    }


    Vec unit_direction = unit_vector(r.dir);
    int t = FPMUL(128,(unit_direction.e[1] + 255));
    // cerr<<t<<endl;
    return (256-t)*Vec(255,255,255) + t*Vec(128, 190, 255);
}

int main() {
    srand(time(NULL));
    double aspect_ratio = 128.0 / 160.0; 
    const int image_width = 128;
    const int image_height = 160;

    // Camera

    int viewport_height = 512;
    int viewport_width = viewport_height * aspect_ratio;
    int focal_length = 256;

    Vec origin = Vec(0, 0, 200);
    Vec horizontal = Vec(viewport_width, 0, 0);
    Vec vertical = Vec(0, viewport_height, 0);
    Vec lower_left_corner = origin - horizontal/512 - vertical/512 - Vec(0, 0, focal_length);


    hittable_list world;

    world.add(make_shared<sphere>(Vec(-128,0,-256), 128, Vec(120,0,0)));
    world.add(make_shared<sphere>(Vec(128,0,-256), 128, Vec(120,120,120)));
    world.add(make_shared<sphere>(Vec(0,-100.5 * 256,-256), 100 * 256, Vec(0,120,0)));

    ray test(origin, Vec(-35, 6 ,256));
    Vec pixel_color = ray_color(test,world, max_depth);
    // Render


    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {

            // cerr<<random_in_unit_sphere()<<endl;

            
            int u = i*256 / image_width;
            int v = j*256 / image_height;
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);

            

            Vec pixel_color = ray_color(r, world, max_depth);
            // cerr<<j<<' '<<i<<endl;
            frame[j][i][0] = pixel_color.e[0];
            frame[j][i][1] = pixel_color.e[1];
            frame[j][i][2] = pixel_color.e[2];
        }
    }

    // int dr[] = {1,-1,0,0};
    // int dc[] = {0,0,1,-1};
    // for (int i = 0; i < image_height; i++) {
    //     for (int j = 0; j < image_width; j++) {
    //         int ar = 0, ag = 0, ab = 0;
    //         for (int k = 0; k < 4; k++) {
    //             int ni = i + dr[i];
    //             int nj = j + dc[j];
    //             if (ni < 0 || nj < 0 || ni >= image_height || nj >= image_width) continue;
    //             ar += frame[ni][nj][0];
    //             ag += frame[ni][nj][1];
    //             ab += frame[ni][nj][2];
    //         }

    //         frame[i][j][0] = frame[i][j][0] * 0.6 + ar * 0.1;
    //         frame[i][j][1] = frame[i][j][1] * 0.6 + ag * 0.1;
    //         frame[i][j][2] = frame[i][j][2] * 0.6 + ab * 0.1;
    //     }
    // }


    print();




}
