#pragma once
#include <ctime>
#include <stdlib.h>
using namespace System::Drawing;
#define Rows 15
#define Cols 17

ref class Map {
	int** matriz;
public:
	Map() {
		matriz = new int* [Rows];
	}
	~Map(){}
	void generateMatriz() {
		srand(time(NULL()));
		for (int i = 0; i < Rows; ++i) {
			matriz[i] = new int[Cols];
		}
		for (int i = 0; i < Rows; ++i) {
			for (int j = 0; j < Cols; ++j) {
				//       0         0
				if (i == 0 || j == 0 || i == Rows - 1 || j == Cols - 1)//Marco al rededor del mapa
					matriz[i][j] = 1;
				else {
					if (i % 2 == 0 && j % 2 == 0) matriz[i][j] = 1; //Bloques fijos en el interior
					else {  //    1          1
						if ((i == 1 && (j == 1 || j == 2)) || (j==1 && i==2) || (i==Rows-2 && (j==Cols-3 || j==Cols-2)) || (i==Rows-3 && j==Cols-2)) //Zona en la que te puedes mover
							matriz[i][j] = 0;
						else { //Zonas que quedan //2 es libre
							matriz[i][j] = rand() % 6;
						}
					}
				}
			}
		}
	}
	void Paint(Graphics^ g, Bitmap^ bmpBase) {
		int X, Y = 0;
		for (int i = 0; i < Rows; ++i) {
			X = 0;
			for (int j = 0; j < Cols; ++j) {
				if (matriz[i][j] == 0 || matriz[i][j] == 2)
					g->DrawImage(bmpBase, X, Y, 30, 30);
				X += 30;
			}
			Y += 30;
		}
	}
	void PaintMatriz(Graphics^ g, Bitmap^ bmpSolid, Bitmap^ bmpDestroy) {
		int X, Y = 0;
		for (int i = 0; i < Rows; ++i) {
			X = 0;
			for (int j = 0; j < Cols; ++j) {
				if (matriz[i][j] == 1)
					g->DrawImage(bmpSolid, X, Y, 30, 30);
				else {
					if (matriz[i][j] == 3 || matriz[i][j] == 4 || matriz[i][j] == 5)
						g->DrawImage(bmpDestroy, X, Y, 30, 30);
				}
				X += 30;
			}
			Y += 30;
		}
	}
	int** getMatriz() { return matriz; }
};

