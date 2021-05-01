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

	int countRonda = 1;
	Label^ labelRonda;

	Player^ player;
	HeartUI^ hearts;
	AssassinGroup^ assassinGroup;

	Map^ oMap;
	Pathfinding^ pathfinding;
	
	List<PathNode^>^ path;
public:
	GameController(Label^ label): labelRonda(label) {

		oMap = gcnew Map(15, 17);
		pathfinding = gcnew Pathfinding(oMap);

		player = gcnew Player(Point(20, 20), 5, 5, 1);
		assassinGroup = gcnew AssassinGroup(player, pathfinding, 6, 4);

		hearts = gcnew HeartUI(player, Point(30, 0), .65f);
		
	}
	void Start() {
		oMap->generateMatriz();
		assassinGroup->SetAllowedSpawnPoints();
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
		int row, col;
		oMap->GetLocNode(player->GetPivotPosition(), row, col);
		if (Point(row, col) == Point(13, 15)) {

			labelRonda->Text = "Ronda: " + ++countRonda;


			oMap->ClearMatriz();
			oMap->setPorcentajeLadrillo(oMap->getPorcentajeLadrillo() + 5);
			oMap->generateMatriz();

			assassinGroup->ClearAssassins();
			assassinGroup->SetAssassinsSpeed(assassinGroup->GetAssassinsSpeed() + 0.1f);
			assassinGroup->SetSpawnTimerMax(assassinGroup->GetSpawnTimerMax() - 0.2f);
			assassinGroup->ResetAllowedSpawnPoints();


			player->SetPosition(Point(20, 20));
			player->SetLifePoints(player->GetLifePoints() + 1);
		}
	}
};

