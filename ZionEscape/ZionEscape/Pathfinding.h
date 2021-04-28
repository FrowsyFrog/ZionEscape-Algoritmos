#pragma once
#include "Map.h"
#include <limits.h>
#include <math.h>
#define MOVE_STRAIGHT_COST 30
#define MOVER_DIAGONAL_COST 42


ref class Pathfinding
{
	Map^ grid;
	List<PathNode^>^ openList;
	List<PathNode^>^ closedList;

public:
	Pathfinding(Map^ grid) {
		this->grid = grid;
	}

private:
	List<PathNode^>^ FindPath(int startY, int startX, int endY, int endX) {
		PathNode^ startNode = grid->getNode(startY, startX);
		PathNode^ endNode = grid->getNode(endY, endX);

		openList = gcnew List<PathNode^>(); openList->Add(startNode);
		closedList = gcnew List<PathNode^>();
	
		for (int i = 0; i < grid->getRows(); i++) {
			for (int j = 0; j < grid->getCols(); i++) {
				PathNode^ pathNode = grid->getNode(i, j);
				pathNode->gCost = INT_MAX;
				pathNode->CalculateFCost();
				pathNode->cameFromNode = nullptr;
			}
		}
	
		startNode->gCost = 0;
		startNode->hCost = CalculateDistanceCost(startNode, endNode);
		startNode->CalculateFCost();

		while (openList->Count > 0) {
			PathNode^ currentNode = GetLowestFCostNode(openList);
			if (currentNode == endNode) {
				return CalculatePath(endNode);
			}

			openList->Remove(currentNode);
			closedList->Add(currentNode);

			for each (PathNode^ neighbourNode in GetNeighbourList(currentNode))
			{
				if (closedList->Contains(neighbourNode)) continue;

				int tentativeGCost = currentNode->gCost + CalculateDistanceCost(currentNode, neighbourNode);
				if (tentativeGCost < neighbourNode->gCost) {
					neighbourNode->cameFromNode = currentNode;
					neighbourNode->gCost = tentativeGCost;
					neighbourNode->hCost = CalculateDistanceCost(neighbourNode, endNode);
					neighbourNode->CalculateFCost();

					if (!openList->Contains(neighbourNode)) {
						openList->Add(neighbourNode);
					}
				}
			}
		}
		//Out of nodes on the openList
		return nullptr;
	}

	List<PathNode^>^ GetNeighbourList(PathNode^ currentNode) {
		List<PathNode^>^ neighbourList = gcnew List<PathNode^>();
		if (currentNode->y - 1 >= 0) {
			//Left
			neighbourList->Add(GetNode(currentNode->y - 1, currentNode->x));
			//Left Down
			if (currentNode->x - 1 >= 0) neighbourList->Add(GetNode(currentNode->y - 1, currentNode->x - 1));
			//Left up
			if (currentNode->x + 1 < grid->getRows()) neighbourList->Add(GetNode(currentNode->y - 1, currentNode->x - 1));
		}
		if (currentNode->y + 1 < grid->getCols()) {
			//Right
			neighbourList->Add(GetNode(currentNode->y + 1, currentNode->x));
			//Right Down
			if (currentNode->x - 1 >= 0) neighbourList->Add(GetNode(currentNode->y + 1, currentNode->x - 1));
			//Right up
			if (currentNode->x + 1 < grid->getRows()) neighbourList->Add(GetNode(currentNode->y + 1, currentNode->x + 1));
		}
		//Down
		if (currentNode->x - 1 >= 0) neighbourList->Add(GetNode(currentNode->y, currentNode->x - 1));
		//Right up
		if (currentNode->x + 1 < grid->getRows()) neighbourList->Add(GetNode(currentNode->y, currentNode->x + 1));

		return neighbourList;
	}


	List<PathNode^>^ CalculatePath(PathNode^ endNode) {
		return nullptr;
	}


	int CalculateDistanceCost(PathNode^ a, PathNode^ b) {
		int xDistance = abs(a->x - b->x);
		int yDistance = abs(a->y - b->y);
		int remaining = abs(xDistance - yDistance);

		return MOVER_DIAGONAL_COST * fmin(xDistance, yDistance) + MOVE_STRAIGHT_COST * remaining;
	}

	PathNode^ GetLowestFCostNode(List<PathNode^>^ pathNodeList) {
		PathNode^ lowestFCostNode = pathNodeList[0];
		for (int i = 1; i < pathNodeList->Count; ++i) {
			if (pathNodeList[i]->fCost < lowestFCostNode->fCost) {
				lowestFCostNode = pathNodeList[i];
			}
		}
		return lowestFCostNode;
	}

	PathNode^ GetNode(int y, int x) {
		return grid->getNode(y, x);
	}
};

