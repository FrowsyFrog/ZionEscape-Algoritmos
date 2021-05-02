#pragma once
#include "Entity.h"
#include "Map.h"

ref class Player : public Entity
{
	Map<int>^ oMap;

public:
	
	Player(Point pos, int life, float speed, Map<int>^ map): Entity(pos, life, speed) {
		//Establecer sprite jugador
		sprite = gcnew Bitmap("Sprites\\Characters\\player.png");
		oMap = map;
		//Establecer filas y columnas del sprite
		SetColumnsRows(4, 4);
		SetFrameSize();
	}

	~Player() {
		oMap = nullptr;
	}
	void MoveEntity(Graphics^ g)override {

		if (CheckCollision(GetPivotPosition().X + dx, GetPivotPosition().Y + dy))
		{
			position.X += dx; position.Y += dy;
		}

	}
	bool CheckCollision(int _x, int _y)
	{
		int row; int col;
		oMap->GetLocNode(Point(_x, _y), row, col);
		if (oMap->getNode(row, col)->value > 1) return false;
		else if (oMap->getNode(row, col)->value == 1) {
			oMap->getNode(row, col)->value = 0;
		}
		return true;
	}

	void SetLifePoints(int value) override {
		if (value > 0) {
			lifePoints = value;
		}
		else {
			//PERDISTE!
			lifePoints = 0;
		}
	}
};

