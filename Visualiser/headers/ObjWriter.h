#pragma once
#include "Writer.h"
#include<QVector>

class ObjWriter : public Writer
{
public:
	ObjWriter();
	~ObjWriter();

	void Write(const std::string& filename, const Triangulation& trianglation);
	std::string formulateText(const Triangulation& triangulation, const Point& point, QVector<Point>&);
	std::string formulateNormal(const Triangulation& triangulation, const Point& point, QVector<Point>&);
	std::string formulateFace(const Triangle& tri, QVector<Point>&, QVector<Point>&);
};
