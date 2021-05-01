#pragma once
#include "Assassin.h"

ref class AssassinGroup
{
	List<Assassin^>^ assassins;
	Entity^ targetEntity;
	Pathfinding^ pathfinding;
	List<Point>^ allowedSpawnPoints;

	Random^ random;

	float assassinsSpeed;

	float spawnTimerMax;
	float spawnTimer;
	
public:
	AssassinGroup(Entity^ t, Pathfinding^ pf, float timer, float speed)
		: targetEntity(t), pathfinding(pf), assassinsSpeed(speed) {
		random = gcnew Random();
		assassins = gcnew List<Assassin^>();
		allowedSpawnPoints = gcnew List<Point>();
		spawnTimer = spawnTimerMax = timer;
	}

	void ActionAssasins(Graphics^ g) {

		SpawnAssassin();
		for (unsigned currentAssassin = this->assassins->Count; currentAssassin > 0; --currentAssassin) {

			assassins[currentAssassin-1]->SetTargetPosition(targetEntity->GetPivotPosition(), pathfinding);
			assassins[currentAssassin-1]->HandleMovement();
			assassins[currentAssassin-1]->MoveEntity(g);
			assassins[currentAssassin-1]->ShowSprite(g);

			if (CollisionAssassin(assassins[currentAssassin-1])) {
				//Sub lifepoint entity
				targetEntity->SetLifePoints(targetEntity->GetLifePoints() - assassins[currentAssassin - 1]->GetDamagePoints());
				//Delete ptr
				this->assassins[currentAssassin-1] = nullptr;
				delete this->assassins[currentAssassin-1];
				//Delete from the list
				assassins->Remove(assassins[currentAssassin-1]);
			}
		}
	}

	void SpawnAssassin() {

		if (spawnTimer <= 0) {
			assassins->Add(gcnew Assassin(GetSpawnPos(), 1, assassinsSpeed, 1));
			spawnTimer = spawnTimerMax;
		}
		spawnTimer -= 0.033;

	}

	void SetAllowedSpawnPoints() {
		Map^ map = pathfinding->GetGrid();
		for each (List<PathNode^> ^ lista in map->getMatriz())
		{
			for each (PathNode ^ pathNode in lista)
			{
				if (pathNode->value == 0 && !allowedSpawnPoints->Contains(map->GetNodePosition(pathNode))) {
					allowedSpawnPoints->Add(map->GetNodePosition(pathNode));
				}
			}
		}
	}

	void AnimateAssassins() {
		for each (Assassin ^ assassin in assassins)
		{
			assassin->AnimateEnitity();
		}
	}

	void ResetAllowedSpawnPoints() {
		allowedSpawnPoints->Clear();
		SetAllowedSpawnPoints();
	}

	void ClearAssassins() {
		for (unsigned currentAssassin = this->assassins->Count; currentAssassin > 0; --currentAssassin) {
			this->assassins[currentAssassin - 1] = nullptr;
			delete this->assassins[currentAssassin - 1];
			//Delete from the list
			assassins->Remove(assassins[currentAssassin - 1]);
		}
	}

	void SetAssassinsSpeed(float value) {
		assassinsSpeed = value;
	}

	void SetSpawnTimerMax(float value) {

		if (value > 0) {
			spawnTimerMax = value;
		}
	}

	float GetAssassinsSpeed() {
		return assassinsSpeed;
	}

	float GetSpawnTimerMax() {
		return spawnTimerMax;
	}

private:
	bool CollisionAssassin(Assassin^ assassin) {
		if (assassin->GetDrawingArea().IntersectsWith(targetEntity->GetDrawingArea())) return true;
		return false;
	}

	Point GetSpawnPos() {
		if (allowedSpawnPoints != nullptr) {
			int randomPoint = random->Next(0, allowedSpawnPoints->Count);
			return Point(allowedSpawnPoints[randomPoint].X -30, allowedSpawnPoints[randomPoint].Y - 48);
		}
		return Point(0, 0);
	}
};

