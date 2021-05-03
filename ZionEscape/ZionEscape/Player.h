#pragma once
#include "Entity.h"
#include "Map.h"
#include <queue>
using namespace System::Windows::Forms;
using System::Collections::Generic::Stack;

ref class Player : public Entity
{
	Map<int>^ oMap;
	Stack<Keys>^ pilaKeys;

public:
	
	Player(Point pos, int life, float speed, Map<int>^ map): Entity(pos, life, speed) {
		pilaKeys = gcnew Stack<Keys>();
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

	void PlayerMovement(bool isPressed, Keys keyPressed) {

		switch (keyPressed)
		{
		case Keys::Up:
			SetDY(-speed * isPressed);
			if (isPressed)SetSpriteDirection(SpriteDirections::up);
			break;
		case Keys::Down:
			SetDY(speed * isPressed);
			if (isPressed)SetSpriteDirection(SpriteDirections::down);
			break;
		case Keys::Left:
			SetDX(-speed * isPressed);
			if (isPressed)SetSpriteDirection(SpriteDirections::left);
			break;
		case Keys::Right:
			SetDX(speed * isPressed);
			if (isPressed)SetSpriteDirection(SpriteDirections::right);
			break;
		}
	}

	void MoveEntity(Graphics^ g)override {

		if (CheckCollision(GetPivotPosition().X + dx, GetPivotPosition().Y + dy))
		{
			position.X += dx; position.Y += dy;
		}

	}
	bool CheckCollision(int _x, int _y)
	{
		int row; int col; oMap->GetLocNode(Point(_x, _y), row, col);
		int %nodeValue = oMap->getNode(row, col)->value;

		if (nodeValue > 1) return false;
		else if (nodeValue == 1) nodeValue = 0;
		return true;
	}

	void SetLifePoints(int value) override {
		lifePoints = value > 0 ? value : 0;
	}
};

