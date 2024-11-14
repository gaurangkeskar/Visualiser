#include "STLReader.h"
#include "Point.h"
#include "Reader.h"
#include<vector>
#include<map>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define TOLERANCE 0.0000001

STLReader::STLReader()
{
}

STLReader::~STLReader()
{
}


bool STLReader::operator()(double a, double b) const
{
    return fabs(a - b) > TOLERANCE ? a < b : false;
}

void STLReader::read(const QString& fileName, Triangulation& triangulation)
{
    std::map<double, int, STLReader> uniqueValueMap;
    double xyz[3];
    std::vector<int> pointIndices;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line1;
    do
    {
        line1 = in.readLine();
        if (line1.contains("normal") || line1.contains("vertex"))
        {
            if (line1.contains("normal"))
            {
                QStringList list = line1.split(" ", QString::SkipEmptyParts);
                for (int i = 0; i < 3; i++)
                {
                    xyz[i] = list[i + 2].toDouble();
                }
            }
            else if (line1.contains("vertex"))
            {
                QStringList list = line1.split(" ", QString::SkipEmptyParts);
                for (int i = 0; i < 3; i++)
                {
                    xyz[i] = list[i + 1].toDouble();
                }
            }
            for (int i = 0; i < 3; i++)
            {
                auto pair = uniqueValueMap.find(xyz[i]);
                if (pair == uniqueValueMap.end())
                {
                    triangulation.UniqueNumbers.push_back(xyz[i]);
                    uniqueValueMap[xyz[i]] = triangulation.UniqueNumbers.size() - 1;
                    pointIndices.push_back(triangulation.UniqueNumbers.size() - 1);
                }
                else
                {
                    pointIndices.push_back(pair->second);
                }
            }
            if (pointIndices.size() == 12)
            {
                Point normal = Point(pointIndices[0], pointIndices[1], pointIndices[2]);
                Point p1 = Point(pointIndices[3], pointIndices[4], pointIndices[5]);
                Point p2 = Point(pointIndices[6], pointIndices[7], pointIndices[8]);
                Point p3 = Point(pointIndices[9], pointIndices[10], pointIndices[11]);
                Triangle t(normal, p1, p2, p3);
                triangulation.Triangles.push_back(t);
                pointIndices.clear();
            }
        }
    } while (!line1.isNull());
}