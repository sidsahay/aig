#pragma once

#include "geometry.h"
#include <cmath>

namespace aig
{
    class Physics
    {
        static bool IsBoundingBoxColliding(const Geometry &a, const Geometry &b);
        static void Move(Geometry *geometry, double elapsed_time);
    };
}