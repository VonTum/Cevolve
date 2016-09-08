#include "physics.h"
#include "Config.h"

#include "math.h"

void tickShape(Shape s, double time) {
	//GRAVITY
	for (int i = 0; i < s.nodeCount; i++) {
		s.nodes[i].fx = 0;
		s.nodes[i].fy = 0;

	}
	
	
	for(int i = 0; i < s.linkCount; i++) {
		Link link = s.links[i];

		double dx = link.node1->x - link.node2->x;
		double dy = link.node1->y - link.node2->y;


		
		double actualLength = sqrt(dx*dx + dy*dy);

		double force = link.strength * (link.preferredLength - actualLength);

		double fx = force * dx / actualLength;
		double fy = force * dy / actualLength;

		link.node1->fx += fx;
		link.node1->fy += fy;

		link.node2->fx -= fx;
		link.node2->fy -= fy;
		
	}
	


	//update velocities
	for(int i = 0; i < s.nodeCount; i++) {
		s.nodes[i].vx += time * s.nodes[i].fx / s.nodes[i].mass;
		s.nodes[i].vy += time * s.nodes[i].fy / s.nodes[i].mass;


		s.nodes[i].x += time * s.nodes[i].vx;
		s.nodes[i].y += time * s.nodes[i].vy;

	}
	int a = 1; 

	return;
}
