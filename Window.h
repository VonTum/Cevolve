#pragma once
#include "Shape.h"

struct tuple {
	int x;
	int y;
};


void createWindow();
void destroyWindow();
void setShape(Shape* s);
void update();
tuple metricToPixelCoords(double x, double y);

void zoom(int deltaZoom);