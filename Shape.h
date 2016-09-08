#pragma once

struct Node;
struct Link;

struct Node {
	double x, y;
	double vx, vy;
	double ax, ay;
	double fx, fy;


	double friction;
	double mass;
	

};

struct Link {
	Node* node1;
	Node* node2;
	double strength;
	double preferredLength;
};

struct Shape {
	Node* nodes;
	int nodeCount;
	
	Link* links;
	int linkCount;
	
};