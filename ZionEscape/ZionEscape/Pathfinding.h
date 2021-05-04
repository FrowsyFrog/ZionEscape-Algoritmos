#pragma once
#include "Map.h"
#include <limits.h>
#include <math.h>
#define MOVE_STRAIGHT_COST 30
#define MOVER_DIAGONAL_COST 42
using namespace System;

template <class T>
ref class Pathfinding
{
	Map<T>^ grid;
	List<PathNode<T>^>^ openList;
	List<PathNode<T>^>^ closedList;
	
public:
	Pathfinding(Map<T>^ grid) {
		this->grid = grid;
	}

	~Pathfinding() {
		grid = nullptr;
		delete openList; openList = nullptr;
		delete closedList; closedList = nullptr;
	}
	// esto devuelve puntos a los que debe ir el asesino habiendo encotrado aqui mismo el las posiciones de ambos
	//                         posicion inicial del asesino, posicion del jugador
	List<Point>^ FindPath(Point startWorldPosition, Point endWorldPosition) {
		//esto es para el asesino
		int startRow = 0, startCol = 0; //fila inicial y columna inicial
		//  busca fila y columna en la que esta el asesino
		// porque el grid tiene una dimension diferente por eso no le sirve lo del startWorldPosition 
		grid->GetLocNode(startWorldPosition, startRow, startCol);
		// lo mismo que arriba pero este es para el jugador
		int endRow = 0, endCol = 0;
		grid->GetLocNode(endWorldPosition, endRow, endCol);

		List<PathNode<T>^>^ path = FindPath(startRow, startCol, endRow, endCol);
		if (path == nullptr) return nullptr;
		else {
			List<Point>^ pointPath = gcnew List<Point>();
			for each (PathNode<T>^ pathnode in path)
			{
				pointPath->Add(Point(pathnode->col * grid->GetCellSize() + (grid->GetCellSize() * .5f) ,pathnode->row * grid->GetCellSize() + (grid->GetCellSize() * .5f)));
			}
			return pointPath;
		}
	}
	//este te da una lista de nodos que debe seguir (camino)
	List<PathNode<T>^>^ FindPath(int startRow, int startCol, int endRow, int endCol) {
		PathNode<T>^ startNode = GetNode(startRow, startCol);
		PathNode<T>^ endNode = GetNode(endRow, endCol);
		//evalua los nodos
		//aca manda los que va revisando
		openList = gcnew List<PathNode<T>^>(); openList->Add(startNode);
		//si no sirve porque genera un camino muy largo entra aca porque descarta el nodo
		closedList = gcnew List<PathNode<T>^>();

		for (int i = 0; i < grid->getRows(); i++) {
			for (int j = 0; j < grid->getCols(); j++) {
				PathNode<T>^ pathNode = GetNode(i, j);
				//TODO ESTO RECIEN SE ESTA INSTANCIANDO LAS PRI
				//aca primero se establece como que el costo es infinito
				//luego conforme se va comparando va disminuyendo acorde al costo correcto
				pathNode->gCost = INT_MAX;

				pathNode->CalculateFCost();
				//para saber de que nodo vino 
				pathNode->cameFromNode = nullptr;
			}
		}
		//inicialmente el primer costo es 0 ps porque esta ahi 
		startNode->gCost = 0;
		//Calcula la distancia entre asesino y jugador
		startNode->hCost = CalculateDistanceCost(startNode, endNode);
		//para luego calcular el costo
		startNode->CalculateFCost();

		while (openList->Count > 0) {
			//       nodo inicial va a obtener el nodo con menor costo y lo manda al open list
			PathNode<T>^ currentNode = GetLowestFCostNode(openList);
			//  menor nodo = nodo final(nodo del jugador)
			if (currentNode == endNode) {
				//Alcanza el �ltimo nodo
				return CalculatePath(endNode);
			}

			openList->Remove(currentNode);
			closedList->Add(currentNode);
			//                    calcula sus nodos vecinos
			for each (PathNode<T> ^ neighbourNode in GetNeighbourList(currentNode))
			{
				//si en los nodos revisados esta uno vecino continuo (no lo va a revisar 2 veces ps) 
				if (closedList->Contains(neighbourNode)) continue;
				// si no es pasto se agrega a la lista donde estan los que no usaremos
				else if (neighbourNode->value != 0) {
					closedList->Add(neighbourNode);
					continue;
				}
				// calcula los costos de los posbles lugares a los que puede ir
				int tentativeGCost = currentNode->gCost + CalculateDistanceCost(currentNode, neighbourNode);
				// si los que puede ir es menor al costo del vecinosse puede agregar a la lista a la que va a ir
				if (tentativeGCost < neighbourNode->gCost) {
					neighbourNode->cameFromNode = currentNode;
					neighbourNode->gCost = tentativeGCost;
					neighbourNode->hCost = CalculateDistanceCost(neighbourNode, endNode);
					neighbourNode->CalculateFCost();
					//se calculo el nuevo nodo eso esta para no repetir nodos osea (que en la lista no este el mismo nodo 2 veces)
					if (!openList->Contains(neighbourNode)) openList->Add(neighbourNode);
				}
			}
		}
		//Out of nodes on the openList
		return nullptr;
	}

	Map<T>^ GetGrid() {
		return grid;
	}

private:
	//esto manda la lista de nodos vecinos osea nodos al alrededor de donde esta y puede caminar por ahi
	List<PathNode<T>^>^ GetNeighbourList(PathNode<T>^ currentNode) {
		List<PathNode<T>^>^ neighbourList = gcnew List<PathNode<T>^>();
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
	//recibe el nodo final
	List<PathNode<T>^>^ CalculatePath(PathNode<T>^ endNode) {
		//crea una lista de nodos y añade a esta lista el nodo final
		List<PathNode<T>^>^ path = gcnew List<PathNode<T>^>();
		path->Add(endNode);
		//luego instancia el endnode en un nuevo nodo
		PathNode<T>^ currentNode = endNode;
		//va calculando el camino cuando avanza guarda el anterior en la lista 
		while (currentNode->cameFromNode != nullptr) {
			path->Add(currentNode->cameFromNode);
			currentNode = currentNode->cameFromNode;
		}
		path->Reverse();
		//regresa el camino hecho en el while
		return path;
	}
	//para calcular la distancia entre 2 puntos y la devuelve
	int CalculateDistanceCost(PathNode<T>^ a, PathNode<T>^ b) {
		int rowDistance = Math::Abs(a->col - b->col);
		int colDistance = Math::Abs(a->row - b->row);
		int remaining = Math::Abs(rowDistance - colDistance);
		return MOVER_DIAGONAL_COST * Math::Min(rowDistance, colDistance) + MOVE_STRAIGHT_COST * remaining;
	}

	PathNode<T>^ GetLowestFCostNode(List<PathNode<T>^>^ pathNodeList) {
		//primero lo iguala a 0 y va comparando hasta que devuelve el menor costo
		PathNode<T>^ lowestFCostNode = pathNodeList[0];
		for (int i = 1; i < pathNodeList->Count; ++i) {
			if (pathNodeList[i]->fCost < lowestFCostNode->fCost) {
				lowestFCostNode = pathNodeList[i];
			}
		}
		return lowestFCostNode;
	}

	PathNode<T>^ GetNode(int row, int col) {
		return grid->getNode(row, col);
	}
};

