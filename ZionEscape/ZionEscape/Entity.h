#pragma once
#include "Sprite.h"
#include "Lambda.h"

ref class Entity abstract : public Sprite
{
protected:

	int lifePoints;
	float speed;
	int dx, dy;

public:
	Entity(Point pos, int life, float speed): 
		lifePoints(life), speed(speed){
		//Establecer posicion de la Entidad
		position = pos;
	}

	virtual void MoveEntity(Graphics^ g) {
		
		if(position.X + dx >= 0 && position.X + frameSize.X + dx < g->VisibleClipBounds.Width)
			position.X += dx;
		if(position.Y + dy >= 0 && position.Y + frameSize.Y + dy < g->VisibleClipBounds.Height)
			position.Y += dy;
	}
	
	virtual void AnimateEnitity() {
		if (dx != 0 || dy != 0) IDx = (IDx + 1) % spriteColumns;
		else IDx = 0;
	}

	void SetDX(int value) {
		dx = value;
	}
	void SetDY(int value) {
		dy = value;
	}
	int GetDX()
	{
		return dx;
	}
	int GetDY() {
		return dy;
	}
	virtual void SetLifePoints(int value) {
		lifePoints = value;
	}
	float GetSpeed() {
		return speed;
	}
	int GetLifePoints() {
		return lifePoints;
	}

	Point GetPivotPosition() {
		return Point(position.X + 30, position.Y + 55);
	}
};

