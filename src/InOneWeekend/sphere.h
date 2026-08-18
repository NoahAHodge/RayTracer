#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) {
        vec3 oc = center - r.origin(); // C - Q
        // streamlined quadratic equation components
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc); // where h = b/-2
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c;

        if (discriminant < 0) {
            return false; // no intersection
        }
        
        // find nearest intersection in range
        auto sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || root >= ray_tmax) {
            root = (h + sqrtd) / a; // need to check pos root as well 
            if (root <= ray_tmin || root >= ray_tmax)
                return false; 
        }

        // set record for interesection
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        return true;
    }

    private:
    point3 center;
    double radius;
};

#endif