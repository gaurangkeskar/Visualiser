#pragma once
#include<QString>
#include "Triangulation.h"

class Reader
{
	virtual void read(const QString& fileName, Triangulation& triangulation) = 0;
};