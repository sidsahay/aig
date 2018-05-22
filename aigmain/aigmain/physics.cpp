#include "physics.h"

bool aig::Physics::IsBoundingBoxColliding(const Geometry & a, const Geometry & b)
{
    return std::abs(a.position.x - b.position.x) < (a.bounding_box_extent.x / 2 + b.bounding_box_extent.x / 2)
        && std::abs(a.position.y - b.position.y) < (a.bounding_box_extent.y / 2 + b.bounding_box_extent.y / 2);
}

void aig::Physics::Move(Geometry * geometry, double elapsed_time)
{
    geometry->position.x += geometry->velocity.x * elapsed_time;
    geometry->position.y += geometry->velocity.y * elapsed_time;
}
