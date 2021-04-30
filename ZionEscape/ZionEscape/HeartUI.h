#pragma once
#include "Entity.h"

ref class HeartUI: Sprite
{
	Entity^ entity;
	Point offSet;
	float scale;

public:
	HeartUI(Entity^ e, Point offSet, float scale): entity(e), offSet(offSet), scale(scale) {
		sprite = gcnew Bitmap("Sprites\\UI\\heart.png");
		SetColumnsRows(1, 1);
		SetFrameSize();
		SetPosition(Point(15, 5));
	}

	void ShowHearts(Graphics^ g) {

		Point auxOffSet = Point(0,0);
		for (int i = 0; i < entity->GetLifePoints(); i++) {

			ShowSprite(g, auxOffSet);
			// Add the X position of where the next heart will be drawn
			auxOffSet.X += offSet.X; auxOffSet.Y += offSet.Y;
		}

		
	}

	void ShowSprite(Graphics^ g, Point auxOffSet) override {
		g->DrawImage(sprite, GetDrawingArea(auxOffSet, scale), GetCropArea(), GraphicsUnit::Pixel);
	}

};

