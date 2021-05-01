#pragma once

#include <ctime>
#include <stdlib.h> 
#include "PathNode.h"
#define CELL_SIZE 30
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using System::Collections::Generic::List;



ref class Map {
	//TGridObject^^ matriz;
	List<List<PathNode^>^>^ matriz;

	Bitmap^ bmpBase;
	Bitmap^ bmpSolid;
	Bitmap^ bmpDestroy;

	int rows, cols;
	int porcentajeLadrillo = 5;

public:
	Map(int r, int c): rows(r), cols(c) {
		matriz = gcnew List<List<PathNode^>^>();
		bmpBase = gcnew Bitmap("Sprites\\MapBlocks\\bmpSuelo.png");
		bmpSolid = gcnew Bitmap("Sprites\\MapBlocks\\bmpSolido.png");
		bmpDestroy = gcnew Bitmap("Sprites\\MapBlocks\\bmpDestruible.png");
	}

	void generateMatriz() {
		srand(time(NULL()));
		for (int i = 0; i < rows; ++i) {
			matriz->Add(gcnew List<PathNode^>());
			for (int j = 0; j < cols; ++j) {

				matriz[i]->Add(gcnew PathNode(i, j));
				////       0         0
				if ((i == 0 || j == 0 || i == rows - 1 || j == cols - 1) || (i % 2 == 0 && j % 2 == 0)) matriz[i][j]->value = 2;//Marco al rededor del mapa //Bloques fijos en el interior
				else if ((i == 1 && (j == 1 || j == 2)) || (j == 1 && i == 2) || (i == rows - 2 && (j == cols - 3 || j == cols - 2)) || (i == rows - 3 && j == cols - 2)) matriz[i][j]->value = 0; //Bloques libres en las esquinas
				else matriz[i][j]->value = GetRandomNodeValue(porcentajeLadrillo);
			}
		}
	}

	void ClearMatriz() {
		for each (List<PathNode^>^ lista in matriz)
		{
			lista->Clear();
		}
		matriz->Clear();
	}
	
	void PaintMatriz(Graphics^ g) {
		int X, Y = 0;
		for (int i = 0; i < rows; ++i) {
			X = 0;
			for (int j = 0; j < cols; ++j) {
				if (matriz[i][j]->value == 0)
					g->DrawImage(bmpBase, X, Y, CELL_SIZE, CELL_SIZE);
				else if (matriz[i][j]->value == 1)
					g->DrawImage(bmpDestroy, X, Y, CELL_SIZE, CELL_SIZE);
				else if (matriz[i][j]->value == 2)
					g->DrawImage(bmpSolid, X, Y, CELL_SIZE, CELL_SIZE);
				X += CELL_SIZE;
			}
			Y += CELL_SIZE;
		}
	}

	List<List<PathNode^>^>^ getMatriz() {
		return matriz; 
	}

	PathNode^ getNode(int row, int col) {
		return matriz[row][col];
	}
	
	int getRows() {
		return rows;
	}

	int getCols() {
		return cols;
	}

	void GetLocNode(Point position, [Out] int% row, [Out] int% col) {
		row = (int)(position.Y / CELL_SIZE);
		col = (int)(position.X / CELL_SIZE);
	}

	int GetCellSize() {
		return CELL_SIZE;
	}

	int getPorcentajeLadrillo() { 
		return porcentajeLadrillo; 
	
	}
	void setPorcentajeLadrillo(int value) { 
		porcentajeLadrillo = value; 
	}

	Point GetNodePosition(PathNode^ pathNode) {
		return GetNodePosition(pathNode->row, pathNode->col);
	}

	Point GetNodePosition(int row, int col) {
		Point nodePosition(col * CELL_SIZE + (CELL_SIZE * .5f), row * CELL_SIZE + (CELL_SIZE * .5f));
		return nodePosition;
	}

private:
	int GetRandomNodeValue(int porcentajeLadrillo) {
		
		int value = rand() % 100;
		return value >= porcentajeLadrillo ? 0 : 1;

	}
};




