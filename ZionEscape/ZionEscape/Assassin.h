#pragma once
#include "Entity.h"
#include "Pathfinding.h"
ref class Assassin : public Entity
{
	List<Point>^  pathPointList;
	int currentPathIndex;

public:
	Assassin(Point pos, int life, float speed) : Entity(pos, life, speed) {
		//Establecer sprite jugador
		sprite = gcnew Bitmap("Sprites\\Characters\\assassin.png");
		//Establecer filas y columnas del sprite
		SetColumnsRows(4, 4);
		SetFrameSize();
	}

	void SetTargetPosition(Point targetPos, Pathfinding^ pathfinding) {
		currentPathIndex = 0;
		Point targetPosition(targetPos.X, targetPos.Y);
		
		pathPointList = pathfinding->FindPath(GetPivotPosition(), targetPosition);

		if (pathPointList != nullptr && pathPointList->Count > 1) {
			pathPointList->RemoveAt(0);
		}
	}
	
	void HandleMovement() {
		if (pathPointList != nullptr) {
			Point targetPosition = pathPointList[currentPathIndex];
			if (GetDistancePoints(targetPosition) > 1.2f) {
				Point moveDir(targetPosition.X - GetPivotPosition().X, targetPosition.Y - GetPivotPosition().Y);
				moveDir = NormalizePoint(moveDir);

				float distanceBefore = GetDistancePoints(targetPosition);
				SetAssassinAnimation(moveDir);
				dx = moveDir.X * speed; dy = moveDir.Y * speed;
			}
			else
			{
				currentPathIndex++;
				if (currentPathIndex >= pathPointList->Count) {
					pathPointList = nullptr;
					dx = 0; dy = 0;
				}
			}
		}
		else {
			//Dejar de animar
			dx = 0; dy = 0;
		}
	}

private:
	float GetDistancePoints(Point targetPosition) {
		return Math::Sqrt(Math::Pow(GetPivotPosition().X - targetPosition.X, 2) + Math::Pow(GetPivotPosition().Y - targetPosition.Y, 2));
	}

	Point NormalizePoint(Point point) {
		float distance = Math::Sqrt(point.X * point.X + point.Y * point.Y);
		int PointX = Math::Round(point.X / distance, MidpointRounding::AwayFromZero);
		int PointY = Math::Round(point.Y / distance, MidpointRounding::AwayFromZero);

		return Point(PointX, PointY);
	}

	void SetAssassinAnimation(Point direction) {
		if (direction.Y > 0) spriteDirection = SpriteDirections::down;
		else if (direction.Y < 0) spriteDirection = SpriteDirections::up;
		else if (direction.X < 0) spriteDirection = SpriteDirections::left;
		else if (direction.X > 0) spriteDirection = SpriteDirections::right;
	}

};

