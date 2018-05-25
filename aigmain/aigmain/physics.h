#pragma once

#include "geometry.h"
#include <cmath>

namespace aig
{
    //Laughable static class for some physics operations. Will add Colliders later.
    class Physics
    {
        public:
        static bool IsBoundingBoxColliding(const Geometry &a, const Geometry &b);
        static void Move(Geometry *geometry, double elapsed_time);
    };
}