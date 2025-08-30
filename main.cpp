#include <iostream>

#include "raylib.h"
#include "raymath.h"
#include "TGeometry.h"
#include "TPhotonRay.h"

inline float cross(const Vector2& a, const Vector2& b) {
    return a.x * b.y - a.y * b.x;
}

struct ResV
{
    Vector2 pt;
    Vector2 normal;
};

std::optional<ResV> result(Vector2 a, Vector2 b, TPhotonRay ray)
{
    Vector2 r = ray.direction;
    Vector2 s = {b.x - a.x, b.y - a.y};

    float rxs = cross(r, s);
    float qpxr = cross({ a.x - ray.origin.x, a.y - ray.origin.y }, r);

    //if (rxs == 0) {return std::nullopt;}

    float t = cross({ a.x - ray.origin.x, a.y - ray.origin.y }, s) / rxs;
    float u = qpxr / rxs;


    if (t >= 0 && u >= 0 && u <= 1)
    {

        return ResV{Vector2{ ray.origin.x + t * r.x, ray.origin.y + t * r.y }, Vector2Normalize({-s.y, s.x})};
    }

    return std::nullopt;
}


std::optional<ResV> reflection_pt(TPhotonRay ray, TGeometry shape)
{
    std::vector<ResV> pts;
    pts.reserve(shape.vertices.size());

    for (int i = 1; i < 5; i++)
    {
        Vector2 a = shape.vertices[i-1];
        Vector2 b = shape.vertices[i == 4 ? 0 : i];

        auto res = result(a, b, ray);

        if (res.has_value())
        {
            pts.push_back(res.value());
        }

    }
    std::optional<ResV> result = std::nullopt;
    float mindist = std::numeric_limits<float>::max();

    for (ResV p : pts)
    {
        if (Vector2LengthSqr(Vector2Subtract(ray.origin, p.pt)) < mindist)
        {
            mindist = Vector2LengthSqr(Vector2Subtract(ray.origin, p.pt));
            result = p;
        }
    }

    return result;

}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "ray tracing example");

    SetTargetFPS(40);

    float quality = 1;

    Vector2 center = { (screenWidth / 2.0f) -300, screenHeight / 2.0f -200}; //400, 225

    TGeometry shape({{400, 400}, {200, 200}, {600, 200}, {500, 400}});

    int fac = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);



        for (int angle = 20; angle < 90*quality; angle += 2)
        {
            float radians = angle * PI/(180.0f*quality);
            Vector2 directionVector = Vector2Normalize({std::cos(radians), std::sin(radians)});
            TPhotonRay ray{center, directionVector};

            bool refl = true;
            Vector2 reflpt;
            auto res = reflection_pt(ray, shape);
            if (res.has_value())
            {
                reflpt = res.value().pt;
            }
            else {refl = false;}

            while (ray.energy > 0)
            {


                if (refl)
                {
                    if (Vector2LengthSqr(Vector2Subtract(ray.head, reflpt)) < 1)
                    {
                        float d = Vector2DotProduct(ray.direction, res.value().normal);
                        ray.direction = {
                            ray.direction.x - 2 * d * res.value().normal.x,
                            ray.direction.y - 2 * d * res.value().normal.y
                        };

                        ray.origin = ray.head;

                        ///ray.direction = Vector2Rotate(ray.direction, res.value().angle);
                        ray.direction = Vector2Normalize(ray.direction);
                        ray.energy = floor(ray.energy*0.75);

                        res = reflection_pt(ray, shape);
                        if (res.has_value())
                        {
                            reflpt = res.value().pt;
                        }
                        else {refl = false;}
                    }
                }
                else
                {
                    //std::cout << false << std::endl;
                }

                ray.move();
            }
            //std::cout << ray.direction.x << "," << ray.direction.y << "\n";
        }

        for (int i = 1; i < 5; i++)
        {
            Vector2 a = shape.vertices[i-1];
            Vector2 b = shape.vertices[i == 4 ? 0 : i];
            DrawLine(a.x, a.y, b.x, b.y, BLUE);
        }

        EndDrawing();

        center = {center.x + 0.5f, center.y + 0.5f};
        fac++;

    }

    CloseWindow();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
