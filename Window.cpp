#include "Window.h"
#include "SDL.h"
#include "stdio.h"

#include "Shape.h"

#include "math.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;

SDL_Surface* screenSurface = NULL;

SDL_Renderer* renderer = NULL;

Shape* shape = NULL;


double CenterX = 0;
double CenterY = 0;
double scale = 100;




void createWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		window = SDL_CreateWindow("Cevolve", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			//Get window surface 
			screenSurface = SDL_GetWindowSurface(window);

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	
}

void destroyWindow() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void setShape(Shape* s) {
	shape = s;
}

void update() {
	CenterX = 0;
	CenterY = 0;

	for (int i = 0; i < shape->nodeCount; i++) {
		CenterX += shape->nodes[i].x;
		CenterY -= shape->nodes[i].y;

	}
	CenterX /= shape->nodeCount;
	CenterY /= shape->nodeCount;



	SDL_SetRenderDrawColor(renderer, 0x90, 0x90, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0x00, 0xB0, 0x00, 0xFF);

	SDL_Rect ground;
	ground.x = 0;
	ground.y = metricToPixelCoords(0, 0).y;
	ground.h = SCREEN_HEIGHT - ground.y;
	ground.w = SCREEN_WIDTH;

	if (ground.h > 0) {
		SDL_RenderFillRect(renderer, &ground);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0x00, 0xFF);
		SDL_RenderDrawLine(renderer, 0, ground.y, SCREEN_WIDTH, ground.y);
	}
		






	

	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	for(int i = 0; i < shape->linkCount; i++) {
		double linkLength = sqrt((shape->links[i].node1->x - shape->links[i].node2->x) * (shape->links[i].node1->x - shape->links[i].node2->x) + (shape->links[i].node1->y - shape->links[i].node2->y) * (shape->links[i].node1->y - shape->links[i].node2->y));
		int colorModifier = (shape->links[i].preferredLength - linkLength) * 200;

		if (colorModifier > 0x7F)
			colorModifier = 0x7F;
		if (colorModifier < -0x80)
			colorModifier = -0x80;

		Uint8 redness = 0x80 + colorModifier;
		
		SDL_SetRenderDrawColor(renderer, redness, 0x00, 0x00, 0xFF);



		tuple pos1 = metricToPixelCoords(shape->links[i].node1->x, shape->links[i].node1->y);
		tuple pos2 = metricToPixelCoords(shape->links[i].node2->x, shape->links[i].node2->y);
		SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
	}

	
	SDL_RenderPresent(renderer);


	//SDL_UpdateWindowSurface(window);
}

tuple metricToPixelCoords(double x, double y) {
	tuple result;
	result.x = (x - CenterX) * scale + SCREEN_WIDTH / 2;
	result.y = (-y - CenterY) * scale + SCREEN_HEIGHT / 2;
	return result;
}

tuple pixelToMetricCoords(double x, double y) {
	tuple result;
	result.x = CenterX - (SCREEN_WIDTH / 2 - x) / scale;
	result.y = CenterY - (SCREEN_HEIGHT / 2 - y) / scale;
	return result;
}

void zoom(int deltaZoom) {
	scale += scale * deltaZoom * 0.2;
	update();
}
