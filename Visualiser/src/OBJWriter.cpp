#include "ObjWriter.h"
#include<fstream>
#include<iomanip>

ObjWriter::ObjWriter() {

}

ObjWriter::~ObjWriter()
{
}

void ObjWriter::Write(const std::string& filename, const Triangulation& triangulation)
{
    QVector<Point> uniqueData;
    QVector<Point> uniqueNormal;
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const Triangle& tri : triangulation.Triangles) {
            outfile << std::fixed << std::setprecision(6)
                << formulateText(triangulation, tri.P3(), uniqueData)
                << formulateText(triangulation, tri.P2(), uniqueData)
                << formulateText(triangulation, tri.P1(), uniqueData);
        }
        for (const Triangle& tri : triangulation.Triangles) {
            outfile << std::fixed << std::setprecision(6)
                << formulateNormal(triangulation, tri.Normal(), uniqueNormal);
        }
        for (const Triangle& tri : triangulation.Triangles) {
            outfile << formulateFace(tri, uniqueNormal, uniqueData)
                << "\n";
        }
    }
}

std::string ObjWriter::formulateText(const Triangulation& triangulation, const Point& point, QVector<Point>& uniqueData)
{
    if (!uniqueData.contains(point)) {
        uniqueData.push_back(point);
        double x = triangulation.UniqueNumbers[point.X()];
        double y = triangulation.UniqueNumbers[point.Y()];
        double z = triangulation.UniqueNumbers[point.Z()];


        return "v " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "\n";
    }
    return "";
}

std::string ObjWriter::formulateNormal(const Triangulation& triangulation, const Point& point, QVector<Point>& uniqueNormal)
{
    if (!uniqueNormal.contains(point)) {
        uniqueNormal.push_back(point);
        double x = triangulation.UniqueNumbers[point.X()];
        double y = triangulation.UniqueNumbers[point.Y()];
        double z = triangulation.UniqueNumbers[point.Z()];

        return "vn " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "\n";
    }
    return "";
}

std::string ObjWriter::formulateFace(const Triangle& tri, QVector<Point>& uniqueNormal, QVector<Point>& uniqueData)
{
    std::string data = "f ";
    for (Point point : {tri.P1(), tri.P2(), tri.P3()}) {
        int v = uniqueData.indexOf(point) + 1;
        int n = uniqueNormal.indexOf(tri.Normal()) + 1;

        data += std::to_string(v);
        data += "//";
        data += std::to_string(n);
        data += " ";
    }
    return data;
}