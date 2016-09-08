#include "physics.h"
#include "Config.h"



void tickShape(Shape* s, double time) {
	//GRAVITY
	
	if (settings::GRAVITY != 0) {
		for (int i = 0; i < s->nodeCount; i++) {
			s->nodes[i].ay -= time * settings::GRAVITY;
		}
	}
	

	


	//update velocities
	for (int i = 0; i < s->nodeCount; i++) {
		s->nodes[i].vx += time * s->nodes[i].ax;
		s->nodes[i].vy += time * s->nodes[i].ay;

		s->nodes[i].x += time * s->nodes[i].vx;
		s->nodes[i].y += time * s->nodes[i].vy;

	}
}
