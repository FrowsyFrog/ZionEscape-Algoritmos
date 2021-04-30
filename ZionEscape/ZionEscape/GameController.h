#pragma once
#include "Player.h"
#include "Assassin.h"
#include "Pathfinding.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class GameController
{
private:
	Player^ player;
	Assassin^ assassin;

	Map^ oMap;
	Pathfinding^ pathfinding;
	
	List<PathNode^>^ path;
public:
	GameController() {

		oMap = gcnew Map(15, 17);
		pathfinding = gcnew Pathfinding(oMap);

		player = gcnew Player(Point(20, 20), 1, 5, 1);
		assassin = gcnew Assassin(Point(435, 340), 1, 3, 1, pathfinding, player);
	}
	void Generate() {
		oMap->generateMatriz();
	}

	void ShowGame(Graphics^g) {
		oMap->PaintMatriz(g);
		player->ShowSprite(g);
		assassin->ShowSprite(g);
	}

	void MoveEntities(Graphics^ g) {
		player->MoveEntity(g);

		assassin->SetTargetPosition();
		assassin->HandleMovement();
		assassin->MoveEntity(g);
	}

	void AnimateEntities() {
		player->AnimateEnitity();
		assassin->AnimateEnitity();
	}

	void PlayerMovement(bool isPressed, Keys keyPressed) {

		switch (keyPressed)
		{
		case Keys::Up:
			player->SetDY(-player->GetSpeed() * isPressed);
			if(isPressed)player->SetSpriteDirection(SpriteDirections::up);
			break;
		case Keys::Down:
			player->SetDY(player->GetSpeed() * isPressed);
			if (isPressed)player->SetSpriteDirection(SpriteDirections::down);
			break;
		case Keys::Left:
			player->SetDX(-player->GetSpeed() * isPressed);
			if (isPressed)player->SetSpriteDirection(SpriteDirections::left);
			break;
		case Keys::Right:
			player->SetDX(player->GetSpeed() * isPressed);
			if (isPressed)player->SetSpriteDirection(SpriteDirections::right);
			break;
		}
	}

	Map^ GetMap() {
		return oMap;
	}
};

