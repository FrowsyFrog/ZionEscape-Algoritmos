#pragma once
#include "Player.h"
#include "AssassinGroup.h"
#include "Pathfinding.h"
#include "HeartUI.h";
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
		save << oMap->getPorcentajeLadrillo() << "\n";
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
			int cantAssassins, numFila;
			string stringFila, stringElemento;
			// Leer el archivo
			while (getline(resume, stringFila)) {
				stringstream am(stringFila);
				if (numFila < 15) {
					short numEspacio = 0;
					while (getline(am, stringElemento, ' ')) { //lee las columnas en la fila actual (17t)
						int num = atoi(stringElemento.c_str());
						oMap->getNode(numFila, numEspacio)->value = num;
						++numEspacio;
					}
					assassinGroup->ResetAllowedSpawnPoints();
				}
				else if (numFila == 15) oMap->setPorcentajeLadrillo(atoi(stringFila.c_str()));
				else if (numFila == 16) player->SetPosition(GetSavedCord(stringFila));
				else if (numFila == 17) player->SetLifePoints(atoi(stringFila.c_str())); // leer la cantidad de vidas del jugador
				else if (numFila == 18) assassinGroup->SetAssassinsSpeed(atoi(stringFila.c_str())); //leer la velocidad de los asesinos
				else if (numFila == 19) assassinGroup->SetSpawnTimerMax(atoi(stringFila.c_str())); //leer cada cuanto aparecen asesinos
				else if (numFila == 20) cantAssassins = atoi(stringFila.c_str()); //leer cantidad de asesinos
				else if (numFila > 20 && numFila<=cantAssassins + 20) { //leer posiciones de cada asesino
					getline(am, stringElemento, '\n');
					assassinGroup->SpawnAssassin(GetSavedCord(stringElemento));
				}
				else { //leer partida en la que te quedaste
					setRondas(atoi(stringFila.c_str()));
					labelRonda->Text = "Round: " + countRonda;
				}
				++numFila;
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

	void KeyDown(Keys keyPressed) {
		if (keyPressed == Keys::Escape) Save();
		else player->PlayerMovement(true, keyPressed);
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

	void setRondas(int newRondas) {
		countRonda = newRondas;
	}

private:
	Point GetSavedCord(string n) {
		string pos; stringstream strPosAss(n);
		getline(strPosAss, pos, ','); int num = atoi(pos.c_str());
		getline(strPosAss, pos, ','); int num2 = atoi(pos.c_str());

		return Point(num, num2);
	}
};

