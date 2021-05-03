#pragma once
#include "Player.h"
#include "AssassinGroup.h"
#include "Pathfinding.h"
#include "HeartUI.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace std;

public ref class GameController
{
private:

	int countRonda = 1;
	Label^ labelRonda;

	Player^ player;
	HeartUI^ hearts;
	AssassinGroup^ assassinGroup;

	Map<int>^ oMap;
	Pathfinding<int>^ pathfinding;

public:
	GameController(Label^ label): labelRonda(label) {

		oMap = gcnew Map<int>(15, 17);
		pathfinding = gcnew Pathfinding<int>(oMap);

		//Posicion - vida - velocidad
		player = gcnew Player(Point(20, 20), 5, 5, oMap);

		// Timepo de Spawn - Velocidad de Asesinos
		assassinGroup = gcnew AssassinGroup(player, pathfinding, 4.5, 4);

		//Posicion inicial de corazones - Offset
		hearts = gcnew HeartUI(player, Point(30, 0), .65f);

		Rectangle rect = Rectangle(0, 0, 150, 100);
		
	}

	~GameController() {
		delete oMap; oMap = nullptr;
		delete pathfinding; pathfinding = nullptr;
		delete player; player = nullptr;
		delete assassinGroup; assassinGroup = nullptr;
		delete hearts; hearts = nullptr;
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
	}

	void AnimateEntities() {
		player->AnimateEnitity();
		assassinGroup->AnimateAssassins();
	}

	void KeyDown(Keys keyPressed) {
		player->PlayerMovement(true, keyPressed);
	}

	void KeyUp(Keys keyPressed) {
		player->PlayerMovement(false, keyPressed);
	}

	bool isPlayerWithLife() {
		return player->GetLifePoints() > 0;
	}

	Map<int>^ GetMap() {
		return oMap;
	}

	void NextLevel() {
		int row, col;
		oMap->GetLocNode(player->GetPivotPosition(), row, col);
		if(LambdaRunner::CompareRowsCols(row, col, 13, 15)) SetDatosLevel(false);
	}

	void SetDatosLevel(bool defaultValues) {

		if (defaultValues) {
			player->SetLifePoints(5);
			player->SetDX(0); player->SetDY(0);

			oMap->setPorcentajeLadrillo(5);
			assassinGroup->SetAssassinsSpeed(4);
			assassinGroup->SetSpawnTimerMax(4.5f);

			labelRonda->Text = "Round: " + 1;
		}
		else {
			oMap->setPorcentajeLadrillo(oMap->getPorcentajeLadrillo() + 5);
			assassinGroup->SetAssassinsSpeed(assassinGroup->GetAssassinsSpeed() + 0.1f);
			assassinGroup->SetSpawnTimerMax(assassinGroup->GetSpawnTimerMax() - 0.2f);

			labelRonda->Text = "Round: " + ++countRonda;
		}

		player->SetPosition(Point(20, 20));

		oMap->ClearMatriz();
		oMap->generateMatriz();

		assassinGroup->ClearAssassins();
		assassinGroup->ResetAllowedSpawnPoints();
	}

	int GetRondas() {
		return countRonda;
	}
};

