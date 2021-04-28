#pragma once

ref class PathNode
{
public:
	int x;
	int y;

	int value;
	int gCost;
	int hCost;
	int fCost;

	PathNode^ cameFromNode;

	PathNode(int y, int x) : y(y), x(x) {}

	void CalculateFCost() {
		fCost = gCost + hCost;
	}



};




