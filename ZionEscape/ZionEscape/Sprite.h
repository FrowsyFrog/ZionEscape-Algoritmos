#pragma once
using namespace System::Drawing;

enum SpriteDirections {
	down,
	left,
	right,
	up
};

ref class Sprite abstract
{
	Rectangle drawingArea;

protected:
	Bitmap^ sprite;
	int spriteColumns;
	int spriteRows;

	Point position;

	Point frameSize;
	int IDx; //Index Animacion - Columnas
	SpriteDirections spriteDirection;

public:
	Sprite(): IDx(0), spriteDirection(SpriteDirections::down){}

	Rectangle GetDrawingArea() {
		return Rectangle(position.X, position.Y, frameSize.X, frameSize.Y);
	}

	virtual void ShowSprite(Graphics^ g) {
		g->DrawImage(sprite, GetDrawingArea(), GetCropArea(), GraphicsUnit::Pixel);
	}

	void SetSpriteDirection(SpriteDirections direction) {
		spriteDirection = direction;
	}

	void SetFrameSize() {
		frameSize = Point(sprite->Width / spriteColumns, sprite->Height / spriteRows);
	}

	void SetColumnsRows(int columns, int rows) {
		spriteColumns = columns;
		spriteRows = rows;
	}

	Rectangle GetCropArea() {
		return Rectangle(IDx * frameSize.X, spriteDirection * frameSize.Y, frameSize.X, frameSize.Y);
	}
};
