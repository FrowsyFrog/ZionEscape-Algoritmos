#pragma once
#include "Player.h"
#include "Map.h"
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class GameController
{
private:
	Player^ player;
	Map^ oMap;
public:
	GameController() {
		player = gcnew Player(Point(20, 20), 1, 5, 1);
		oMap = gcnew Map();
	}
	void Start() {
		oMap->generateMatriz();
	}
	void Resume() {

	}
	void Draw(Graphics^ g, Bitmap^ bmpbase, Bitmap^ bmpSolid, Bitmap^ bmpDestroy) {
		oMap->Paint(g, bmpbase);
		oMap->PaintMatriz(g, bmpSolid,bmpDestroy);
	}
	void ShowGame(Graphics^g) {
		player->ShowSprite(g);
	}

	void MoveEntities(Graphics^ g) {
		player->MoveEntity(g);
	}

	void AnimateEntities() {
		player->AnimateEnitity();
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
};

