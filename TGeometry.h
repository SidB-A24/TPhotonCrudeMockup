//
// Created by Sid B on 29/08/25.
//
#pragma once
#include <vector>

#include "raylib.h"

class TGeometry
{
    public:
    TGeometry(const std::vector<Vector2>& vertices): vertices(vertices) {};

    std::vector<Vector2> vertices;
};


