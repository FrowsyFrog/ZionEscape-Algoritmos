#pragma once
#include "Map.h"
#include <limits.h>
#include <math.h>
#define MOVE_STRAIGHT_COST 30
#define MOVER_DIAGONAL_COST 42
using namespace System;

ref class Pathfinding
{
	Map^ grid;
	List<PathNode^>^ openList;
	List<PathNode^>^ closedList;
	
public:
	Pathfinding(Map^ grid) {
		this->grid = grid;
	}

	~Pathfinding() {
		grid = nullptr;
		delete openList; openList = nullptr;
		delete closedList; closedList = nullptr;
	}

	List<Point>^ FindPath(Point startWorldPosition, Point endWorldPosition) {
		int startRow = 0, startCol = 0;
		grid->GetLocNode(startWorldPosition, startRow, startCol);
		int endRow = 0, endCol = 0;
		grid->GetLocNode(endWorldPosition, endRow, endCol);

		List<PathNode^>^ path = FindPath(startRow, startCol, endRow, endCol);
		if (path == nullptr) {
			return nullptr;
		}
		else {
			List<Point>^ pointPath = gcnew List<Point>();
			for each (PathNode^ pathnode in path)
			{
				pointPath->Add(Point(pathnode->col * grid->GetCellSize() + (grid->GetCellSize() * .5f) ,pathnode->row * grid->GetCellSize() + (grid->GetCellSize() * .5f)));
			}
			return pointPath;
		}
	}

	List<PathNode^>^ FindPath(int startRow, int startCol, int endRow, int endCol) {
		PathNode^ startNode = GetNode(startRow, startCol);
		PathNode^ endNode = GetNode(endRow, endCol);

		openList = gcnew List<PathNode^>(); openList->Add(startNode);
		closedList = gcnew List<PathNode^>();

		for (int i = 0; i < grid->getRows(); i++) {
			for (int j = 0; j < grid->getCols(); j++) {
				PathNode^ pathNode = GetNode(i, j);
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
				//Alcanza el último nodo
				return CalculatePath(endNode);
			}

			openList->Remove(currentNode);
			closedList->Add(currentNode);

			for each (PathNode ^ neighbourNode in GetNeighbourList(currentNode))
			{
				if (closedList->Contains(neighbourNode)) continue;
				else if (neighbourNode->value != 0) {
					closedList->Add(neighbourNode);
					continue;
				}

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

	Map^ GetGrid() {
		return grid;
	}

private:

	List<PathNode^>^ GetNeighbourList(PathNode^ currentNode) {
		List<PathNode^>^ neighbourList = gcnew List<PathNode^>();
		//Left
		if (currentNode->col - 1 >= 0) neighbourList->Add(GetNode(currentNode->row, currentNode->col - 1));
		//Right
		if (currentNode->col + 1 < grid->getCols()) neighbourList->Add(GetNode(currentNode->row, currentNode->col + 1));
		//Up
		if (currentNode->row - 1 >= 0) neighbourList->Add(GetNode(currentNode->row - 1, currentNode->col));
		//Down
		if (currentNode->row + 1 < grid->getRows()) neighbourList->Add(GetNode(currentNode->row + 1, currentNode->col));

		return neighbourList;
	}

	List<PathNode^>^ CalculatePath(PathNode^ endNode) {
		List<PathNode^>^ path = gcnew List<PathNode^>();
		path->Add(endNode);
		PathNode^ currentNode = endNode;
		while (currentNode->cameFromNode != nullptr) {
			path->Add(currentNode->cameFromNode);
			currentNode = currentNode->cameFromNode;
		}
		path->Reverse();
		return path;
	}

	int CalculateDistanceCost(PathNode^ a, PathNode^ b) {
		int rowDistance = Math::Abs(a->col - b->col);
		int colDistance = Math::Abs(a->row - b->row);
		int remaining = Math::Abs(rowDistance - colDistance);
		return MOVER_DIAGONAL_COST * Math::Min(rowDistance, colDistance) + MOVE_STRAIGHT_COST * remaining;
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

	PathNode^ GetNode(int row, int col) {
		return grid->getNode(row, col);
	}
};

