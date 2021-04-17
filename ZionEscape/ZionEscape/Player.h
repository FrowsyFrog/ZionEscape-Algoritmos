#pragma once
#include "Entity.h"

ref class Player : public Entity
{
public:
	Player(Point pos, int life, float speed, int damage): Entity(pos, life, speed, damage) {
		//Establecer sprite jugador
		sprite = gcnew Bitmap("Sprites\\Characters\\player.png");
		//Establecer filas y columnas del sprite
		SetColumnsRows(4, 4);
		SetFrameSize();
	}



};

