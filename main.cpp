#include "SDL.h"
#include "stdio.h"
#include <iostream>

#include "Shape.h"
#include "Window.h"
#include "Physics.h"



int main(int argc, char* args[]) {
	Node nodes[3];
	Link links[3];

	nodes[0].x = 0.2;
	nodes[0].y = 0.3;
	nodes[0].friction = 0.5;
	nodes[0].mass = 1;
	
	nodes[1].x = 0.5;
	nodes[1].y = 0.7;
	nodes[1].friction = 0.5;
	nodes[1].mass = 1;

	nodes[2].x = 0.8;
	nodes[2].y = 0.5;
	nodes[2].friction = 0.5;
	nodes[2].mass = 1;

	for(int i = 0; i < 3; i++){
		nodes[i].ax = 0;
		nodes[i].ay = 0;
		nodes[i].vx = 0;
		nodes[i].vy = 0;
		nodes[i].fx = 0;
		nodes[i].fy = 0;
		
	}



	links[0].node1 = &nodes[0];
	links[0].node2 = &nodes[1];
	links[1].node1 = &nodes[0];
	links[1].node2 = &nodes[2];
	links[2].node1 = &nodes[1];
	links[2].node2 = &nodes[2];

	links[0].preferredLength = 0.5;
	links[1].preferredLength = 0.5;
	links[2].preferredLength = 0.5;

	links[0].strength = 0.5;
	links[1].strength = 0.5;
	links[2].strength = 0.5;

	Shape s;
	s.nodes = nodes;
	s.links = links;
	s.nodeCount = 3;
	s.linkCount = 3;

	createWindow();

	setShape(&s);
	update();

	
	
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
				if (e.key.keysym.sym == SDLK_SPACE) {
					for (Node n : nodes) {
						std::cout << "X:";
						std::cout << n.x;
						std::cout << "  Y:";
						std::cout << n.y;
						std::cout << "  VX:";
						std::cout << n.vx;
						std::cout << "  VY:";
						std::cout << n.vy;
						std::cout << "\n";

					}
				}
				break;



			}
		}
		if(quit) {
			break;
		}
		
		SDL_Delay(5);
		tickShape(&s, 0.005);
		update();
		


	}

	destroyWindow();
	return 0;
}