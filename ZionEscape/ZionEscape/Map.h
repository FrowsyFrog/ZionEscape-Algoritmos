#pragma once

#include <ctime>
#include <stdlib.h> 
#include "PathNode.h"
using namespace System::Drawing;
using System::Collections::Generic::List;


ref class Map {
	//TGridObject^^ matriz;
	List<List<PathNode^>^>^ matriz;
	int rows, cols;

public:
	Map(int r, int c): rows(r), cols(c) {
		matriz = gcnew List<List<PathNode^>^>();
	}
	~Map() {}
	void generateMatriz() {
		srand(time(NULL()));
		for (int i = 0; i < rows; ++i) {
			matriz->Add(gcnew List<PathNode^>());
			for (int j = 0; j < cols; ++j) {

				matriz[i]->Add(gcnew PathNode(i, j));
				//
				////       0         0
				if ((i == 0 || j == 0 || i == rows - 1 || j == cols - 1) || (i % 2 == 0 && j % 2 == 0)) matriz[i][j]->value = 1;//Marco al rededor del mapa //Bloques fijos en el interior
				else if((i == 1 && (j == 1 || j == 2)) || (j == 1 && i == 2) || (i == rows - 2 && (j == cols - 3 || j == cols - 2)) || (i == rows - 3 && j == cols - 2)) matriz[i][j]->value = 0; //Bloques libres en las esquinas
				else matriz[i][j]->value = rand() % 2 + 2;			
			}
		}


	}

	void PaintMatriz(Graphics^ g, Bitmap^ bmpBase, Bitmap^ bmpSolid, Bitmap^ bmpDestroy) {
		int X, Y = 0;
		for (int i = 0; i < rows; ++i) {
			X = 0;
			for (int j = 0; j < cols; ++j) {
				if (matriz[i][j]->value == 0 || matriz[i][j]->value >= 2)
					g->DrawImage(bmpBase, X, Y, 30, 30);
		
				if (matriz[i][j]->value == 1)
					g->DrawImage(bmpSolid, X, Y, 30, 30);
				else if (matriz[i][j]->value == 3)
					g->DrawImage(bmpDestroy, X, Y, 30, 30);
				X += 30;
			}
			Y += 30;
		}
	}
	List<List<PathNode^>^>^ getMatriz() {
		return matriz; 
	}

	PathNode^ getNode(int y, int x) {
		return matriz[y][x];
	}

	int getRows() {
		return rows;
	}

	int getCols() {
		return cols;
	}
};




