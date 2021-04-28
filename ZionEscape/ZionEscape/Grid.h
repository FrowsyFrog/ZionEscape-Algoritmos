#pragma once
class Grid
{
	int width;
	int height;
	int** gridArray;
public:
	Grid(int** matriz): gridArray(matriz){
		gridArray = matriz;
		
	}

	void SetGrid(int** matriz) {
		gridArray = matriz;
	}

};

