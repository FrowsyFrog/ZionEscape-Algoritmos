#pragma once

#include "PathNode.h"
#include "Lambda.h"
#define CELL_SIZE 30
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using System::Collections::Generic::List;


template <class T>
ref class Map {
	//TGridObject^^ matriz;
	List<List<PathNode<T>^>^>^ matriz;

	Bitmap^ bmpBase;
	Bitmap^ bmpSolid;
	Bitmap^ bmpDestroy;
	Bitmap^ crossSprite;

	int rows, cols;
	int porcentajeLadrillo = 5;

public:
	Map(int r, int c): rows(r), cols(c) {
		matriz = gcnew List<List<PathNode<T>^>^>();
		bmpBase = gcnew Bitmap("Sprites\\MapBlocks\\bmpSuelo.png");
		bmpSolid = gcnew Bitmap("Sprites\\MapBlocks\\bmpSolido.png");
		bmpDestroy = gcnew Bitmap("Sprites\\MapBlocks\\bmpDestruible.png");
		crossSprite = gcnew Bitmap("Sprites\\MapBlocks\\cross.png");
	}

	~Map() {
		for each (List<PathNode<T>^>^ lista in matriz)
		{
			lista->Clear();
			delete lista;
			lista = nullptr;
		}
		matriz->Clear();
		delete matriz; matriz = nullptr;

		delete bmpBase; bmpBase = nullptr;
		delete bmpSolid; bmpSolid = nullptr;
		delete bmpDestroy; bmpDestroy = nullptr;
	}

	void generateMatriz() {
		srand(time(NULL()));
		for (int i = 0; i < rows; ++i) {
			matriz->Add(gcnew List<PathNode<T>^>());
			for (int j = 0; j < cols; ++j) {
				matriz[i]->Add(gcnew PathNode<T>(i, j));
				matriz[i][j]->value = LambdaRunner::MatrixGetNodeValue(i,j,rows,cols,porcentajeLadrillo);
			}
		}
	}

	void ClearMatriz() {
		for each (List<PathNode<T>^>^ lista in matriz)
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

		g->DrawImage(crossSprite, 450, 390, CELL_SIZE, CELL_SIZE);
	}

	List<List<PathNode<T>^>^>^ getMatriz() {
		return matriz; 
	}

	PathNode<T>^ getNode(int row, int col) {
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

	Point GetNodePosition(PathNode<T>^ pathNode) {
		return GetNodePosition(pathNode->row, pathNode->col);
	}

	Point GetNodePosition(int row, int col) {
		Point nodePosition(col * CELL_SIZE + (CELL_SIZE * .5f), row * CELL_SIZE + (CELL_SIZE * .5f));
		return nodePosition;
	}

private:

};




