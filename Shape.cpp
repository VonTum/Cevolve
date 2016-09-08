#include "Shape.h"

#include <math.h>

double getLinkLength(const Link link) {
	double dx = (link.node1->x - link.node2->x);
	double dy = (link.node1->y - link.node2->y);
	return sqrt(dx*dx + dy*dy);
	
}


