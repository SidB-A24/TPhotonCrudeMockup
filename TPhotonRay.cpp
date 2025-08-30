//
// Created by Sid B on 29/08/25.
//

#include "TPhotonRay.h"

#include <cmath>

void TPhotonRay::move()
{
    head.x += direction.x;
    head.y += direction.y;

    Color color{255, 255, 255, energy};

    DrawPixel(floor(head.x), floor(head.y), color);
    DrawPixel(floor(origin.x), floor(origin.y), RED);

    if (energy > 2) { energy -= 1;}
    else {energy = 0;}
}
