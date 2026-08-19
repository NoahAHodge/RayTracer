#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "const.h"

class sphere : public hittable {
    public:
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
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
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a; // need to check pos root as well 
            if (!ray_t.surrounds(root))
                return false; 
        }

        // set record for interesection
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

    private:
    point3 center;
    double radius;
};

#endif