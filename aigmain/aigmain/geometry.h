#pragma once

namespace aig
{
    class Vector2
    {
        public:
        Vector2() : x(0), y(0) {}
        Vector2(double x, double y) : x(x), y(y) {}

        double x = 0.;
        double y = 0.;
    };

    class Geometry
    {
        public:
        Geometry();
        Geometry(Vector2 p, Vector2 bounding, Vector2 vel);


        Vector2 position;
        Vector2 bounding_box_extent;
        Vector2 velocity;
    };

    class Rectangle : public Geometry
    {
        
    };

    class Circle : public Geometry
    {
        public:
        Circle();
        Circle(double r);

        double radius = 0.0;
        void SetRadius(double r);
    };
}