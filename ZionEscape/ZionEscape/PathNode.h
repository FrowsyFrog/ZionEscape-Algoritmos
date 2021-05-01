#pragma once

ref class PathNode
{
public:
	int row;
	int col;

	int value;
	int gCost;
	int hCost;
	int fCost;

	PathNode^ cameFromNode;

	PathNode(int r, int c) : row(r), col(c) {}

	~PathNode() {
		delete cameFromNode;
		cameFromNode = nullptr;
	}

	void CalculateFCost() {
		fCost = gCost + hCost;
	}



};




