//
// Created by Sid B on 29/08/25.
//

#pragma once

#include "raylib.h"


class TPhotonRay
{
public:
    TPhotonRay(Vector2 origin, Vector2 direction)
        : origin{ origin }, head(origin), direction(direction) {;}

    Vector2 origin;
    Vector2 head;
    Vector2 direction;

    unsigned char energy = 255; //0 - 255

    void move();
};

