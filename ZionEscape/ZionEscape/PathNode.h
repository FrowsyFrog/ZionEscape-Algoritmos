#pragma once

template<class T>
ref class PathNode
{
public:
	int row;
	int col;

	T value;
	int gCost;
	int hCost;
	int fCost;

	PathNode^ cameFromNode;

	PathNode(int r, int c) : row(r), col(c) {}

	~PathNode() {
		delete cameFromNode;
		cameFromNode = nullptr;
	}
	//calcula costos (para saber que tanto debe recorrer entre nodos)
	void CalculateFCost() { 
		fCost = gCost + hCost;
	}
};




