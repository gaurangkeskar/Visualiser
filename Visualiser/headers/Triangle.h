#pragma once
#include "point.h"

class Triangle
{
    // Three points representing the vertices of the triangle
private:
    Point p1;
    Point p2;
    Point p3;
    Point normal;

public:
    Triangle(Point normal, Point p1, Point p2, Point p3);
    ~Triangle();

    // Getter functions to access the private members 
    Point P1() const;
    Point P2() const;
    Point P3() const;
    Point Normal() const;

};