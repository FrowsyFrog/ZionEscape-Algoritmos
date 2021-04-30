#pragma once
#include "Player.h"
#include "AssassinGroup.h"
#include "Pathfinding.h"
#include "HeartUI.h";

using namespace System::Drawing;
using namespace System::Windows::Forms;

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

		player = gcnew Player(Point(20, 20), 3, 5, 1);

		assassinGroup = gcnew AssassinGroup(player, pathfinding, 4, 3);

		hearts = gcnew HeartUI(player, Point(30, 0), .65f);
		
	}
	void Start() {
		int porcentajeLadrillo = 10;
		oMap->generateMatriz(porcentajeLadrillo);
		assassinGroup->ResetAllowedSpawnPoints();
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
		
		//Mover enemigo, los3 son necesarios!
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
	void NextLevel() {
		if (player->GetPivotPosition() == oMap->GetNodePosition(13, 15)) {
			oMap->generateMatriz(oMap->setPorcentajeLadrillo(5));
			assassinGroup->ErraseAssasins();
			player->SetPosition(Point(20, 20));
		}
	}
};

