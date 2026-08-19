#include "const.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

// blue to white gradient depending on a ray's y coordinate
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)){
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    // auto a = 0.5 * (unit_direction.x() + 1.0); // depending on ray's x coordinate
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main(){

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // clac image height, min 1
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World
    
    hittable_list world;
    // previous centered circle
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    // ground
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    // find real ratio as rounding/min 1 can alter from idea aspect ratio
    auto viewport_width = viewport_height * (double (image_width) / image_height);
    auto camera_center = point3(0,0,0);

    // left to right and top to bottom viewport vectors 
    auto viewport_u = vec3(viewport_width, 0, 0); // left to right
    auto viewport_v = vec3(0, -viewport_height, 0);  // top to bottom

    // vertical and horizontal delta vectors between individual pixels
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // location of upper left pixel
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length)
        - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanLines remaining: " << (image_height-j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout , pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}