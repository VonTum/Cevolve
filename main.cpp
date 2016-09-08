#include "SDL.h"
#include "stdio.h"
#include <iostream>

#include "Shape.h"
#include "Window.h"
#include "Physics.h"


Node createNode(double x, double y, double friction, double mass) {
	Node n;
	n.x = x;
	n.y = y;
	n.friction = friction;
	n.mass = mass;
	n.vx = 0;
	n.vy = 0;
	n.fx = 0;
	n.fy = 0;
	return n;
}
Link createLink(Node* node1, Node* node2, double preferredLength, double strength) {
	Link l;
	l.node1 = node1;
	l.node2 = node2;
	l.preferredLength = preferredLength;
	l.strength = strength;
	return l;
}


int main(int argc, char* args[]) {
	Node nodes[6];
	Link links[9];

	
	nodes[0] = createNode(1, 1.5, 0, 1);
	nodes[1] = createNode(2, 1, 0, 1);
	nodes[2] = createNode(1.5, 2, 0, 1);
	nodes[3] = createNode(2, 2, 0, 1);
	nodes[4] = createNode(3, 2, 0, 1);
	nodes[5] = createNode(3, 3, 0, 1);

	links[0] = createLink(&nodes[0], &nodes[1], 1, 10);
	links[1] = createLink(&nodes[0], &nodes[2], 1, 1);
	links[2] = createLink(&nodes[1], &nodes[2], 1, 1);
	links[3] = createLink(&nodes[1], &nodes[3], 1, 1);
	links[4] = createLink(&nodes[1], &nodes[4], 1, 10);
	links[5] = createLink(&nodes[2], &nodes[4], 2, 1);
	links[6] = createLink(&nodes[4], &nodes[3], 1, 1);
	links[7] = createLink(&nodes[0], &nodes[3], 1.5, 1);
	links[8] = createLink(&nodes[5], &nodes[2], 1.8, 2);
	

	Shape s;
	s.nodes = nodes;
	s.links = links;
	s.nodeCount = 6;
	s.linkCount = 9;

	createWindow();

	setShape(&s);
	update();

	Node* selectedNode = NULL;
	
	SDL_Event e;
	while(true) {
		

		bool quit = false;
		while(SDL_PollEvent(&e)) {

			switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_MOUSEWHEEL:
				zoom(e.wheel.y);
				std::cout << "Zoomed:";
				std::cout << "\n";
				break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					s.links[1].preferredLength = 2;
					break;
				}


				break;

			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					s.links[1].preferredLength = 1;
					break;
				}
				break;

			
			case SDL_MOUSEBUTTONUP:
				selectedNode = NULL;
				break;
			case SDL_MOUSEBUTTONDOWN:
				// WIP

				/*
				{
					Node* closestNode = NULL;
					double closestDist = 2e30;


					for (int i = 0; i < s.nodeCount; i++) {
						tuple nodePos = metricToPixelCoords(s.nodes[i].x, s.nodes[i].y);
						double distance = (e.button.x - nodePos.x) * (e.button.x - nodePos.x) + (e.button.y - nodePos.y) * (e.button.y - nodePos.y);
						if (distance < closestDist) {
							closestNode = &s.nodes[i];
							closestDist = distance;

						}
					}
					selectedNode = closestNode;
				}
				
				
				
				//no break to update directly
			case SDL_MOUSEMOTION:
				if (selectedNode != NULL) {
					tuple MousePos = pixelToMetricCoords(e.motion.x, e.motion.y);
					selectedNode->x = MousePos.x;
					selectedNode->y = MousePos.y;
				}
				
				*/


				break;
			}
			

		}
		if(quit) {
			break;
		}
		
		SDL_Delay(1);
		tickShape(s, 0.005);
		update();
		


	}

	destroyWindow();
	return 0;
}