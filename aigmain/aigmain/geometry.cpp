#include "geometry.h"

aig::Geometry::Geometry()
{
}

aig::Geometry::Geometry(Vector2 p, Vector2 bounding, Vector2 vel)
    : position(p), bounding_box_extent(bounding), velocity(vel)
{
}

aig::Circle::Circle()
{
}

aig::Circle::Circle(double r)
{
    SetRadius(r);
}

void aig::Circle::SetRadius(double r)
{
    bounding_box_extent.x = r;
    bounding_box_extent.y = r;
}
