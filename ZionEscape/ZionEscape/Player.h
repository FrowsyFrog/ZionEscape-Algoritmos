#pragma once
#include "Entity.h"
#include "Map.h"


ref class Player : public Entity
{
public:
	Map^ oMap;
	Player(Point pos, int life, float speed, int damage): Entity(pos, life, speed, damage) {
		//Establecer sprite jugador
		sprite = gcnew Bitmap("Sprites\\Characters\\player.png");
		//Establecer filas y columnas del sprite
		SetColumnsRows(4, 4);
		SetFrameSize();
	}
	void MoveEntity(Graphics^ g)override {

		if (CheckCollision(GetPivotPosition().X + dx, GetPivotPosition().Y + dy))
		{
			position.X += dx;
			position.Y += dy;
		}

	}
	bool CheckCollision(int _x, int _y)
	{
		int row;
		int col;
		Point _point = Point(_x, _y);
		//player->GetPosition().x
		oMap->GetLocNode(_point, row, col);

		int value = oMap->getNode(row, col)->value;
		//cout << "Tile code : " << value << " , " << row << " , " << col << endl;

		if (value == 1)
			return false;
		else if (value == 2)
			return false;
		else
			return true;

	}
};

