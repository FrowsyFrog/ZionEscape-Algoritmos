#pragma once
#include "Player.h"
#include "AssassinGroup.h"
#include "Pathfinding.h"
#include "HeartUI.h";
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

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

	Map^ oMap;
	Pathfinding^ pathfinding;
	
	List<PathNode^>^ path;

public:
	GameController(Label^ label): labelRonda(label) {

		oMap = gcnew Map(15, 17);
		pathfinding = gcnew Pathfinding(oMap);

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

	void Save() {
		fstream save("LastGame.txt", ios::out); //donde se guardara la partida
		for (int i = 0; i < 15; ++i) { //guardar la matriz
			for (int j = 0; j < 17; ++j) {
				save << oMap->getNode(i, j)->value;
				if (j != 16) save << " ";
			}
			save << "\n";
		}
		save << player->GetPosition().X << "," << player->GetPosition().Y << "\n"; //guardar posicion del jugador en x,y;
		save << player->GetLifePoints() << "\n"; // guardar cantidad de vidas
		save << assassinGroup->GetAssassinsSpeed() << "\n";
		save << assassinGroup->GetSpawnTimerMax() << "\n";
		save << assassinGroup->getAssassins()->Count<< "\n";
		for (int i = 0; i < assassinGroup->getAssassins()->Count; ++i) {
			save << assassinGroup->getAssassins()[i]->GetPosition().X << "," << assassinGroup->getAssassins()[i]->GetPosition().Y << "\n";
		}
		save << GetRondas();
	}

	void Resume() {
		fstream resume("LastGame.txt", ios::in); //partida a cargar
		Start();
		if (resume.is_open()) {
			int cant = 0;
			// Leer el archivo
			string str;
			short i = 0;
			short j = 0;
			while (getline(resume, str)) {
				string n;
				stringstream am(str);
				if (i < 15) {
					while (getline(am, n, ' ')) { //leer la matriz
						int num = atoi(n.c_str());
						oMap->getNode(i, j)->value = num;
						++j;
					}
				}
				else if (i == 15) { // leer la posicion del jugador
					while (getline(am, n, ',')) {
						int num, num2;
						if (j == 0) num = atoi(n.c_str());
						else if (j == 1) num2 = atoi(n.c_str());
						player->SetPosition(Point(num, num2));
						++j;
					}
				}
				else if (i == 16) { // leer la cantidad de vidas del jugador
					player->SetLifePoints(atoi(str.c_str()));
				}
				else if (i == 17) { //leer la velocidad de los asesinos
					assassinGroup->SetAssassinsSpeed(atoi(str.c_str()));
				}
				else if (i == 18) { //leer cada cuanto aparecen asesinos
					assassinGroup->SetSpawnTimerMax(atoi(str.c_str()));
				}
				else if (i == 19) { //leer cantidad de asesinos
						cant = atoi(str.c_str()); 
				}
				else if (i > 19 && i<=cant + 19) { //leer posiciones de cada asesino
					int num, num2;
					while (getline(am, n, ',')) {
						if (j == 0) num = atoi(n.c_str());
						else if (j == 1) num2 = atoi(n.c_str());
						++j;
					}
					assassinGroup->SpawnAssassin(Point(num, num2));
				}
				else if (i > cant + 19) { //leer partida en la que te quedaste
					setRondas(atoi(str.c_str()));
					labelRonda->Text = "Round: " + countRonda;
				}
				j = 0;
				++i;
			}
			//para ver si se lee y guarda
			resume.close();
		}
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
		case Keys::Escape:
				Save();
			break;
		}
	}

	bool isPlayerWithLife() {
		return player->GetLifePoints() > 0;
	}

	Map^ GetMap() {
		return oMap;
	}

	void NextLevel() {
		int row, col;
		oMap->GetLocNode(player->GetPivotPosition(), row, col);
		if (Point(row, col) == Point(13, 15)) {

			SetDatosLevel(false);
		}
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
	void setRondas(int newRondas) {
		countRonda = newRondas;
	}
};

