#pragma once
#include "Sprite.h"

ref class Entity abstract : public Sprite
{
protected:
	int lifePoints;
	float speed;
	int damagePoints;

	int dx, dy;

public:
	Entity(Point pos, int life, float speed, int damage): 
		lifePoints(life), speed(speed), damagePoints(damage){
		//Establecer posicion de la Entidad
		position = pos;
	}

	virtual void MoveEntity(Graphics^ g) {
		
		if(position.X + dx >= 0 && position.X + frameSize.X + dx < g->VisibleClipBounds.Width)
			position.X += dx;
		if(position.Y + dx >= 0 && position.Y + frameSize.Y + dy < g->VisibleClipBounds.Height)
			position.Y += dy;
	}

	virtual void AnimateEnitity() {
		if (dx != 0 || dy != 0)
			IDx = (IDx + 1) % spriteColumns;
		else
			IDx = 0;
	}

	void SetDX(int value) {
		dx = value;
	}
	void SetDY(int value) {
		dy = value;
	}
	float GetSpeed() {
		return speed;
	}


};
