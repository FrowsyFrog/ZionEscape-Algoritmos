#pragma once
#include "Player.h"
#include "AssassinGroup.h"
#include "Pathfinding.h"
#include "HeartUI.h";
#include <iostream>


using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace std;

public ref class GameController
{
private:
	Player^ player;
	HeartUI^ hearts;
	AssassinGroup^ assassinGroup;

	Map^ oMap;
	Pathfinding^ pathfinding;
	
	List<PathNode^>^ path;

public:
	GameController() {

		oMap = gcnew Map(15, 17);
		pathfinding = gcnew Pathfinding(oMap);

		player = gcnew Player(Point(20, 20), 3, 5, 1, oMap);

		assassinGroup = gcnew AssassinGroup(player, pathfinding);
		assassinGroup->SpawnAssassin(Point(435, 340));

		hearts = gcnew HeartUI(player, Point(30, 0), .65f);

		Rectangle rect = Rectangle(0, 0, 150, 100);
		
		
	}
	void Start() {
		int porcentajeLadrillo = 10;
		oMap->generateMatriz(porcentajeLadrillo);
	}

	void Resume() {

	}

	void ShowGame(Graphics^g) {
		oMap->PaintMatriz(g);
		player->ShowSprite(g);
		assassinGroup->ActionAssasins(g);

		hearts->ShowHearts(g);
	}

	void MoveEntities(Graphics^ g) {
		player->MoveEntity(g);
	}

	void AnimateEntities() {
		player->AnimateEnitity();
		assassinGroup->AnimateAssassins();
	}

	void PlayerMovement(bool isPressed, Keys keyPressed) {

		switch (keyPressed)
		{
		case Keys::Up:
				player->SetDY(-player->GetSpeed() * isPressed);
				if (isPressed)player->SetSpriteDirection(SpriteDirections::up);
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
	void NextLevel() {
		if (player->GetPivotPosition() == oMap->GetNodePosition(13, 15)) {
			oMap->generateMatriz(oMap->setPorcentajeLadrillo(5));
			assassinGroup->ErraseAssasins();
			player->SetPosition(Point(20, 20));
		}
	}
};

